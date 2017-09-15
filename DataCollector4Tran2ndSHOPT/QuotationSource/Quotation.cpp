#include <math.h>
#include <iostream>
#include <algorithm>
#include "MVPlat.h"
#include "Quotation.h"
#include "../Infrastructure/IniFile.h"
#include "../DataCollector4Tran2ndSHOPT.h"


WorkStatus::WorkStatus()
: m_eWorkStatus( ET_SS_UNACTIVE )
{
}

WorkStatus::WorkStatus( const WorkStatus& refStatus )
{
	CriticalLock	section( m_oLock );

	m_eWorkStatus = refStatus.m_eWorkStatus;
}

WorkStatus::operator enum E_SS_Status()
{
	CriticalLock	section( m_oLock );

	return m_eWorkStatus;
}

std::string& WorkStatus::CastStatusStr( enum E_SS_Status eStatus )
{
	static std::string	sUnactive = "未激活";
	static std::string	sDisconnected = "断开状态";
	static std::string	sConnected = "连通状态";
	static std::string	sLogin = "登录成功";
	static std::string	sInitialized = "初始化中";
	static std::string	sWorking = "推送行情中";
	static std::string	sUnknow = "不可识别状态";

	switch( eStatus )
	{
	case ET_SS_UNACTIVE:
		return sUnactive;
	case ET_SS_DISCONNECTED:
		return sDisconnected;
	case ET_SS_CONNECTED:
		return sConnected;
	case ET_SS_LOGIN:
		return sLogin;
	case ET_SS_INITIALIZING:
		return sInitialized;
	case ET_SS_WORKING:
		return sWorking;
	default:
		return sUnknow;
	}
}

WorkStatus&	WorkStatus::operator= ( enum E_SS_Status eWorkStatus )
{
	CriticalLock	section( m_oLock );

	if( m_eWorkStatus != eWorkStatus )
	{
		QuoCollector::GetCollector()->OnLog( TLV_INFO, "WorkStatus::operator=() : Exchange Session Status [%s]->[%s]"
											, CastStatusStr(m_eWorkStatus).c_str(), CastStatusStr(eWorkStatus).c_str() );
				
		m_eWorkStatus = eWorkStatus;
	}

	return *this;
}


///< ----------------------------------------------------------------


T_MAP_RATE		Quotation::m_mapRate;
T_MAP_KIND		Quotation::m_mapKind;


Quotation::Quotation()
 : m_pDataBuff( NULL )
{
	m_pDataBuff = new char[MAX_IMAGE_BUFF];
}

Quotation::~Quotation()
{
	Release();

	if( NULL != m_pDataBuff )
	{
		delete [] m_pDataBuff;
		m_pDataBuff = NULL;
	}
}

WorkStatus& Quotation::GetWorkStatus()
{
	return m_oWorkStatus;
}

int Quotation::Initialize()
{
	if( NULL == m_pDataBuff )
	{
		QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::Initialize() : invalid data buffer ptr(NULL)." );
		return -1;
	}

	if( GetWorkStatus() == ET_SS_UNACTIVE )
	{
		unsigned int				nSec = 0;
		int							nErrCode = 0;
		tagCcComm_MarketInfoHead	tagHead = { 0 };
		tagCcComm_MarketInfoDetail	tagDetail[32] = { 0 };
		QuoCollector::GetCollector()->OnLog( TLV_INFO, "Quotation::Initialize() : ............ Quotation Is Activating............" );

		Release();
		if( m_oSHOPTDll.Instance( "tran2ndshopt.dll" ) < 0 )
		{
			QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::Initialize() : failed 2 initialize tran2ndsz.dll" );
			Release();
			return -2;
		}

		for( nSec = 0; nSec < 60*2; nSec++ )
		{
			SimpleTask::Sleep(1000);

			if( true == m_oSHOPTDll.IsWorking() )
			{
				if( (nErrCode = m_oSHOPTDll.GetMarketInfo( &tagHead, tagDetail, sizeof tagDetail/sizeof tagDetail[0] )) < 0 )
				{
					continue;
				}

				if( tagHead.MarketStatus <= 0 )
				{	
					continue;
				}

				break;
			}
		}

		if( nSec >= 60*2 )
		{
			QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::Initialize() : overtime > (2mins)" );
			Release();
			return -3;
		}

		if( (nErrCode = BuildImageData()) < 0 )
		{
			QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::Initialize() : failed 2 build image data 2 database" );
			return -4;
		}

		m_oWorkStatus = ET_SS_WORKING;				///< 更新Quotation会话的状态

		QuoCollector::GetCollector()->OnLog( TLV_INFO, "Quotation::Initialize() : ............ Quotation Activated!.............." );
	}

	return 0;
}

int Quotation::Release()
{
	if( m_oWorkStatus != ET_SS_UNACTIVE )
	{
		QuoCollector::GetCollector()->OnLog( TLV_INFO, "Quotation::Release() : ............ Destroying .............." );

		m_oWorkStatus = ET_SS_UNACTIVE;	///< 更新Quotation会话的状态

		QuoCollector::GetCollector()->OnLog( TLV_INFO, "Quotation::Release() : ............ Destroyed! .............." );
	}

	return 0;
}

int Quotation::BuildImageData()
{
	int								nErrCode = 0;
	tagCcComm_MarketInfoHead		tagHead = { 0 };
	tagCcComm_MarketInfoDetail		tagDetail[32] = { 0 };
	tagSHOptMarketInfo_LF157		tagMkInfo = { 0 };
	tagSHOptMarketStatus_HF159		tagMkStatus = { 0 };

	if( (nErrCode = m_oSHOPTDll.GetMarketInfo( &tagHead, tagDetail, sizeof tagDetail/sizeof tagDetail[0] )) < 0 )
	{
		QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::BuildImageData() : cannot fetch marketinfo, errorcode=%d", nErrCode );
		return -1;
	}

	if( tagHead.MarketStatus <= 0 )
	{
		QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::BuildImageData() : marketstatus =%d ", tagHead.MarketStatus );
		return -2;
	}

	m_mapRate.clear();
	m_mapKind.clear();
	tagMkStatus.StatusFlag[0] = tagHead.MarketStatus==0?'0':'1';
	tagMkStatus.MarketTime = tagHead.Time;
	QuoCollector::GetCollector()->OnImage( 159, (char*)&tagMkStatus, sizeof(tagSHOptMarketStatus_HF159), false );

	tagMkInfo.MarketDate = tagHead.Date;
	tagMkInfo.MarketID = Configuration::GetConfig().GetMarketID();
	tagMkInfo.WareCount = tagHead.WareCount;

	tagCcComm_ShOptNameTable*	pTable = (tagCcComm_ShOptNameTable*)m_pDataBuff;
	if( (nErrCode = m_oSHOPTDll.GetNameTable( 0, pTable, tagHead.WareCount )) < 0 )
	{
		QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::BuildImageData() : cannot fetch nametable from dll, errorcode = %d ", nErrCode );
		return -3;
	}

	for( int i = 0; i < tagHead.WareCount; ++i )
	{
		std::string							sCodeKey( pTable[i].UnderlyingSecurityID, 6 );

		if( m_mapKind.find( sCodeKey ) == m_mapKind.end() )
		{
			tagSHOptKindDetail_LF158&	refKind = m_mapKind[sCodeKey];

			::memset( &refKind, 0, sizeof(refKind) );
			::sprintf( refKind.Key, "%u", m_mapKind.size()-1 );
			::strncpy( refKind.KindName, pTable[i].UnderlyingSecurityID, 6 );
			::strncpy( refKind.UnderlyingCode, pTable[i].UnderlyingSecurityID, 6 );
			refKind.PriceRate = 2;
			refKind.LotSize = 1;
			refKind.LotFactor = 100;
			refKind.ContractUnit = pTable[i].ContractUnit;
			::memcpy( &(refKind.MarketPeriods), &(tagHead.Periods), sizeof(tagHead.Periods) );
			refKind.PeriodsCount = tagHead.PeriodsCount;

			m_mapRate[::atoi(refKind.Key)] = refKind.PriceRate;
			QuoCollector::GetCollector()->OnImage( 158, (char*)&refKind, sizeof(tagSHOptKindDetail_LF158), true );
		}

		tagSHOptReferenceData_LF160	tagRef = { 0 };

		::strncpy( tagRef.Code, pTable[i].Code, sizeof(pTable[i].Code) );
		::strncpy( tagRef.ContractID, pTable[i].ContractID, sizeof(pTable[i].ContractID) );
		tagRef.DeliveryDate = pTable[i].DeliveryDate;
		tagRef.EndDate = pTable[i].EndDate;
		tagRef.ExpireDate = pTable[i].ExpireDate;
		T_MAP_KIND::iterator it = m_mapKind.find( sCodeKey );
		if( it != m_mapKind.end() )
		{
			tagRef.Kind = ::atoi( it->second.Key );
		}
		::strncpy( tagRef.Name, pTable[i].SecuritySymbol, sizeof(pTable[i].SecuritySymbol) );
		tagRef.StartDate = pTable[i].StartDate;
		::strncpy( tagRef.StatusFlag, pTable[i].StatusFlag, sizeof(pTable[i].StatusFlag) );
		tagRef.UpdateVersion = pTable[i].UpdateVersion;
		tagRef.XqDate = pTable[i].XqDate;
		tagRef.XqPrice = pTable[i].XqPrice;

		QuoCollector::GetCollector()->OnImage( 160, (char*)&tagRef, sizeof(tagSHOptReferenceData_LF160), false );
	}

	tagMkInfo.KindCount = tagHead.KindCount;
	QuoCollector::GetCollector()->OnImage( 157, (char*)&tagMkInfo, sizeof(tagSHOptMarketInfo_LF157), false );

	//5,获取个股快照
	tagCcComm_ShOptionData*	pStock = (tagCcComm_ShOptionData*)m_pDataBuff;
	if( (nErrCode = m_oSHOPTDll.GetStock(0, pStock, tagHead.WareCount)) < 0 )
	{
		QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::BuildImageData() : cannot fetch stocktable from dll, errorcode = %d ", nErrCode );
		return -6;
	}

	for (int i = 0; i < nErrCode; ++i)
	{
		tagSHOptSnapData_LF161		tagStockLF = { 0 };
		tagSHOptSnapData_HF162		tagStockHF = { 0 };
		tagSHOptSnapBuySell_HF163	tagStockBS = { 0 };

		::strncpy( tagStockLF.Code, pStock[i].Code, sizeof(pStock[i].Code) );
		::strncpy( tagStockHF.Code, pStock[i].Code, sizeof(pStock[i].Code) );
		::strncpy( tagStockBS.Code, pStock[i].Code, sizeof(pStock[i].Code) );

		tagStockLF.AuctionPrice = pStock[i].AuctionPrice;
		tagStockLF.AuctionQty = pStock[i].AuctionQty;
		tagStockLF.Open = pStock[i].OpenPx;
		//tagStockLF.PreClose
		//tagStockLF.PreOpenInterest = pStock[
		tagStockLF.PreSettlePrice = pStock[i].PreSettlePrice;
		tagStockLF.SettlePrice = pStock[i].SettlePrice;
		tagStockLF.TradingPhaseCode[0] = 'T';
		::memcpy( tagStockLF.TradingPhaseCode, pStock[i].TradingPhaseSecurityID, sizeof(pStock[i].TradingPhaseSecurityID) );

		tagStockHF.Amount = pStock[i].Amount;
		tagStockHF.High = pStock[i].HighPx;
		tagStockHF.Low = pStock[i].LowPx;
		tagStockHF.Now = pStock[i].Now;
		tagStockHF.Position = pStock[i].Position;
		tagStockHF.Volume = pStock[i].Volume;

		memcpy( tagStockBS.Buy, pStock[i].Buy, sizeof(tagStockBS.Buy) );
		memcpy( tagStockBS.Sell, pStock[i].Sell, sizeof(tagStockBS.Sell) );

		QuoCollector::GetCollector()->OnImage( 161, (char*)&tagStockLF, sizeof(tagSHOptSnapData_LF161), false );
		QuoCollector::GetCollector()->OnImage( 162, (char*)&tagStockHF, sizeof(tagSHOptSnapData_HF162), false );
		QuoCollector::GetCollector()->OnImage( 163, (char*)&tagStockBS, sizeof(tagSHOptSnapBuySell_HF163), true );
	}

	return 0;
}

void Quotation::OnPushMarketInfo(const char *buf, size_t len)
{
	tagSHOptMarketStatus_HF159		tagMkStatus = { 0 };
	tagCcComm_ShOptMarketStatus*	marketinfo = (tagCcComm_ShOptMarketStatus *)buf;

	tagMkStatus.StatusFlag[0] = '1';
	tagMkStatus.MarketTime = marketinfo->MarketTime;
	tagMkStatus.StatusFlag[1] = '1';
	QuoCollector::GetCollector()->OnData( 159, (char*)&tagMkStatus, sizeof(tagSHOptMarketStatus_HF159), true );
}

void Quotation::OnPushStock(const char * buf, size_t InSize)
{
	tagSHOptSnapData_LF161		tagStockLF = { 0 };
	tagSHOptSnapData_HF162		tagStockHF = { 0 };
	tagSHOptSnapBuySell_HF163	tagStockBS = { 0 };
	tagCcComm_ShOptionData*		stock = (tagCcComm_ShOptionData*)buf;

		::strncpy( tagStockLF.Code, stock->Code, sizeof(stock->Code) );
		::strncpy( tagStockHF.Code, stock->Code, sizeof(stock->Code) );
		::strncpy( tagStockBS.Code, stock->Code, sizeof(stock->Code) );

		tagStockLF.AuctionPrice = stock->AuctionPrice;
		tagStockLF.AuctionQty = stock->AuctionQty;
		tagStockLF.Open = stock->OpenPx;
		//tagStockLF.PreClose
		//tagStockLF.PreOpenInterest = pStock[
		tagStockLF.PreSettlePrice = stock->PreSettlePrice;
		tagStockLF.SettlePrice = stock->SettlePrice;
		tagStockLF.TradingPhaseCode[0] = 'T';
		::memcpy( tagStockLF.TradingPhaseCode, stock->TradingPhaseSecurityID, sizeof(stock->TradingPhaseSecurityID) );

		tagStockHF.Amount = stock->Amount;
		tagStockHF.High = stock->HighPx;
		tagStockHF.Low = stock->LowPx;
		tagStockHF.Now = stock->Now;
		tagStockHF.Position = stock->Position;
		tagStockHF.Volume = stock->Volume;

		memcpy( tagStockBS.Buy, stock->Buy, sizeof(tagStockBS.Buy) );
		memcpy( tagStockBS.Sell, stock->Sell, sizeof(tagStockBS.Sell) );

	QuoCollector::GetCollector()->OnData( 161, (char*)&tagStockLF, sizeof(tagSHOptSnapData_LF161), true );
	QuoCollector::GetCollector()->OnData( 162, (char*)&tagStockHF, sizeof(tagSHOptSnapData_HF162), true );
	QuoCollector::GetCollector()->OnData( 163, (char*)&tagStockBS, sizeof(tagSHOptSnapBuySell_HF163), true );
}

void Quotation::OnInnerPush( unsigned char MainType, unsigned char ChildType, const char * InBuf, unsigned short InSize, unsigned char marketid )
{
	int								nErrCode = 0;
	tagSHOptMarketStatus_HF159		tagMkStatus = { 0 };
	int								offset = sizeof(tagCcComm_TimeInfo);
	tagCcComm_TimeInfo*				updataTime = (tagCcComm_TimeInfo*)InBuf;

	if( (InSize < sizeof(tagCcComm_TimeInfo)) )
	{
		return;
	}

	if( ChildType == 83 )
	{
        while( offset < InSize )
        {
            char	type = InBuf[offset];
            offset += 1;

			tagMkStatus.StatusFlag[0] = '1';
			tagMkStatus.MarketTime = updataTime->CurTime;
			tagMkStatus.StatusFlag[1] = '1';
			QuoCollector::GetCollector()->OnData( 159, (char*)&tagMkStatus, sizeof(tagSHOptMarketStatus_HF159), true );

            switch( type )
            {
            case 0:
                OnPushMarketInfo(InBuf + offset, 0);
                offset += sizeof( tagCcComm_ShOptMarketStatus );
                break;
            case 1:
                OnPushStock(InBuf+offset, 0);
                offset += sizeof( tagCcComm_ShOptionData );
                break;
            default:
                return;
            }
        }
	    return;	
    }
}

void Quotation::OnPush( unsigned char MainType, unsigned char ChildType, const char *InBuf, unsigned short InSize, unsigned char Marketid, unsigned short UnitNo, bool SendDirectFlag )
{
    char inbuf[16 * 1024] = {0};
    assert(InSize < sizeof inbuf);
    memcpy(inbuf, InBuf, InSize);

    if( SendDirectFlag )
    {
        char output[16*1024]={0};
        char *pszCurrentPosPt =NULL;
        //解压一下
        int rv = MVPlatIO::RestoreDataFrame(inbuf, InSize, &pszCurrentPosPt, output, 16*1024);
        if (rv <=0)
        {
            return;
        }
		QuoCollector::GetCollector().GetQuoObj().OnInnerPush(MainType, ChildType, pszCurrentPosPt+sizeof(tagComm_FrameHead), rv- sizeof(tagComm_FrameHead), Marketid);
    }
    else
    {
		QuoCollector::GetCollector().GetQuoObj().OnInnerPush(MainType, ChildType, inbuf, InSize, Marketid);
    }
}









#include <math.h>
#include <iostream>
#include <algorithm>
#include "MVPlat.h"
#include "Quotation.h"
#include "../Infrastructure/IniFile.h"
#include "../DataCollector4Tran2ndSHL1.h"


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
		if( m_oSHL1Dll.Instance( "tran2ndsh.dll" ) < 0 )
		{
			QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::Initialize() : failed 2 initialize tran2ndsz.dll" );
			Release();
			return -2;
		}

		for( nSec = 0; nSec < 60*2; nSec++ )
		{
			SimpleTask::Sleep(1000);

			if( true == m_oSHL1Dll.IsWorking() )
			{
				if( (nErrCode = m_oSHL1Dll.GetMarketInfo( &tagHead, tagDetail, sizeof tagDetail/sizeof tagDetail[0] )) < 0 )
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
	tagSHL1MarketInfo_LF149			tagMkInfo = { 0 };
	tagSHL1MarketStatus_HF151		tagMkStatus = { 0 };

	if( (nErrCode = m_oSHL1Dll.GetMarketInfo( &tagHead, tagDetail, sizeof tagDetail/sizeof tagDetail[0] )) < 0 )
	{
		QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::BuildImageData() : cannot fetch marketinfo, errorcode=%d", nErrCode );
		return -1;
	}

	if( tagHead.MarketStatus <= 0 )
	{
		QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::BuildImageData() : marketstatus =%d ", tagHead.MarketStatus );
		return -2;
	}

	::strcpy( tagMkStatus.Key, "status" );
	tagMkStatus.MarketStatus = tagHead.MarketStatus;
	tagMkStatus.MarketTime = tagHead.Time;
	QuoCollector::GetCollector()->OnImage( 151, (char*)&tagMkStatus, sizeof(tagSHL1MarketStatus_HF151), false );

	::strcpy( tagMkInfo.Key, "mkinfo" );
	tagMkInfo.KindCount = tagHead.KindCount;
	tagMkInfo.MarketDate = tagHead.Date;
	tagMkInfo.MarketID = Configuration::GetConfig().GetMarketID();
	::memcpy( &(tagMkInfo.MarketPeriods), &(tagHead.Periods), sizeof(tagHead.Periods) );
	tagMkInfo.PeriodsCount = tagHead.PeriodsCount;
	tagMkInfo.WareCount = tagHead.WareCount;
	QuoCollector::GetCollector()->OnImage( 149, (char*)&tagMkInfo, sizeof(tagSHL1MarketInfo_LF149), false );

	for( int i = 0 ; i < tagMkInfo.KindCount; i++ )
	{
		char						pszKey[12] = { 0 };
		tagSHL1KindDetail_LF150		tagCategory = { 0 };

		::sprintf( pszKey, "%d", i );
		::strcpy( tagCategory.Key, pszKey );
		::strncpy( tagCategory.KindName, tagDetail[i].KindName, sizeof(tagDetail[i].KindName) );
		tagCategory.LotSize = tagDetail[i].LotSize;
		tagCategory.PriceRate = tagDetail[i].PriceRate;
		tagCategory.WareCount = tagDetail[i].WareCount;

		QuoCollector::GetCollector()->OnImage( 150, (char*)&tagCategory, sizeof(tagSHL1KindDetail_LF150), false );
	}

	tagCcComm_ShNameTable*	pTable = (tagCcComm_ShNameTable*)m_pDataBuff;
	if( (nErrCode = m_oSHL1Dll.GetNameTable( 0, pTable, tagHead.WareCount )) < 0 )
	{
		QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::BuildImageData() : cannot fetch nametable from dll, errorcode = %d ", nErrCode );
		return -3;
	}

	for( int i = 0; i < tagHead.WareCount; ++i )
	{
		tagSHL1ReferenceData_LF152	tagRef = { 0 };

		strncpy( tagRef.Code, pTable[i].Code, sizeof(pTable[i].Code) );
		tagRef.Kind = pTable[i].Type;
		strncpy( tagRef.Name, pTable[i].Name, sizeof(pTable[i].Name) );
		QuoCollector::GetCollector()->OnImage( 152, (char*)&tagRef, sizeof(tagSHL1ReferenceData_LF152), false );
	}

	//3,获取扩展码表
	tagCcComm_NameTableEx*	pNameEx = (tagCcComm_NameTableEx*)m_pDataBuff;
	if( (nErrCode = m_oSHL1Dll.GetNameTableEx(0, pNameEx, tagHead.WareCount)) < 0 )
	{
		QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::BuildImageData() : cannot fetch nametableEx from dll, errorcode = %d ", nErrCode );
		return -4;
	}

	for( int i = 0; i < tagHead.WareCount; i++ )
	{
		tagSHL1ReferenceExtension_LF153	tagExtension = { 0 };

		strncpy( tagExtension.Code, pNameEx[i].Code, sizeof(pNameEx[i].Code) );
		tagExtension.ExTts = pNameEx[i].ExTts;
		tagExtension.MaxExVol = pNameEx[i].MaxExVol;
		tagExtension.MinExVol = pNameEx[i].MinExVol;
		tagExtension.PLimit = pNameEx[i].PLimit;
		tagExtension.StopFlag = pNameEx[i].SFlag;
		tagExtension.Worth = pNameEx[i].Worth;
		QuoCollector::GetCollector()->OnImage( 153, (char*)&tagExtension, sizeof(tagSHL1ReferenceExtension_LF153), false );
	}

	//4,获取指数快照
	tagCcComm_IndexData*	pIndex = (tagCcComm_IndexData*)m_pDataBuff;
	if( (nErrCode = m_oSHL1Dll.GetIndex( 0, pIndex, tagHead.WareCount )) < 0 )
	{
		QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::BuildImageData() : cannot fetch indextable from dll, errorcode = %d ", nErrCode );
		return -5;
	}

	for( int i = 0; i < nErrCode; ++i )
	{
		tagSHL1SnapData_LF154		tagIndexLF = { 0 };
		tagSHL1SnapData_HF155		tagIndexHF = { 0 };

		::strncpy( tagIndexLF.Code, pIndex[i].Code, sizeof(pIndex[i].Code) );
		::strncpy( tagIndexHF.Code, pIndex[i].Code, sizeof(pIndex[i].Code) );
		tagIndexLF.Open = pIndex[i].Open;
		tagIndexLF.PreClose = pIndex[i].Close;
		tagIndexHF.Amount = pIndex[i].Amount;
		tagIndexHF.Volume = pIndex[i].Volume;
		tagIndexHF.Now = pIndex[i].Now;
		tagIndexHF.High = pIndex[i].High;
		tagIndexHF.Low = pIndex[i].Low;

		QuoCollector::GetCollector()->OnImage( 154, (char*)&tagIndexLF, sizeof(tagSHL1SnapData_LF154), false );
		QuoCollector::GetCollector()->OnImage( 155, (char*)&tagIndexHF, sizeof(tagSHL1SnapData_HF155), false );
	}

	//5,获取个股快照
	tagCcComm_StockData5*	pStock = (tagCcComm_StockData5*)m_pDataBuff;
	if( (nErrCode = m_oSHL1Dll.GetStock(0, pStock, tagHead.WareCount)) < 0 )
	{
		QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::BuildImageData() : cannot fetch stocktable from dll, errorcode = %d ", nErrCode );
		return -6;
	}

	for (int i = 0; i < nErrCode; ++i)
	{
		tagSHL1SnapData_LF154		tagStockLF = { 0 };
		tagSHL1SnapData_HF155		tagStockHF = { 0 };
		tagSHL1SnapBuySell_HF156	tagStockBS = { 0 };

		::strncpy( tagStockLF.Code, pStock[i].Code, sizeof(pStock[i].Code) );
		::strncpy( tagStockHF.Code, pStock[i].Code, sizeof(pStock[i].Code) );
		::strncpy( tagStockBS.Code, pStock[i].Code, sizeof(pStock[i].Code) );

		tagStockLF.Open = pStock[i].Open;
		tagStockLF.PreClose = pStock[i].Close;
		tagStockHF.Amount = pStock[i].Amount;
		tagStockHF.High = pStock[i].High;
		tagStockHF.Low = pStock[i].Low;
		tagStockHF.Now = pStock[i].Now;
		tagStockHF.Volume = pStock[i].Volume;
		tagStockHF.IOPV = pStock[i].Voip;

		memcpy( tagStockBS.Buy, pStock[i].Buy, sizeof(tagStockBS.Buy) );
		memcpy( tagStockBS.Sell, pStock[i].Sell, sizeof(tagStockBS.Sell) );

		QuoCollector::GetCollector()->OnImage( 154, (char*)&tagStockLF, sizeof(tagSHL1SnapData_LF154), false );
		QuoCollector::GetCollector()->OnImage( 155, (char*)&tagStockHF, sizeof(tagSHL1SnapData_HF155), false );
		QuoCollector::GetCollector()->OnImage( 156, (char*)&tagStockBS, sizeof(tagSHL1SnapBuySell_HF156), true );
	}

	return 0;
}


void Quotation::OnPushOrder(const char *buf, size_t len) {
    //tagCcComm_SzL2OderData *order = (tagCcComm_SzL2OderData *)buf;
}

void Quotation::OnPushVirtualPrice(const char *buf, size_t len) {

}

void Quotation::OnPushTrade(const char *buf, size_t len) {
/*    tagCcComm_SzL2TransData *trade = (tagCcComm_SzL2TransData *)buf;

    DF_Trade data = {0};
    memcpy(data.code, trade->Code, 6);
    data.serial = GetNameTable()->GetIndex(data.code);
    double scale = GetScale(data.serial);
    data.number = trade->TransNo;
    data.price = trade->TransPrice * scale + 0.5;
    data.time = trade->TransTime;
    data.type = trade->TranType;
    data.volume = trade->TransVolume;
    if (g_pushcb) {
        g_pushcb(kMarket, 4, (char *)&data, sizeof data, "", 0);
    }*/
}

void Quotation::OnPushPreClose(const char *buf, size_t len) {
}

void Quotation::OnPushPreName(const char *buf, size_t len) {
/*    tagCcComm_SzPerNameChg *prename = (tagCcComm_SzPerNameChg *)buf;
    DF_Prefix data = {0};
    memcpy(data.code, prename->Code, 6);
    data.serial = GetNameTable()->GetIndex(prename->Code);
    memcpy(data.PreName, prename->PreName, sizeof data.PreName);

    if (data.serial >= GetIndexTable()->GetCount()) {
        DF_StockData stock;
        int rv = GetStockTable()->Get(GetIndexTable()->GetCount(), data.serial, &stock);
        if (rv == 0) {
            memcpy(&stock.prefix, &data.PreName, sizeof stock.prefix);
            GetStockTable()->Put(GetIndexTable()->GetCount(), stock);
            if (g_pushcb) {
                g_pushcb(kMarket, 9, (char *)&data, sizeof data, data.code, 6);
            }
        }
    }*/
}

void Quotation::OnPushMarketInfo(const char *buf, size_t len)
{
	tagSHL1MarketStatus_HF151		tagMkStatus = { 0 };
	tagCcComm_MarketStatusInfo*		marketinfo = (tagCcComm_MarketStatusInfo *)buf;

	tagMkStatus.MarketStatus = 1;
	::strcpy( tagMkStatus.Key, "status" );
	tagMkStatus.MarketTime = marketinfo->MarketTime;
	QuoCollector::GetCollector()->OnData( 151, (char*)&tagMkStatus, sizeof(tagSHL1MarketStatus_HF151), true );
}

void Quotation::OnPushOrderQueue(const char *buf, size_t len) {
/*    tagCcComm_OrderQueueHeadSzL2 *orderqueue = (tagCcComm_OrderQueueHeadSzL2 *)buf;
    tagCcComm_OrderVolDetail *detail = (tagCcComm_OrderVolDetail *)(orderqueue + 1);

    DF_OrderQueue data = {0};
    memcpy(data.code, orderqueue->Code, 6);
    data.serial = GetNameTable()->GetIndex(data.code);
    double scale = GetScale(data.serial);
    data.totalcount = orderqueue->TVolCount;
    data.count = orderqueue->VolCount;
    data.price = orderqueue->Price * scale + 0.5;
    data.side = orderqueue->Side;
    for (int i = 0; i < data.count; ++i) {
        data.volume[i] = detail[i].Volume;
    }
    if (g_pushcb) {
        g_pushcb(kMarket, 2, (char *)&data, sizeof data, data.code, 6);
    }*/
}

void Quotation::OnPushIndex(const char * buf, size_t len)
{
	tagSHL1SnapData_LF154		tagIndexLF = { 0 };
	tagSHL1SnapData_HF155		tagIndexHF = { 0 };
	tagCcComm_IndexData*		index = (tagCcComm_IndexData *)buf;

	::strncpy( tagIndexLF.Code, index->Code, sizeof(index->Code) );
	::strncpy( tagIndexHF.Code, index->Code, sizeof(index->Code) );
	tagIndexLF.Open = index->Open;
	tagIndexLF.PreClose = index->Close;
	tagIndexHF.Amount = index->Amount;
	tagIndexHF.Volume = index->Volume;
	tagIndexHF.Now = index->Now;
	tagIndexHF.High = index->High;
	tagIndexHF.Low = index->Low;

	QuoCollector::GetCollector()->OnData( 154, (char*)&tagIndexLF, sizeof(tagSHL1SnapData_LF154), true );
	QuoCollector::GetCollector()->OnData( 155, (char*)&tagIndexHF, sizeof(tagSHL1SnapData_HF155), true );
}

void Quotation::OnPushStock(const char * buf, size_t InSize)
{
	tagSHL1SnapData_LF154		tagStockLF = { 0 };
	tagSHL1SnapData_HF155		tagStockHF = { 0 };
	tagSHL1SnapBuySell_HF156	tagStockBS = { 0 };
	tagCcComm_StockData5*		stock = (tagCcComm_StockData5 *)buf;

	::strncpy( tagStockLF.Code, stock->Code, sizeof(stock->Code) );
	::strncpy( tagStockHF.Code, stock->Code, sizeof(stock->Code) );
	::strncpy( tagStockBS.Code, stock->Code, sizeof(stock->Code) );

	tagStockLF.Open = stock->Open;
	tagStockLF.PreClose = stock->Close;
	tagStockHF.Amount = stock->Amount;
	tagStockHF.High = stock->High;
	tagStockHF.Low = stock->Low;
	tagStockHF.Now = stock->Now;
	tagStockHF.Volume = stock->Volume;
	tagStockHF.IOPV = stock->Voip;

	memcpy( tagStockBS.Buy, stock->Buy, sizeof(tagStockBS.Buy) );
	memcpy( tagStockBS.Sell, stock->Sell, sizeof(tagStockBS.Sell) );

	QuoCollector::GetCollector()->OnData( 154, (char*)&tagStockLF, sizeof(tagSHL1SnapData_LF154), true );
	QuoCollector::GetCollector()->OnData( 155, (char*)&tagStockHF, sizeof(tagSHL1SnapData_HF155), true );
	QuoCollector::GetCollector()->OnData( 156, (char*)&tagStockBS, sizeof(tagSHL1SnapBuySell_HF156), true );
}

void Quotation::OnInnerPush( unsigned char MainType, unsigned char ChildType, const char * InBuf, unsigned short InSize, unsigned char marketid )
{
	int								nErrCode = 0;
	tagSHL1MarketStatus_HF151		tagMkStatus = { 0 };
	int								offset = sizeof(tagCcComm_TimeInfo);
	tagCcComm_TimeInfo*				updataTime = (tagCcComm_TimeInfo*)InBuf;

	if( (InSize < sizeof(tagCcComm_TimeInfo)) )
	{
		return;
	}

    if( ChildType == 9 )
	{
        while( offset < InSize )
		{
            char	type = InBuf[offset];
            offset += 1;

            switch( type )
			{
            case 0:
				{
					tagSHL1ReferenceExtension_LF153		tagExtension = { 0 };
					::memcpy( tagExtension.Code, InBuf + offset, 6 );
					offset += 6;

					if( (nErrCode=QuoCollector::GetCollector()->OnQuery( 153, (char*)&tagExtension, sizeof(tagSHL1ReferenceExtension_LF153) )) <= 0 )
					{
						QuoCollector::GetCollector()->OnLog( TLV_WARN, "Quotation::OnInnerPush() : code[%s] is not existed in table, errorcode = %d ", tagExtension.Code, nErrCode );
					}
					else
					{
						tagExtension.StopFlag = *(InBuf + 6);
						QuoCollector::GetCollector()->OnImage( 153, (char*)&tagExtension, sizeof(tagSHL1ReferenceExtension_LF153), true );
					}

					offset++;
				}
                break;
            case 1:
                offset += sizeof(unsigned long)+6;
                break;
            case 2:
                offset += sizeof(unsigned long)+6;
                break;
            case 3:
                offset += sizeof(unsigned long)+6;
                break;
            case 4:
                offset += sizeof(unsigned long)+6;
                break;
            default:
                return;
            }
        }	
    }
	else if( ChildType == 50 )
	{
        while( offset < InSize )
        {
            char	type = InBuf[offset];
            offset += 1;

			tagMkStatus.MarketStatus = 1;
			::strcpy( tagMkStatus.Key, "status" );
			tagMkStatus.MarketTime = updataTime->CurTime;
			QuoCollector::GetCollector()->OnData( 151, (char*)&tagMkStatus, sizeof(tagSHL1MarketStatus_HF151), true );

            switch( type )
            {
            case 0:
                OnPushMarketInfo(InBuf + offset, 0);
                offset += sizeof( tagCcComm_MarketStatusInfo );
                break;
            case 1://推送指数
                OnPushIndex(InBuf+offset, 0);
                offset += sizeof( tagCcComm_IndexData );
                break;
            case 2://推送个股
                OnPushStock(InBuf + offset, 0);
                offset += sizeof(tagCcComm_StockData5);
                break;
            case 3://推送逐笔
                OnPushTrade(InBuf + offset, 0);
                offset += sizeof(tagCcComm_SzL2TransData);
                break;
            case 4://推送委托队列
                OnPushOrder(InBuf + offset, 0);
                offset += sizeof(tagCcComm_SzL2OderData);
                break;
            case 5:
                {
                    OnPushOrderQueue(InBuf + offset, 0);

                    tagCcComm_OrderQueueHeadSzL2 *	pOrderHead;
                    pOrderHead = (tagCcComm_OrderQueueHeadSzL2 *)(InBuf+offset);
                    offset += sizeof(tagCcComm_OrderQueueHeadSzL2);

                    tagCcComm_OrderVolDetail * pDetail = (tagCcComm_OrderVolDetail *)(InBuf + offset);
                    
                    offset += pOrderHead->VolCount*sizeof(tagCcComm_OrderVolDetail);
                }
                break;
            case 6://推送前缀变化
                {
                    OnPushPreName(InBuf + offset, 0);
                    offset += sizeof(tagCcComm_SzPerNameChg);
                }
                break;
            case 7:
                offset += sizeof(tagCcComm_Gzlx);
                break;
            case 8:
                offset += sizeof(tagCcComm_SZJjjz);
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
    if( Marketid == 16 && MainType ==2 )
    {
        if( ChildType == 9 || ChildType == 59 )
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
	}
}









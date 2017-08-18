#include "L2Dll.h"
#include "MVPlat.h"
#include "Quotation.h"
#include "../DataCollector4Tran2ndSHOPT.h"


L2Dll::L2Dll()
{
	memset( &m_tagDllFunc, 0, sizeof(m_tagDllFunc) );
	m_pControlIO = NULL;
}

L2Dll::~L2Dll()
{
}

int L2Dll::Instance(const char *dll)
{
	int							nRetVal;
	tagDll_DataCenterInput		tagDcInput;

	Release();

	nRetVal = m_driverdll.LoadDll(dll);
	if( nRetVal < 0 )
	{
		return nRetVal;
	}

	m_tagDllFunc.GetDllVersion = (tagGetDllVersion *)m_driverdll.GetDllFunction( "GetDllVersion" );
	m_tagDllFunc.GetBaseInfo = (tagGetDriverBaseInfo *)m_driverdll.GetDllFunction( "GetDriverBaseInfo" );
	m_tagDllFunc.BeginWork = (tagBeginDriverWork *)m_driverdll.GetDllFunction( "BeginDriverWork" );
	m_tagDllFunc.EndWork = (tagEndDriverWork *)m_driverdll.GetDllFunction( "EndDriverWork" );
	m_tagDllFunc.GetMarketInfo = (tagGetMarketInfo *)m_driverdll.GetDllFunction( "GetMarketInfo" );
	m_tagDllFunc.GetFrameCount = (tagGetDataFrameCount *)m_driverdll.GetDllFunction( "GetDataFrameCount" );
	m_tagDllFunc.GetFrameData = (tagGetOneDataFrame *)m_driverdll.GetDllFunction( "GetOneDataFrame" );
	m_tagDllFunc.IsWorking = (tagIsDriverWorking *)m_driverdll.GetDllFunction( "IsDriverWorking" );
	m_tagDllFunc.GetStatusInfo = (tagGetDriverStatusInfo *)m_driverdll.GetDllFunction( "GetDriverStatusInfo" );

	if( m_tagDllFunc.GetDllVersion == NULL || m_tagDllFunc.GetBaseInfo == NULL || 
		m_tagDllFunc.BeginWork == NULL ||m_tagDllFunc.EndWork == NULL || 
		m_tagDllFunc.GetMarketInfo == NULL || 
		m_tagDllFunc.GetFrameCount == NULL || m_tagDllFunc.GetFrameData == NULL ||
		m_tagDllFunc.IsWorking == NULL || m_tagDllFunc.GetStatusInfo == NULL )
	{
		Release();

		return -2;
	}

	memset(&tagDcInput, 0, sizeof(tagDll_DataCenterInput));
	GetDataCenterFunc( tagDcInput);

	tagDcInput.DriverUnitCode = 0;

	tagDll_DriverOutput tagDcOutput;
	memset(&tagDcOutput, 0, sizeof(tagDll_DriverOutput));
	nRetVal = m_tagDllFunc.BeginWork( &tagDcInput, &tagDcOutput );
	if( nRetVal < 0 )
	{
		Release();

		return nRetVal;
	}

	tagDll_DriverBaseInfo BaseInfo;
	memset(&BaseInfo, 0, sizeof(tagDll_DriverBaseInfo));
	m_tagDllFunc.GetBaseInfo(&BaseInfo);
	m_pControlIO = BaseInfo.drvControlClassPtr;

	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void L2Dll::Release()
{
	m_pControlIO=NULL;

	if( m_tagDllFunc.EndWork )
	{
		m_tagDllFunc.EndWork();
	}
	memset( &m_tagDllFunc, 0, sizeof(m_tagDllFunc) );

	m_driverdll.CloseDll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int	L2Dll::GetMarketInfo( tagCcComm_MarketInfoHead * pHead, tagCcComm_MarketInfoDetail * pDetail, int nCount )
{
	int						nRetVal = 0;
	tagDll_GetMarketInfoIn	tagIn = {0};
	tagDll_GetMarketInfoOut tagOut = {0};

	tagIn.nCount = nCount;
	tagOut.pHead = pHead;
	tagOut.pInfo = pDetail;

	if( m_tagDllFunc.GetMarketInfo )
	{
		nRetVal = m_tagDllFunc.GetMarketInfo( &tagIn, &tagOut );
	}

	return nRetVal;
}

bool L2Dll::IsWorking()
{
	if( NULL == m_tagDllFunc.IsWorking )
	{
		return false;
	}

	return m_tagDllFunc.IsWorking();
}
	
int	L2Dll::GetDataFrameCount(tagDll_GetDataFrameCountIn * In,tagDll_GetFrameCountOut * Out)
{
	return m_tagDllFunc.GetFrameCount( In, Out);
}

int	L2Dll::GetDataFrame(tagDll_GetOneDataFrameIn * In,tagDll_GetOneDataFrameOut * Out)
{
	return m_tagDllFunc.GetFrameData( In, Out);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int	L2Dll::GetData( unsigned char MainType, unsigned char AssiType, unsigned short dwStartNo, void * pOutData, int nSize, int nRecordSize )
{
	tagCcComm_MarketSubApply		apply = {0};
	tagDll_GetDataFrameCountIn		paramcountin = {0};
	tagDll_GetFrameCountOut			paramcountout = {0};
	tagDll_GetOneDataFrameIn		paramdatain = {0};
	tagDll_GetOneDataFrameOut		paramdataout = {0};
	int								nFrameCount;
	int								nGetCount = 0;
	int								nTemp;
	int								nDataSize;
	char							tempbuf[8192];

	if( m_tagDllFunc.GetFrameCount == NULL || m_tagDllFunc.GetFrameData == NULL || nRecordSize <= 0 )
	{
		return -1;
	}

	apply.MarketID = 0;
	nGetCount = 0;
//	apply.ApplyOffset = dwStartNo;
	
	paramdatain.MainType = paramcountin.MainType = MainType;
	paramdatain.ChildType = paramcountin.ChildType = AssiType;
	paramdatain.ApplyBuf = paramcountin.ApplyBuf = (char *)&apply;
	paramdatain.ApplySize = paramcountin.ApplySize = sizeof(apply);

	do
	{
		apply.ApplyOffset = dwStartNo + nGetCount;
	
		paramdatain.DataOutBufSize = sizeof(tempbuf);
		paramdataout.DataOutBuf = tempbuf;

		nFrameCount = m_tagDllFunc.GetFrameCount( &paramcountin, &paramcountout );
		if( nFrameCount < 0 )
		{
			return -3;
		}

		for( int i = 0; i < nFrameCount; ++i )
		{
			paramdatain.FrameNo = i;
			nDataSize = m_tagDllFunc.GetFrameData( &paramdatain, &paramdataout );
			if( nDataSize <= sizeof(tagCcComm_MarketSubResponse) )
			{
				paramcountout.RequestCompleteFlag = 1;
				break;
			}
			nDataSize -= sizeof(tagCcComm_MarketSubResponse);
			assert( nDataSize % nRecordSize == 0 );
			nTemp = nGetCount*nRecordSize;
			if( nTemp + nDataSize <= nSize )
			{
				memcpy( (char *)pOutData+nTemp, paramdataout.DataOutBuf+sizeof(tagCcComm_MarketSubResponse), nDataSize ); 
				nGetCount += (nDataSize/nRecordSize);
			}
			else
			{
				paramcountout.RequestCompleteFlag = 1;
				break;
			}
		}
	}while( paramcountout.RequestCompleteFlag != 1 );


	return nGetCount;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int	L2Dll::GetNameTable( unsigned short dwStartNo, tagCcComm_ShOptNameTable * pValue, int nCount )
{
	assert( pValue != NULL && nCount > 0 );

	return GetData( 2, 80, dwStartNo, pValue, nCount*sizeof(tagCcComm_ShOptNameTable), sizeof(tagCcComm_ShOptNameTable) );
}

int	L2Dll::GetNameTableEx(unsigned short dwStartNo, tagCcComm_ShOptNameTableEx * pValue, int nCount)
{
	assert( pValue != NULL && nCount > 0 );
	
	return GetData( 2, 81, dwStartNo, pValue, nCount*sizeof(tagCcComm_ShOptNameTableEx), sizeof(tagCcComm_ShOptNameTableEx) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int L2Dll::GetStock( unsigned short dwStartNo, tagCcComm_ShOptionData * pValue, int nCount )
{
	assert( pValue != NULL && nCount > 0 );
	
	return GetData( 2, 82, dwStartNo, pValue, nCount*sizeof(tagCcComm_ShOptionData), sizeof(tagCcComm_ShOptionData) );
}

unsigned long	L2Dll::GetDataL2Ver()
{
	if (m_tagDllFunc.GetDllVersion)
	{
		return m_tagDllFunc.GetDllVersion();
	}
	return 0;
}
/*
int	L2Dll::GetGzlx(unsigned short dwStartNo, tagCcComm_Gzlx * pValue, int nCount)
{
	assert( pValue != NULL && nCount > 0 );
	
	return GetData( 2, 3, dwStartNo, pValue, nCount*sizeof(tagCcComm_Gzlx), sizeof(tagCcComm_Gzlx) );
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void	L2Dll::ShowDllHelp(unsigned long ulCmdSerial)
{
}

void	L2Dll::DllCmd(unsigned long ulCmdSerial, char * argv[], int nArgc)
{
}

void __stdcall WriteDrvLog(unsigned char type, unsigned short wSrvUnit, unsigned short lLogLevel, 
						   const char * Source, const char * Format, ... )
{
    char buf[4096];
    va_list	valist;
    va_start(valist, Format);
    _vsnprintf(buf, sizeof buf, Format, valist);
    va_end(valist);
    buf[sizeof buf - 1] = 0;

	QuoCollector::GetCollector()->OnLog( TLV_INFO, "Tran2nd::WriteDrvLog() :%s", buf );
}

void L2Dll::GetDataCenterFunc(tagDll_DataCenterInput & datacenterinput)
{
	datacenterinput.PlatUnitType = 0;
	datacenterinput.PlatVersion = 0;
	datacenterinput.DriverUnitCode = 0; 
	datacenterinput.SendBufSize = 819200;
	datacenterinput.FrameSize = 8192;
	datacenterinput.PushDataFunPtr = Quotation::OnPush;
	datacenterinput.WriteLogFunPtr = (tagWriteLogFun*)&WriteDrvLog;
	datacenterinput.CmdPrintFunPtr = NULL;
	datacenterinput.CmdPrintlnFunPtr = NULL;
	datacenterinput.CloseFunptr = static_CloseFun;
	datacenterinput.PrepareDataFrame = static_PrepareDataFrame;
	datacenterinput.RestoreDataFrame = static_RestoreDataFrame;

}

void	L2Dll::GetDLLStatus(tagDll_DriverStatusInfo * pInfo)
{
	if (m_tagDllFunc.GetStatusInfo)
	{
		m_tagDllFunc.GetStatusInfo(pInfo);
	}
}

void	L2Dll::GetL2DllInfo(tagDll_DriverBaseInfo& pInfo)
{
	if (m_tagDllFunc.GetStatusInfo)
	{
		m_tagDllFunc.GetBaseInfo(&pInfo);
	}
}	

void __cdecl L2Dll::static_OnPushDataFun(unsigned char MainType,unsigned char ChildType,const char * InBuf,unsigned short InSize,unsigned char Marketid,unsigned short UnitNo,bool SendDirectFlag)
{
}

void __cdecl L2Dll::static_PrintLnFun(unsigned long CmdSerial,const char * Format,...)
{
	va_list valist;
	
	va_start(valist,Format);
    vprintf(Format,valist);
    printf("\n");
	va_end(valist); 
}

void __cdecl L2Dll::static_PrintFun(unsigned long CmdSerial,const char * Format,...)
{
	va_list valist;
	
	va_start(valist,Format);
	vprintf(Format,valist);
	va_end(valist); 
}

void __cdecl L2Dll::static_CloseFun(unsigned char MarketId,unsigned short UnitCode)
{
	printf("收到L2传输断开连接的通知");
}
//............................................................................................................................
int  __cdecl L2Dll::static_PrepareDataFrame(unsigned char cMainType,unsigned char cChildType,const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize)
{
    return(MVPlatIO::PrepareDataFrame(cMainType,cChildType,lpInBuf,sInSize,lpOutBuf,sOutSize));
}

//............................................................................................................................
int  __cdecl L2Dll::static_RestoreDataFrame(const char * lpInBuf,unsigned short sInSize,char * * lpOutPtr,char * lpTempBuf,unsigned short sTempSize )
{
    return(MVPlatIO::RestoreDataFrame(lpInBuf,sInSize,lpOutPtr,lpTempBuf,sTempSize));
}
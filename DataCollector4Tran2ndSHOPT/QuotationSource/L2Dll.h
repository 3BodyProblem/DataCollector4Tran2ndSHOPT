#ifndef _SZL2THIRDSRV_L2DLL_H
#define _SZL2THIRDSRV_L2DLL_H


#include "MInterface.hpp"
#include "../Infrastructure/Dll.h"


typedef struct
{
	tagGetDllVersion		*			GetDllVersion;
	tagGetDriverBaseInfo	*			GetBaseInfo;
	tagBeginDriverWork		*			BeginWork;
	tagEndDriverWork		*			EndWork;
	tagGetMarketInfo		*			GetMarketInfo;
	tagGetDataFrameCount	*			GetFrameCount;
	tagGetOneDataFrame		*			GetFrameData;
	tagIsDriverWorking		*			IsWorking;
	tagGetDriverStatusInfo	*			GetStatusInfo;
} tag4XDll_Func;


class L2Dll
{
public:
	L2Dll();
	virtual ~L2Dll();
	
public:
	int		Instance(const char *dll);
	void	Release();
	
public:
	//��ȡ����
	//��ȡ�г���Ϣ
	int		GetMarketInfo( tagCcComm_MarketInfoHead *, tagCcComm_MarketInfoDetail *, int nCount );

	//��ȡ���[2,2]
	int		GetNameTable( unsigned short dwStartNo, tagCcComm_ShNameTable *, int nCount );

	//��ȡ��չ���[2,8]
	int		GetNameTableEx(unsigned short dwStartNo, tagCcComm_NameTableEx * , int nCount);

	//��ȡָ������[2,6]
	int		GetIndex( unsigned short dwStartNo, tagCcComm_IndexData *, int nCount );

	//��ȡ��������[2,13]
	int		GetStock( unsigned short dwStartNo, tagCcComm_StockData5 *, int nCount );

	//��ȡ��ծ��Ϣ[2,3]
	//int		GetGzlx(unsigned short dwStartNo, tagCcComm_Gzlx * , int nCount);
	
	int	GetDataFrameCount(tagDll_GetDataFrameCountIn * In,tagDll_GetFrameCountOut * Out);

	int	GetDataFrame(tagDll_GetOneDataFrameIn * In,tagDll_GetOneDataFrameOut * Out);

	// �Ƿ�����
	bool		IsWorking();
public:
	//��ʾL2 DLL �е�help��Ϣ
	void	ShowDllHelp(unsigned long ulCmdSerial);
	//ִ��L2 DLL �е�����
	void	DllCmd(unsigned long ulCmdSerial, char * argv[], int nArgc);
	
public:
	unsigned long	GetDataL2Ver();
	void		GetDLLStatus(tagDll_DriverStatusInfo * pInfo);
	void		GetL2DllInfo(tagDll_DriverBaseInfo& pInfo);
	
protected:
	int			GetData( unsigned char MainType, unsigned char AssiType, unsigned short dwStartNo, void * pOutData, int nSize, int nRecordSize );
	void		GetDataCenterFunc(tagDll_DataCenterInput & oInput);

public:
	static void __cdecl static_OnPushDataFun(unsigned char MainType,unsigned char ChildType,const char * InBuf,unsigned short InSize,unsigned char Marketid,unsigned short UnitNo,bool SendDirectFlag);
	static void __cdecl static_PrintFun(unsigned long CmdSerial,const char * Format,...);
	static void __cdecl static_PrintLnFun(unsigned long CmdSerial,const char * Format,...);
	static void __cdecl static_CloseFun(unsigned char MarketId,unsigned short UnitCode);
	static int  __cdecl static_PrepareDataFrame(unsigned char cMainType,unsigned char cChildType,const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize);
	static int  __cdecl static_RestoreDataFrame(const char * lpInBuf,unsigned short sInSize,char * * lpOutPtr,char * lpTempBuf,unsigned short sTempSize );

protected:
	tag4XDll_Func					m_tagDllFunc;
	Dll								m_driverdll;
	MControlBaseClass	*			m_pControlIO;
};


#endif




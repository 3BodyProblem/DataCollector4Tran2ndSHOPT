#ifndef __TRANSRVPLAT_MVPLATH__
#define __TRANSRVPLAT_MVPLATH__


#define		COMM_MAX_FRAME_SIZE				8192					//最大数据包（数据包头部+数据体）长度
#define		COMM_MAX_DATAFRAME_SIZE			8000					//最大数据体（内容）长度
#define		COMM_MAX_REQUEST_TIMEOUT		5000					//最大请求超时时间（毫秒）
#define		COMM_MAX_COMPRESS_SIZE			100						//最小压缩长度（字节）

#define		SRVCOMM_INVALID_LINKNO		0xFFFFFFFF					//无效连接号
#define		SRVCOMM_MAX_LISTEN_PORT		64							//最大监听的端口数量

//通讯请求返回通用错误定义
#define			COMMERR_NOREQUEST			-1		//没有对应的请求
#define			COMMERR_GETDATA				-2		//获取数据错误
#define			COMMERR_CANNOT				-3		//不能完成相应操作
#define			COMMERR_CERTIFY				-4		//认证失败
#define			COMMERR_INITIALIZE			-5		//认证失败
//..........................................................................................................................
//extern void Global_WriteLog(unsigned char type,unsigned short wSrvUnit,unsigned short logLevel,const char * source,const char * Format,...);
//extern unsigned short Global_DataCenterUnitCode;
//--------------------------------------------------------------------------------------------------------------------------
//..........................................................................................................................
//..........................................................................................................................
//..........................................................................................................................
//..........................................................................................................................
//--------------------------------------------------------------------------------------------------------------------------
class MVPlatIO 
{
public:
	MVPlatIO(void);
	virtual ~MVPlatIO();
public:
	static int			Instance(void);
	static void		Release(void);
public:
	static bool IsValidIPAddr(unsigned long lIPAddr);
	static int  SpProcFrame(unsigned char cMarket,unsigned long lLinkNo,unsigned char cMainType,unsigned char cChildType,unsigned short sRequestCode,unsigned char cFrameCount,unsigned char cFrameNo,short sErrorCode,const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize);
public:
	//准备推送的数据包（包括对数据包金融金融压缩、标准压缩等处理），准备成功后，直接对每一个连接调用SendToBuf进行发送，就不用每次发送都对数据包进行压缩了。
	static int			PrepareDataFrame(unsigned char cMainType,unsigned char cChildType,const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize);
	static int			RestoreDataFrame(const char * lpInBuf,unsigned short sInSize,char * * lpOutPtr,char * lpTempBuf,unsigned short sTempSize );
public:
	static bool		IsEconomicalCompress(void);
protected:

};
//--------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------
////////////////////////This Code AUTO Mount Point By Append////////////

////////////////////////LINUX newline 请在该注释上面加CODE///////////////////

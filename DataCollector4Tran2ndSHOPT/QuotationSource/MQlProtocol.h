#ifndef __MEngine_MQlProtocolH__
#define __MEngine_MQlProtocolH__


#ifndef LINUXCODE
//..............................................................................................................................
#include <winsock2.h>
//..............................................................................................................................
#else
//..............................................................................................................................
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
//..............................................................................................................................
#endif
#include "MLZW.h"


#pragma pack(1)

typedef struct
{
	char								cMarket;				//同步标记，为'$'
    unsigned char						cMainType;				//帧类型
	unsigned char						cChildType;				//子类型
    unsigned short						sFrameCount;			//连续数据包数量
    unsigned short				        sFrameNo;				//连续数据包编号（从0开始编号）
    unsigned short				        sDataSize;				//数据长度（不包含数据包头部）
    unsigned char				        cDataStatus;			//数据状态（包含压缩、加密）
    unsigned short						sErrorCode;				//数据包返回码
    unsigned short						sCheckCode;				//数据包头部校验码
    unsigned short						sRequestCode;			//请求编号
	unsigned char						szReserved[4];			//保留字节
} tagComm_3XFrameHead;
//..............................................................................................................................
typedef struct
{
	unsigned char						cMarket;				//版本号（也可以作为同步标记），目前定义为'#'，也方便在抓取数据包时进行分析
	unsigned short						sDataSize	:	13;		//数据体的长度
	unsigned short						sStatus		:	 3;		//数据包状态，定义见上说明
	unsigned short						sCheckCode;				//校验码（对数据体进行CRC16校验）
	unsigned char						cMainType;				//数据包主类型
	unsigned char						cChildType;				//数据包辅助类型
	unsigned short						sRequestCode;			//请求编号（注意：0--39999为请求编号、40000--50000为推送编号，其他保留）
} tagComm_L2RequestHead;
//..............................................................................................................................
typedef struct
{
	unsigned char						cMarket;				//版本号（也可以作为同步标记），目前定义为'#'，也方便在抓取数据包时进行分析
	unsigned short						sDataSize	:	13;		//数据体的长度
	unsigned short						sStatus		:	 3;		//数据包状态，定义见上说明
	unsigned short						sCheckCode;				//校验码（对数据体进行CRC16校验）
	unsigned char						cMainType;				//数据包主类型
	unsigned char						cChildType;				//数据包辅助类型
	unsigned short						sRequestCode;			//请求编号（注意：0--39999为请求编号、40000--50000为推送编号，其他保留）
	short								sErrorCode;				//错误编号（请见上面详细说明）
} tagComm_FrameHead;
//..............................................................................................................................
#define		COMM_MAX_FRAME_SIZE				8192					//最大数据包（数据包头部+数据体）长度
#define		COMM_MAX_DATAFRAME_SIZE			8000					//最大数据体（内容）长度
#define		COMM_MAX_REQUEST_TIMEOUT		5000					//最大请求超时时间（毫秒）
#define		COMM_MAX_COMPRESS_SIZE			100						//最小压缩长度（字节）
//..............................................................................................................................
//..............................................................................................................................
//..............................................................................................................................
#pragma pack()
//------------------------------------------------------------------------------------------------------------------------------
class MQlTCPProtocol
{
protected:
	static __inline int  inner_trans3x(const char * lpInBuf,unsigned short sInSize,char * * lpOutPtr,char * lpTempBuf,unsigned short sTempSize);
	static __inline int  inner_transl2(const char * lpInBuf,unsigned short sInSize,char * * lpOutPtr,char * lpTempBuf,unsigned short sTempSize);
	static __inline int  inner_transnew(const char * lpInBuf,unsigned short sInSize,char * * lpOutPtr,char * lpTempBuf,unsigned short sTempSize);
protected:
	static __inline int  inner_bulid3x(	    unsigned char cMarket,
											unsigned char cMainType,
											unsigned char cChildType,
											unsigned short sRequestCode,
											unsigned char cFrameCount,
											unsigned char cFrameNo,
											short sErrorCode,
											const char * lpInBuf,
											unsigned short sInSize,
											char * lpOutBuf,
											unsigned short sOutSize,
											bool bSpProcFlag = false,
											bool bCompressFlag = true
											);
	static __inline int  inner_bulidl2(	    unsigned char cMarket,
											unsigned char cMainType,
											unsigned char cChildType,
											unsigned short sRequestCode,
											unsigned char cFrameCount,
											unsigned char cFrameNo,
											short sErrorCode,
											const char * lpInBuf,
											unsigned short sInSize,
											char * lpOutBuf,
											unsigned short sOutSize,
											bool bSpProcFlag = false,
											bool bCompressFlag = true
											);
	static __inline int  inner_bulidnew(	unsigned char cMarket,
											unsigned char cMainType,
											unsigned char cChildType,
											unsigned short sRequestCode,
											unsigned char cFrameCount,
											unsigned char cFrameNo,
											short sErrorCode,
											const char * lpInBuf,
											unsigned short sInSize,
											char * lpOutBuf,
											unsigned short sOutSize,
											bool bSpProcFlag = false,
											bool bCompressFlag = true
											);
protected:
	MQlTCPProtocol(void);
public:
	virtual ~MQlTCPProtocol();
public:
	//解析数据包
	static int  TransPacket(const char * lpInBuf,unsigned short sInSize,char * * lpOutPtr,char * lpTempBuf,unsigned short sTempSize);
	//格式化数据包（生成数据包）
	static int  BulidPacket(	unsigned char cMarket,
								unsigned char cMainType,
								unsigned char cChildType,
								unsigned short sRequestCode,
								unsigned char cFrameCount,
								unsigned char cFrameNo,
								short sErrorCode,
								const char * lpInBuf,
								unsigned short sInSize,
								char * lpOutBuf,
								unsigned short sOutSize,
								bool bSpProcFlag = false,
								bool bCompressFlag = true
								);
public:
	//同步发送请求
	static int  SendSyncRequest(	SOCKET lSocketID,
									unsigned char cMainType,
									unsigned char cChildType,
									unsigned short sRequestCode,
									const char * lpInBuf,
									unsigned short sInSize,
									unsigned char cMarket = '#');
	//同步接收应答	
	static int  RecvSyncResponse(	SOCKET lSocketID,
									char * lpOutBuf,
									unsigned short sInSize,
									unsigned char cMarket = '#');
									
};
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------------------------------------------------------

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
	char								cMarket;				//ͬ����ǣ�Ϊ'$'
    unsigned char						cMainType;				//֡����
	unsigned char						cChildType;				//������
    unsigned short						sFrameCount;			//�������ݰ�����
    unsigned short				        sFrameNo;				//�������ݰ���ţ���0��ʼ��ţ�
    unsigned short				        sDataSize;				//���ݳ��ȣ����������ݰ�ͷ����
    unsigned char				        cDataStatus;			//����״̬������ѹ�������ܣ�
    unsigned short						sErrorCode;				//���ݰ�������
    unsigned short						sCheckCode;				//���ݰ�ͷ��У����
    unsigned short						sRequestCode;			//������
	unsigned char						szReserved[4];			//�����ֽ�
} tagComm_3XFrameHead;
//..............................................................................................................................
typedef struct
{
	unsigned char						cMarket;				//�汾�ţ�Ҳ������Ϊͬ����ǣ���Ŀǰ����Ϊ'#'��Ҳ������ץȡ���ݰ�ʱ���з���
	unsigned short						sDataSize	:	13;		//������ĳ���
	unsigned short						sStatus		:	 3;		//���ݰ�״̬���������˵��
	unsigned short						sCheckCode;				//У���루�����������CRC16У�飩
	unsigned char						cMainType;				//���ݰ�������
	unsigned char						cChildType;				//���ݰ���������
	unsigned short						sRequestCode;			//�����ţ�ע�⣺0--39999Ϊ�����š�40000--50000Ϊ���ͱ�ţ�����������
} tagComm_L2RequestHead;
//..............................................................................................................................
typedef struct
{
	unsigned char						cMarket;				//�汾�ţ�Ҳ������Ϊͬ����ǣ���Ŀǰ����Ϊ'#'��Ҳ������ץȡ���ݰ�ʱ���з���
	unsigned short						sDataSize	:	13;		//������ĳ���
	unsigned short						sStatus		:	 3;		//���ݰ�״̬���������˵��
	unsigned short						sCheckCode;				//У���루�����������CRC16У�飩
	unsigned char						cMainType;				//���ݰ�������
	unsigned char						cChildType;				//���ݰ���������
	unsigned short						sRequestCode;			//�����ţ�ע�⣺0--39999Ϊ�����š�40000--50000Ϊ���ͱ�ţ�����������
	short								sErrorCode;				//�����ţ����������ϸ˵����
} tagComm_FrameHead;
//..............................................................................................................................
#define		COMM_MAX_FRAME_SIZE				8192					//������ݰ������ݰ�ͷ��+�����壩����
#define		COMM_MAX_DATAFRAME_SIZE			8000					//��������壨���ݣ�����
#define		COMM_MAX_REQUEST_TIMEOUT		5000					//�������ʱʱ�䣨���룩
#define		COMM_MAX_COMPRESS_SIZE			100						//��Сѹ�����ȣ��ֽڣ�
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
	//�������ݰ�
	static int  TransPacket(const char * lpInBuf,unsigned short sInSize,char * * lpOutPtr,char * lpTempBuf,unsigned short sTempSize);
	//��ʽ�����ݰ����������ݰ���
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
	//ͬ����������
	static int  SendSyncRequest(	SOCKET lSocketID,
									unsigned char cMainType,
									unsigned char cChildType,
									unsigned short sRequestCode,
									const char * lpInBuf,
									unsigned short sInSize,
									unsigned char cMarket = '#');
	//ͬ������Ӧ��	
	static int  RecvSyncResponse(	SOCKET lSocketID,
									char * lpOutBuf,
									unsigned short sInSize,
									unsigned char cMarket = '#');
									
};
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------------------------------------------------------

#ifndef __TRANSRVPLAT_MVPLATH__
#define __TRANSRVPLAT_MVPLATH__


#define		COMM_MAX_FRAME_SIZE				8192					//������ݰ������ݰ�ͷ��+�����壩����
#define		COMM_MAX_DATAFRAME_SIZE			8000					//��������壨���ݣ�����
#define		COMM_MAX_REQUEST_TIMEOUT		5000					//�������ʱʱ�䣨���룩
#define		COMM_MAX_COMPRESS_SIZE			100						//��Сѹ�����ȣ��ֽڣ�

#define		SRVCOMM_INVALID_LINKNO		0xFFFFFFFF					//��Ч���Ӻ�
#define		SRVCOMM_MAX_LISTEN_PORT		64							//�������Ķ˿�����

//ͨѶ���󷵻�ͨ�ô�����
#define			COMMERR_NOREQUEST			-1		//û�ж�Ӧ������
#define			COMMERR_GETDATA				-2		//��ȡ���ݴ���
#define			COMMERR_CANNOT				-3		//���������Ӧ����
#define			COMMERR_CERTIFY				-4		//��֤ʧ��
#define			COMMERR_INITIALIZE			-5		//��֤ʧ��
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
	//׼�����͵����ݰ������������ݰ����ڽ���ѹ������׼ѹ���ȴ�����׼���ɹ���ֱ�Ӷ�ÿһ�����ӵ���SendToBuf���з��ͣ��Ͳ���ÿ�η��Ͷ������ݰ�����ѹ���ˡ�
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

////////////////////////LINUX newline ���ڸ�ע�������CODE///////////////////

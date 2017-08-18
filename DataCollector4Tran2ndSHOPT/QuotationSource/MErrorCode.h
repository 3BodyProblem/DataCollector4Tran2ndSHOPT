#ifndef __MEngine_MErrorCodeH__
#define __MEngine_MErrorCodeH__


#include <string>
#include "MTypeDefine.h"


#define MERROR_SYSTEM				0x80000000					//����ϵͳ����
#define MERROR_USER					0xA0000000					//�Զ������


#pragma pack(1)

typedef struct													//�Զ�������¼�ڵ�
{
	unsigned long					lErrorCode;					//�������
	const char					*	strClassName;				//������Դ��
	const char					*	strDescribe;				//�������Ϣ����
} tagMErrorRecord;

#pragma pack()


#define ERR_PUBLIC_NOMEMORY			(MERROR_USER + 1)			//û���㹻���ڴ���Է���
#define ERR_PUBLIC_SLOPOVER			(MERROR_USER + 2)			//���������Խ��
#define ERR_PUBLIC_NOINSTANCE		(MERROR_USER + 3)			//����û�г�ʼ��
#define ERR_MSTRING_NOMATCH			(MERROR_USER + 4)			//û��ƥ���Ԫ��
#define ERR_MDATETIME_INVALID		(MERROR_USER + 5)			//��Ч��ʱ�������
#define ERR_MFILE_READALL			(MERROR_USER + 6)			//���ܰ��չ涨���ȴ��ļ��ж�ȡ����
#define ERR_MFILE_WRITEALL			(MERROR_USER + 7)			//���ܰ��չ涨����д���ļ�����
#define ERR_MFILE_NOTSIZE			(MERROR_USER + 8)			//���ܴ��ļ��ж�ȡ����ָ�����ȵ��ַ���
#define ERR_MFILE_LINUXCREATTIME	(MERROR_USER + 9)			//LINUX����ϵͳ��֧�������ļ�����ʱ��
#define ERR_MFILE_LINUXCOPYFILE		(MERROR_USER + 10)			//�ļ��Ѿ�����������Ϊ��������
#define ERR_MFILE_LINUXMATCH		(MERROR_USER + 11)			//�����ļ�ƥ���������
#define ERR_MSHAREMEM_NOINS			(MERROR_USER + 12)			//����û��ʵ����
#define ERR_MSOCKET_TIMEOUT			(MERROR_USER + 13)			//�������ݻ������ݳ�ʱ
#define ERR_MLZW_BUFFULL			(MERROR_USER + 14)			//���������޷���Ÿ��������
#define ERR_MLZW_NODATA				(MERROR_USER + 15)			//û�����ݿ��Ի�ȡ�޷���ȡ��Ҫ������
#define ERR_MLZW_NOMATCHDIRECT		(MERROR_USER + 16)			//���ֵ���û���ҵ�ƥ����������޸�����ֵ�ռ�
#define ERR_MLZW_DECODE				(MERROR_USER + 17)			//����ʧ���޷�ƥ��
#define ERR_MLOG_FILEHEAD			(MERROR_USER + 18)			//��־�ļ�ͷ����ʽ����
#define ERR_MLOG_VERSION			(MERROR_USER + 19)			//��־�ļ��汾������
#define ERR_MLOOPBUF_FULL			(MERROR_USER + 20)			//�ռ�����
#define ERR_MLOOPBUF_EMPTY			(MERROR_USER + 21)			//û���κ�����
#define ERR_MRDBFFILE_HEAD			(MERROR_USER + 22)			//DBF�ļ�ͷ������
#define ERR_MRDBFFILE_FIELDCHG		(MERROR_USER + 23)			//DBF�ֶ���Ϣ�����仯
#define ERR_MRDBFFILE_FIELDREAD		(MERROR_USER + 24)			//DBF��ȡ�ֶ���Ϣ��������
#define ERR_MRDBFFILE_DATAREAD		(MERROR_USER + 25)			//DBF��ȡ���ݷ�������
#define ERR_MRDBFFILE_NONAME		(MERROR_USER + 26)			//DBFû��ƥ����ֶ�����
#define ERR_MRDBFFILE_FIRST			(MERROR_USER + 27)			//DBF�Ѿ�Ϊ��һ����¼
#define ERR_MRDBFFILE_LAST			(MERROR_USER + 28)			//DBF�Ѿ�Ϊ���һ����¼
#define ERR_MDATABASE_NULL			(MERROR_USER + 29)			//��ȡ���ݿ��ֶ�����ΪNULL
#define ERR_MDATABASE_OPEN			(MERROR_USER + 30)			//�����ݿⷢ������
#define ERR_MDATABASE_EXECUTE		(MERROR_USER + 31)			//ִ��SQL��䷢������
#define ERR_MSELFRISEARRAY_LIMIT	(MERROR_USER + 32)			//�����޶��ռ䲻��������Ԫ��
#define ERR_MQLTCPPROTOCOL_SIZE		(MERROR_USER + 33)			//���ݰ����ȴ���
#define ERR_MQLTCPPROTOCOL_COMPRESS	(MERROR_USER + 34)			//ѹ�����ݰ�����
#define ERR_MQLTCPPROTOCOL_PACKET	(MERROR_USER + 35)			//��������ݰ�
#define ERR_MQLTCPPROTOCOL_REQUEST	(MERROR_USER + 36)			//�����������ʧ��
#define ERR_MSRVCOMM_TEIMOUT		(MERROR_USER + 37)			//�������ݳ�ʱ
#define ERR_MSRVCOMM_LISTENFULL		(MERROR_USER + 38)			//�����������ܴ�������ļ����˿�
#define ERR_MSRVCOMM_INVALIDLINK	(MERROR_USER + 39)			//��Ч�����Ӻ�
#define ERR_MSRVCOMM_LINKFULL		(MERROR_USER + 40)			//���������޷�������������
#define ERR_MCOMPRESSBASE_FULL		(MERROR_USER + 41)			//�����������޷����ѹ������
#define ERR_MCOMPRESSBASE_EMPTY		(MERROR_USER + 42)			//û�����ݿ��Ի�ȡ�޷���ȡ��Ҫ������
#define ERR_MHUFFMAN_OVER			(MERROR_USER + 43)			//���볤�ȳ�������󳤶�
#define ERR_MFINANCE_VALUE			(MERROR_USER + 44)			//������������ֵ���󣬲�����Ч��Χ
#define ERR_STEPMSG_MAXSIZE			(MERROR_USER + 45)			//STEP��Ϣ�Ѿ��������趨����󳤶�
#define ERR_STEPMSG_TAGMAXSIZE		(MERROR_USER + 46)			//STEP��Ϣ��TAG��NAME��VALUE�������趨����󳤶�����
#define ERR_STEPMSG_HEADNOTAG		(MERROR_USER + 47)			//����STEP��Ϣͷ������ȱ�ٱ�Ҫ�ֶ�
#define ERR_STEPMSG_CHECKCODE		(MERROR_USER + 48)			//����STEP��Ϣͷ������У�������
#define ERR_QLSTEP_READTAGCODE		(MERROR_USER + 49)			//��ȡSTEP��������[��ȡCODE����]
#define ERR_QLSTEP_READTAGVALUE		(MERROR_USER + 50)			//��ȡSTEP��������[��ȡVALUE����]
#define ERR_QLSTEP_WRITEERROR		(MERROR_USER + 51)			//д��STEP��������[������󳤶�]
#define ERR_IPSEARCH_READFILEERR	(MERROR_USER + 52)			//��ȡIPSearch���ݿ��ļ���������[�ļ�����]
#define ERR_IPSEARCH_MEMORY			(MERROR_USER + 53)			//��ȡIPSearch���ݿ��ļ���������[�����ڴ����]
#define	ERR_MDLL_LOSTDLLMAIN		(MERROR_USER + 54)			//LINUX�汾��so,��ʧDllMain����
#define	ERR_PARAM_NOMEMORY			(MERROR_USER + 55)			//�����Ŀռ䲻��
#define	ERR_CALL_NONEXIST_FUNCT		(MERROR_USER + 56)			//���õĺ���������


class MErrorCode
{
protected:
	static tagMErrorRecord			s_stErrorCodeTable[];		//�Զ�������б�
protected:
	MErrorCode(void);
public:
	virtual ~MErrorCode();
public:
	//��ȡ����ϵͳ�������
	static unsigned long GetSysErr(void);
	static unsigned long GetSysErr(unsigned long lSysErr);
	//���ݴ�������ȡ��������
	static std::string GetErrString(unsigned long lErrorCode);
};


#endif



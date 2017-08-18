#ifndef __CTP_QUOTATION_H__
#define __CTP_QUOTATION_H__


#pragma warning(disable:4786)
#include <set>
#include <map>
#include <string>
#include <stdexcept>
#include "L2Dll.h"
#include "../Configuration.h"
#include "../Infrastructure/Lock.h"
#include "../Infrastructure/Thread.h"
#include "../Infrastructure/DateTime.h"
#include "../Tran2nd_SHL1_QuoProtocal.h"


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


/**
 * @class			WorkStatus
 * @brief			����״̬����
 * @author			barry
 */
class WorkStatus
{
public:
	/**
	 * @brief				Ӧ״ֵ̬ӳ���״̬�ַ���
	 */
	static	std::string&	CastStatusStr( enum E_SS_Status eStatus );

public:
	/**
	 * @brief			����
	 * @param			eMkID			�г����
	 */
	WorkStatus();
	WorkStatus( const WorkStatus& refStatus );

	/**
	 * @brief			��ֵ����
						ÿ��ֵ�仯������¼��־
	 */
	WorkStatus&			operator= ( enum E_SS_Status eWorkStatus );

	/**
	 * @brief			����ת����
	 */
	operator			enum E_SS_Status();

private:
	CriticalObject		m_oLock;				///< �ٽ�������
	enum E_SS_Status	m_eWorkStatus;			///< ���鹤��״̬
};


#define			MAX_IMAGE_BUFF				(1024*1024*10)


/**
 * @class			Quotation
 * @brief			�Ự�������
 * @detail			��װ�������Ʒ�ڻ���Ȩ���г��ĳ�ʼ����������Ƶȷ���ķ���
 * @author			barry
 */
class Quotation
{
public:
	Quotation();
	~Quotation();

	/**
	 * @brief			�ͷ�ctp����ӿ�
	 */
	int					Release();

	/**
	 * @brief			��ʼ��ctp����ӿ�
	 * @return			>=0			�ɹ�
						<0			����
	 * @note			������������������У�ֻ������ʱ��ʵ�ĵ���һ��
	 */
	int					Initialize();

public:///< ������������
	/**
	 * @brief			��ȡ�Ự״̬��Ϣ
	 */
	WorkStatus&			GetWorkStatus();

	/**
	 * @brief			������������
	 * @return			==0			�ɹ�
	 */
	int					BuildImageData();

    static void			OnPush( unsigned char MainType, unsigned char ChildType, const char *InBuf, unsigned short InSize, unsigned char Marketid, unsigned short UnitNo, bool SendDirectFlag );

    void				OnInnerPush( unsigned char MainType, unsigned char ChildType, const char * InBuf, unsigned short InSize, unsigned char marketid );

    void OnPushIndex(const char *buf, size_t len);
    void OnPushStock(const char *buf, size_t len);
    void OnPushVirtualPrice(const char *buf, size_t len);
    void OnPushOrderQueue(const char *buf, size_t len);
    void OnPushOrder(const char *buf, size_t len);
    void OnPushTrade(const char *buf, size_t len);
    void OnPushMarketInfo(const char *buf, size_t len);
    void OnPushPreClose(const char *buf, size_t len);
    void OnPushPreName(const char *buf, size_t len);

private:
	CriticalObject		m_oLock;				///< �ٽ�������
	WorkStatus			m_oWorkStatus;			///< ����״̬
	L2Dll				m_oSHL1Dll;				///< ���ڴ���ģ��������
	char*				m_pDataBuff;			///< ������ʱ����
};




#endif







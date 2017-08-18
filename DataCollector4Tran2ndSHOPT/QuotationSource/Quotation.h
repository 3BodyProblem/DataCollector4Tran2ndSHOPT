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
	unsigned char						cMarket;				//版本号（也可以作为同步标记），目前定义为'#'，也方便在抓取数据包时进行分析
	unsigned short						sDataSize	:	13;		//数据体的长度
	unsigned short						sStatus		:	 3;		//数据包状态，定义见上说明
	unsigned short						sCheckCode;				//校验码（对数据体进行CRC16校验）
	unsigned char						cMainType;				//数据包主类型
	unsigned char						cChildType;				//数据包辅助类型
	unsigned short						sRequestCode;			//请求编号（注意：0--39999为请求编号、40000--50000为推送编号，其他保留）
	short								sErrorCode;				//错误编号（请见上面详细说明）
} tagComm_FrameHead;


/**
 * @class			WorkStatus
 * @brief			工作状态管理
 * @author			barry
 */
class WorkStatus
{
public:
	/**
	 * @brief				应状态值映射成状态字符串
	 */
	static	std::string&	CastStatusStr( enum E_SS_Status eStatus );

public:
	/**
	 * @brief			构造
	 * @param			eMkID			市场编号
	 */
	WorkStatus();
	WorkStatus( const WorkStatus& refStatus );

	/**
	 * @brief			赋值重载
						每次值变化，将记录日志
	 */
	WorkStatus&			operator= ( enum E_SS_Status eWorkStatus );

	/**
	 * @brief			重载转换符
	 */
	operator			enum E_SS_Status();

private:
	CriticalObject		m_oLock;				///< 临界区对象
	enum E_SS_Status	m_eWorkStatus;			///< 行情工作状态
};


#define			MAX_IMAGE_BUFF				(1024*1024*10)


/**
 * @class			Quotation
 * @brief			会话管理对象
 * @detail			封装了针对商品期货期权各市场的初始化、管理控制等方面的方法
 * @author			barry
 */
class Quotation
{
public:
	Quotation();
	~Quotation();

	/**
	 * @brief			释放ctp行情接口
	 */
	int					Release();

	/**
	 * @brief			初始化ctp行情接口
	 * @return			>=0			成功
						<0			错误
	 * @note			整个对象的生命过程中，只会启动时真实的调用一次
	 */
	int					Initialize();

public:///< 公共方法函数
	/**
	 * @brief			获取会话状态信息
	 */
	WorkStatus&			GetWorkStatus();

	/**
	 * @brief			构建快照数据
	 * @return			==0			成功
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
	CriticalObject		m_oLock;				///< 临界区对象
	WorkStatus			m_oWorkStatus;			///< 工作状态
	L2Dll				m_oSHL1Dll;				///< 深圳传输模块管理对象
	char*				m_pDataBuff;			///< 数据临时缓存
};




#endif







#ifndef __MEngine_MErrorCodeH__
#define __MEngine_MErrorCodeH__


#include <string>
#include "MTypeDefine.h"


#define MERROR_SYSTEM				0x80000000					//操作系统错误
#define MERROR_USER					0xA0000000					//自定义错误


#pragma pack(1)

typedef struct													//自定义错误纪录节点
{
	unsigned long					lErrorCode;					//错误代码
	const char					*	strClassName;				//错误来源类
	const char					*	strDescribe;				//错误的信息描述
} tagMErrorRecord;

#pragma pack()


#define ERR_PUBLIC_NOMEMORY			(MERROR_USER + 1)			//没有足够的内存可以分配
#define ERR_PUBLIC_SLOPOVER			(MERROR_USER + 2)			//参数错误或越界
#define ERR_PUBLIC_NOINSTANCE		(MERROR_USER + 3)			//对象没有初始化
#define ERR_MSTRING_NOMATCH			(MERROR_USER + 4)			//没有匹配的元素
#define ERR_MDATETIME_INVALID		(MERROR_USER + 5)			//无效的时间或日期
#define ERR_MFILE_READALL			(MERROR_USER + 6)			//不能按照规定长度从文件中读取数据
#define ERR_MFILE_WRITEALL			(MERROR_USER + 7)			//不能按照规定长度写入文件数据
#define ERR_MFILE_NOTSIZE			(MERROR_USER + 8)			//不能从文件中读取超过指定长度的字符串
#define ERR_MFILE_LINUXCREATTIME	(MERROR_USER + 9)			//LINUX操作系统不支持设置文件创建时间
#define ERR_MFILE_LINUXCOPYFILE		(MERROR_USER + 10)			//文件已经存在且设置为不被拷贝
#define ERR_MFILE_LINUXMATCH		(MERROR_USER + 11)			//查找文件匹配参数错误
#define ERR_MSHAREMEM_NOINS			(MERROR_USER + 12)			//对象没有实例化
#define ERR_MSOCKET_TIMEOUT			(MERROR_USER + 13)			//接收数据或发送数据超时
#define ERR_MLZW_BUFFULL			(MERROR_USER + 14)			//缓冲已满无法存放更多的数据
#define ERR_MLZW_NODATA				(MERROR_USER + 15)			//没有数据可以获取无法读取需要的数据
#define ERR_MLZW_NOMATCHDIRECT		(MERROR_USER + 16)			//在字典中没有找到匹配的数据且无更多的字典空间
#define ERR_MLZW_DECODE				(MERROR_USER + 17)			//解码失败无法匹配
#define ERR_MLOG_FILEHEAD			(MERROR_USER + 18)			//日志文件头部格式错误
#define ERR_MLOG_VERSION			(MERROR_USER + 19)			//日志文件版本不兼容
#define ERR_MLOOPBUF_FULL			(MERROR_USER + 20)			//空间已满
#define ERR_MLOOPBUF_EMPTY			(MERROR_USER + 21)			//没有任何数据
#define ERR_MRDBFFILE_HEAD			(MERROR_USER + 22)			//DBF文件头部错误
#define ERR_MRDBFFILE_FIELDCHG		(MERROR_USER + 23)			//DBF字段信息发生变化
#define ERR_MRDBFFILE_FIELDREAD		(MERROR_USER + 24)			//DBF读取字段信息发生错误
#define ERR_MRDBFFILE_DATAREAD		(MERROR_USER + 25)			//DBF读取数据发生错误
#define ERR_MRDBFFILE_NONAME		(MERROR_USER + 26)			//DBF没有匹配的字段名称
#define ERR_MRDBFFILE_FIRST			(MERROR_USER + 27)			//DBF已经为第一条纪录
#define ERR_MRDBFFILE_LAST			(MERROR_USER + 28)			//DBF已经为最后一条纪录
#define ERR_MDATABASE_NULL			(MERROR_USER + 29)			//读取数据库字段数据为NULL
#define ERR_MDATABASE_OPEN			(MERROR_USER + 30)			//打开数据库发生错误
#define ERR_MDATABASE_EXECUTE		(MERROR_USER + 31)			//执行SQL语句发生错误
#define ERR_MSELFRISEARRAY_LIMIT	(MERROR_USER + 32)			//超过限定空间不能再增加元素
#define ERR_MQLTCPPROTOCOL_SIZE		(MERROR_USER + 33)			//数据包长度错误
#define ERR_MQLTCPPROTOCOL_COMPRESS	(MERROR_USER + 34)			//压缩数据包错误
#define ERR_MQLTCPPROTOCOL_PACKET	(MERROR_USER + 35)			//错误的数据包
#define ERR_MQLTCPPROTOCOL_REQUEST	(MERROR_USER + 36)			//加入请求队列失败
#define ERR_MSRVCOMM_TEIMOUT		(MERROR_USER + 37)			//发送数据超时
#define ERR_MSRVCOMM_LISTENFULL		(MERROR_USER + 38)			//队列已满不能创建更多的监听端口
#define ERR_MSRVCOMM_INVALIDLINK	(MERROR_USER + 39)			//无效的连接号
#define ERR_MSRVCOMM_LINKFULL		(MERROR_USER + 40)			//连接已满无法加入更多的连接
#define ERR_MCOMPRESSBASE_FULL		(MERROR_USER + 41)			//缓冲已满，无法添加压缩数据
#define ERR_MCOMPRESSBASE_EMPTY		(MERROR_USER + 42)			//没有数据可以获取无法读取需要的数据
#define ERR_MHUFFMAN_OVER			(MERROR_USER + 43)			//编码长度超过了最大长度
#define ERR_MFINANCE_VALUE			(MERROR_USER + 44)			//金融数据类型值错误，不在有效范围
#define ERR_STEPMSG_MAXSIZE			(MERROR_USER + 45)			//STEP消息已经超过了设定的最大长度
#define ERR_STEPMSG_TAGMAXSIZE		(MERROR_USER + 46)			//STEP消息中TAG的NAME或VALUE超过了设定的最大长度限制
#define ERR_STEPMSG_HEADNOTAG		(MERROR_USER + 47)			//解析STEP消息头部错误，缺少必要字段
#define ERR_STEPMSG_CHECKCODE		(MERROR_USER + 48)			//解析STEP消息头部错误，校验码错误
#define ERR_QLSTEP_READTAGCODE		(MERROR_USER + 49)			//读取STEP发生错误[读取CODE错误]
#define ERR_QLSTEP_READTAGVALUE		(MERROR_USER + 50)			//读取STEP发生错误[读取VALUE错误]
#define ERR_QLSTEP_WRITEERROR		(MERROR_USER + 51)			//写入STEP发生错误[超过最大长度]
#define ERR_IPSEARCH_READFILEERR	(MERROR_USER + 52)			//读取IPSearch数据库文件发生错误[文件错误]
#define ERR_IPSEARCH_MEMORY			(MERROR_USER + 53)			//读取IPSearch数据库文件发生错误[分配内存错误]
#define	ERR_MDLL_LOSTDLLMAIN		(MERROR_USER + 54)			//LINUX版本的so,丢失DllMain函数
#define	ERR_PARAM_NOMEMORY			(MERROR_USER + 55)			//参数的空间不够
#define	ERR_CALL_NONEXIST_FUNCT		(MERROR_USER + 56)			//调用的函数不存在


class MErrorCode
{
protected:
	static tagMErrorRecord			s_stErrorCodeTable[];		//自定义错误列表
protected:
	MErrorCode(void);
public:
	virtual ~MErrorCode();
public:
	//获取操作系统错误代码
	static unsigned long GetSysErr(void);
	static unsigned long GetSysErr(unsigned long lSysErr);
	//根据错误代码获取错误描述
	static std::string GetErrString(unsigned long lErrorCode);
};


#endif



#include "MErrorCode.h"


tagMErrorRecord					MErrorCode::s_stErrorCodeTable[] = 
{
	{ERR_PUBLIC_NOMEMORY,		"Public",							"没有足够的内存可以分配"},
	{ERR_PUBLIC_SLOPOVER,		"Public",							"参数错误或越界"},
	{ERR_PUBLIC_NOINSTANCE,		"Public",							"对象没有初始化"},
	{ERR_MSTRING_NOMATCH,		"MString",							"没有匹配的元素"},
	{ERR_MDATETIME_INVALID,		"MDateTime",						"无效的时间或日期"},
	{ERR_MFILE_READALL,			"MFile",							"不能按照规定长度从文件中读取数据"},
	{ERR_MFILE_WRITEALL,		"MFile",							"不能按照规定长度写入文件数据"},
	{ERR_MFILE_NOTSIZE,			"MFile",							"不能从文件中读取超过指定长度的字符串"},
	{ERR_MFILE_LINUXCREATTIME,	"MFile",							"LINUX操作系统不支持设置文件创建时间"},
	{ERR_MFILE_LINUXCOPYFILE,	"MFile",							"文件已经存在且设置为不被拷贝"},
	{ERR_MFILE_LINUXMATCH,		"MFile",							"查找文件匹配参数错误"},
	{ERR_MSHAREMEM_NOINS,		"MShareMem",						"对象没有实例化"},
	{ERR_MSOCKET_TIMEOUT,		"MSocket",							"接收数据或发送数据超时"},
	{ERR_MLZW_BUFFULL,			"MLZW",								"缓冲已满无法存放更多的数据"},
	{ERR_MLZW_NODATA,			"MLZW",								"没有数据可以获取无法读取需要的数据"},
	{ERR_MLZW_NOMATCHDIRECT,	"MLZW",								"在字典中没有找到匹配的数据且无更多的字典空间"},
	{ERR_MLZW_DECODE,			"MLZW",								"解码失败无法匹配"},
	{ERR_MLOG_FILEHEAD,			"MLog"	,							"日志文件头部格式错误"},
	{ERR_MLOG_VERSION,			"MLog",								"日志文件版本不兼容"},
	{ERR_MLOOPBUF_FULL,			"MLoopbuf",							"空间已满"},
	{ERR_MLOOPBUF_EMPTY,		"MLoopbuf",							"没有任何数据"},
	{ERR_MRDBFFILE_HEAD,		"MRDbFile",							"DBF文件头部错误"},
	{ERR_MRDBFFILE_FIELDCHG,	"MRDbFile",							"DBF字段信息发生变化"},
	{ERR_MRDBFFILE_FIELDREAD,	"MRDbFile",							"DBF读取字段信息发生错误"},
	{ERR_MRDBFFILE_DATAREAD,	"MRDbFile",							"DBF读取数据发生错误"},
	{ERR_MRDBFFILE_NONAME,		"MRDbFile",							"DBF没有匹配的字段名称"},
	{ERR_MRDBFFILE_FIRST,		"MRDbFile",							"DBF已经为第一条纪录"},
	{ERR_MRDBFFILE_LAST,		"MRDbFile",							"DBF已经为最后一条纪录"},
	{ERR_MDATABASE_NULL,		"MDataBase",						"读取数据库字段数据为NULL"},
	{ERR_MDATABASE_OPEN	,		"MDataBase",						"打开数据库发生错误"},
	{ERR_MDATABASE_EXECUTE,		"MDataBase",						"执行SQL语句发生错误"},
	{ERR_MSELFRISEARRAY_LIMIT,	"MSelfRiseArry",					"超过限定空间不能再增加元素"},
	{ERR_MQLTCPPROTOCOL_SIZE,	"QlProtocol",						"数据包长度错误"},
	{ERR_MQLTCPPROTOCOL_COMPRESS,"QlProtocol",						"压缩数据包错误"},
	{ERR_MQLTCPPROTOCOL_PACKET,	"QlProtocol",						"错误的数据包"},
	{ERR_MQLTCPPROTOCOL_REQUEST,"QlProtocol",						"加入请求队列失败"},
	{ERR_MSRVCOMM_TEIMOUT,		"QlProtocol",						"发送数据超时"},
	{ERR_MSRVCOMM_LISTENFULL,	"QlProtocol",						"队列已满不能创建更多的监听端口"},
	{ERR_MSRVCOMM_INVALIDLINK,	"QlProtocol",						"无效的连接号"},
	{ERR_MSRVCOMM_LINKFULL,		"QlProtocol",						"连接已满无法加入更多的连接"},
	{ERR_MCOMPRESSBASE_FULL,	"MCompress",						"缓冲已满，无法添加压缩数据"},
	{ERR_MCOMPRESSBASE_EMPTY,	"MCompress",						"没有数据可以获取无法读取需要的数据"},
	{ERR_MHUFFMAN_OVER,			"MHuffman",							"编码长度超过了最大长度"},
	{ERR_MFINANCE_VALUE,		"MFinance",							"金融数据类型值错误，不在有效范围"},
	{ERR_QLSTEP_READTAGCODE,	"MQlStep",							"读取STEP发生错误[读取CODE错误]"},
	{ERR_QLSTEP_READTAGVALUE,	"MQlStep",							"读取STEP发生错误[读取VALUE错误]"},
	{ERR_QLSTEP_WRITEERROR,		"MQlStep",							"写入STEP发生错误[超过最大长度]"},
	{ERR_IPSEARCH_READFILEERR,	"MIPSearch",						"读取IPSearch数据库文件发生错误[文件错误]"},
	{ERR_IPSEARCH_MEMORY,		"MIPSearch",						"读取IPSearch数据库文件发生错误[分配内存错误]"},
	{ERR_MDLL_LOSTDLLMAIN,		"MDll",								"LINUX版本的so,丢失DllMain函数"},
	{ERR_PARAM_NOMEMORY,		"Public",								"参数的空间不够"},
	{ERR_CALL_NONEXIST_FUNCT,	"Public",							"调用的函数不存在"},
	{0,							"MErrorCode",						"错误表结束标志"}
};
//..............................................................................................................................
MErrorCode::MErrorCode(void)
{

}
//..............................................................................................................................
MErrorCode::~MErrorCode()
{

}
//..............................................................................................................................
//获取操作系统错误代码
unsigned long MErrorCode::GetSysErr(void)
{
	unsigned long					errorcode;

	#ifndef LINUXCODE
		//Windows操作系统
		errorcode = (unsigned long)::GetLastError();
	#else
		//Linux操作系统
		errorcode = (unsigned long)errno;
	#endif

	errorcode = errorcode & 0x7FFFFFFF;
	return(MERROR_SYSTEM + errorcode);
}
//..............................................................................................................................
unsigned long MErrorCode::GetSysErr(unsigned long lSysErr)
{
	lSysErr = lSysErr & 0x7FFFFFFF;

	return(MERROR_SYSTEM + lSysErr);
}
//..............................................................................................................................
//根据错误代码获取错误描述
std::string MErrorCode::GetErrString(unsigned long lErrorCode)
{
	register int					i;
	std::string						strtemp;
	char							pszTemp[1024];

	//自定义错误
	if ( lErrorCode >= MERROR_USER )
	{
		for ( i=0;i<sizeof(s_stErrorCodeTable) / sizeof(tagMErrorRecord);i++ )
		{
			if ( s_stErrorCodeTable[i].lErrorCode == lErrorCode )
			{
				::sprintf( pszTemp, "<%s>%s",s_stErrorCodeTable[i].strClassName,s_stErrorCodeTable[i].strDescribe );
				return pszTemp;
			}
		}

		::sprintf( pszTemp, "<MErrorCode>不能匹配的错误号(%d)，请与软件提供商联系。",lErrorCode);
		return pszTemp;
	}
	//操作系统错误
	else if ( lErrorCode >= MERROR_SYSTEM )
	{
		lErrorCode -= MERROR_SYSTEM;
		
		#ifndef LINUXCODE

			//Windows操作系统
			LPVOID					lpmsgabuf;
			char				*	lptempptr;

			if ( ::FormatMessage(	FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
									NULL,
									lErrorCode,
									0,
									(LPTSTR) &lpmsgabuf,
									0,
									NULL    ) != 0 && lpmsgabuf != NULL )
			{
				lptempptr = (char *)lpmsgabuf;
				if ( (i = strlen(lptempptr)) >= 2 )
				{
					lptempptr[i-2] = 0;
				}
				::sprintf( pszTemp, "<Windows>%s",lptempptr );
				::LocalFree(lpmsgabuf);
			}
			else
			{
				::sprintf( pszTemp, "<MErrorCode>无法获取Windows错误代码的描述信息(%d)。",lErrorCode);
			}
			
			return pszTemp;

		#else

			//Linux操作系统
			strtemp.Format("<Linux>%s。",strerror(lErrorCode));

			return(strtemp);

		#endif
	}
	//没有错误
	else
	{
		::sprintf( pszTemp, "<MErrorCode>成功返回，没有错误。" );
		return pszTemp;
	}
}
//------------------------------------------------------------------------------------------------------------------------------

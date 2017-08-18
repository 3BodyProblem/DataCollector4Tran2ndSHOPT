#include "MErrorCode.h"


tagMErrorRecord					MErrorCode::s_stErrorCodeTable[] = 
{
	{ERR_PUBLIC_NOMEMORY,		"Public",							"û���㹻���ڴ���Է���"},
	{ERR_PUBLIC_SLOPOVER,		"Public",							"���������Խ��"},
	{ERR_PUBLIC_NOINSTANCE,		"Public",							"����û�г�ʼ��"},
	{ERR_MSTRING_NOMATCH,		"MString",							"û��ƥ���Ԫ��"},
	{ERR_MDATETIME_INVALID,		"MDateTime",						"��Ч��ʱ�������"},
	{ERR_MFILE_READALL,			"MFile",							"���ܰ��չ涨���ȴ��ļ��ж�ȡ����"},
	{ERR_MFILE_WRITEALL,		"MFile",							"���ܰ��չ涨����д���ļ�����"},
	{ERR_MFILE_NOTSIZE,			"MFile",							"���ܴ��ļ��ж�ȡ����ָ�����ȵ��ַ���"},
	{ERR_MFILE_LINUXCREATTIME,	"MFile",							"LINUX����ϵͳ��֧�������ļ�����ʱ��"},
	{ERR_MFILE_LINUXCOPYFILE,	"MFile",							"�ļ��Ѿ�����������Ϊ��������"},
	{ERR_MFILE_LINUXMATCH,		"MFile",							"�����ļ�ƥ���������"},
	{ERR_MSHAREMEM_NOINS,		"MShareMem",						"����û��ʵ����"},
	{ERR_MSOCKET_TIMEOUT,		"MSocket",							"�������ݻ������ݳ�ʱ"},
	{ERR_MLZW_BUFFULL,			"MLZW",								"���������޷���Ÿ��������"},
	{ERR_MLZW_NODATA,			"MLZW",								"û�����ݿ��Ի�ȡ�޷���ȡ��Ҫ������"},
	{ERR_MLZW_NOMATCHDIRECT,	"MLZW",								"���ֵ���û���ҵ�ƥ����������޸�����ֵ�ռ�"},
	{ERR_MLZW_DECODE,			"MLZW",								"����ʧ���޷�ƥ��"},
	{ERR_MLOG_FILEHEAD,			"MLog"	,							"��־�ļ�ͷ����ʽ����"},
	{ERR_MLOG_VERSION,			"MLog",								"��־�ļ��汾������"},
	{ERR_MLOOPBUF_FULL,			"MLoopbuf",							"�ռ�����"},
	{ERR_MLOOPBUF_EMPTY,		"MLoopbuf",							"û���κ�����"},
	{ERR_MRDBFFILE_HEAD,		"MRDbFile",							"DBF�ļ�ͷ������"},
	{ERR_MRDBFFILE_FIELDCHG,	"MRDbFile",							"DBF�ֶ���Ϣ�����仯"},
	{ERR_MRDBFFILE_FIELDREAD,	"MRDbFile",							"DBF��ȡ�ֶ���Ϣ��������"},
	{ERR_MRDBFFILE_DATAREAD,	"MRDbFile",							"DBF��ȡ���ݷ�������"},
	{ERR_MRDBFFILE_NONAME,		"MRDbFile",							"DBFû��ƥ����ֶ�����"},
	{ERR_MRDBFFILE_FIRST,		"MRDbFile",							"DBF�Ѿ�Ϊ��һ����¼"},
	{ERR_MRDBFFILE_LAST,		"MRDbFile",							"DBF�Ѿ�Ϊ���һ����¼"},
	{ERR_MDATABASE_NULL,		"MDataBase",						"��ȡ���ݿ��ֶ�����ΪNULL"},
	{ERR_MDATABASE_OPEN	,		"MDataBase",						"�����ݿⷢ������"},
	{ERR_MDATABASE_EXECUTE,		"MDataBase",						"ִ��SQL��䷢������"},
	{ERR_MSELFRISEARRAY_LIMIT,	"MSelfRiseArry",					"�����޶��ռ䲻��������Ԫ��"},
	{ERR_MQLTCPPROTOCOL_SIZE,	"QlProtocol",						"���ݰ����ȴ���"},
	{ERR_MQLTCPPROTOCOL_COMPRESS,"QlProtocol",						"ѹ�����ݰ�����"},
	{ERR_MQLTCPPROTOCOL_PACKET,	"QlProtocol",						"��������ݰ�"},
	{ERR_MQLTCPPROTOCOL_REQUEST,"QlProtocol",						"�����������ʧ��"},
	{ERR_MSRVCOMM_TEIMOUT,		"QlProtocol",						"�������ݳ�ʱ"},
	{ERR_MSRVCOMM_LISTENFULL,	"QlProtocol",						"�����������ܴ�������ļ����˿�"},
	{ERR_MSRVCOMM_INVALIDLINK,	"QlProtocol",						"��Ч�����Ӻ�"},
	{ERR_MSRVCOMM_LINKFULL,		"QlProtocol",						"���������޷�������������"},
	{ERR_MCOMPRESSBASE_FULL,	"MCompress",						"�����������޷����ѹ������"},
	{ERR_MCOMPRESSBASE_EMPTY,	"MCompress",						"û�����ݿ��Ի�ȡ�޷���ȡ��Ҫ������"},
	{ERR_MHUFFMAN_OVER,			"MHuffman",							"���볤�ȳ�������󳤶�"},
	{ERR_MFINANCE_VALUE,		"MFinance",							"������������ֵ���󣬲�����Ч��Χ"},
	{ERR_QLSTEP_READTAGCODE,	"MQlStep",							"��ȡSTEP��������[��ȡCODE����]"},
	{ERR_QLSTEP_READTAGVALUE,	"MQlStep",							"��ȡSTEP��������[��ȡVALUE����]"},
	{ERR_QLSTEP_WRITEERROR,		"MQlStep",							"д��STEP��������[������󳤶�]"},
	{ERR_IPSEARCH_READFILEERR,	"MIPSearch",						"��ȡIPSearch���ݿ��ļ���������[�ļ�����]"},
	{ERR_IPSEARCH_MEMORY,		"MIPSearch",						"��ȡIPSearch���ݿ��ļ���������[�����ڴ����]"},
	{ERR_MDLL_LOSTDLLMAIN,		"MDll",								"LINUX�汾��so,��ʧDllMain����"},
	{ERR_PARAM_NOMEMORY,		"Public",								"�����Ŀռ䲻��"},
	{ERR_CALL_NONEXIST_FUNCT,	"Public",							"���õĺ���������"},
	{0,							"MErrorCode",						"����������־"}
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
//��ȡ����ϵͳ�������
unsigned long MErrorCode::GetSysErr(void)
{
	unsigned long					errorcode;

	#ifndef LINUXCODE
		//Windows����ϵͳ
		errorcode = (unsigned long)::GetLastError();
	#else
		//Linux����ϵͳ
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
//���ݴ�������ȡ��������
std::string MErrorCode::GetErrString(unsigned long lErrorCode)
{
	register int					i;
	std::string						strtemp;
	char							pszTemp[1024];

	//�Զ������
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

		::sprintf( pszTemp, "<MErrorCode>����ƥ��Ĵ����(%d)����������ṩ����ϵ��",lErrorCode);
		return pszTemp;
	}
	//����ϵͳ����
	else if ( lErrorCode >= MERROR_SYSTEM )
	{
		lErrorCode -= MERROR_SYSTEM;
		
		#ifndef LINUXCODE

			//Windows����ϵͳ
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
				::sprintf( pszTemp, "<MErrorCode>�޷���ȡWindows��������������Ϣ(%d)��",lErrorCode);
			}
			
			return pszTemp;

		#else

			//Linux����ϵͳ
			strtemp.Format("<Linux>%s��",strerror(lErrorCode));

			return(strtemp);

		#endif
	}
	//û�д���
	else
	{
		::sprintf( pszTemp, "<MErrorCode>�ɹ����أ�û�д���" );
		return pszTemp;
	}
}
//------------------------------------------------------------------------------------------------------------------------------

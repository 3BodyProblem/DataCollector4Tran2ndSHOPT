#include "MQlProtocol.h"
#include "MVPlat.h"
#include "MDataProc.h"
MDataProc Global_DataProc;

//--------------------------------------------------------------------------------------------------------------------------
MVPlatIO::MVPlatIO(void)
{


}

//..........................................................................................................................
MVPlatIO::~MVPlatIO()
{
	Release();
}
//..........................................................................................................................
int  MVPlatIO::Instance(void)
{
	Release();

	return(1);
}
//..........................................................................................................................
void MVPlatIO::Release(void)
{
	
}
//..........................................................................................................................
bool MVPlatIO::IsValidIPAddr(unsigned long lIPAddr)
{
	return(true);
}
//..........................................................................................................................
int  MVPlatIO::SpProcFrame(unsigned char cMarket,unsigned long lLinkNo,unsigned char cMainType,unsigned char cChildType,unsigned short sRequestCode,unsigned char cFrameCount,unsigned char cFrameNo,short sErrorCode,const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize)
{

	tagSpProcFrame_CompressFrame *		pCompressFunc = NULL;
	tagSpProcFrame_ExpandFrame	 *		pUnCompressfunc = NULL;

	pCompressFunc = Global_DataProc.DCompressFrame(), pUnCompressfunc = Global_DataProc.DExpandFrame();
	if ( pCompressFunc == NULL || pUnCompressfunc == NULL )
	{
		//不支持金融压缩
		return(-1);
	}

	return pCompressFunc(lpInBuf,cMainType,cChildType,sInSize,lpOutBuf,sOutSize);

}
//..........................................................................................................................
int  MVPlatIO::PrepareDataFrame(unsigned char cMainType,unsigned char cChildType,const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize)
{
	char								tempbuf[COMM_MAX_FRAME_SIZE];
	register int						errorcode;
	static unsigned long				static_seqcode = 0;

	static_seqcode = (static_seqcode + 1) % 10000;

	//开始进行数据包特殊处理（金融压缩）
	if ( (errorcode = SpProcFrame(	'#',
									SRVCOMM_INVALID_LINKNO,
									cMainType,
									cChildType,
									40000 + static_seqcode,
									1,
									0,
									0,
									lpInBuf,
									sInSize,
									tempbuf,
									COMM_MAX_FRAME_SIZE)) < 0 )
	{
		//特殊处理失败，直接采用标准压缩方式，然后对数据包进行组包
		errorcode = MQlTCPProtocol::BulidPacket(	'#',
													cMainType,
													cChildType,
													40000 + static_seqcode,
													1,
													0,
													0,
													lpInBuf,
													sInSize,
													lpOutBuf,
													sOutSize,
													false,
													true	);			
	}
	else
	{
		//特殊处理成功，再对数据包进行组包
		errorcode = MQlTCPProtocol::BulidPacket(	'#',
													cMainType,
													cChildType,
													40000 + static_seqcode,
													1,
													0,
													0,
													tempbuf,
													errorcode,
													lpOutBuf,
													sOutSize,
													true,
													false	);
	}


	return(errorcode);
}

//..........................................................................................................................
int  MVPlatIO::RestoreDataFrame(const char * lpInBuf,unsigned short sInSize,char * * lpOutPtr,char * lpTempBuf,unsigned short sTempSize )
{
	char								tempbuf[COMM_MAX_FRAME_SIZE];
	register int						errorcode;
	tagComm_FrameHead				*	framehead;

	if ( (errorcode = MQlTCPProtocol::TransPacket(lpInBuf,sInSize,lpOutPtr,lpTempBuf,sTempSize)) < 0 )
	{
		//解析数据失败
		return(errorcode);
	}
	else if ( errorcode > COMM_MAX_FRAME_SIZE )
	{
		//解析数据长度失败
		return(-1);
	}

	framehead = (tagComm_FrameHead *)(* lpOutPtr);

	if ( framehead->sStatus != 2 && framehead->sStatus != 3 )
	{
		//不需要特殊处理
        /*
		framehead->sStatus = 0x00;
		framehead->sCheckCode = 0;
        */

		return(errorcode);
	}

	//需要进行特殊处理
	if ( * lpOutPtr == lpTempBuf )
	{
		memcpy(tempbuf,lpTempBuf,errorcode);
		* lpOutPtr = tempbuf;
	}

	tagSpProcFrame_ExpandFrame	 *		pUnCompressfunc = NULL;

	pUnCompressfunc = Global_DataProc.DExpandFrame();
	if ( pUnCompressfunc == NULL )
	{
		return(-2);
	}
	
	if ( (errorcode = pUnCompressfunc((* lpOutPtr) + sizeof(tagComm_FrameHead),framehead->cMainType,framehead->cChildType,errorcode - sizeof(tagComm_FrameHead),lpTempBuf + sizeof(tagComm_FrameHead),sTempSize - sizeof(tagComm_FrameHead))) < 0 )
	{
		return(-3);
	}
	memcpy(lpTempBuf,(* lpOutPtr),sizeof(tagComm_FrameHead));

	* lpOutPtr = lpTempBuf;

	framehead = (tagComm_FrameHead *)(* lpOutPtr);

	framehead->sStatus = 0x00;
	framehead->sCheckCode = 0;
	framehead->sDataSize = errorcode;

	return(errorcode + sizeof(tagComm_FrameHead));
}
//--------------------------------------------------------------------------------------------------------------------------
bool MVPlatIO::IsEconomicalCompress(void)
{
	tagSpProcFrame_CompressFrame *		pCompressFunc = NULL;
	tagSpProcFrame_ExpandFrame	 *		pUnCompressfunc = NULL;

	pCompressFunc = Global_DataProc.DCompressFrame(), pUnCompressfunc = Global_DataProc.DExpandFrame();
	if ( pCompressFunc == NULL || pUnCompressfunc == NULL )
	{
		return(false);
	}
	else
	{
		return(true);
	}
}
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
////////////////////////This Code AUTO Mount Point By Append////////////

////////////////////////LINUX newline 请在该注释上面加CODE///////////////////

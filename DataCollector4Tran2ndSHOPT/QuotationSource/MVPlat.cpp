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
		//��֧�ֽ���ѹ��
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

	//��ʼ�������ݰ����⴦������ѹ����
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
		//���⴦��ʧ�ܣ�ֱ�Ӳ��ñ�׼ѹ����ʽ��Ȼ������ݰ��������
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
		//���⴦��ɹ����ٶ����ݰ��������
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
		//��������ʧ��
		return(errorcode);
	}
	else if ( errorcode > COMM_MAX_FRAME_SIZE )
	{
		//�������ݳ���ʧ��
		return(-1);
	}

	framehead = (tagComm_FrameHead *)(* lpOutPtr);

	if ( framehead->sStatus != 2 && framehead->sStatus != 3 )
	{
		//����Ҫ���⴦��
        /*
		framehead->sStatus = 0x00;
		framehead->sCheckCode = 0;
        */

		return(errorcode);
	}

	//��Ҫ�������⴦��
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

////////////////////////LINUX newline ���ڸ�ע�������CODE///////////////////

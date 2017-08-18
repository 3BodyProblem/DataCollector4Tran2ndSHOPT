//------------------------------------------------------------------------------------------------------------------------------
#include "MQlProtocol.h"
//------------------------------------------------------------------------------------------------------------------------------
int  MQlTCPProtocol::inner_trans3x(const char * lpInBuf,unsigned short sInSize,char * * lpOutPtr,char * lpTempBuf,unsigned short sTempSize)
{
	tagComm_3XFrameHead					*	lpframehead;
	MCRC16									mcrc16;

	//长度错误
	if ( sTempSize < sInSize )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}

	//数据包头部未接收完整
	if ( sInSize < sizeof(tagComm_3XFrameHead) )
	{
		return(0);
	}

	lpframehead = (tagComm_3XFrameHead *)lpInBuf;

	//数据长度发生错误
	if ( lpframehead->sDataSize > COMM_MAX_DATAFRAME_SIZE )
	{
		return(ERR_MQLTCPPROTOCOL_PACKET);
	}

	//数据体未接收完整
	if ( (lpframehead->sDataSize + sizeof(tagComm_3XFrameHead)) > sInSize )
	{
		return(0);
	}

	//校验发生错误
	if ( mcrc16.CheckCode(lpInBuf + sizeof(tagComm_3XFrameHead),lpframehead->sDataSize) != lpframehead->sCheckCode )
	{
		return(ERR_MQLTCPPROTOCOL_PACKET);
	}

	* lpOutPtr = (char *)lpInBuf;

	return(sizeof(tagComm_3XFrameHead) + lpframehead->sDataSize);
}
//..............................................................................................................................
int  MQlTCPProtocol::inner_transl2(const char * lpInBuf,unsigned short sInSize,char * * lpOutPtr,char * lpTempBuf,unsigned short sTempSize)
{
	tagComm_L2RequestHead				*	lpframehead;
	MCRC16								mcrc16;

	//参数错误
	if ( sTempSize < sInSize )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}
	
	//数据包头部未接收完成
	if ( sInSize < sizeof(tagComm_L2RequestHead) )
	{
		return(0);
	}
	
	lpframehead = (tagComm_L2RequestHead *)lpInBuf;
	
	//数据包长度错误
	if ( lpframehead->sDataSize > COMM_MAX_DATAFRAME_SIZE )
	{
		return(ERR_MQLTCPPROTOCOL_PACKET);
	}
	
	//数据包体未接收完成
	if ( (lpframehead->sDataSize + sizeof(tagComm_L2RequestHead) - 4) > sInSize )
	{
		return(0);
	}
	
	//校验错误
	if ( mcrc16.CheckCode(lpInBuf + sizeof(tagComm_L2RequestHead) - 4,lpframehead->sDataSize) != lpframehead->sCheckCode )
	{
		return(ERR_MQLTCPPROTOCOL_PACKET);
	}
	
	
	* lpOutPtr = (char *)lpInBuf;
	
	return(sizeof(tagComm_L2RequestHead) - 4 + lpframehead->sDataSize);
}
//..............................................................................................................................
int  MQlTCPProtocol::inner_transnew(const char * lpInBuf,unsigned short sInSize,char * * lpOutPtr,char * lpTempBuf,unsigned short sTempSize)
{
	tagComm_FrameHead				*	lpframehead;
	MCRC16								mcrc16;
	MLZW8192C							mlzw;
	register int						errorcode;

	//参数错误
	if ( sTempSize < sInSize )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}
	
	//数据包头部未接收完成
	if ( sInSize < sizeof(tagComm_FrameHead) )
	{
		return(0);
	}
	
	lpframehead = (tagComm_FrameHead *)lpInBuf;
	
	//数据包长度错误
	if ( lpframehead->sDataSize > COMM_MAX_DATAFRAME_SIZE )
	{
		return(ERR_MQLTCPPROTOCOL_PACKET);
	}
	
	//数据包体未接收完成
	if ( (lpframehead->sDataSize + sizeof(tagComm_FrameHead)) > sInSize )
	{
		return(0);
	}
	
	//校验错误
	if ( mcrc16.CheckCode(lpInBuf + sizeof(tagComm_FrameHead),lpframehead->sDataSize) != lpframehead->sCheckCode )
	{
		return(ERR_MQLTCPPROTOCOL_PACKET);
	}
	
	if ( lpframehead->sStatus == 1 || lpframehead->sStatus == 3 )
	{
		//需要解压缩
		memcpy(lpTempBuf,lpInBuf,sizeof(tagComm_FrameHead));
		lpframehead = (tagComm_FrameHead *)lpTempBuf;

		if ( (errorcode = mlzw.ExpandBuf(		(char *)lpInBuf + sizeof(tagComm_FrameHead),
												lpframehead->sDataSize,
												lpTempBuf + sizeof(tagComm_FrameHead),
												sTempSize - sizeof(tagComm_FrameHead)	)) < 0 )
		{
			//解压缩错误
			return(errorcode);
		}
		
		if ( lpframehead->sStatus == 3 )
		{
			lpframehead->sStatus = 2;
		}
		else
		{
			lpframehead->sStatus = 0;
		}
		
		* lpOutPtr = lpTempBuf;
		
		return(sizeof(tagComm_FrameHead) + errorcode);
	}
	else
	{
		//不需要解压缩
		* lpOutPtr = (char *)lpInBuf;
		return(sizeof(tagComm_FrameHead) + lpframehead->sDataSize);
	}	
}
//..............................................................................................................................
int  MQlTCPProtocol::TransPacket(const char * lpInBuf,unsigned short sInSize,char * * lpOutPtr,char * lpTempBuf,unsigned short sTempSize)
{
	if ( sInSize == 0 )
	{
		return(0);
	}
	else if ( lpInBuf[0] == '$' )
	{
		return(inner_trans3x(lpInBuf,sInSize,lpOutPtr,lpTempBuf,sTempSize));
	}
	else if ( lpInBuf[0] == 0x00 )
	{
		return(inner_transl2(lpInBuf,sInSize,lpOutPtr,lpTempBuf,sTempSize));
	}
	else if ( lpInBuf[0] == '#' )
	{
		return(inner_transnew(lpInBuf,sInSize,lpOutPtr,lpTempBuf,sTempSize));
	}
	else
	{
		return(ERR_MQLTCPPROTOCOL_PACKET);
	}
}
//..............................................................................................................................
int  MQlTCPProtocol::inner_bulid3x(	   unsigned char cMarket,
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
									   bool bSpProcFlag,
									   bool bCompressFlag	)
{
	tagComm_3XFrameHead				*	lpframehead;
	MCRC16								mcrc16;
	MLZW4096							mlzw4096;
	register int						errorcode;

	if ( sOutSize < sInSize )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}

	lpframehead = (tagComm_3XFrameHead *)lpOutBuf;

	lpframehead->sRequestCode = sRequestCode;
	lpframehead->cMarket = cMarket;
	lpframehead->cMainType = cMainType;
	lpframehead->cChildType = cChildType;
	lpframehead->sFrameCount = cFrameCount;
	lpframehead->sFrameNo = cFrameNo;
	lpframehead->sErrorCode = sErrorCode;
	memset(lpframehead->szReserved,0x00,4);

	if ( bCompressFlag == true && sInSize >= 100 )
	{
		//需要压缩数据
		errorcode = mlzw4096.CompressBuf(	lpInBuf,
											sInSize,
											lpOutBuf + sizeof(tagComm_3XFrameHead),
											sOutSize - sizeof(tagComm_3XFrameHead)	);
		if ( errorcode >= 0 )
		{
			lpframehead->sDataSize = errorcode;
			lpframehead->cDataStatus = 0x48;
			lpframehead->sCheckCode = mcrc16.CheckCode(lpOutBuf + sizeof(tagComm_3XFrameHead),errorcode);

			return(errorcode + sizeof(tagComm_3XFrameHead));
		}
	}

	//不需要压缩数据或压缩数据失败
	if ( sInSize > 0 )
	{
		memcpy(lpOutBuf + sizeof(tagComm_3XFrameHead),lpInBuf,sInSize);
	}
	errorcode = sInSize;

	lpframehead->sDataSize = errorcode;
	lpframehead->cDataStatus = 0x40;
	lpframehead->sCheckCode = mcrc16.CheckCode(lpOutBuf + sizeof(tagComm_3XFrameHead),errorcode);
	
	return(errorcode + sizeof(tagComm_3XFrameHead));	
}
//..............................................................................................................................
int  MQlTCPProtocol::inner_bulidl2(	   unsigned char cMarket,
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
									   bool bSpProcFlag,
									   bool bCompressFlag
									   )
{
	tagComm_FrameHead				*	lpframehead;
	MCRC16								mcrc16;
	MLZW8192							mlzw8192;
	register int						errorcode;
	char								tempbuf[COMM_MAX_FRAME_SIZE];

	if ( sOutSize < sInSize )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}

	lpframehead = (tagComm_FrameHead *)lpOutBuf;

	lpframehead->cMarket = cMarket;
	lpframehead->cMainType = cMainType;
	lpframehead->cChildType = cChildType;
	lpframehead->sRequestCode = sRequestCode;
	if ( sErrorCode >= 0 )
	{
		lpframehead->sErrorCode = (unsigned short)cFrameCount * 100 + cFrameNo;
	}
	else
	{
		lpframehead->sErrorCode = sErrorCode;
	}

	if ( sInSize > 0 )
	{
		memcpy(lpOutBuf + sizeof(tagComm_FrameHead),lpInBuf,sInSize);
	}
	errorcode = sInSize;
	
	if ( bCompressFlag == true && sInSize >= 100 )
	{
		//需要压缩数据
		errorcode = mlzw8192.CompressBuf(		lpInBuf,
												sInSize,
												tempbuf,
												COMM_MAX_FRAME_SIZE	);
		if ( errorcode >= 0 )
		{
			memcpy(lpOutBuf + 5,tempbuf,errorcode);

			lpframehead->sDataSize = errorcode + 6;
			lpframehead->sStatus = 0x01;
			lpframehead->sCheckCode = mcrc16.CheckCode(lpOutBuf + 5,errorcode + 6);

			return(5 + errorcode);
		}
	}

	//不需要压缩或压缩失败
	lpframehead->sDataSize = errorcode + 6;
	lpframehead->sStatus = 0x00;
	lpframehead->sCheckCode = mcrc16.CheckCode(lpOutBuf + 5,errorcode + 6);

	return(5 + errorcode);
}
//..............................................................................................................................
int  MQlTCPProtocol::inner_bulidnew(	unsigned char cMarket,
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
										bool bSpProcFlag,
										bool bCompressFlag
									)
{
	tagComm_FrameHead				*	lpframehead;
	MCRC16								mcrc16;
	MLZW8192C							mlzw8192;
	register int						errorcode;

	if ( sOutSize < sInSize )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}

	lpframehead = (tagComm_FrameHead *)lpOutBuf;

	lpframehead->cMarket = cMarket;
	lpframehead->cMainType = cMainType;
	lpframehead->cChildType = cChildType;
	lpframehead->sRequestCode = sRequestCode;
	if ( sErrorCode >= 0 )
	{
		lpframehead->sErrorCode = (unsigned short)cFrameCount * 100 + cFrameNo;
	}
	else
	{
		lpframehead->sErrorCode = sErrorCode;
	}

	if ( bCompressFlag == true && sInSize >= 100 )
	{
		//需要压缩数据
		errorcode = mlzw8192.CompressBuf(	lpInBuf,
											sInSize,
											lpOutBuf + sizeof(tagComm_FrameHead),
											sOutSize - sizeof(tagComm_FrameHead)	);
		if ( errorcode >= 0 )
		{
			lpframehead->sDataSize = errorcode;
			if ( bSpProcFlag == true )
			{
				lpframehead->sStatus = 0x03;
			}
			else
			{
				lpframehead->sStatus = 0x01;
			}
			lpframehead->sCheckCode = mcrc16.CheckCode(lpOutBuf + sizeof(tagComm_FrameHead),errorcode);

			return(errorcode + sizeof(tagComm_FrameHead));
		}
	}

	//不需要压缩或压缩失败
	if ( sInSize > 0 )
	{
		memcpy(lpOutBuf + sizeof(tagComm_FrameHead),lpInBuf,sInSize);
	}
	errorcode = sInSize;

	lpframehead->sDataSize = errorcode;
	if ( bSpProcFlag == true )
	{
		lpframehead->sStatus = 0x02;
	}
	else
	{
		lpframehead->sStatus = 0x00;
	}
	lpframehead->sCheckCode = mcrc16.CheckCode(lpOutBuf + sizeof(tagComm_FrameHead),errorcode);
	
	return(errorcode + sizeof(tagComm_FrameHead));
}
//..............................................................................................................................
int  MQlTCPProtocol::BulidPacket(	 unsigned char cMarket,
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
									 bool bSpProcFlag,
									 bool bCompressFlag
									 )
{
	if ( cMarket == '$' )
	{
		return(inner_bulid3x(cMarket,cMainType,cChildType,sRequestCode,cFrameCount,cFrameNo,sErrorCode,lpInBuf,sInSize,lpOutBuf,sOutSize,bSpProcFlag,bCompressFlag));
	}
	else if ( cMarket == 0x00 )
	{
		return(inner_bulidl2(cMarket,cMainType,cChildType,sRequestCode,cFrameCount,cFrameNo,sErrorCode,lpInBuf,sInSize,lpOutBuf,sOutSize,bSpProcFlag,bCompressFlag));
	}
	else if ( cMarket == '#' )
	{
		return(inner_bulidnew(cMarket,cMainType,cChildType,sRequestCode,cFrameCount,cFrameNo,sErrorCode,lpInBuf,sInSize,lpOutBuf,sOutSize,bSpProcFlag,bCompressFlag));
	}
	else
	{
		return(ERR_MQLTCPPROTOCOL_PACKET);
	}
}







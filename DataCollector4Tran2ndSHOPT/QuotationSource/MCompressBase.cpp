//------------------------------------------------------------------------------------------------------------------------------
#include "MCompressBase.h"
//------------------------------------------------------------------------------------------------------------------------------
MCompressBase::MCompressBase(void)
{

}
//..............................................................................................................................
MCompressBase::~MCompressBase()
{

}
//..............................................................................................................................
int  MCompressBase::PutBitToBuf32(char * lpInBuf,unsigned long lInSize,unsigned long lBitOffset,unsigned long lValue,unsigned short sBitSize)
{
	register unsigned long								lbyteoffset;
	register unsigned long								lbytestart;
	
	//判断参数
	if ( lpInBuf == NULL || sBitSize > 32 || sBitSize == 0 )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}
	
	//计算写入的偏移
	lbyteoffset = lBitOffset >> 3;
	lbytestart = lBitOffset - ( (lBitOffset >> 3) << 3 );
	
	//判断是否可以写入
	if ( (lbyteoffset + 4) >= lInSize )
	{
		return(ERR_MCOMPRESSBASE_FULL);
	}

	//将写入的值只保留写入部分
	lValue = lValue & ((unsigned long)0xFFFFFFFF >> (32 - sBitSize));
	
	//开始写入
	if ( ( 8 - lbytestart ) >= sBitSize )
	{
		lpInBuf[lbyteoffset] = (unsigned char)lpInBuf[lbyteoffset] | (unsigned char)( lValue << ( 8 - lbytestart - sBitSize ) );
		return(1);
	}
	else
	{
		lpInBuf[lbyteoffset] = (unsigned char)lpInBuf[lbyteoffset] | (unsigned char)( lValue >> ( sBitSize - 8 + lbytestart ) );
		
		lBitOffset += 8 - lbytestart;
		sBitSize -= 8 - lbytestart;

		return(PutBitToBuf32(lpInBuf,lInSize,lBitOffset,lValue,sBitSize));
	}
}
//..............................................................................................................................
int  MCompressBase::PutBitToBuf64(char * lpInBuf,unsigned long lInSize,unsigned long lBitOffset,unsigned __int64 iValue,unsigned short sBitSize)
{
	unsigned long					lhigh,llow;
	register int					errorcode;
	
	memcpy(&lhigh,((char *)&iValue) + 4,4);
	memcpy(&llow,(char *)&iValue,4);
	
	if ( sBitSize > 32 )
	{
		if ( (errorcode = PutBitToBuf32(lpInBuf,lInSize,lBitOffset,llow,32)) < 0 )
		{
			return(errorcode);
		}

		return(PutBitToBuf32(lpInBuf,lInSize,lBitOffset + 32,lhigh,sBitSize - 32));
	}
	else
	{
		return(PutBitToBuf32(lpInBuf,lInSize,lBitOffset,llow,sBitSize));
	}
}
//..............................................................................................................................
int  MCompressBase::PutBitToBufString(char * lpInBuf,unsigned long lInSize,unsigned long lBitOffset,const char * lString,unsigned short sStringSize)
{
	register int					errorcode;
	register int					i = 0;

	for ( i=0;i<sStringSize;i++ )
	{
		if ( (errorcode = PutBitToBuf32(lpInBuf,lInSize,lBitOffset,(unsigned char)lString[i],8)) < 0 )
		{
			return(errorcode);
		}

		lBitOffset += 8;
	}

	return(1);
}
//..............................................................................................................................
int  MCompressBase::GetBitFromBuf32(const char * lpInBuf,unsigned long lInBitSize,unsigned long lBitOffset,unsigned long * lValue,unsigned short sBitSize)
{
	register unsigned long									lbyteoffset;
	register unsigned long									lbytestart;
	register unsigned char									cinvalue;
	register unsigned long									ltempvalue;
	register int											errorcode;
	
	//判断参数是否正确
	if ( lpInBuf == NULL || lValue == NULL )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}

	//判断是否能够读取
	if ( (lBitOffset + sBitSize) > lInBitSize )
	{
		return(ERR_MLZW_NODATA);
	}

	//计算读取数据的偏移位置
	* lValue = 0;
	lbyteoffset = lBitOffset >> 3;
	lbytestart = lBitOffset - ( (lBitOffset >> 3) << 3 );
	
	if ( ( 8 - lbytestart ) >= sBitSize )
	{
		cinvalue = lpInBuf[lbyteoffset];
		* lValue = ((unsigned long)cinvalue & ( (unsigned char)0xFF >> lbytestart )) >> ( 8 - lbytestart - sBitSize );
		
		return(1);
	}
	else
	{
		cinvalue = lpInBuf[lbyteoffset];
		* lValue = ((unsigned long)cinvalue & ( (unsigned char)0xFF >> lbytestart ));
		
		lBitOffset += 8 - lbytestart;
		sBitSize -= 8 - lbytestart;
		
		if ( (errorcode = GetBitFromBuf32(lpInBuf,lInBitSize,lBitOffset,&ltempvalue,sBitSize)) < 0 )
		{
			return(errorcode);
		}
		
		* lValue = (( * lValue ) << sBitSize) | ltempvalue;
		return(1);
	}
}
//..............................................................................................................................
int  MCompressBase::GetBitFromBuf64(const char * lpInBuf,unsigned long lInBitSize,unsigned long lBitOffset,unsigned __int64 * iValue,unsigned short sBitSize)
{
	unsigned long					lhigh = 0,llow = 0;
	register int					errorcode;
	
	if ( sBitSize > 32 )
	{
		if ( (errorcode = GetBitFromBuf32(lpInBuf,lInBitSize,lBitOffset,&llow,32)) < 0 )
		{
			return(errorcode);
		}
		
		if ( (errorcode = GetBitFromBuf32(lpInBuf,lInBitSize,lBitOffset + 32,&lhigh,sBitSize - 32)) < 0 )
		{
			return(errorcode);
		}
	}
	else
	{
		if ( (errorcode = GetBitFromBuf32(lpInBuf,lInBitSize,lBitOffset,&llow,sBitSize)) < 0 )
		{
			return(errorcode);
		}
	}
	
	memcpy(((char *)iValue) + 4,&lhigh,4);
	memcpy((char *)iValue,&llow,4);

	return(1);
}
//..............................................................................................................................
int  MCompressBase::GetBitFromBufString(const char * lpInBuf,unsigned long lInBitSize,unsigned long lBitOffset,char * lString,unsigned short sStringSize)
{
	register int					errorcode;
	register int					i;
	unsigned long					ltemp;

	for ( i=0;i<sStringSize;i++ )
	{
		if ( (errorcode = GetBitFromBuf32(lpInBuf,lInBitSize,lBitOffset,&ltemp,8)) < 0 )
		{
			return(errorcode);
		}

		lString[i] = (unsigned char)ltemp;
		lBitOffset += 8;
	}

	return(1);
}
//------------------------------------------------------------------------------------------------------------------------------

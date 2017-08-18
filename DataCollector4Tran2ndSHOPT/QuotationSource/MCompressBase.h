#ifndef __MEngine_MCompressBaseH__
#define __MEngine_MCompressBaseH__


#include "MErrorCode.h"
#include "MCheckCode.h"


class MCompressBase
{
protected:
public:
	MCompressBase(void);
	virtual ~MCompressBase();
public:
	static int  PutBitToBuf32(char * lpInBuf,unsigned long lInSize,unsigned long lBitOffset,unsigned long lValue,unsigned short sBitSize);
	static int  PutBitToBuf64(char * lpInBuf,unsigned long lInSize,unsigned long lBitOffset,unsigned __int64 iValue,unsigned short sBitSize);
	static int  PutBitToBufString(char * lpInBuf,unsigned long lInSize,unsigned long lBitOffset,const char * lString,unsigned short sStringSize);
public:
	static int  GetBitFromBuf32(const char * lpInBuf,unsigned long lInBitSize,unsigned long lBitOffset,unsigned long * lValue,unsigned short sBitSize);
	static int  GetBitFromBuf64(const char * lpInBuf,unsigned long lInBitSize,unsigned long lBitOffset,unsigned __int64 * iValue,unsigned short sBitSize);
	static int  GetBitFromBufString(const char * lpInBuf,unsigned long lInBitSize,unsigned long lBitOffset,char * lString,unsigned short sStringSize);
};


#endif


#ifndef __MEngine_MLZWH__
#define __MEngine_MLZWH__
//------------------------------------------------------------------------------------------------------------------------------
#include "MCompressBase.h"
//------------------------------------------------------------------------------------------------------------------------------
#pragma pack(1)
//..............................................................................................................................
typedef struct
{
	short										nCodeValue;
	short										nParentCode;
	char										cCharacter;
} tagLzwDirectInfo;
//..............................................................................................................................
typedef struct
{
	long										nCodeValue;
	long										nParentCode;
	char										cCharacter;
} tagLzwDirectInfo32;
//..............................................................................................................................
#pragma pack()
//------------------------------------------------------------------------------------------------------------------------------
//仅仅局限于4096长度以内的压缩
#define MLZW4096_BITS							12
#define MLZW4096_MAXCODE						((1 << MLZW4096_BITS) - 1)
#define MLZW4096_TABLESIZE						5021
#define MLZW4096_END							256
#define MLZW4096_BUMPCODE						257
#define MLZW4096_FIRSTCODE						258
#define MLZW4096_UNUSER							-1
//..............................................................................................................................
class MLZW4096 : public MCompressBase
{
private:
	tagLzwDirectInfo						m_stDictory[MLZW4096_TABLESIZE];
	char									m_szStackBuf[MLZW4096_TABLESIZE];
private:
	__inline void Initialize(void);
	__inline int  FindChildNode(long nParentCode,long lChildCode,unsigned long * lpOutIndex);
	__inline unsigned long DecodeString(unsigned long lCount,unsigned long lCode);
public:
	MLZW4096(void);
	~MLZW4096();
public:
	int  CompressBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize);
	int  ExpandBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize);
};
//------------------------------------------------------------------------------------------------------------------------------
//仅仅局限于8192长度以内的压缩
#define MLZW8192_BITS							13
#define MLZW8192_MAXCODE						((1 << MLZW4096_BITS) - 1)
#define MLZW8192_TABLESIZE						9973
#define MLZW8192_END							256
#define MLZW8192_BUMPCODE						257
#define MLZW8192_FIRSTCODE						258
#define MLZW8192_UNUSER							-1
//..............................................................................................................................
class MLZW8192 : public MCompressBase
{
private:
	tagLzwDirectInfo						m_stDictory[MLZW8192_TABLESIZE];
	char									m_szStackBuf[MLZW8192_TABLESIZE];
private:
	__inline void Initialize(void);
	__inline int  FindChildNode(long nParentCode,long lChildCode,unsigned long * lpOutIndex);
	__inline unsigned long DecodeString(unsigned long lCount,unsigned long lCode);
public:
	MLZW8192(void);
	~MLZW8192();
public:
	int  CompressBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize);
	int  ExpandBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize);
};
//------------------------------------------------------------------------------------------------------------------------------
//支持任意长度的压缩方式(当然不能超过(2的32次方)/8 = 512M)
#define MLZW_BITS								15							//每个单元最大表示的BIT数量
#define MLZW_TABLESIZE							35023						//字典的大小
#define MLZW_END								256							//结束标志
#define MLZW_BUMPCODE							257							//当前单元BIT数量增加标志
#define MLZW_CLEARTABLE							258							//重新构造字典标志
#define MLZW_FIRSTCODE							259							//第一个表示的序号
#define MLZW_UNUSER								-1							//字典中未使用的单元
//..............................................................................................................................
class MLZW : public MCompressBase
{
private:
	tagLzwDirectInfo32						m_stDictory[MLZW_TABLESIZE];
	char									m_szStackBuf[MLZW_TABLESIZE];
private:
	__inline void Initialize(void);
	__inline int  FindChildNode(long nParentCode,long lChildCode,unsigned long * lpOutIndex);
	__inline unsigned long DecodeString(unsigned long lCount,unsigned long lCode);
public:
	MLZW(void);
	~MLZW();
public:
	int  CompressBuf(const char * lpInBuf,unsigned long sInSize,char * lpOutBuf,unsigned long sOutSize);
	int  ExpandBuf(const char * lpInBuf,unsigned long sInSize,char * lpOutBuf,unsigned long sOutSize);
};
//------------------------------------------------------------------------------------------------------------------------------
//以下压缩类加入了校验功能，一般使用下面的类
//..............................................................................................................................
class MLZW4096C : public MLZW4096
{
protected:
public:
	MLZW4096C(void);
	virtual ~MLZW4096C();
public:
	int  CompressBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize);
	int  ExpandBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize);
};
//..............................................................................................................................
class MLZW8192C : public MLZW8192
{
protected:
public:
	MLZW8192C(void);
	virtual ~MLZW8192C();
public:
	int  CompressBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize);
	int  ExpandBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize);
};
//..............................................................................................................................
class MLZWC : public MLZW
{
protected:
public:
	MLZWC(void);
	virtual ~MLZWC();
public:
	int  CompressBuf(const char * lpInBuf,unsigned long sInSize,char * lpOutBuf,unsigned long sOutSize);
	int  ExpandBuf(const char * lpInBuf,unsigned long sInSize,char * lpOutBuf,unsigned long sOutSize);
};
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------------------------------------------------------

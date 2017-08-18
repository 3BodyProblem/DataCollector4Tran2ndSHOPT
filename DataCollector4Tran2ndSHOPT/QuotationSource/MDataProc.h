#ifndef __TRANSRVPLAT_MDATAPROC_H__
#define __TRANSRVPLAT_MDATAPROC_H__


#include <stdio.h>
#include <string>
#include "../Infrastructure/Dll.h"


typedef unsigned long  __stdcall tagSpProcFrame_GetDllVersion(void);
typedef int  __stdcall tagSpProcFrame_Instance(void);
typedef void __stdcall tagSpProcFrame_Release(void);
typedef int  __stdcall tagSpProcFrame_CompressFrame(const char * lpInBuf,unsigned char cMainType,unsigned char cChildType,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize);
typedef int  __stdcall tagSpProcFrame_ExpandFrame(const char * lpInBuf,unsigned char cMainType,unsigned char cChildType,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize);


class MDataProc
{
protected:
	Dll								m_DllHandle;

	tagSpProcFrame_GetDllVersion	*	m_funGetDllVersion;
	tagSpProcFrame_Instance			*	m_funInstance;
	tagSpProcFrame_Release			*	m_funRelease;
	tagSpProcFrame_CompressFrame	*	m_funCompressFrame;
	tagSpProcFrame_ExpandFrame		*	m_funExpandFrame;
public:
	MDataProc();
	~MDataProc();
public:
	int									Instance();
	void								Release();
	tagSpProcFrame_GetDllVersion	*	DGetVerSion();
	tagSpProcFrame_Instance			*	DInstance();
	tagSpProcFrame_Release			*	DRelease();
	tagSpProcFrame_CompressFrame	*	DCompressFrame();
	tagSpProcFrame_ExpandFrame		*	DExpandFrame();
};

#endif//__TRANSRVPLAT_MDATAPROC_H__
////////////////////////This Code AUTO Mount Point By Append////////////

////////////////////////LINUX newline 请在该注释上面加CODE///////////////////

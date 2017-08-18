/*
	
*/
//#include "StdAfx.h"
#include "./MDataProc.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MDataProc::MDataProc()
{
	m_funGetDllVersion = NULL;
	m_funInstance = NULL;
	m_funRelease = NULL;
	m_funCompressFrame = NULL;
	m_funExpandFrame = NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MDataProc::~MDataProc()
{
	Release();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MDataProc::Instance()
{
	std::string					dllpath;

	Release();

	//初始化金融压缩
	dllpath = "./spprocframedll.dll";
	if ( m_DllHandle.LoadDll(dllpath) > 0 )
	{
		m_funGetDllVersion = (tagSpProcFrame_GetDllVersion *)m_DllHandle.GetDllFunction("GetDllVersion");
		m_funInstance = (tagSpProcFrame_Instance *)m_DllHandle.GetDllFunction("Dll_EconomicalCompress_Instance");
		m_funRelease = (tagSpProcFrame_Release *)m_DllHandle.GetDllFunction("Dll_EconomicalCompress_Release");
		m_funCompressFrame = (tagSpProcFrame_CompressFrame *)m_DllHandle.GetDllFunction("Dll_EconomicalCompress_SpCompressFrame");
		m_funExpandFrame = (tagSpProcFrame_ExpandFrame *)m_DllHandle.GetDllFunction("Dll_EconomicalCompress_SpExpandFrame");

		if ( m_funGetDllVersion == NULL || m_funInstance == NULL || m_funRelease == NULL || m_funCompressFrame == NULL || m_funExpandFrame == NULL )
		{
			//映射函数发生错误
			m_funGetDllVersion = NULL;
			m_funInstance = NULL;
			m_funRelease = NULL;
			m_funCompressFrame = NULL;
			m_funExpandFrame = NULL;

			m_DllHandle.CloseDll();

			return -1;
		}

		if ( m_funInstance() < 0 )
		{
			//初始化金融压缩发生错误
			m_funGetDllVersion = NULL;
			m_funInstance = NULL;
			m_funRelease = NULL;
			m_funCompressFrame = NULL;
			m_funExpandFrame = NULL;
			
			m_DllHandle.CloseDll();

			return -2;
		}
	}

	return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MDataProc::Release()
{
	if ( m_funRelease != NULL )
	{
		m_funRelease();
	}
	
	m_funGetDllVersion = NULL;
	m_funInstance = NULL;
	m_funRelease = NULL;
	m_funCompressFrame = NULL;
	m_funExpandFrame = NULL;
	
	m_DllHandle.CloseDll();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
tagSpProcFrame_GetDllVersion * MDataProc::DGetVerSion()
{
	return m_funGetDllVersion;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
tagSpProcFrame_Instance * MDataProc::DInstance()
{
	return m_funInstance;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
tagSpProcFrame_Release * MDataProc::DRelease()
{
	return m_funRelease;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
tagSpProcFrame_CompressFrame * MDataProc::DCompressFrame()
{
	return m_funCompressFrame;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
tagSpProcFrame_ExpandFrame * MDataProc::DExpandFrame()
{
	return m_funExpandFrame;
}

////////////////////////This Code AUTO Mount Point By Append////////////

////////////////////////LINUX newline 请在该注释上面加CODE///////////////////

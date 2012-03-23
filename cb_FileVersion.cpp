// cb_FileVersion.cpp
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#include "stdafx.h"
#include "cb_FileVersion.h"

HRESULT LastError () 
{
	HRESULT hr = HRESULT_FROM_WIN32(GetLastError());
	if (SUCCEEDED(hr))
	{
		return E_FAIL;
	}
	return hr;
}

// This function gets the file version info structure
HRESULT cb_GetFileVersion(LPCTSTR szFilename, VS_FIXEDFILEINFO *pFileInfo)
{
	DWORD dwHandle;
	DWORD dwVerSize = GetFileVersionInfoSize(szFilename, &dwHandle);
	if (dwVerSize == 0)
	{
		return LastError();
	}
	char* pVer = new char[dwVerSize];
	BOOL bRet = GetFileVersionInfo(szFilename, dwHandle, dwVerSize, pVer);
	if (!bRet)
	{
		return LastError();
	}
	UINT uLen;
	void *pBuf;
	bRet = VerQueryValue(pVer, _T("\\"), &pBuf, &uLen);
	if (!bRet)
	{
		return LastError();
	}
	memcpy(pFileInfo, pBuf, sizeof(VS_FIXEDFILEINFO));
	delete[] pVer;
	return S_OK;
}

CString cb_GetFileVersionString(HINSTANCE hInstance)
{
	CString sFileName;
	DWORD dwRet;
	dwRet = GetModuleFileName(hInstance, sFileName.GetBuffer(_MAX_PATH), _MAX_PATH);
	VS_FIXEDFILEINFO FileInfo;
	if ( SUCCEEDED(cb_GetFileVersion(sFileName, &FileInfo)) )
	{
		DWORD dwMajor, dwMinor, dwBeta, dwBuild;
		dwMajor = HIWORD(FileInfo.dwFileVersionMS);
		dwMinor = LOWORD(FileInfo.dwFileVersionMS);
		dwBeta = HIWORD(FileInfo.dwFileVersionLS);
		dwBuild = LOWORD(FileInfo.dwFileVersionLS);
		sFileName.Format(_T("%d.%d.%d.%d"), dwMajor, dwMinor, dwBeta, dwBuild);
	}
	return sFileName;
}

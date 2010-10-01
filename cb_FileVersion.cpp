
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
	CString sVersionString = _T("0.0 Beta");
	DWORD dwRet;
	dwRet = GetModuleFileName(hInstance, sFileName.GetBuffer(_MAX_PATH), _MAX_PATH);
	VS_FIXEDFILEINFO FileInfo;
	if ( SUCCEEDED(cb_GetFileVersion(sFileName, &FileInfo)) )
	{
		DWORD dwMajor, dwMinor, dwBeta, dwBuild;
		CString sBeta = _T("");
		dwMajor = HIWORD(FileInfo.dwFileVersionMS);
		dwMinor = LOWORD(FileInfo.dwFileVersionMS);
		dwBeta = HIWORD(FileInfo.dwFileVersionLS);
		dwBuild = LOWORD(FileInfo.dwFileVersionLS);
		if ( dwBeta > 0 )
		{
			sBeta.Format(_T(" - Beta %d (Build %d)"), dwBeta, dwBuild);
		}
		sFileName.Format(_T("%d.%02d%s"), dwMajor, dwMinor, sBeta);
	}
	return sFileName;
}

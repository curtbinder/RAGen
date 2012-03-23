// cb_FileOperations.cpp
//

/*
 * Copyright (c) 2011-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#include "stdafx.h"
#include "cb_FileOperations.h"

BOOL cb_IsDirectory(LPCTSTR sDir)
{
	BOOL fRet = FALSE;
	DWORD dwAttrib;

	dwAttrib = GetFileAttributes(sDir);

	if ( (dwAttrib & FILE_ATTRIBUTE_DIRECTORY) &&
		 (dwAttrib != INVALID_FILE_ATTRIBUTES) )
	{
		fRet = TRUE;
	}

	return fRet;
}

BOOL cb_IsFolderWritable(LPCTSTR sFolder)
{
	BOOL bRet = FALSE;
	CString sTestFile = sFolder;

	// check if there is a trailing backslash
	if ( sTestFile.GetAt(sTestFile.GetLength()-1) != '\\' )
	{
		sTestFile.AppendChar('\\');
	}
	sTestFile += _T("test.txt");

	TRACE("Test file ready to go:  %s\n", sTestFile);

	TRY
	{
		CFile f(sTestFile, CFile::modeCreate|CFile::modeReadWrite);
		CString s = _T("Testing...test one, test two.\n");
		f.Write(&s, s.GetLength());
		f.Close();
		if ( ! DeleteFile(sTestFile) )
		{
			TRACE("Error deleting test file\n");
			AfxThrowUserException();
		}
		bRet = TRUE;
	}
	CATCH_ALL(e)
	{
		TCHAR szError[MAX_PATH];
		e->GetErrorMessage(szError, MAX_PATH);
		TRACE("Error testing file:  %s\n", szError);
	}
	END_CATCH_ALL

	return bRet;
}

BOOL cb_DoesFileExist(LPCTSTR sFile)
{
	BOOL fRet = FALSE;
	DWORD dwAttrib;

	dwAttrib = GetFileAttributes(sFile);
	if ( ! (dwAttrib == INVALID_FILE_ATTRIBUTES) )
	{
		fRet = TRUE;
	}
	return fRet;
}

BOOL cb_DoesArduinoExist(LPCTSTR sDir)
{
	BOOL fRet = FALSE;
	CString s = sDir;
	if ( s.GetAt(s.GetLength()-1) != '\\' )
	{
		s.AppendChar('\\');
	}
	s += _T("arduino.exe");
	if ( cb_DoesFileExist(s) )
	{
		fRet = TRUE;
	}
	return fRet;
}

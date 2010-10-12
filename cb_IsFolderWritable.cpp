
#include "stdafx.h"
#include "cb_IsFolderWritable.h"

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

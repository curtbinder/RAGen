
#include "stdafx.h"
#include "Resource.h"
#include "RAGen.h"
#include "GlobalVars.h"
#include "Controller.h"

// Global Functions
CString ReadLibraryVersion(CString sLibraryDirectory)
{
	CString sVersion = _T("");
	CString sCompleteFile = _T("");
	CString sLibraryHeader;
	sLibraryHeader.Format(_T("%s\\ReefAngel\\ReefAngel.h"), sLibraryDirectory);
	sCompleteFile = ReadEntireFile(sLibraryHeader);
	/*
	Search for #define
	when found, look at the previous 2 chars
		if they are //, then we ignore the #define line and move on
		if they are a space, tab, \r\n, then we process the define statement
	process the #define
		grab the chars between spaces and save the text
		if the text requires a parameter, then read the parameter in
	*/
	BOOL fFound = FALSE;
	int pos = 0;
	int npos = 0;
	CString sTokenString;
	sTokenString.LoadString(IDS_NEWLINE);
	CString sWhiteSpace;
	sWhiteSpace.LoadString(IDS_WHITESPACE);
	CString sCRLF;
	sCRLF.LoadString(IDS_CRLF);
	CString token;
	CString token2;
	token = sCompleteFile.Tokenize(sTokenString, pos);
	while ( token != _T("") && !fFound )
	{
		// process token
		token.TrimLeft(sWhiteSpace);
		token.TrimRight(sCRLF);
		// split the line up into spaces if it begins with #define
		if ( token.Left(7) == _T("#define") )
		{
			token = token.Mid(7);
			// have a define line
			npos = 0;
			int count = 0;
			CString ptoken = _T("");
			token2 = token.Tokenize(sWhiteSpace, npos);
			while ( token2 != _T("") )
			{
				TRACE("t:  '%s'\n", token2);
				count++;
				if ( count == 1 )
				{
					// carry token over and look for next token in line
					ptoken = token2;
				} else 
				{
					if ( count == 2 )
					{
						// found additional information
						if ( ptoken.Compare(_T("ReefAngel_Version")) == 0 )
						{
							// we have the correct define, let's save the version
							sVersion = token2;
							fFound = true;
							break;
						}
					}
				}
				token2 = token.Tokenize(sWhiteSpace, npos);
			}
		}
		token = sCompleteFile.Tokenize(sTokenString, pos);
	}

	// we have the version, so we are done
	sVersion.Trim(_T("\""));
	return sVersion;
}

CString ReadEntireFile(CString sFile)
{
	CString sCompleteFile = _T("");
	TRY
	{
		CFile f;
		if ( ! f.Open(sFile, CFile::modeRead | CFile::shareDenyWrite) )
		{
			TRACE("Invalid file:  %s\n", sFile);
			return sCompleteFile;
		}
		DWORD dwRead;
		char buf[1024];
		do
		{
			dwRead = f.Read(buf, 1024);
			sCompleteFile.Append(buf, dwRead);
		} while ( dwRead > 0 );
		f.Close();
	}
	CATCH_ALL(e)
	{
		CString sBuffer;
		TCHAR szMsg[255];
		e->GetErrorMessage(szMsg, 255);
		sBuffer.Format(_T("Unable to read file:\n\n"));
		sBuffer += szMsg;
		TRACE("%s", sBuffer);
	}
	END_CATCH_ALL

	return sCompleteFile;
}

BOOL AutodetectDevVersion(CString sLibraryDirectory)
{
	BOOL fRet = FALSE;
	/*
	Read ReefAngel.h file
	Search for #define ReefAngel_Version "VERSION"
	Check for version 0.8.5, 0.9.
	*/
	CString sVersion = ReadLibraryVersion(sLibraryDirectory);
	TRACE("Version:  %s\n", sVersion);
	// let's split the version into tokens and compare the revision
	CString token;
	CString t = _T(".");
	int pos = 0;
	int count = 0;
	token = sVersion.Tokenize(t, pos);
	while ( token != _T("") )
	{
		count++;
		if ( (count == 1) && (token.Compare(_T("0")) != 0) )
		{
			// fail
			break;
		}
		if ( count == 2 )
		{
			if ( token.Compare(_T("8")) == 0 ) 
			{
				// version 8
				TRACE("Version 8\n");
				break;
			} else if ( token.Compare(_T("9")) == 0 )
			{
				// version 9
				TRACE("Version 9\n");
				fRet = TRUE;
				break;
			} else
			{
				// fail
				break;
			}
		}
		if ( count >= 3 ) 
		{
			//if ( token.Compare(_T("5")) == 0 )
			//{
			//	// version 8 rev 5 series, still fails
			//}
			break;
		}

		token = sVersion.Tokenize(t, pos);
	} // while
	return fRet;
}

void LaunchArduino(CString sFilename)
{
	// use CreateProcess function to launch arduino
	// use m_sArduinoFolder + arduino.exe for application
	// use m_sSketchFolder + sketchfilename for PDE file to open
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	TCHAR sPDE[32768];
	CString sFileExtension;

	if ( a_Controller.IsLatestDevVersion() )
	{
		sFileExtension.LoadString(IDS_INO_EXTENSION);
	}
	else
	{
		sFileExtension.LoadString(IDS_PDE_EXTENSION);
	}

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	_stprintf_s(sPDE, 32768, _T("%s\\arduino.exe \"%s\\%s\\%s%s\""), 
			theApp.m_sArduinoDirectory, theApp.m_sSketchDirectory, sFilename, sFilename, sFileExtension);

	if ( ! CreateProcess(NULL, sPDE, NULL, NULL, FALSE,
						0, NULL, theApp.m_sArduinoDirectory,
						&si, &pi) )
	{
		TRACE("Failed to launch arduino.exe\n");
		AfxMessageBox(_T("Failed to launch arduino.exe"), MB_ICONINFORMATION|MB_OK);
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

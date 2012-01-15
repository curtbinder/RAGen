
#include "stdafx.h"
#include "Resource.h"
#include "GlobalVars.h"

// Global Functions
void GetEnabledFeaturesList(Features& fs, CString& s)
{
	s = _T("");
	if ( fs.fDisplayImages )
	{
		s += _T("#define DisplayImages\r\n");
	}
	if ( fs.fSetupExtras )
	{
		s += _T("#define SetupExtras\r\n");
	}
	if ( fs.fDosingPumpSetup && !fs.fDosingIntervalSetup )
	{
		// Only enable if Repeat setup is disabled
		s += _T("#define DosingPumpSetup\r\n");
	}
	if ( fs.fDosingIntervalSetup && fs.fDosingPumpSetup )
	{
		// Only enable if user selected it AND they have chosen a Dosing Pump to be used
		s += _T("#define DosingPumpIntervalSetup\r\n");
	}
	if ( fs.fWavemakerSetup )
	{
		s += _T("#define WavemakerSetup\r\n");
	}
	if ( fs.fOverheatSetup )
	{
		s += _T("#define OverheatSetup\r\n");
	}
	if ( fs.fDateTimeSetup )
	{
		s += _T("#define DateTimeSetup\r\n");
	}
	if ( fs.fVersionMenu )
	{
		s += _T("#define VersionMenu\r\n");
	}
	if ( fs.fATOSetup )
	{
		s += _T("#define ATOSetup\r\n");
	}
	if ( fs.fMetalHalideSetup )
	{
		s += _T("#define MetalHalideSetup\r\n");
	}
	if ( fs.fDirectTempSensor )
	{
		s += _T("#define DirectTempSensor\r\n");
	}
	if ( fs.fDisplayLEDPWM )
	{
		s += _T("#define DisplayLEDPWM\r\n");
	}
	if ( fs.fWifi )
	{
		s += _T("#define wifi\r\n");
	}
	if ( fs.fExpansionModule )
	{
		s += _T("#define RelayExp\r\n");
	}
	if ( fs.fAlternateFont )
	{
		s += _T("#define AlternateFont\r\n");
	}
	if ( fs.fSingleATO )
	{
		s += _T("#define SingleATOSetup\r\n");
	}
	if ( fs.fStandardLightSetup )
	{
		s += _T("#define StandardLightSetup\r\n");
	}
	if ( fs.fRemoveAllLights )
	{
		s += _T("#define RemoveAllLights\r\n");
	}
	if ( fs.fSaveRelayState )
	{
		s += _T("#define SaveRelayState\r\n");
	}
	if ( fs.fWDT )
	{
		s += _T("#define WDT\r\n");
	}
	if ( fs.fCustomMenu )
	{
		s += _T("#define CUSTOM_MENU\r\n");
		CString buf;
		buf.Format(_T("#define CUSTOM_MENU_ENTRIES  %d\r\n"), fs.iCustomMenuEntries);
		s += buf;
	}
	if ( fs.fSimpleMenu )
	{
		s += _T("#define SIMPLE_MENU\r\n");
	}
	if ( fs.fPWMExpansion )
	{
		s += _T("#define PWMEXPANSION\r\n");
	}
	if ( fs.fCustomMain )
	{
		s += _T("#define CUSTOM_MAIN\r\n");
	}
	if ( fs.fColorsPDE )
	{
		s += _T("#define COLORS_PDE\r\n");
	}
	if ( fs.fAtoLogging )
	{
		s += _T("#define ENABLE_ATO_LOGGING\r\n");
	}
	if ( fs.fExceedFlags )
	{
		s += _T("#define ENABLE_EXCEED_FLAGS\r\n");
	}
}

CString ReadLibraryVersion(CString sLibraryHeader)
{
	CString sVersion = _T("");
	CString sCompleteFile = _T("");
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
	CString sFile;
	sFile.Format(_T("%s\\ReefAngel\\ReefAngel.h"), sLibraryDirectory);
	CString sVersion = ReadLibraryVersion(sFile);
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

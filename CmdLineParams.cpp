//
// CmdLineParams.cpp - implementation file
//
// Processes command line

#include "stdafx.h"
#include "CmdLineParams.h"
#include "GlobalVars.h"

CmdLineParams::CmdLineParams()
{
	m_nCount = 0;
	m_iAppMode = NOT_SET;
	m_iSaveReg = NOT_SET;
}

void CmdLineParams::ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL /*bLast*/)
{
	m_nCount++;
	TRACE(_T("Param %d:  %s (%s)\n"), m_nCount, pszParam, bFlag?"Flag":"Param");
	// if bFlag is set, then pszParam has the / or - removed from it
	if ( bFlag )
	{
		if ( strcmp(pszParam, _T("dev")) == 0 )
		{
			m_iAppMode = DEV_MODE;
		}
		if ( strcmp(pszParam, _T("normal")) == 0 )
		{
			m_iAppMode = NORMAL_MODE;
		}
		if ( strcmp(pszParam, _T("prompt")) == 0 )
		{
			m_iSaveReg = PROMPT;
		}
		if ( strcmp(pszParam, _T("never")) == 0 )
		{
			m_iSaveReg = NEVER;
		}
		if ( strcmp(pszParam, _T("always")) == 0 )
		{
			m_iSaveReg = ALWAYS;
		}
		if ( strcmp(pszParam, _T("autodetect")) == 0 )
		{
			m_iDevVersion = AUTODETECT;
		}
		if ( strcmp(pszParam, _T("force08x")) == 0 )
		{
			m_iDevVersion = FORCE_08X;
		}
		if ( strcmp(pszParam, _T("force09x")) == 0 )
		{
			m_iDevVersion = FORCE_09X;
		}
	}
}

// CmdLineParams.h
//
// Processes the command line switches

/*
 * Copyright (c) 2011-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#pragma once

class CmdLineParams : public CCommandLineInfo
{
public:
	CmdLineParams();
	virtual void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast);

	// Flag checks
	int TotalParams() { return m_nCount; }
	int GetAppMode() { return m_iAppMode; }
	int GetSaveRegMode() { return m_iSaveReg; }
	int GetDevVersionMode() { return m_iDevVersion; }

protected:
	int m_nCount;

	int m_iAppMode;
	int m_iSaveReg;
	int m_iDevVersion;

	// consider adding in other switches/parameters
};
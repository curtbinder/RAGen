// cb_BrowseFolder.cpp
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#include "stdafx.h"
#include "cb_BrowseFolder.h"

BOOL cb_BrowseFolder(HWND hWnd, LPTSTR szFolder, LPCTSTR szTitle, TCHAR szPath[])
{
	BOOL bRet = FALSE;
	BROWSEINFO bi_BrowseInfo = {0};
	LPITEMIDLIST pid_Folder = NULL;

	TRY
	{
		// fill the browseinfo struct
		bi_BrowseInfo.hwndOwner = hWnd;
		bi_BrowseInfo.pidlRoot = NULL;
		bi_BrowseInfo.pszDisplayName = szFolder;
		bi_BrowseInfo.lpszTitle = szTitle;
		bi_BrowseInfo.ulFlags = 0;
		bi_BrowseInfo.lpfn = NULL;
		bi_BrowseInfo.lParam = NULL;
		bi_BrowseInfo.iImage = NULL;

		TRACE("Browsing for folder\n");
		pid_Folder = SHBrowseForFolder(&bi_BrowseInfo);
		if ( ! pid_Folder )
		{
			// Cancel was pressed, so exit
			TRACE("Cancel pressed.\n");
			AfxThrowUserException();
		}

		// gotta get the folder
		ZeroMemory(szPath, MAX_PATH*sizeof(TCHAR));
		if ( ! SHGetPathFromIDList(pid_Folder, szPath) )
		{
			// failed to get path
			TRACE("Failed to get full path\n");
			AfxMessageBox(_T("Unable to get selected path.  Please choose another folder.\n"));
			AfxThrowUserException();
		}

		// now we need to fill the location box with the chosen path
		TRACE("Selected '%s' folder.\n", szPath);
		bRet = TRUE;
	}
	CATCH_ALL(e)
	{
		bRet = FALSE;
	}
	END_CATCH_ALL

	return bRet;
}

// cb_FileVersion.h
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#pragma once

HRESULT cb_GetFileVersion(LPCTSTR szFilename, VS_FIXEDFILEINFO *pFileInfo);
CString cb_GetFileVersionString(HINSTANCE hInstance);
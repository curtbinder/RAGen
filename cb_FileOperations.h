// cb_FileOperations.h
//

/*
 * Copyright (c) 2011-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#pragma once

BOOL cb_IsDirectory(LPCTSTR sDir);
BOOL cb_IsFolderWritable(LPCTSTR sFolder);
BOOL cb_DoesFileExist(LPCTSTR sFile);
BOOL cb_DoesArduinoExist(LPCTSTR sDir);
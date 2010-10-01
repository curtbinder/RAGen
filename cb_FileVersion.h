
#pragma once

HRESULT cb_GetFileVersion(LPCTSTR szFilename, VS_FIXEDFILEINFO *pFileInfo);
CString cb_GetFileVersionString(HINSTANCE hInstance);
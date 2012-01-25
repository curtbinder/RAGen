//
// GlobalVars.h
//

#pragma once

enum _Prompt {
	NOT_SET = -1,
	ALWAYS,
	PROMPT,
	NEVER,
};

enum _AppMode {
	NORMAL_MODE,
	DEV_MODE,
};

enum _DevLibVersion {
	AUTODETECT,
	FORCE_08X,
	FORCE_09X,
};

CString ReadLibraryVersion(CString sLibraryDirectory);
CString ReadEntireFile(CString sFile);
BOOL AutodetectDevVersion(CString sLibraryDirectory);

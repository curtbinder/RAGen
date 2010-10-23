//
// GlobalVars.h
//

#pragma once

enum _SaveReg {
	NOT_SET = -1,
	ALWAYS_SAVE,
	PROMPT_SAVE,
	NEVER_SAVE,
};

enum _AppMode {
	NORMAL_MODE,
	DEV_MODE,
};
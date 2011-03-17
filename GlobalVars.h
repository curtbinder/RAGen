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

// Features structure, update this if you change (add/remove) any of the features in the RAFeaturesPage class
typedef struct _Features {
	BOOL fDisplayImages;
	BOOL fSetupExtras;
	BOOL fDosingPumpSetup;
	BOOL fWavemakerSetup;
	BOOL fOverheatSetup;
	BOOL fDateTimeSetup;
	BOOL fVersionMenu;
	BOOL fATOSetup;
	BOOL fMetalHalideSetup;
	BOOL fDirectTempSensor;
	BOOL fDisplayLEDPWM;
	BOOL fWifi;
	BOOL fAlternateFont;
	BOOL fSingleATO;
	BOOL fStandardLightSetup;
	BOOL fRemoveAllLights;
	BOOL fSaveRelayState;
	BOOL fExpansionModule;
	BOOL fDosingIntervalSetup;
} Features;

void GetEnabledFeaturesList(Features& fs, CString& s);
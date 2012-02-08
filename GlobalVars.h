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

/*! Reef Angel device structure
 *
 * Contains the device ID (ID of the checkbox) and the ReefAngel function name
 * associated with the device
 */
// TODO move to Relay.h when migration is completed
typedef struct _device {
	int id;   //!< ID of the check box
	CString sRAFunction;  //!< Function name only, no ReefAngel or parentheses
} device;

/*!
 * Maximum ports for the controller
 */
#define MAX_PORTS					8
/*! 
 * Maximum devices to choose from
 */
#define MAX_DEVICES					14
//! Default ports toggled during Feeding mode, 10110000
#define DEFAULT_FEEDINGMODE			176
//! Default ports toggled during Water Change mode, 10110000
#define DEFAULT_WATERCHANGEMODE		176
//! Default ports shutoff when Overheat is triggered, 00000100
#define DEFAULT_OVERHEAT			4
//! Default ports toggled during lights on/lights off, 00000110
#define DEFAULT_LIGHTSON			6
//! Default Port 1 device is Dual ATO
#define DEFAULT_PORT1_DEVICE		IDC_RELAY_CK_DUALATO
//! Default Port 2 device is Standard Lights
#define DEFAULT_PORT2_DEVICE		IDC_RELAY_CK_STDLIGHTS
//! Default Port 3 device is Metal Halides
#define DEFAULT_PORT3_DEVICE		IDC_RELAY_CK_METALHALIDES
//! Default Port 4 device is Fan/Chiller
#define DEFAULT_PORT4_DEVICE		IDC_RELAY_CK_CHILLER
//! Default Port 5 device is Wavemaker 1
#define DEFAULT_PORT5_DEVICE		IDC_RELAY_CK_WM1
//! Default Port 6 device is Wavemaker 2
#define DEFAULT_PORT6_DEVICE		IDC_RELAY_CK_WM2
//! Default Port 7 device is Heater
#define DEFAULT_PORT7_DEVICE		IDC_RELAY_CK_HEATER
//! Default Port 8 device is Sump/Always On
#define DEFAULT_PORT8_DEVICE		IDC_RELAY_CK_ALWAYS_ON

CString ReadLibraryVersion(CString sLibraryDirectory);
CString ReadEntireFile(CString sFile);
BOOL AutodetectDevVersion(CString sLibraryDirectory);
void LaunchArduino(CString sFilename);

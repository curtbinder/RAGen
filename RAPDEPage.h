#pragma once

#include "GlobalVars.h"

/*! Reef Angel device structure
 *
 * Contains the device ID (ID of the checkbox) and the ReefAngel function name
 * associated with the device
 */
/*
typedef struct _device {
	int id;   //!< ID of the check box
	CString sRAFunction;  //!< Function name only, no ReefAngel or parentheses
} device;
*/

/*!
 * Maximum ports for the controller
 */
//#define MAX_PORTS					8
/*! 
 * Maximum devices to choose from
 */
/*
#define MAX_DEVICES					14
//! Default ports toggled during Feeding mode, 10011000
#define DEFAULT_FEEDINGMODE			152
//! Default ports toggled during Water Change mode, 10011000
#define DEFAULT_WATERCHANGEMODE		152
//! Default ports shutoff when Overheat is triggered, 00000100
#define DEFAULT_OVERHEAT			4
//! Default ports toggled during lights on/lights off, 00000110
#define DEFAULT_LIGHTSON			6
//! Default Port 1 device is Dual ATO
#define DEFAULT_PORT1_DEVICE		IDC_PDE_CK_DUALATO
//! Default Port 2 device is Standard Lights
#define DEFAULT_PORT2_DEVICE		IDC_PDE_CK_STDLIGHTS
//! Default Port 3 device is Metal Halides
#define DEFAULT_PORT3_DEVICE		IDC_PDE_CK_METALHALIDES
//! Default Port 4 device is Fan/Chiller
#define DEFAULT_PORT4_DEVICE		IDC_PDE_CK_CHILLER
//! Default Port 5 device is Wavemaker 1
#define DEFAULT_PORT5_DEVICE		IDC_PDE_CK_WM1
//! Default Port 6 device is Wavemaker 2
#define DEFAULT_PORT6_DEVICE		IDC_PDE_CK_WM2
//! Default Port 7 device is Heater
#define DEFAULT_PORT7_DEVICE		IDC_PDE_CK_HEATER
//! Default Port 8 device is Sump/Always On
#define DEFAULT_PORT8_DEVICE		IDC_PDE_CK_ALWAYS_ON
*/

// RAPDEPage dialog
/*! RAPDEPage Dialog class
 *
 * Contains all the operations for the program
 */
class RAPDEPage : public CDialog
{
	DECLARE_DYNAMIC(RAPDEPage)

public:
	RAPDEPage(CWnd* pParent = NULL);
	virtual ~RAPDEPage();

// Dialog Data
	enum { IDD = IDD_RAPDEPAGE };

	CString sFilename;  //!< Filename of the PDE file generated
	CString sFileExtension;

protected:
	//! DDX/DDV Data Exchange between controls and variables
	virtual void DoDataExchange(CDataExchange* pDX);


// Implementation
protected:
	int Ports[MAX_PORTS]; //!< Array of Ports
	int Delays[MAX_PORTS];  //!< Array of Delays for Delayed on
	device Devices[MAX_DEVICES];  //!< Array of Devices, 13 main devices and 1 device labeled Not Used

	//! Enum of the different byte arrays
	enum Modes {
		Feeding,  //!< Feeding Mode ports
		WaterChange, //!< WaterChange Mode ports
		Overheat,  //!< Overheat ports
		LightsOn  //!< LightsOn ports
	};
	// Ports that get toggled on/off in specified modes
	BYTE FeedingModePorts;  //!< Ports toggled during Feeding Mode
	BYTE WaterChangeModePorts;  //!< Ports toggled during Water Change Mode
	BYTE OverheatPorts;  //!< Ports that get shutoff during Overheat
	BYTE LightsOnPorts;  //!< Ports toggled during lights on/off

	BOOL fTemp;  //!< Temperature flag, 0 - Fahrenheit, 1 - Celcuis
	BOOL fBanner;  //!< Web banner mode flag, 0 - no banner / logging, 1 - web banner enabled
	int bCurrentPort;  //!< Currently selected Port
	CString sFeatureList;  //!< List of features enabled when PDE generated
	BOOL fUseDPRepeat;  //!< Do we use DosingPumpRepeat instead of DosingPump
	BOOL fCustomMenu;  //!< Is the CustomMenu enabled?
	int iCustomMenuEntries;  //!< Number of CustomMenuEntries
	BOOL fCustomMain;	//!< Is the CustomMain screen enabled?
	BOOL fColorsPDE;	//!< Are we using CustomColors?

	// Single use devices
	BOOL fWM1;  //!< Flag for determining if WM1 is selected
	BOOL fWM2;  //!< Flag for determining if WM2 is selected
	BOOL fDP1;  //!< Flag for determining if DP1 is selected
	BOOL fDP2;  //!< Flag for determining if DP2 is selected
	BOOL fDualATO;  //!< Flag for determining if Dual ATO is selected
	BOOL fSingleATOLow;  //!< Flag for determining if Single ATO Low switch is selected
	BOOL fSingleATOHigh;  //!< Flag for determining if Single ATO High switch is selected

	//! Initializes the dialog box
	virtual BOOL OnInitDialog();
	//! Message Map Macros for processing Windows Messages
	DECLARE_MESSAGE_MAP()
	/*! Writes the PDE file
	 *
	 * Generates the PDE file based on the selections made.  The file name is autogenerated
	 * and is in the format RA_MMDDYY_HHMM.(pde|ino).  The file is placed in the default directory
	 * selected in the settings dialog.
	 *
	 * \retval BOOL True if successfully created PDE file, FALSE otherwise
	 */
	BOOL WritePDE();
	//! Initialize the values of the variables for the Ports
	void InitPorts();
	/*! Loads the default values for everything
	 *
	 * \sa InitPorts(), LoadDefaultPortDevices(), SetPortMode()
	 */
	void LoadDefaults();
	/*! Initializes the Devices variable
	 *
	 * Functions will be stored as
     *
	 * FUNCTION
	 *
	 * The ReefAngel.XXX(PORT); will be added after the function call.  We just store the 
	 * function names and not the class name or parenthesis afterwards.
	 * The ID for the window/item is also stored for comparison.
	 */
	void LoadDeviceFunctions();
	/*! Creates the Binary string for the mode
	 *
	 * The mode (Feeding, WaterChange, Overheat, Lights On) is created in a binary string
	 * for use in generation of the PDE file so the controller knows what ports to toggle
	 * during the appropriate mode.
	 *
	 * \param Mode ID of the mode to generate (Feeding, WaterChange, Overheat, Lights On)
	 * \param sMode CString that contains the finalized binary string
	 */
	void GetPortMode(BYTE Mode, CString &sMode);
	/*! Sets the mode based on the specified ports
	 *
	 * Stores the ports to the corresponding port mode member varialbe.
	 *
	 * \sa UpdateDisplayPorts()
	 * \param Mode ID of the mode to generate (Feeding, WaterChange, Overheat, Lights On)
	 * \param Ports the ports that are toggled during the appropriate mode
	 */
	void SetPortMode(BYTE Mode, BYTE Ports);
	/*! Updates the display check boxes for the specified mode
	 *
	 * \param Mode ID of the mode to generate (Feeding, WaterChange, Overheat, Lights On)
	 */
	void UpdateDisplayPorts(BYTE Mode);
	/*! Refreshes the port modes based on check boxes
	 *
	 * Updates the member variables for all 4 of the modes based on the check boxes
	 * on the display.
	 */
	void RefreshModePorts();
	/*! Assigns the specified device to the specified port
	 *
	 * Stores the Device (check box id) in the Ports array assigned to the port.
	 *
	 * \sa UpdateDisplayDevice()
	 * \param Port Port number to be used
	 * \param Device Device ID to be stored
	 * \param Delay Delay in minutes to be stored for DelayedOn
	 */
	void SetPortDevice(int Port, int Device, int Delay = 0);
	/*! Retrieves the device associated with the port
	 *
	 * \param Port Port number to retrieve
	 * \retval int Device ID associated with the port
	 */
	int GetPortDevice(int Port);
	/*! Updates the device list for the specified port
	 *
	 * Updates the device list based on the port provided.  This is called when the port
	 * is switched.  Calls the appropriate functions to checked/uncheck 
	 * and enabled/disabled devices appropriately.
	 *
	 * \sa GetPortDevice(), ToggleDeviceChecks(), UpdateDeviceAvailability()
	 * \param Port Port number being switched to
	 */
	void UpdateDisplayDevice(int Port);
	/*! Updates the device list by enabling/disabling appropriate devices
	 *
	 * Calls ToggleDeviceFlag to toggle the single device flags appropriately based on
	 * the selected devices.  Also enables/disables the devices based on the logic
	 * in IsDeviceCkEnabled function.
	 *
	 * \sa IsDeviceCkEnabled(), ToggleDeviceFlag()
	 */
	void UpdateDeviceAvailability();
	/*! Checks if the single use device is to be enabled or disabled
	 *
	 * Determines if the device is to be enabled or disabled based on a specified logic.
	 * The single use device flags are updated first.
	 * The single use devices have corresponding opposite devices.  The pairs are as follows:
	 * - Wavemaker 1 or Dosing Pump 1
	 * - Wavemaker 2 or Dosing Pump 2
	 * - Dual ATO or Single ATO's
	 *
	 * The logic for determining this is as follows:
	 * - Disable if opposite device is selected
	 * - Disable if device is enabled on another port
	 * - Enable is device is selected on current port
	 * - Enable if device not selected at all
	 *
	 * The ATO ports requires additional checks and only uses the last 3 rules.
	 * - if Dual enabled, disable both single ports
	 * - if Single enabled
	 *		- Disable Dual
	 *		- Check Single Low and Single High independently of each other (no opposite devices)
	 *
	 * \sa ToggleDeviceFlag()
	 * \param Device ID of the device
	 * \param fDevFlag Boolean flag for the current device
	 * \param fOppDevFlag Boolean flag for the opposite device
	 * \retval BOOL True if the device is enabled, FALSE otherwise
	 */
	BOOL IsDeviceCkEnabled(int Device, BOOL fDevFlag, BOOL fOppDevFlag);
	/*! Updates the check boxes for the devices
	 *
	 * Handles updating the check boxes based on the device to be checked.  Checks the 
	 * specified device, unchecks the other devices and toggles the device flags as 
	 * needed.
	 *
	 * \sa ToggleDeviceFlag()
	 * \param Device ID of the device to be checked
	 */
	void ToggleDeviceChecks(int Device);
	/*! Toggles the single use device flag
	 *
	 * \param Device ID of the device
	 * \param fValue Value to be assigned to the flag, defaults to TRUE
	 */
	void ToggleDeviceFlag(int Device, BOOL fValue = TRUE);
	/*! Assigns the default devices to the ports
	 *
	 * Resets the devices back to the default port assignments.  Simulates a button press
	 * for Port1 and checks Port1 while unchecking the other port.
	 *
	 * \sa SetPortDevice()
	 */
	void LoadDefaultPortDevices();
	/*! Looks up the ReefAngel Function associated with the device
	 *
	 * \param Device ID of the device
	 * \param sFunction string that contains the ReefAngel function call
	 */
	void LookupDeviceFunction(int Device, CString &sFunction);
	void SaveSettings();
	void LoadSettings();
	void SelectPort1();
	void MenuRemoveUnusedFeatures(/*Features& fs*/);

public:
	void UpdatePDEFeatures(/*Features& fs*/);
	/*! Generate Button Press
	 * \sa WritePDE()
	 */
	void OnBnClickedBtnGenerate();
	/*! Edit Menu, Settings selection
	 * 
	 * Launches Settings Dialog box
	 */
	//afx_msg void OnEditSettings();
	/*! Edit Menu, Reset All selection
	 *
	 * Resets all the values to the default
	 * - Ports
	 * - Temperature
	 * - All Modes (FeedingMode, WaterChangeMode, Overheat, LightsOn)
	 * \sa LoadDefaults()
	 */
	void OnResetAll();
	void OnResetSaved();
	/*! Edit Menu, Reset Ports selection
	 *
	 * Resets all the Ports to their default 
	 * \sa InitPorts(), LoadDefaultPortDevices()
	 */
	void OnResetPorts();
	/*! Edit Menu, Reset Temperature selection
	 *
	 * Resets the temperature selection to default
	 */
	void OnResetTemperature();
	/*! Edit Menu, Reset Logging selection
	 *
	 * Resets the logging selection to default
	 */
	void OnResetLogging();
	/*! Edit Menu, Reset Feeding Mode selection
	 *
	 * Resets the FeedingModePorts to default
	 * \sa SetPortMode()
	 */
	void OnResetFeedingMode();
	/*! Edit Menu, Reset Water Change Mode selection
	 *
	 * Resets the WaterChangeModePorts to default
	 * \sa SetPortMode()
	 */
	void OnResetWaterChangeMode();
	/*! Edit Menu, Reset Overheat selection
	 *
	 * Resets the OverheatPorts to default
	 * \sa SetPortMode()
	 */
	void OnResetOverheat();
	/*! Edit Menu, Reset Lights On selection
	 *
	 * Resets the LightsOnPorts to default
	 * \sa SetPortMode()
	 */
	void OnResetLightsOn();
	/*! Port1 Button Press
	 * \sa UpdateDisplayDevice()
	 */
	afx_msg void OnBnClickedPort1();
	/*! Port2 Button Press
	 * \sa UpdateDisplayDevice()
	 */
	afx_msg void OnBnClickedPort2();
	/*! Port3 Button Press
	 * \sa UpdateDisplayDevice()
	 */
	afx_msg void OnBnClickedPort3();
	/*! Port4 Button Press
	 * \sa UpdateDisplayDevice()
	 */
	afx_msg void OnBnClickedPort4();
	/*! Port5 Button Press
	 * \sa UpdateDisplayDevice()
	 */
	afx_msg void OnBnClickedPort5();
	/*! Port6 Button Press
	 * \sa UpdateDisplayDevice()
	 */
	afx_msg void OnBnClickedPort6();
	/*! Port7 Button Press
	 * \sa UpdateDisplayDevice()
	 */
	afx_msg void OnBnClickedPort7();
	/*! Port8 Button Press
	 * \sa UpdateDisplayDevice()
	 */
	afx_msg void OnBnClickedPort8();
	/*! Wavemaker1 CheckBox Press
	 * \sa SetPortDevice()
	 */
	afx_msg void OnBnClickedCkWm1();
	/*! Wavemaker2 CheckBox Press
	 * \sa SetPortDevice()
	 */
	afx_msg void OnBnClickedCkWm2();
	/*! DosingPump1 CheckBox Press
	 * \sa SetPortDevice()
	 */
	afx_msg void OnBnClickedCkDp1();
	/*! DosingPump2 CheckBox Press
	 * \sa SetPortDevice()
	 */
	afx_msg void OnBnClickedCkDp2();
	/*! DualATO CheckBox Press
	 * \sa SetPortDevice()
	 */
	afx_msg void OnBnClickedCkDualato();
	/*! SingleATOLow CheckBox Press
	 * \sa SetPortDevice()
	 */
	afx_msg void OnBnClickedCkSingleatolow();
	/*! SingleATOHigh CheckBox Press
	 * \sa SetPortDevice()
	 */
	afx_msg void OnBnClickedCkSingleatohigh();
	/*! AlwaysOn CheckBox Press
	 * \sa SetPortDevice()
	 */
	afx_msg void OnBnClickedCkAlwaysOn();
	/*! MetalHalides CheckBox Press
	 * \sa SetPortDevice()
	 */
	afx_msg void OnBnClickedCkMetalhalides();
	/*! StandardLights CheckBox Press
	 * \sa SetPortDevice()
	 */
	afx_msg void OnBnClickedCkStdlights();
	/*! Heater CheckBox Press
	 * \sa SetPortDevice()
	 */
	afx_msg void OnBnClickedCkHeater();
	/*! Chiller CheckBox Press
	 * \sa SetPortDevice()
	 */
	afx_msg void OnBnClickedCkChiller();
	/*! NotUsed CheckBox Press
	 * \sa SetPortDevice()
	 */
	afx_msg void OnBnClickedCkNotused();
	/*! DelayedOn CheckBox Press
	 * \sa SetPortDevice()
	 */
	afx_msg void OnBnClickedCkDelayedOn();
	afx_msg void OnEnChangePdeEditDelayOn();
};

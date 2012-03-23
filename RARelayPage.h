// RARelayPage.h
//

/*
 * Copyright (c) 2011-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#pragma once

#include "GlobalVars.h"

// RARelayPage dialog
/*! RARelayPage Dialog class
 *
 * Contains all the operations for the program
 */
class RARelayPage : public CDialog
{
	DECLARE_DYNAMIC(RARelayPage)

public:
	RARelayPage(CWnd* pParent = NULL);
	virtual ~RARelayPage();

// Dialog Data
	enum { IDD = IDD_RARELAYPAGE };

protected:
	//! DDX/DDV Data Exchange between controls and variables
	virtual void DoDataExchange(CDataExchange* pDX);


// Implementation
protected:
	int bCurrentPort;  //!< Currently selected Port
	CString sFeatureList;  //!< List of features enabled when PDE generated
	BOOL fUseDPRepeat;  //!< Do we use DosingPumpRepeat instead of DosingPump

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

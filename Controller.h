#pragma once

#include "GlobalVars.h"
#include "Features.h"
#include "Relay.h"

class CController
{
public:
	CController(void);
	~CController(void);

	inline void EnablePortal(BOOL fEnable = TRUE) { m_fPortal = fEnable; }
	inline BOOL IsPortalEnabled() { return m_fPortal; }
	inline void SetTemperatureUnit(BOOL fEnableCelsius) { m_fTemp = fEnableCelsius; }
	inline void SetCelsius() { m_fTemp = TRUE; }
	inline void SetFahrenheit() { m_fTemp = FALSE; }
	inline BOOL IsCelsius() { return m_fTemp; }
	inline CString GetFilename() { return m_sFilename; }
	inline CString GetExtension() { return m_sExtension; }
	inline void SetDevLibVersion(int iVersion) { m_iDevVersion = iVersion; }
	inline int GetDevLibVersion() { return m_iDevVersion; }
	inline BOOL IsLatestDevVersion() { return m_fLatestDev; }
	inline void AddPWMSlope(BOOL fEnable = TRUE) { m_fAddPWMSlope = fEnable; }
	/*
	inline CString GetWifiUsername() { return m_sWifiUsername; }
	inline CString GetWifiPassword() { return m_sWifiPassword; }
	void SetWifiUP(CString sUser, CString sPassword);
	CString GetWifiString();
	*/
	BOOL WriteFile();
	CString LookupDeviceFunction(int Device);
	void AutodetectVersion(CString sLibraryFolder);

	CFeatures Features;
	CRelay Relay;
	// CCustomMenu
	// CCustomMain
	
	device Devices[MAX_DEVICES];  //!< Array of Devices, 13 main devices and 1 device labeled Not Used

private:
	CString m_sFilename;
	CString m_sExtension;
	BOOL m_fPortal;
	BOOL m_fTemp;
	//BOOL m_fWifiPassordEnabled;
	int m_iDevVersion;  //!< 0 - autodetect, 1 - force 0.8.x, 2 - force 0.9.x or later
	BOOL m_fLatestDev;
	BOOL m_fAddPWMSlope;
	//CString m_sWifiUsername;
	//CString m_sWifiPassword;

	void LoadDeviceFunctions();
	void GenerateFilename(CTime &t);
	void GenerateHeader(CFile &f, CTime &t);
	void WriteIncludes(CFile &f);
	void WriteCustomMenu(CFile &f);
	void WriteCustomMain(CFile &f);
	void WriteSetup(CFile &f);
	void WriteLoop(CFile &f);

};

extern CController a_Controller;
#pragma once

#include "GlobalVars.h"
#include "Features.h"
#include "Relay.h"

class CController
{
public:
	CController(void);
	~CController(void);

	inline void EnableBanner(BOOL fEnable = TRUE) { m_fBanner = fEnable; }
	inline BOOL IsWebBannerEnabled() { return m_fBanner; }
	inline void SetTemperatureUnit(BOOL fEnableCelsius) { m_fTemp = fEnableCelsius; }
	inline void SetCelsius() { m_fTemp = TRUE; }
	inline void SetFahrenheit() { m_fTemp = FALSE; }
	inline BOOL IsCelsius() { return m_fTemp; }
	inline CString GetFilename() { return m_sFilename; }
	inline CString GetExtension() { return m_sExtension; }
	BOOL WriteFile();
	void LookupDeviceFunction(int Device, CString &sFunction);

	CFeatures Features;
	CRelay Relay;
	
	device Devices[MAX_DEVICES];  //!< Array of Devices, 13 main devices and 1 device labeled Not Used

private:
	CString m_sFilename;
	CString m_sExtension;
	BOOL m_fBanner;
	BOOL m_fTemp;
	//BOOL m_fWifiPassordEnabled;

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
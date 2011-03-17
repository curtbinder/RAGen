
#include "stdafx.h"
#include "GlobalVars.h"

// Global Functions
void GetEnabledFeaturesList(Features& fs, CString& s)
{
	s = _T("");
	if ( fs.fDisplayImages )
	{
		s += _T("#define DisplayImages\r\n");
	}
	if ( fs.fSetupExtras )
	{
		s += _T("#define SetupExtras\r\n");
	}
	if ( fs.fDosingPumpSetup && !fs.fDosingIntervalSetup )
	{
		// Only enable if Repeat setup is disabled
		s += _T("#define DosingPumpSetup\r\n");
	}
	if ( fs.fDosingIntervalSetup && fs.fDosingPumpSetup )
	{
		// Only enable if user selected it AND they have chosen a Dosing Pump to be used
		s += _T("#define DosingPumpIntervalSetup\r\n");
	}
	if ( fs.fWavemakerSetup )
	{
		s += _T("#define WavemakerSetup\r\n");
	}
	if ( fs.fOverheatSetup )
	{
		s += _T("#define OverheatSetup\r\n");
	}
	if ( fs.fDateTimeSetup )
	{
		s += _T("#define DateTimeSetup\r\n");
	}
	if ( fs.fVersionMenu )
	{
		s += _T("#define VersionMenu\r\n");
	}
	if ( fs.fATOSetup )
	{
		s += _T("#define ATOSetup\r\n");
	}
	if ( fs.fMetalHalideSetup )
	{
		s += _T("#define MetalHalideSetup\r\n");
	}
	if ( fs.fDirectTempSensor )
	{
		s += _T("#define DirectTempSensor\r\n");
	}
	if ( fs.fDisplayLEDPWM )
	{
		s += _T("#define DisplayLEDPWM\r\n");
	}
	if ( fs.fWifi )
	{
		s += _T("#define wifi\r\n");
	}
	if ( fs.fExpansionModule )
	{
		s += _T("#define RelayExp\r\n");
	}
	if ( fs.fAlternateFont )
	{
		s += _T("#define AlternateFont\r\n");
	}
	if ( fs.fSingleATO )
	{
		s += _T("#define SingleATOSetup\r\n");
	}
	if ( fs.fStandardLightSetup )
	{
		s += _T("#define StandardLightSetup\r\n");
	}
	if ( fs.fRemoveAllLights )
	{
		s += _T("#define RemoveAllLights\r\n");
	}
	if ( fs.fSaveRelayState )
	{
		s += _T("#define SaveRelayState\r\n");
	}
}

#pragma once

#include "GlobalVars.h"
#include "InternalMemoryDefaults.h"



class CRelay
{
public:
	CRelay(void);
	CRelay(int expansion);
	~CRelay(void);

	//! Enum of the different byte arrays
	enum Modes {
		Feeding,  //!< Feeding Mode ports
		WaterChange, //!< WaterChange Mode ports
		Overheat,  //!< Overheat ports
		LightsOn  //!< LightsOn ports
	};

	BOOL IsPortAlwaysOn(int port);
	BOOL IsPortNotUsed(int port);
	BOOL IsPortDelayedOn(int port);
	int GetPortDelay(int port);
	void SetPortDelay(int port, int delay);
	// TODO update based on what expansion relay device
	CString GetPortMode(BYTE mode);  // returns complete string "ReefAngel.PORTSMODE = ports;"
	CString GetPortModeText(BYTE mode);
	BYTE GetPortModes(BYTE mode);
	void SetPortMode(BYTE mode, BYTE Ports);
	void SetPortDevice(int Port, int Device, int Delay = DEFAULT_DELAY_MINUTES);
	int GetPortDevice(int Port);
	void ResetPortModes();
	void ResetPortDevices();

private:
	int m_iRelayDevice;  // What relay device are we? 0 - main, 1 - 8 - expansion relays
	int Ports[MAX_PORTS]; //!< Array of Ports
	int Delays[MAX_PORTS];  //!< Array of Delays for Delayed on

	// Ports that get toggled on/off in specified modes
	BYTE FeedingModePorts;  //!< Ports toggled during Feeding Mode
	BYTE WaterChangeModePorts;  //!< Ports toggled during Water Change Mode
	BYTE OverheatPorts;  //!< Ports that get shutoff during Overheat
	BYTE LightsOnPorts;  //!< Ports toggled during lights on/off

	void InitPorts();
};

#include "StdAfx.h"
#include "Resource.h"
#include "Relay.h"
#include "InternalMemoryDefaults.h"

CRelay::CRelay(void)
{
	CRelay(0);
}

CRelay::CRelay(int expansion)
{
	m_iRelayDevice = expansion;
	InitPorts();
}

CRelay::~CRelay(void)
{
}

BOOL CRelay::IsPortAlwaysOn(int port)
{
	return (Ports[port] == IDC_RELAY_CK_ALWAYS_ON);
}

BOOL CRelay::IsPortNotUsed(int port)
{
	return (Ports[port] == IDC_RELAY_CK_NOTUSED);
}

BOOL CRelay::IsPortDelayedOn(int port)
{
	return (Ports[port] == IDC_RELAY_CK_DELAYON);
}

int CRelay::GetPortDelay(int port)
{
	return Delays[port-1];
}

void CRelay::SetPortDelay(int port, int delay)
{
	Delays[port-1] = delay;
}

CString CRelay::GetPortMode(BYTE mode)
{
	return _T("");
}

BYTE CRelay::GetPortModes(BYTE mode)
{
	BYTE ports;
	switch ( mode )
	{
	default:
	case Feeding:
		ports = FeedingModePorts;
		break;
	case WaterChange:
		ports = WaterChangeModePorts;
		break;
	case Overheat:
		ports = OverheatPorts;
		break;
	case LightsOn:
		ports = LightsOnPorts;
		break;
	}
	return ports;
}

void CRelay::SetPortMode(BYTE mode, BYTE Ports)
{
	switch ( mode )
	{
	case Feeding:
		FeedingModePorts = Ports;
		break;
	case WaterChange:
		WaterChangeModePorts = Ports;
		break;
	case Overheat:
		OverheatPorts = Ports;
		break;
	case LightsOn:
		LightsOnPorts = Ports;
		break;
	default:
		return;
		break;
	}
}

void CRelay::SetPortDevice(int Port, int Device, int Delay /*= DEFAULT_DELAY_MINUTES*/)
{
	Ports[Port-1] = Device;
	if ( Delay > 0 )
	{
		Delays[Port-1] = Delay;
	}
}

int CRelay::GetPortDevice(int Port)
{
	return Ports[Port-1];
}

void CRelay::ResetPortModes()
{
	FeedingModePorts = DEFAULT_FEEDINGMODE;
	WaterChangeModePorts = DEFAULT_WATERCHANGEMODE;
	OverheatPorts = DEFAULT_OVERHEAT;
	LightsOnPorts = DEFAULT_LIGHTSON;
}

void CRelay::ResetPortDevices()
{
	SetPortDevice(1, DEFAULT_PORT1_DEVICE, DEFAULT_DELAY_MINUTES);
	SetPortDevice(2, DEFAULT_PORT2_DEVICE, DEFAULT_DELAY_MINUTES);
	SetPortDevice(3, DEFAULT_PORT3_DEVICE, DEFAULT_DELAY_MINUTES);
	SetPortDevice(4, DEFAULT_PORT4_DEVICE, DEFAULT_DELAY_MINUTES);
	SetPortDevice(5, DEFAULT_PORT5_DEVICE, DEFAULT_DELAY_MINUTES);
	SetPortDevice(6, DEFAULT_PORT6_DEVICE, DEFAULT_DELAY_MINUTES);
	SetPortDevice(7, DEFAULT_PORT7_DEVICE, DEFAULT_DELAY_MINUTES);
	SetPortDevice(8, DEFAULT_PORT8_DEVICE, DEFAULT_DELAY_MINUTES);
}

void CRelay::InitPorts()
{
	// blank out the ports first before we populate them
	for ( int i = 0; i < MAX_PORTS; i++ )
	{
		Ports[i] = 0;
		Delays[i] = DEFAULT_DELAY_MINUTES;
	}
}
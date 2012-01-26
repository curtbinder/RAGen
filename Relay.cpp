#include "StdAfx.h"
#include "Resource.h"
#include "Relay.h"
#include "InternalMemoryDefaults.h"

CRelay::CRelay(void)
{
	m_iRelayDevice = 0;
}

CRelay::CRelay(int expansion)
{
	m_iRelayDevice = expansion;
}

CRelay::~CRelay(void)
{
}

BOOL CRelay::IsPortAlwaysOn(int port)
{
	return (Ports[port] == IDC_PDE_CK_ALWAYS_ON);
}

BOOL CRelay::IsPortNotUsed(int port)
{
	return (Ports[port] == IDC_PDE_CK_NOTUSED);
}

BOOL CRelay::IsPortDelayedOn(int port)
{
	return (Ports[port] == IDC_PDE_CK_DELAYON);
}

int CRelay::GetPortDelay(int port)
{
	return Delays[port];
}

CString CRelay::GetPortMode(BYTE mode)
{
	return _T("");
}

void CRelay::SetPortDevice(int Port, int Device, int Delay /*= 0*/)
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

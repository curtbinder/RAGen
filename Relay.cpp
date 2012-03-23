// Relay.cpp
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

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
	CString s;
	BYTE ports;
	switch ( mode )
	{
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
	default:
		return _T("0");
		break;
	}
	BYTE v = 0;
	for (int i = 0; i < MAX_PORTS; i++, v++ )
	{
		if ( ports & (1<<v) )
		{
			s.Insert(0, _T("1"));
		}
		else
		{
			s.Insert(0, _T("0"));
		}
	}
	s.Insert(0, _T("B"));
	return s;
}

CString CRelay::GetPortModeText(BYTE mode)
{
	CString s;
	BYTE ports;
	switch ( mode )
	{
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
	default:
		return _T("0");
		break;
	}
	BYTE v = 0;
	s = _T("");
	CString s1;
	int count = 0;
	for (int i = 0; i < MAX_PORTS; i++, v++ )
	{
		if ( ports & (1<<v) )
		{
			//s.Insert(0, _T("1"));
			s1.Format(_T("Port%dBit"), v+1);
			if ( count > 0 )
			{
				s.Append(_T(" | "));
			}
			s.Append(s1);
			count++;
		}
	}
	if ( s.IsEmpty() )
	{
		s = _T("0");
	}
	return s;
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
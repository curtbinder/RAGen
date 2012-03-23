// ComPortFunctions.h
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#pragma once

typedef struct _Port {
	int iPort;
	BOOL fHasRA;
	BOOL fOptiboot;
} Port;

BOOL TestPort(int nCom, int nBaudRate = CBR_115200);
BOOL OpenPort(int nCom);
BOOL ConfigureComPort();
BOOL SendCommand();
BOOL ReadData();
BOOL GetPorts(Port p[], int &count, BOOL fGetCountOnly);
BOOL FillPortsArray(Port p[]);
int CountPorts();

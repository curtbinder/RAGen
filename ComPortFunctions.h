
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

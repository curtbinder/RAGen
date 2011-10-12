//
// ComPortFunctions.cpp - Contains relevant COM Port functions
//

#include "stdafx.h"
#include "ComPortFunctions.h"

HANDLE g_hCom = NULL;
BYTE g_1S = 0x30;  // first byte to send
BYTE g_2S = 0x20;  // second byte to send
BYTE g_1R = 0x14;  // first byte to receive
BYTE g_2R = 0x10;  // second byte to receive
int g_iComTimeout = 5;
int g_iBaudRate = CBR_115200;


BOOL TestPort(int nCom, int nBaudRate /*= CBR_115200*/)
{
    BOOL fRet = FALSE;

	if ( nBaudRate == CBR_115200 )
	{
		// didn't pass in a value, so they wanted 115
		if ( g_iBaudRate != CBR_115200 )
		{
			// make sure that the baudrate is equal
			g_iBaudRate = CBR_115200;
		}
	}
	else
	{
		// user passed in a specific baudrate, so let's use it
		g_iBaudRate = nBaudRate;
	}

    if ( g_hCom )
    {
        CloseHandle(g_hCom);
        g_hCom = NULL;
    }

    TRACE(_T("Testing COM%d\n"), nCom);

    try
    {
        TRACE(_T("(COM%d): Opening port\n"), nCom);
        if ( ! OpenPort(nCom) )
        {
            TRACE(_T("(COM%d): Failed to open port\n"), nCom);
            throw;
        }

        if ( g_hCom )
        {
            CloseHandle(g_hCom);
            TRACE(_T("(COM%d): Closing port\n"), nCom);
            g_hCom = NULL;
        }

        TRACE(_T("(COM%d): Opening port (again)\n"), nCom);
        if ( ! OpenPort(nCom) )
        {
            TRACE(_T("(COM%d): Failed to open port (again)\n"), nCom);
            throw;
        }

        Sleep(1000);
        // We have a good com port, now let's see if it's a valid RA Controller
        TRACE(_T("(COM%d): Sending command (0x%02X, 0x%02X)\n"), nCom, g_1S, g_2S);
        if ( ! SendCommand() )
        {
            TRACE(_T("(COM%d Failed to send command\n"), nCom);
            throw;
        }

        TRACE(_T("(COM%d): Reading response, expecting (0x%02X, 0x%02X)\n"), nCom, g_1R, g_2R);
        if ( ReadData() )
        {
            // we got the proper response
            fRet = TRUE;
            TRACE(_T("(COM%d): Valid response\n"), nCom);
        }
    }
    catch(...)
    {
        fRet = FALSE;
    }

    // extra sanity check to make sure that the port is closed
    if ( g_hCom )
    {
        CloseHandle(g_hCom);
        g_hCom = NULL;
    }

    return fRet;
}

BOOL OpenPort(int nCom)
{
    TCHAR szPortName[32];
    _stprintf_s(szPortName, 32, _T("\\\\.\\COM%d"), nCom);
    g_hCom = CreateFile(szPortName,
                        GENERIC_WRITE | GENERIC_READ,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        0,
                        NULL);

    if ( (g_hCom == NULL) || (g_hCom == INVALID_HANDLE_VALUE) )
    {
        // port is not valid
        TRACE(_T("(COM%d): Invalid COM port\n"), nCom);
        return FALSE;
    }

    TRACE(_T("(COM%d): Testing COM state\n"), nCom);
    if ( ! ConfigureComPort() )
    {
        if ( g_hCom )
        {
            CloseHandle(g_hCom);
            g_hCom = NULL;
        }
        TRACE(_T("(COM%d): Failed to test COM port\n"), nCom);
        return FALSE;
    }
    TRACE(_T("(COM%d): Opened\n"), nCom);
    return TRUE;
}

BOOL ConfigureComPort()
{
    DCB dcb;
    // prep the serial port for communication
    ZeroMemory(&dcb, sizeof(dcb));
    TRACE(_T("       - Getting COM state\n"));
    if ( ! GetCommState(g_hCom, &dcb) )
    {
        TRACE(_T("       - Failed getting COM state\n"));
        return FALSE;
    }

    // configure the com port values
    dcb.BaudRate	= g_iBaudRate;
    dcb.ByteSize	= 8;
    dcb.Parity	    = NOPARITY;
    dcb.StopBits	= ONESTOPBIT;

    TRACE(_T("       - Updating COM state\n"));
    if ( ! SetCommState(g_hCom, &dcb) )
    {
        TRACE(_T("       - Failed setting COM state\n"));
        return FALSE;
    }

    COMMTIMEOUTS ct;
    ZeroMemory(&ct, sizeof(ct));
    ct.ReadIntervalTimeout = MAXDWORD;
    ct.ReadTotalTimeoutMultiplier = MAXDWORD;
    ct.ReadTotalTimeoutConstant = g_iComTimeout * 1000;
    TRACE(_T("       - Setting %d second COM timeout\n"), g_iComTimeout);
    if ( ! SetCommTimeouts(g_hCom, &ct) )
    {
        TRACE(_T("       - Failed setting COM timeout\n"));
        return FALSE;
    }

    // valid com port
    return TRUE;
}

BOOL SendCommand()
{
	BYTE buf[2];
	buf[0] = g_1S;
	buf[1] = g_2S;
	DWORD dwBytesWritten;
	if ( ! WriteFile(g_hCom,
					 buf,
					 sizeof(buf),
					 &dwBytesWritten,
					 0) )
	{
		return FALSE;
	}
    return TRUE;
}

BOOL ReadData()
{
	BYTE buf[2] = {0, 0};
	BYTE b;
	DWORD dwBytesRead;
	DWORD dwTotalBytes = 0;
	BOOL fDone = FALSE;
    int pos = 0;
    BOOL fRet = FALSE;

    do
    {
        if ( ReadFile(g_hCom, &b, sizeof(b), &dwBytesRead, NULL) )
        {
            if ( dwBytesRead > 0 )
            {
                dwTotalBytes += dwBytesRead;
                TRACE(_T("       - Read (0x%02X)\n"), b);
                buf[pos] = b;
                pos++;
            }
            else if ( dwBytesRead == 0 )
            {
                // EOF
                TRACE(_T("       - Read NULL\n"));
                fDone = TRUE;
            }
        }
        else
        {
            TRACE(_T("       - Error Reading (%ld)\n"), GetLastError());
            fDone = TRUE;
        }
        if ( dwTotalBytes == 2 )
        {
            fDone = TRUE;
        }
    } while ( ! fDone );

    if ( (buf[0] == g_1R) && (buf[1] == g_2R) )
    {
        // valid RA response
        fRet = TRUE;
    }
    return fRet;
}

BOOL GetPorts(Port p[], int &count, BOOL fGetCountOnly)
{
    BOOL fRet = FALSE;
    TCHAR buf[65535];
    unsigned long dwChars = QueryDosDevice(NULL, buf, sizeof(buf));
    int x = 0;

    if ( dwChars == 0 )
    {
        TRACE(_T("Error with querydosdevice:  (%ld)\n"), GetLastError());
        fRet = FALSE;
    }
    else
    {
        TCHAR *ptr = buf;
		int port;
        while (dwChars)
        {
            if ( _stscanf_s(ptr, "COM%d", &port) == 1 )
            {
				if ( ! fGetCountOnly )
				{
					p[x].iPort = port;
					p[x].fHasRA = FALSE;
				}
                x++;
            }
            TCHAR *temp_ptr = strchr(ptr,0);
            dwChars -= (DWORD)((temp_ptr-ptr)/sizeof(TCHAR)+1);
            ptr = temp_ptr+1;
        }  // while
        fRet = TRUE;
		if ( fGetCountOnly )
		{
			count = x;
		}
    }

    return fRet;
}

BOOL FillPortsArray(Port p[])
{
	int count = 0;
	return GetPorts(p, count, FALSE);
}

int CountPorts()
{
	int count = 0;
	GetPorts(NULL, count, TRUE);
	return count;
}

/*******************************************************************************
 *
 *  FindAppUART.cpp - PC command line utility for enumerating MSP430 EVM's
 *                    Application UARTs.
 *
 *  Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

//------------------------------------------------------------------------------
// Desc: PC command line utility for enumerating MSP430 EVM's Application UARTs.
//       The application returns the COM port number of the first UART that is
//       found. If this is successful the error code is set to '0'. In case of
//       the UART string could not be determined '1' is returned.
//
//       The code was developed with the Express Edition of Visual C++ 2008
//       http://www.microsoft.com/express/
//
// Ver.: 0.1 (February 2011)
//       - Alpha version
//
// Auth: Andreas Dannenberg
//       MSP430 Applications
//       Texas Instruments, Inc.
//------------------------------------------------------------------------------

// Windows Header Files
#define WIN32_LEAN_AND_MEAN						// Exclude rarely-used stuff
                                                // from Windows headers
#include <windows.h>
#include <tchar.h>
#include <shellapi.h>
#include <setupapi.h>							// "setupapi.lib" must be linked
    											// to the project
// C Runtime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

//------------------------------------------------------------------------------
// DWORD WINAPI EnumComPorts(DWORD dwIndex, LPTSTR lptszName,
//      DWORD dwNumOfElements)
//
// User-mode code fragment to identify attached VCP COMnn port[s] with a
// specific device instance ID based on USB VID and PID and returns the COMnn
// port that the OS embeds into the device instance ID. When called with
// dwIndex = 0, the function will enumerate all COMPORT class devices and
// return the name of the first one that was found. Subsequent calls using an
// incremented dwIndex parameter can be performed until ERROR_NO_MORE_ITEMS
// is returned.
//
// IN:  dwIndex               COMPORT class device # 0, 1, 2, ... to check
//      dwNumOfElements       The size of the lptszName buffer
// OUT: lptszName             COMnn name of given device #
//      return()              ERROR_SUCCESS - lpszName is valid
//                            ERROR_NO_MORE_ITEMS - End of device list reached
//------------------------------------------------------------------------------
DWORD WINAPI EnumComPorts(DWORD dwIndex, LPTSTR lptszName, DWORD dwNumOfElements)
{
    HDEVINFO hDevInfo;
    SP_DEVINFO_DATA DeviceInfoData;
    DWORD i;
    TCHAR *pcParse;

    // Create a HDEVINFO with all present devices
    hDevInfo = SetupDiGetClassDevs(
                    NULL,
                    0, // Enumerator
                    0,
                    DIGCF_PRESENT | DIGCF_ALLCLASSES);
    
    if (INVALID_HANDLE_VALUE == hDevInfo)
    {
        return GetLastError();
    }
    
    // Enumerate through all devices in set
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    for (i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)
    {
        LPTSTR buffer     = NULL;
        DWORD  buffersize = 0;

        // Get the device instance ID that is associated with the device information element
        while (!SetupDiGetDeviceInstanceId(
                    hDevInfo, 
                    &DeviceInfoData, 
                    buffer, 
                    buffersize, 
                    &buffersize))
        {
            if (buffer)
            {
               LocalFree(buffer);
            }
                
            if (ERROR_INSUFFICIENT_BUFFER == GetLastError())
            {
                // Change the buffer size. Double the size to avoid problems on
                // W2K MBCS systems per KB 888609.
                buffer = (LPTSTR)LocalAlloc(LPTR, buffersize * 2);
            }
            else
            {
                // Error: could not get device instance ID
                // Cleanup and return error code
                SetupDiDestroyDeviceInfoList(hDevInfo);
                return GetLastError();
            }
        }

        if (buffer)
        {
            // Look for the "Application UART" of common MSP430 EVMs. The application UART
            // has an USB VID of 0x0451 (Texas Instruments) and an PID of 0xF432.
			const TCHAR testval[] = _T("USB\\VID_0451&PID_F432&MI_00");

			if (NULL != _tcsstr(buffer, testval))
            {
				TCHAR szFriendlyName[MAX_PATH];
			    
				if (SetupDiGetDeviceRegistryProperty(
					hDevInfo,
					&DeviceInfoData,
					SPDRP_FRIENDLYNAME,
					NULL,
					(PBYTE)szFriendlyName,
					sizeof(szFriendlyName) - 1,
					NULL))
				{
                    // Check if we have reached the dwIndex-th element, if not keep looking
                    if (dwIndex == 0)
                    {
                        // Find pointer to "COM" substring (secure)
                        szFriendlyName[sizeof(szFriendlyName) - 1] = 0x00;
                        pcParse = _tcsstr(szFriendlyName, _T("COM"));

                        if (pcParse != NULL)
                        {
                            // Zero-terminate COM port string after last digit
                            if (!isdigit(pcParse[4])) {
                                pcParse[4] = 0;
                            }
                            else if (!isdigit(pcParse[5])) {
                                pcParse[5] = 0;
                            }
                            else {
                                pcParse[6] = 0;
                            }

                            // Pass string to the return parameter
                            _tcscpy_s(lptszName, dwNumOfElements, pcParse);

                            // Cleanup
                            SetupDiDestroyDeviceInfoList(hDevInfo);

                            return ERROR_SUCCESS;
                        }
                    }
                    else
                    {
                        dwIndex--;
                    }
				}
			}
		}
    }
   
    //  Cleanup
    SetupDiDestroyDeviceInfoList(hDevInfo);
    
    return ERROR_NO_MORE_ITEMS;
}

//------------------------------------------------------------------------------
// Main application entry point. Simply return the first Application UART
// COM port that was found to STDOUT.
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    TCHAR szDeviceName[MAX_PATH];
    DWORD dwReturnValue;

    dwReturnValue = EnumComPorts(0, szDeviceName, _countof(szDeviceName));

    if (dwReturnValue == ERROR_SUCCESS) {
        _ftprintf_s(stdout, _T("%s\r\n"), szDeviceName);
        return 0;
    }

	return 1;
}

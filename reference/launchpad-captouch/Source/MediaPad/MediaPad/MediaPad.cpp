/*******************************************************************************
 *
 *  MediaPad.cpp - PC demo application for establishing a serial connection
 *                 with the LaunchPad CapTouch BoosterPack.
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
 *
 ******************************************************************************/

//------------------------------------------------------------------------------
// Desc: PC demo application for establishing a serial connection with the
//       LaunchPad CapTouch BoosterPack. It receives capacitive touch button
//		 presses and capacitive wheel gestures that are captured and trasmitted
//       by the MSP430, and uses this to simulate virtual keystrokes to control 
//		 windows media. The program will not open a window; instead it will place 
//		 a small icon into the taskbar notification area.
//       To exit the program, right-click on the icon, and then select "Exit".
//
//       The code was developed with the Express Edition of Visual C++ 2010
//       http://www.microsoft.com/express/
//
// Ver.: 1.00 (February 2011)
//       - Initial Release
//
// Auth: Dung Dang
//       MSP430 Applications
//       Texas Instruments Inc.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "MediaPad.h"
#include "time.h"
//------------------------------------------------------------------------------
// Misc definitions
//------------------------------------------------------------------------------
#define MAX_LOADSTRING          100
#define WM_USER_SHELLICON       WM_USER         // Custom message for systray icon
#define MAX_COM_SEARCH_INDEX    100             // Max COM # to check

//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------
HWND hWnd;                                      // Current window handle
HINSTANCE hInst;                                // Current instance
HMENU hPopMenu;                                 // Handle to the systray menu
TCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];            // The main window class name
TCHAR szApplicationToolTip[MAX_LOADSTRING];     // Notification area icon tool tip
NOTIFYICONDATA nidApp;

//------------------------------------------------------------------------------
// Globals used for communication
//------------------------------------------------------------------------------
HANDLE hCom;                                    // Handle for COM port
OVERLAPPED OverlappedIn = { 0, 0, 0, 0, 0 };    // For ASYNC I/O operations
OVERLAPPED OverlappedOut = { 0, 0, 0, 0, 0 };   // For ASYNC I/O operations
BYTE COMBuffer[100];                            // Holds RX data from COM port

//------------------------------------------------------------------------------
// Application variables
//------------------------------------------------------------------------------
BYTE lastWheelPosition=255, errorDetected=0;         
INT wheelPositionCounter=0, initialWheelTouch=0, wheelPosistionRegistered=255 ;
clock_t  thisUartEvent, lastUartEvent=0; //, timeBegin, timeEnd, timeInitialTouch;
UCHAR uart0, uart1;

//------------------------------------------------------------------------------
// Forward declarations of functions included in this code module
//------------------------------------------------------------------------------
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

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
// void CALLBACK FileIOCompletionRoutine(DWORD dwErrorCode,
//   DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
//
// IN:  dwErrorCode
//      dwNumberOfBytesTransfered
//      lpOverlapped
//      hCom
//      COMBuffer[]
// OUT: COMBuffer[]
//------------------------------------------------------------------------------
#define WAKE_UP_UART_CODE       0xBE
#define WAKE_UP_UART_CODE2      0xEF
#define SLEEP_MODE_UART_CODE    0xDE
#define SLEEP_MODE_UART_CODE2   0xAD
#define MIDDLE_BUTTON_CODE      0x80

#define INVALID_GESTURE         0xFD
#define GESTURE_START           0xFC
#define GESTURE_STOP            0xFB
#define COUNTER_CLOCKWISE       1
#define CLOCKWISE               2
#define GESTURE_POSITION_OFFSET 0x20
#define WHEEL_POSITION_OFFSET   0x30

void CALLBACK FileIOCompletionRoutine(DWORD dwErrorCode,
    DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
{
	static BYTE previousPresses[100], pressIndex=0, tempIndex, resetWheelPosition;



    // Data received?
    if (dwErrorCode == 0 && dwNumberOfBytesTransfered)
    {
		// Always reset wheel position, unless a wheel position	packet is sent	
		resetWheelPosition = 1;
		thisUartEvent = clock() * 1000 / CLOCKS_PER_SEC ;
		if (errorDetected)
		{
            // Try to recover from 1-byte out of sync error
			uart0 = uart1;
			uart1 = COMBuffer[0];
			errorDetected = 0;
		}
		else
		{
			uart0 = COMBuffer[0];
			uart1 = COMBuffer[1];
		}

		switch (uart0)
		{
		    case WAKE_UP_UART_CODE: 
			    if (uart1 != WAKE_UP_UART_CODE2) 
				    errorDetected = 1;			    
			    break;
		    case SLEEP_MODE_UART_CODE: 
			    if (uart1 != SLEEP_MODE_UART_CODE2) 
				    errorDetected = 1;			
			    break;
		    case MIDDLE_BUTTON_CODE: 
			    if (uart1 != MIDDLE_BUTTON_CODE) 
					errorDetected = 1;			    
			    else
				    keybd_event(VK_LAUNCH_MEDIA_SELECT, 0, 0, 0);
			    break;

		    case GESTURE_START:
			    if ((uart1 < GESTURE_POSITION_OFFSET) || (uart1 > GESTURE_POSITION_OFFSET + 0x0F))	
				    errorDetected = 1;
	
			    break;

		    case GESTURE_STOP:
			    if (uart1 != GESTURE_STOP)			  
				    errorDetected = 1;			    
			    break;

		    default:
			    // Process wheel position
			    if ((uart0>= WHEEL_POSITION_OFFSET) && (uart0 <=WHEEL_POSITION_OFFSET + 0x0F))
			    {  
				    if (uart1 != uart0)		
					    errorDetected = 1;				    
				    else				
				    {						
						resetWheelPosition = 0;							
					    uart0 -= WHEEL_POSITION_OFFSET;
						if ( (uart0 != lastWheelPosition) || (thisUartEvent - lastUartEvent  > 1000))
							wheelPositionCounter = 1;
						
						else						
							if (++wheelPositionCounter == 2)
								wheelPositionCounter = 0;
						
						lastWheelPosition = uart0;
     				    if (wheelPositionCounter == 0)
							{					
							    switch (uart0)
							    {
							    case 15 : case 0  : case 1  : /*Insert your own command */ break;
							    case 3  : case 4  : case 5  : keybd_event(VK_MEDIA_NEXT_TRACK, 0, 0, 0); break;
							    case 7  : case 8  : case 9  : keybd_event(VK_MEDIA_PLAY_PAUSE  , 0, 0, 0); break;
							    case 11 : case 12 : case 13 : keybd_event(VK_MEDIA_PREV_TRACK, 0, 0, 0); break;
						
							    }
							}
						
					}
			    }
			    else if ((uart0 >= 0) && (uart0 <= 0x1F))   // Process gesture 
			    {
				    if ((uart1<GESTURE_POSITION_OFFSET) || (uart1>GESTURE_POSITION_OFFSET + 0x0F))				
					    errorDetected = 1;				    
				    else
				    {
					    if (uart0 >= 0x10)
					    {
						    uart0 -= 0x10;
						    while (uart0-->0)
							    keybd_event(VK_VOLUME_DOWN, 0, 0, 0);  
					    }
					    else
						    while (uart0-->0)
							    keybd_event(VK_VOLUME_UP, 0, 0, 0);
				    }
			    }
			    else
				    errorDetected = 1;			    
	    }
		if ( resetWheelPosition == 1)
			lastWheelPosition = 255;
    }

    // Initiate next overlapped read operation
	lastUartEvent = thisUartEvent; 
    ReadFileEx(hCom, COMBuffer, 2, lpOverlapped, FileIOCompletionRoutine);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
    // Application related local variables
    MSG msg;
    HACCEL hAccelTable;
    TCHAR Text[100 + MAX_PATH];

    // COM related local variables
    DWORD dwIndex;
    TCHAR szDeviceName[MAX_PATH];
    TCHAR ComPort[20];
    DWORD dwReturnValue;
    DCB dcb;                                    // COM device-control block
    COMMTIMEOUTS CommTimeouts;                  // COM timeout structure

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_430BOOST_CAPTOUCH_MEDIAPAD, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization
    if (!InitInstance(hInstance, nCmdShow))
    {
        MessageBox(NULL,
            _T("An error occured during application init!\r\n") \
            _T("Press OK to exit program."),
            _T("430Boost-CapTouch MediaControl Error Dialog"),
            MB_OK | MB_ICONEXCLAMATION);
        return 1;                               // Exit program
    }

    // Scan through all COM port class devices in the system and
    // check for a friendly name / HW ID match with the MSP-EXP430F5438
    // demo board. COM devices from 0 to MAX_COM_SEARCH_INDEX
    // are scanned.
    for (dwIndex = 0; dwIndex < MAX_COM_SEARCH_INDEX; dwIndex++)
    {
        dwReturnValue = EnumComPorts(dwIndex, szDeviceName, _countof(szDeviceName));
		

        if (dwReturnValue == ERROR_SUCCESS)
        {
            break;                                    // COM port found!
        }
        else if (dwReturnValue == ERROR_NO_MORE_ITEMS)
        {
            MessageBox(hWnd,
                _T("MSP430G2-LaunchPad not found!\r\n") \
                _T("Double-check LaunchPad USB driver installation and connections.\r\n\r\n") \
                _T("Press OK to exit program."),
                _T("430Boost-CapTouch MediaControl Error Dialog"),
                MB_OK | MB_ICONEXCLAMATION);
            Shell_NotifyIcon(NIM_DELETE, &nidApp);    // Remove notification bar icon
            return 1;
        }
        else
        {
           MessageBox(hWnd,
                _T("An error occured during VCP initialization!\r\n") \
                _T("Press OK to exit program."),
                _T("430Boost-CapTouch MediaControl Error Dialog"),
                MB_OK | MB_ICONEXCLAMATION);
            Shell_NotifyIcon(NIM_DELETE, &nidApp);    // Remove notification bar icon
            return 1;
        }
    }

    // COM Interface Initializations
    _tcscpy_s(&ComPort[0], _countof(ComPort), _T("\\\\.\\"));       // Preceed name with "\\.\" to
    _tcscpy_s(&ComPort[4], _countof(ComPort) - 4, szDeviceName);    // access higher # ports

    hCom = CreateFile(ComPort,                  // COM-Port
						
        GENERIC_READ | GENERIC_WRITE,           // read/write-mode
        0,                                      // Open w/ exclusive-access
        NULL,                                   // no security attributes
        OPEN_EXISTING,                          // creation distribution
        FILE_FLAG_OVERLAPPED,                   // Use overlapped I/O
        NULL);                                  // hTemplate must be NULL

    if (hCom == INVALID_HANDLE_VALUE)           // Open successful?
    {
        _stprintf_s(Text, _countof(Text),
            _T("Error opening %s!"), szDeviceName);

        MessageBox(hWnd, Text,
            _T("430Boost-CapTouch MediaControl Error Dialog"),
            MB_OK | MB_ICONEXCLAMATION);
        Shell_NotifyIcon(NIM_DELETE, &nidApp);  // Remove notification bar icon
        return 1;
    }

    if (!GetCommState(hCom, &dcb))              // Read current DCB
    {
        MessageBox(hWnd,
            _T("An error occured during VCP initialization!\r\n") \
            _T("Press OK to exit program."),
            _T("430Boost CapTouch MediaControl Error Dialog"),
            MB_OK | MB_ICONEXCLAMATION);
        CloseHandle(hCom);                      // Close COM ressource
        return 1;                               // Exit program
    }

    dcb.BaudRate        = 9600;               // Set baud rate
    dcb.fBinary         = TRUE;
    dcb.fParity         = FALSE;
    dcb.fOutxCtsFlow    = FALSE;                // Disable flow-control for
    dcb.fOutxDsrFlow    = FALSE;                // working with only 3 lines
    dcb.fDsrSensitivity = FALSE;                // (GND, RXD, TXD)
    dcb.fOutX           = FALSE;
    dcb.fInX            = FALSE;
    dcb.fNull           = FALSE;
    dcb.fRtsControl     = RTS_CONTROL_DISABLE;  // Disable flow control
    dcb.fAbortOnError   = FALSE;
    dcb.ByteSize        = 8;
    dcb.StopBits        = ONESTOPBIT;

    if (!SetCommState(hCom, &dcb))              // Set DCB
    {
        MessageBox(hWnd,
            _T("An error occured during VCP initialization!\r\n") \
            _T("Press OK to exit program."),
            _T("430Boost-CapTouch MediaControl Error Dialog"),
            MB_OK | MB_ICONEXCLAMATION);
        Shell_NotifyIcon(NIM_DELETE, &nidApp);  // Remove notification bar icon
        CloseHandle(hCom);                      // Close COM ressource
        return 1;                               // Exit program
    }

    CommTimeouts.ReadIntervalTimeout         = 0;
    CommTimeouts.ReadTotalTimeoutMultiplier  = 1000;  // Wait 1s per RX char
    CommTimeouts.ReadTotalTimeoutConstant    = 0;
    CommTimeouts.WriteTotalTimeoutMultiplier = 0;
    CommTimeouts.WriteTotalTimeoutConstant   = 0;

    if (!SetCommTimeouts(hCom, &CommTimeouts))  // Set COM timeouts
    {
        MessageBox(hWnd,
            _T("An error occured during VCP initialization!\r\n") \
            _T("Press OK to exit program."),
            _T("430Boost-CapTouch MediaControl Error Dialog"),
            MB_OK | MB_ICONEXCLAMATION);
        Shell_NotifyIcon(NIM_DELETE, &nidApp);  // Remove notification bar icon
        CloseHandle(hCom);                      // Close COM ressource
        return 1;                               // Exit program
    }

    // Initialization sequence all-go. Show the COM port to the user
    // and start the run loop.
    _stprintf_s(Text, sizeof Text / sizeof TCHAR,
        _T("LaunchPad CapTouch found on %s.\r\n") \
        _T("Press OK to minimize the application and start the program."),
        szDeviceName);
    MessageBox(hWnd, Text,
        _T("430Boost-CapTouch MediaControl Dialog"),
        MB_OK | MB_ICONINFORMATION);

    // Activate UART RX functionality
    if (!ReadFileEx(hCom, COMBuffer, 2, &OverlappedIn, FileIOCompletionRoutine))
    {
        MessageBox(hWnd,
            _T("An error occured during VCP initialization!\r\n") \
            _T("Press OK to exit program."),
            _T("430Boost-CapTouch MediaControl Error Dialog"),
            MB_OK | MB_ICONEXCLAMATION);
        Shell_NotifyIcon(NIM_DELETE, &nidApp);  // Remove notification bar icon
        CloseHandle(hCom);                      // Close COM ressource
        return 1;                               // Exit program
    }


    ZeroMemory(&msg, sizeof(msg));

    // Enter the message handling loop
    while (msg.message != WM_QUIT)
    {
        // Wait for any message while staying in an alertable state to
        // process asynchronous I/O.
        MsgWaitForMultipleObjectsEx(0, NULL, INFINITE, QS_ALLINPUT, MWMO_ALERTABLE);

        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    // Application cleanup
    Shell_NotifyIcon(NIM_DELETE, &nidApp);      // Remove notification bar icon
    CloseHandle(hCom);                          // Close COM ressource

    return 0;                                   // Exit application
}

//------------------------------------------------------------------------------
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//------------------------------------------------------------------------------
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_430BOOST_CAPTOUCH_MEDIAPAD));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_430BOOST_CAPTOUCH_MEDIAPAD);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = NULL;

    return RegisterClassEx(&wcex);
}

//------------------------------------------------------------------------------
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//------------------------------------------------------------------------------
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HICON hMainIcon;

   hInst = hInstance;                           // Store instance handle in global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
                                                // Store window handle in global variable

   if (!hWnd)
   {
      return FALSE;
   }

   hMainIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_430BOOST_CAPTOUCH_MEDIAPAD));

   nidApp.cbSize = sizeof(NOTIFYICONDATA);      // Sizeof the struct in bytes
   nidApp.hWnd = (HWND) hWnd;                   // Handle of the window which will process msgs
   nidApp.uID = IDI_430BOOST_CAPTOUCH_MEDIAPAD; // ID of the icon for notification area
   nidApp.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;  // ORing of all the flags
   nidApp.hIcon = hMainIcon;                    // Handle of the icon to be displayed
   nidApp.uCallbackMessage = WM_USER_SHELLICON;
   wcscpy_s(nidApp.szTip, _countof(nidApp.szTip), L"430Boost-CapTouch MediaControl");

   Shell_NotifyIcon(NIM_ADD, &nidApp);

   // The following two lines have been commented out to hide the program
   // main window since we want to use the notification icon only.
   //ShowWindow(hWnd, nCmdShow);
   //UpdateWindow(hWnd);

   return TRUE;
}

//------------------------------------------------------------------------------
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_USER_SHELLICON   - Process the system tray icon
//  WM_COMMAND          - Process the application menu
//  WM_PAINT            - Paint the main window
//  WM_DESTROY          - Post a quit message and return
//------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    POINT lpClickPoint;

    switch (message)
    {
        case WM_USER_SHELLICON:
            switch (LOWORD(lParam))
            {
                case WM_RBUTTONDOWN:
                    GetCursorPos(&lpClickPoint);
                    hPopMenu = CreatePopupMenu();
                    InsertMenu(hPopMenu ,0xffffffff, MF_BYPOSITION | MF_STRING, IDM_ABOUT, _T("About"));
                    InsertMenu(hPopMenu, 0xffffffff, MF_SEPARATOR, IDM_SEP, _T("SEP"));
                    InsertMenu(hPopMenu, 0xffffffff ,MF_BYPOSITION| MF_STRING, IDM_EXIT, _T("Exit"));
                    SetForegroundWindow(hWnd);
                    TrackPopupMenu(hPopMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_BOTTOMALIGN, lpClickPoint.x, lpClickPoint.y, 0, hWnd, NULL);
                    return TRUE;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        case WM_COMMAND:
            wmId    = LOWORD(wParam);
            wmEvent = HIWORD(wParam);

            switch (wmId)                       // Parse the menu selections
            {
                case IDM_ABOUT:
                    // The below line has been commented out since the project's default
                    // dialog box is not used here (the VC++ Express Edition doesn't allow
                    // changing ressource files, therefore a standard MessageBox is used)
                    //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    MessageBox(hWnd,
                        _T("430Boost-CapTouch MediaControl \r\n\r\n") \
                        _T("Uses the MSP430G2-LaunchPad CapTouch BoosterPack  \r\n") \
                        _T("capative touch data to provide key input for the Windows system.\r\n\r\n") \
                        _T("Dung Dang\r\n") \
                        _T("MSP430 Applications\r\n") \
                        _T("Texas Instruments Inc.\r\n") \
                        _T("February 2011"),
                        _T("About 430Boost-CapTouch MediaControl"), MB_ICONINFORMATION | MB_OK);
                    break;
                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code here...
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

//------------------------------------------------------------------------------
// Message handler for about box.
//------------------------------------------------------------------------------
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        case WM_INITDIALOG:
            return (INT_PTR)TRUE;
        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
    }
    return (INT_PTR)FALSE;
}

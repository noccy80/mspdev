-------------------------------MEDIAPAD README----------------------------------
Ver.: 1.00 (February 2011)
- Initial Release
Author: Dung Dang 
MSP430 Applications
Texas Instruments Inc.                  
--------------------------------------------------------------------------------
                
CONTENTS
                
I. DESCRIPTION
II. APPLICATION USAGE
III. PROJECT SOLUTION & FILE CONFIGURATION   
IV. USB SERIAL COM PORT PROTOCOL

I. DESCRIPTION
-----------------------------------

PC demo application for establishing a serial connection with the LaunchPad 
CapTouch BoosterPack. It receives capacitive touch button presses and capacitive
wheel gestures that are captured and transmitted by the MSP430, and uses this 
data to simulate virtual keystrokes to control windows media. The program will 
not open a window; instead it will place a small icon into the taskbar 
notification area.
To exit the program, right-click on the icon, and then select "Exit".

The code was developed with the Express Edition of Visual C++ 2008
http://www.microsoft.com/express/
Big thanks to Andreas Dannenberg for creating the .NET COM Serial port 
auto-detection code. 

II. APPLICATION USAGE 
-----------------------------------

Upon execution, the application starts looking for a LaunchPad or an eZ430 
emulator compatible USB serial COM port. If no compatible COM port is found, 
the application displays an error message which then exits the application.
If a LaunchPad COM port is found, the application prompts a greeting start-up 
message. Once the message is closed, the application minimizes itself to the 
taskbar. The application then executes in background, receiving UART data from
the serial port and translating them into Windows virtual key strokes. 
These keystrokes are determined based on the user capacitive input on the 
LaunchPad CapTouch BoosterPack when the device is in active mode*.

1. Center button press: Start Media Player [Windows Media Player by default]**
2. Bottom arrow button press: Play/Pause
3. Left arrow button press: Previous Track
4. Right arrow button press: Next Track
5. Scroll wheel clockwise: Volume Up
6. Scroll wheel counter-clockwise: Volume Down

*Make sure to wake up device before providing touch inputs. 
Device frequently goes to sleep after inactivity. To wake up, slowly wave hand 
1-2 inch away from the BoosterPack, an LED sequence (slow clockwise, then fast
counter-clockwise) indicates a device wakeup. Only after device fully wakes up,
the capacitive touch inputs can be captured and transmitted to the program.

**Depending on the computer system, opening the Media Player might take some 
time. 

The prorgam's system tray icon provides an About dialog box and an option to 
exit the application.
   
III. PROJECT SOLUTION & FILE CONFIGURATION      
-----------------------------------

PROJECT SOLUTION ROOT - MediaPad
|   430Boost_CapTouchMediaPad.ncb
|   430Boost_CapTouchMediaPad.sln
|   ReadMe.txt
|   
+---[MediaPad]
|   |   MediaPad.cpp
|   |   MediaPad.h
|   |   MediaPad.ico
|   |   MediaPad.rc
|   |   MediaPad.vcproj
|   |   MediaPad.vcproj.ENT.a0271518.user
|   |   ReadMe.txt
|   |   Resource.h
|   |   small.ico
|   |   stdafx.cpp
|   |   stdafx.h
|   |   targetver.h
|   |   
|   \---[Release]
|           
\---[Release]
        430Boost_CapTouchMediaPad.exe      <Executable Program>
        430Boost_CapTouchMediaPad.pdb

Legend: [Directory]     
           |---filename 

IV. USB SERIAL COM PORT PROTOCOL
-----------------------------------

Per each event (wake up, go to sleep, touch/press, or gesture), the LaunchPad 
transmits a 2-byte UART packet, which appears from the USB serial COM port on 
the PC. They are specified as follows.

WAKE UP [due to proximity sensor detection]:      0xBE  0xEF
SLEEP [after period of inactivity]:               0xDE  0xAD
CENTER BUTTON PRESS:                              0x80  0x80
WHEEL POSITION TOUCH/PRESS [z = touch position]:  0x3z  0x3z [z=1 nibble 0x0-F]       
GESTURE START [z = touch position]:               0xFC  0x2z [z=1 nibble 0x0-F]
GESTURE STOP:                                     0xFB  0xFB
GESTURE & GESTURE END POSITION :                  0xGG  0x2z
  GG = [binary] b???????? 
    First bit is direction: 0 = clockwise, 1 = counter-clockwise
    Last 7 bits = count of gesture movement
  z = ending position of the immediate gesture [[z=1 nibble 0x0-F]   
  
The UART receiver can decipher the packets by comparing them against the fixed
values (WAKE UP, SLEEP, CENTER BUTTON PRESS, GESTURE START & STOP) or against 
ranges (WHEEL TOUCH = 0x30-0x3F, GESTURE = 0x00-0x1F, GESTURE POSITION = 
0x20-0x2F)             

MediaPad processes all UART packets and checks for their integrity. However, the
application only uses the inputs from CENTER BUTTON PRESS, WHEEL POSITIONS, and
GESTURES to generate virtual keystrokes. 
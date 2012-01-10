------------MSP430G2-LaunchPad CapTouch BoosterPack User Experience-------------
Ver.: 1.00 Initial Release
February 2011
Dung Dang
MSP430 Applications
Texas Instruments, Inc.
--------------------------------------------------------------------------------

CONTENTS
         
I. DESCRIPTION
II. PROJECT & FILE CONFIGURATION
III. PROJECT IMPORT IN CCS & IAR
IV. CAP TOUCH LIBRARY  
V. TOUCH & GESTURE DEFINITIONS
VI. UART COMMUNICATION PROTOCOL 
VII. HISTORY

I. DESCRIPTION
-----------------------------------

This application operates on the LaunchPad platform using the MSP430G2452
device and the CapTouch BoosterPack plugin board. The capacitive touch and 
proximity sensing are enabled by the pin oscillator feature new to the 
MSP430G2xx2 family devices. The User Experience application also utilizes 
the cap touch library to realize & measure the capacitive touch and proximity
sensors. The cap touch library also provides layers of abstractions to 
generate higher logical outputs such as logical touches, geometry (in this 
hardware, a four-button wheel), and even gestures. 

The User Experience application starts up and remains in 'sleep' mode, 
sampling the proximity sensor every ~8.3ms [VLO/100=12kHz/100=120Hz]. Upon 
registering a valid proximity event [hand/finger/object hovering ~3-5cm from
the BoosterPack], the application wakes up to operate in the 'active' mode. 
During the wake up period, the LEDs surrounding the wheel light in a wake-up
sequence, starting with a slow clockwise and ending with a fast 
counter-clockwise motion. As this sequence ends, the device enters active mode.

In active mode, the application samples and registers individual finger touches 
on the 16-position wheel or the center button as well as simple gestures 
[Clockwise & Counter-clockwise] while the finger moves along and remains on 
the wheel. Upon wheel position detection, the corresponding LEDs surrounding 
the wheel light up accordingly. Each individual tap on the center capactive 
touch button toggles the center LED. 
After a predetermined amount of time without any touch activity (on the wheel
or on the center button) the application returns to sleep mode, enabling only
the proximity sensor.         

A 9600 baud UART link is also implemented using SW TimerA to provide 
application and cap touch data to the PC via the UART-USB back channel.
The application sends UART data upon events such as wake up, sleep, touch,
or gesture.  

II. PROJECT & FILE CONFIGURATION
-----------------------------------

PROJECT ROOT  - CapTouchBoosterPack_UserExperience 
|   CapTouchBoosterPack_UserExperience.c
|                           <Main application code>
|   README                  <This file>
|   uart.c                  <C file: UART implementation using TimerA & SW>
|   uart.h                  <H file: UART implementation using TimerA & SW> 
|   
+---[CapTouchLibrary]       <Capacitive Touch Library Code>
|       Cap_Touch_HAL.c         
|       Cap_Touch_HAL.h
|       Cap_Touch_Layer.c
|       Cap_Touch_Layer.h
|       requirements.doc
|       structure.c           <Created using template_structure.*>
|       structure.h           <Configured/calibrated specifically for this HW>
|       
+---[CCS]                   <CCS Project Configuration Files>  
|   |                         <All listed files are required>
|   |                         <The non-listed can be safely removed>
|   |   .ccsproject           
|   |   .cdtbuild             
|   |   .cdtproject
|   |   .project             <Contains links to portable project folders/files>
|   |   lnk_msp430g2452.cmd
|   |   macros.ini           <Enables portable project>
|   |   MSP430G2452.ccxml
|   |   
|   \---All other folders & files: IDE/build generated files
                remove/ignore when exporting projects
|               
\---[IAR]                   <CCS Project Configuration Files>
    |                         <All listed files are required>
    |                         <The non-listed can be safely removed>  
    |   CapTouch_BoosterPack_UserExperience.ewd
    |   CapTouch_BoosterPack_UserExperience.ewp
    |   CapTouch_BoosterPack_UserExperience.eww    
    \---All other folders & files: IDE/build generated files
                remove/ignore when exporting projects    
            
Legend: [Directory]     
           |---filename 

           
III. PROJECT IMPORT IN CCS & IAR
-----------------------------------  
  1. Project Import in CCS  
       a. Open CCS.
       b. Select a new project workspace outside of the project folder*           
       c. Select Project-->Import Existing Project 
       d. Browse to the [PROJECT_ROOT]\CCS folder
       e. Select Finish 
       
       *Ideally, workspace should be in completely independent folder, not
       containing or contained by the project/package folder.
       
       !Note: For CCS, while project root is in the outer directory, the CCS 
       project files are located inside CCS. To enable the portability of
       the project, the file macros.ini is created to define the root. 
       Additionally, all project code files (*.c, *.h) are added as linked 
       resources with their relative path to the project root.
       
  2. Open project & workspace in IAR
       a. Browse to the [PROJECT_ROOT]\IAR folder
       b. Open the CapTouch_BoosterPack_UserExperience.eww workspace.
       
IV. CAP TOUCH LIBRARY

The MSP430G2-LaunchPad CapTouch BoosterPack User Experience uses the Cap Touch
Library to configure, calibrate, and control the capacitive sensors. 

The sensor pads are configured in the structure.h & structure.c files. 
Specifically 6 elements are divided into three sensors: 1 proximity sensor, 1 
cap touch button (center button), and a 4-element wheel. 

After each element is calibrated to determine the touch threshold as well as
their maximum values in number of counts (which correlate to the measured 
capacitances), these calibration values are also registered inside structure.c.

The cap_touch_hal.* files provide the hardware abstract layer for the cap touch
library, which essentially provides different hardware/peripheral options to 
drive the cap touch functionality. Specifically for the CapTouch BoosterPack 
using an MSP430G2xx2/MSP430G2xx3 device, the Pin Oscillator peripheral is used.

The cap_touch_layer.* files provides the cap touch layer, which offers functions
that process the raw data into structured format. The main application utilizes 
this layer for their API calls to setup, measure baseline, detect touches, and
detect wheel positions. 

For more information on the Cap Touch Library, refer to the Cap Touch Library 
documentation. 

V. TOUCH & GESTURE DEFINITIONS
-----------------------------------
Proximity Sensor

The proximity sensor is made of the entire top PCB layer surface that covers the 
capacitive touch wheel. The proximity sensor detection occurs when the measured
capacitance increases due to the presence of some conductive object within 1-2
inch from the surface. Generally, a hand wave motion in parallel and 1-2 inch
from the CapTouch BoosterPack can trigger the detection. 

Individual Cap Touch Presses

The center button (small round button in the middle of the board) can register
an individual touch/press.

The capactive touch wheel consists of four physical "ninja-star" elements 
arranged in a wheel formation that is calibrated & programed to provide 
16-position detection. These positions can be detected individually as a 
button press. A press by the application's definition is consituted by a 
separate and single position detection registered continously [i.e. press 
begins when the position is touched and after no other position was detected, 
and ends when another position is detected or no further position is dectected.

Wheel Gesture

A gesture on the capacitive touch wheel is formed when a continuous series of 
touches is detected (no no-detection is reported, i.e. finger never leaves the
wheel). A complete continuous finger motion on the wheel might consist of 
several intermediate gestures, each with one separate direction (clockwise or
counter-clockwise).

VI. UART COMMUNICATION PROTOCOL 
-----------------------------------

Per each event (wake up, go to sleep, touch/press, or gesture), a UART packet
of two bytes is sent. They are specified as follows.

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

VII. HISTORY 
-----------------------------------

Ver. 1.0
- Implemented 64-position detection in the cap touch layer (defined in
structure.h/c fies). These 64 position are still translated into 16-position 
representational wheel. 
- Instead of sending continuous wheel touch packets, only send initial, last
and every other WHEEL_TOUCH_DELAY wheel touch detections. This modification does
not affect the MSP430G2-LaunchPad CapTouch BoosterPack User Experience GUI, but 
enables full and expected behavior of the MediaPad program in Windows.
Ver. 0.9:  
-Initial firmware release for small lot production. Supports MSP430G2-LaunchPad 
CapTouch BoosterPack User Experience GUI. Partial support for MediaPad,  
application behavior might not be optimized.
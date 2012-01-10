----------MSP430G2-LaunchPad CapTouch BoosterPack User Experience GUI-----------
Ver.: 1.00 Initial Release
February 2011
Dung Dang
MSP430 Applications
Texas Instruments, Inc.
--------------------------------------------------------------------------------

CONTENTS 

I. DESCRIPTION
II. APPLICATION USAGE
III. PROJECT SETUP & RESOURCES
IV. OTHER PLATFORM SUPPORT


I. DESCRIPTION
-----------------------------------

Written in processing, this Windows PC GUI application communicates with the 
LaunchPad to receive specific capacitive touch data from the LaunchPad CapTouch
BoosterPack and provides the visualization of said information in the GUI.   
 
The GUI uses a small .NET utility (FindAppUART.exe) to automatically detect
a proper LaunchPad/430Emulator device connected to the PC USB port. Upon 
correct USB COM port discovery, the application initiates a 9600baud UART 
connection and starts receiving data. 

Upon each LaunchPad event, data is transmitted [always] via a simple '2-byte' 
protocol as described below.


[LaunchPad]  Wake up       :    0xBE 0xEF 
[LaunchPad]  Sleep         :    0xDE 0xAD 
[CapTouch]   Center Button :    0x80 0x80
[CapTouch]   Wheel Tap     :    WT   WT  = pos. on wheel [0-0x0F] + 0x30
[CapTouch]   Gesture Start :    0xFC POS = pos. on wheel [0-0x0F] + 0x20
[CapTouch]   Gesture Stop  :    0xFB POS = pos. on wheel [0-0x0F] + 0x20
[CapTouch]   Gesture Update:    GES  POS 

    [GES] Gesture = [0-0x0F]        --> Clockwise gesture 
                  = 0x10+ [0-0x0F]  --> Counter-clockwise gesture 

II. APPLICATION USAGE             
-----------------------------------
1. Startup
Upon startup, the GUI checks for a valid LaunchPad USB serial COM port. If
no compatible port connection is available, the GUI prompts user to plug in
the LaunchPad CapTouch BoosterPack. The GUI will continue as normal whenever
a LaunchPad is plugged into the PC.

2. Sleep Mode
Upon start-up or after long period of inactivity, the device goes into sleep
mode. The GUI grays out accordingly indicate such inactivity. 
Upon proximity sensor detection (wave hand 1-2 inch above the BoosterPack) the 
device returns to active mode and triggers the GUI to wake up as well. 

3. Active Mode
- The 'Center Button' press data toggles the center circle color, mimicking the 
behavior of the center LED on the BoosterPack.
- The 'Wheel Tap' is represented by lighting up a single slice on the wheel.
- The gesture tracking [Start, Stop, Update] is visualized on the wheel with 
the coloration of the wheel slices. Gesture can be tracked for several 
revolutions of the wheel, in both clockwise and counter-clockwise directions.

* A hidden code/lock is embedded in the wheel. Correct sequence [similar to a
rotational combination lock] reveals a secret.


III. PROJECT SETUP & RESOURCES
-----------------------------------

Below is the directory structure of the processing project

[CapTouch_BoosterPack_UserExperience_GUI] [PROJECT_ROOT]
|
|   CapTouch_BoosterPack_UserExperience_GUI.pde  <Processing appcalition code> 
|   FindAppUART.exe <to copy to application.windows after each processing build>
|   README <this file> 
|
+---[data]                <images & sounds>
|     |---*.png
|     \---*.aiff
|
+---[application.windows] <processing java source export & binary build>
|     |---[lib]
|     |---[source]      
|     |---CapTouch_BoosterPack_UserExperience_GUI.exe  <Main application>     
|     |---FindAppUART.exe <.NET utility to detect LaunchPad USB serial COM port>          
|     \--- . . .
    
 
Legend: [Directory]     
           |---filename 
 
The processing application code is contained within one file, 
CapTouch_BoosterPack_UserExperience_GUI.pde, which must reside in a similarly 
named workspace-acting folder. The code invokes two additional libraries, serial
[comes with processing] for serial communication through the USB COM port and 
pitaru.sonia_v2_9.* (available at http://sonia.pitaru.com/download.htm) for 
sound processing feature [optional in the GUI]. The libraries DLLs will be 
generated in the [application.windows] folder when the application is exported.

The application also invokes a small .NET utility <FindAppUART.exe> to 
automatically detect a compatible LaunchPad USB COM port available to the PC.
The code expects this executable file to be present locally to the effective
working directory during execution. 
* Specifically, during debug, processing's working directory is 
C:\processing-1.1\java\bin and processing expects to be able to locate 
<FindAppUART.exe> here. For the sake of simplicity, simply create a copy of the
 file here. 
* After application export and the final application executable has been 
created, <FindAppUART.exe> should be placed in the same directory with the file
CapTouch_BoosterPack_UserExperience_GUI.exe. By default this directory is 
[application.windows]

!NOTE: The FindUART.exe file must be copied back into the [application.windows]
directory after each export, as processing removes the entire directory during
the application export process. Make sure to keep a local copy of the file 
FindUART.exe.

IV. OTHER PLATFORM SUPPORT
-----------------------------------

The main application code is written in processing, a java-based language that
is portable to different OS platforms such as Windows, Linux or Mac. However
it utilizes the serial driver & the .NET COM port utility that is developed 
for Windows only. Replacing this component with the equivalent [driver] in Linux
or Mac would enable a complete port of this application. 

Additionally, a Linux or Mac USB/COM port driver must also be installed in order
to connect and communicate with the LaunchPad.
 
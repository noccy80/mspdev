***********************************************************

Texas Instruments MSP430 USB Developers' Package

***********************************************************

PACKAGE CONTENTS:

-> MSP430_USB_API_Stacks. (The MSP430 USB API & Application Examples):  
   -> Contains the MSP430 USB CDC/HID/MSC API.  You can use this as the 
      foundation of your MSP430 USB development.  
   -> Contains a recommended Main Loop Framework (a commented framework from 
      which to begin development)

-> Descriptor_Tool. (The MSP430 USB Descriptor Tool):
   -> Configures the API stack prior to development for whatever interfaces you
      want to use; automatically generates the needed USB descriptors.
   -> This applicaton needs the Java Runtime Engine (JRE), available at
	    http://www.oracle.com/technetwork/java/javase/downloads/index.html.  If 
	    your PC lacks a sufficient JRE version, the Tool will prompt you to 
	    download it when you execute it.  

-> Programmers_Guide_MSP430_USB_API.  (The MSP430 USB API Programmer's Guide)
   -> The complete reference for developing USB applications on MSP430, using 
      the API stacks and Descriptor Tool.  
   -> See it for information about:
      * Loading/running the API stack examples
      * Documentation of the API calls
      * How to use the Descriptor Tool
      * Practical guidance on writing USB applications
      * Links to other MSP430 USB information

-> Windows_HID_API_Installer_1.x.x-Setup.exe.  (Installs the Windows HID API)
   -> An API for implementing the Human Interface Device class (HID) on Windows.  
      It abstracts to a level similar to what the USB API stacks provide 
      on the MSP430 -- that is, it can send/receive blocks of data of any size
      with a single function call.  It's designed for use with the HID-Datapipe
      interface implemented by the MSP430 HID API.    
   -> The demo app for this API ("HID Demo App") is similar to a terminal 
      application (i.e., Hyperterminal), except it uses HID instead of CDC.  
      Designed to interact with an MSP430 implementing a HID-Datapipe interface.
   -> See the "MSP430 USB HID Windows API Programmer's Guide" (slaa453).  
   -> Requires the Windows Driver Kit (WDK) for proper functioning. 
      http://www.microsoft.com/whdc/devtools/wdk/wdkpkg.mspx

-> Field_Firmware_Updater_Installer-1.x.x-Setup.exe. 
   (Installs the Field Firmware Updater Windows Visual Studio project)
   -> Allows easy creation of a Windows app that downloads firmware to an MSP430
      over USB.  It interfaces with the MSP430's built-in bootstrap loader  
      (BSL), but minimizes the need to learn the BSL -- just drop in your new  
      firmware image, change the settings, customize the GUI, and re-build.   
      Windows Visual Studio Express (available at no cost from Microsoft) is  
      required for development.
   -> See the app report "USB Field Firmware Updates on MSP430 MCUs" (slaa452).  
   -> The default executable can be used as-is for development purposes without 
      rebuilding, to download any MSP430 firmware image of the format 
      "msp430-txt" (also known as TI-TXT).  
   -> Requires the Windows Driver Kit (WDK) for proper functioning. 
      http://www.microsoft.com/whdc/devtools/wdk/wdkpkg.mspx


Subdirectories also contain readme's with additional information.  

MSP-EXP430F5529 Experimenter's Board User Experience Demo v1.20.00
Texas Instruments, Inc.

********************************************************************************
Revision History
********************************************************************************
Ver 1.20.00 - August 3rd, 2011
- Added support for CCSv5

Ver 1.10.01 - May 26th, 2011
- Fixed ImageDog JRE compatibility issue
- Changed default installer directory

Ver 1.10 - May 5th, 2011
- Added "Drivers" folder
- Added limited code size project for CCS
- Changed CCS optimizer settings
- General cleanup / bug fixes

Ver 1.00 - April 7th, 2011
- Initial Production Release

********************************************************************************
Project File Listing
********************************************************************************
|
|--CCS                        : Folder containing the CCSv4 project files
   |--lnk_msp430f5529.cmd     : Device linker command file
   |--lnk_msp430f5529_USB.cmd : USB-stack related linker command file
   |--system_pre_init.c       : CCS-specific runtime library customization
|--CCS_Code_Size_Limited      : Folder containing the CCSv4 project files - 16KB
|--CTS                        : Folder containing SW library for capacitive touch
|--Drivers                    : Drivers for USB demo functionality
|--F5xx_F6x_Core_Lib		  : Folder containing MSP430 low-level HAL (SLAA448)
|--FatFs                      : Folder containing the open-source FatFs file system
|--IAR                        : Folder containing the IAR EW430 project files
   |--low_level_init.c        : IAR-specific runtime library customization
|--ImageDog                   : Folder containing an image converter tool
|--MSP-EXP430F5529_HAL        : Folder containing board-level HAL
|--USB                        : Folder containing the MSP430 USB stack
   |--USB_User                : USB-stack related application files
|--UserExperienceDemo         : Folder containing User Experience Code application
|--readme.txt                 : This file
|--UserExperience.c           : Contains main entry point
|--MSP-EXP430F5529 User Experience Manifest.pdf   : Software manifest

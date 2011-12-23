// (c)2010 by Texas Instruments Incorporated, All Rights Reserved.
/*----------------------------------------------------------------------------+
  |                                                                             |
  |                              Texas Instruments                              |
  |                                                                             |
  |                          MSP430 USB-Example (MSC Driver)                    |
  |                                                                             |
  +-----------------------------------------------------------------------------+
  |  Source: msc_mbr.h, File Version 1.01                                       |
  |  Description: This file contains the inittilaized data for                  |
  |               file system emulation example.The emulation now is shown for  |
  |               1 file only for demo purpose. It is user responsibility       |
  |               to change this if a different configuration is required.      |
  |  Author: MSP                                                                |
  |                                                                             |
  |  WHO          WHEN         WHAT                                             |
  |  ---          ----------   ------------------------------------------------ |
  |  RSTO         2010/10/20   Created                                          |
  |                                                                             | 
  +----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

extern const BYTE MBR[];
extern const BYTE Partition[];
extern const BYTE FAT[];
extern const BYTE Root_Dir[];
extern const BYTE Data559[];
extern BYTE* Data560;
extern BYTE* Data561;
extern BYTE* Data562;
extern BYTE* Data563;
extern BYTE* Data564;
extern BYTE* Data565;
extern BYTE* Data566;
extern BYTE Data_LUN1[];
/*------------------------ Nothing Below This Line ----------------------------*/

#ifdef __cplusplus
}
#endif

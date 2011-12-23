// (c)2009 by Texas Instruments Incorporated, All Rights Reserved.
/*----------------------------------------------------------------------------+
|                                                                             |
|                              Texas Instruments                              |
|                                                                             |
|                          MSP430 USB-Example (CDC/HID Driver)                |
|                                                                             |
+-----------------------------------------------------------------------------+
|  Source: main.h, v1.18 2009/06/11                                           |
|  Author: RSTO                                                               |
|                                                                             |
|  WHO          WHEN         WHAT                                             |
|  ---          ----------   ------------------------------------------------ |
|  RSTO         2008/09/03   born                                             |
+----------------------------------------------------------------------------*/

#ifndef _MAIN_H_
#define _MAIN_H_

#ifdef __cplusplus
extern "C"
{
#endif


/**
Call all needed Init_...() functions.
  Needed Init_...() functions depends on build settings.
*/
VOID Init_StartUp(VOID);
VOID Init_Ports(VOID);
VOID Init_Clocks(VOID);
BYTE retInString(char*);
VOID Init_TimerA1(VOID);


#ifdef __cplusplus
}
#endif
#endif /* _MAIN_H_ */
/*------------------------ Nothing Below This Line --------------------------*/


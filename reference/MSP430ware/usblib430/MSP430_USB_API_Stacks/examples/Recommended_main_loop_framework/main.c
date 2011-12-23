// (c)2010 by Texas Instruments Incorporated, All Rights Reserved.
/*----------------------------------------------------------------------------*
|                                                                             |
|                              Texas Instruments                              |
|                                                                             |
|                          MSP430 USB-Example                                 |
|                                                                             |
+-----------------------------------------------------------------------------+
|  Source: main.c                                                             |
------------------------------------------------------------------------------+ 

#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/types.h"          // Basic Type declarations
#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/usb.h"        // USB-specific functions
#include "F5xx_F6xx_Core_Lib/HAL_UCS.h"
#include "F5xx_F6xx_Core_Lib/HAL_PMM.h"
#ifdef _CDC_
    #include "USB_API/USB_CDC_API/UsbCdc.h"
#endif
#ifdef _HID_
    #include "USB_API/USB_HID_API/UsbHid.h"
#endif

#include <intrinsics.h>
#include <string.h>
#include "usbConstructs.h"


VOID main(VOID)
{
    WDTCTL = WDTPW + WDTHOLD;	    // Stop watchdog timer
    Init_StartUp();                 //initialize device
    __enable_interrupt(); 
    USB_init();                     //init USB

    // Enable various USB event handling routines
    USB_setEnabledEvents(kUSB_allUsbEvents);
    
    
    // See if we're already attached physically to USB, and if so, connect to it
    // Normally applications don't invoke the event handlers, but this is an exception.  
    if (USB_connectionInfo() & kUSB_vbusPresent)
      USB_handleVbusOnEvent();

    
    while(1)
    {
        switch(USB_connectionState())
        {
          case ST_USB_DISCONNECTED:
             // This state indicates that VBUS is not present, meaning there is no USB connection.  
             // If a device is self-powered, this becomes the main loop when there is no USB connection.    
             __bis_SR_register(LPM3_bits + GIE); 	       // Enter LPM3 until VBUS-on event

             // Here, write the main loop for how the device should behave when USB is disconnected.  
             
             break;
            
          case ST_USB_CONNECTED_NO_ENUM:
             // This state indicates that VBUS is present but USB_connect() has not yet been called (the PUR signal has
             // not yet been pulled high).  Most USB devices respond to a VBUS-on event by pulling PUR high -- and so the 
             // recommendation is to call USB_connect() from USB_handleVbusOnEvent().  If this is done, then this state 
             // is very short-lived, thus there is no code here.  This state is provided because some applications may not
             // wish to assert PUR immediately upon connection.  
             break;
            
          case ST_ENUM_ACTIVE:             
             // This state indicates that the device has successfully enumerated on a USB host.  When connected to USB, the
             // code in this branch becomes the main loop of the program.  Those familiar with common MSP430 coding 
             // practices recognize the immediate entry into LPM0, out of which an interrupt can be used to make one run
             // through the main loop.  (This of course is application-specific, and the s/w engineer is free to use other
             // constructs.)  Note that during an active USB connection (enumerated and not suspended), the MSP430 should 
             // not be placed into a mode below LPM0 (no LPM3/4/5).  
            
             __bis_SR_register(LPM0_bits + GIE); 	             // Enter LPM0 + enable interrupts
             
             // Here, write the main loop for how the device should behave when USB is connected and active.  
             
              break;
              
          case ST_ENUM_SUSPENDED:
             // This state indicates  the device is enumerated on a USB host, but the host has suspended it.  The device is 
             // not allowed to draw more than 2.5mA from VBUS during this time, and thus the main loop might look different
             // than it did during ST_ENUM_ACTIVE.  It's recommended to insert code into handleSuspendEvent() (or here)
             // that disables any circuitry drawing excessive current from VBUS.  During suspend, the power mode may enter 
             // LPM3 or LPM4. 
            
             __bis_SR_register(LPM3_bits + GIE);            // Enter LPM3, until a resume or VBUS-off event

             // Here, write the main loop for how the device should behave when USB is disconnected.  
             
             break;
            
          case ST_ENUM_IN_PROGRESS:
             // This state indicates the device is in the process of being enumerated on a USB host.  This process is usually brief,
             // although in rare enumeration failures it might stay here indefinitely.  A timeout could be implemented for such cases;
             // the API doesn't implement this timeout internally.  During enumeration, the USB module must stay fully active; 
             // therefore, the power mode shouldn't enter LPM3/4.  Since it's typically very brief, there's often no LPM entry placed here.  
             break;
            
           case ST_NOENUM_SUSPENDED:
             // This state indicates that VBUS is present, the device attempted to enumerate by pulling PUR high, but then the host suspended 
             // the device.  This differs from ST_ENUM_IN_PROGRESS, in that ST_ENUM_IN_PROGRESS doesn't involve the device getting suspended.  
             // This state might happen from a failed enumeration; becoming attached to a host that is in standby; or becoming attached 
             // to a powered hub without a host upstream.  To handle this, code has been placed in USB_handleSuspendEvent() to 'cancel' the
             // enumeration.  As a result, this state shouldn't last very long, and no code is placed here.  
             // Another way of handling might be to simply stay in this state until an active host attempts to enumerate.   
           
             break;
               
          case ST_ERROR:
            break;
            
          default:;
        }    
    }  // while(1)
} //main()


/*----------------------------------------------------------------------------+
| System Initialization Routines                                              |
+----------------------------------------------------------------------------*/

VOID Init_Clock(VOID)
{
#   if defined (__MSP430F563x_F663x)
		while(BAKCTL & LOCKIO)                    // Unlock XT1 pins for operation
      	BAKCTL &= ~(LOCKIO);                    // enable XT1 pins
     	// Workaround for USB7
    	UCSCTL6 &= ~XT1OFF;
#   endif
    
    //Initialization of clock module
    if (USB_PLL_XT == 2)
    {
#       if defined (__MSP430F552x) || defined (__MSP430F550x)
        	P5SEL |= 0x0C;                        // enable XT2 pins for F5529
#       elif defined (__MSP430F563x_F663x)
			P7SEL |= 0x0C;
#       endif
        // use REFO for FLL and ACLK
        UCSCTL3 = (UCSCTL3 & ~(SELREF_7)) | (SELREF__REFOCLK);
        UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK);
         
        Init_FLL(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768);             // set FLL (DCOCLK)
        XT2_Start(XT2DRIVE_3);
    }
    else
    {
#       if defined (__MSP430F552x) || defined (__MSP430F550x)
            P5SEL |= 0x10;                    // enable XT1 pins
#       endif 
        UCSCTL3 = SELREF__REFOCLK;            // run FLL mit REF_O clock
        UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK); // set ACLK = REFO
        Init_FLL(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768);       // set FLL (DCOCLK)
        XT1_Start(XT1DRIVE_3);
    }
    //  SFRIE1 |= OFIFG;                     // Enable OscFault ISR
}

//----------------------------------------------------------------------------

VOID Init_Ports(VOID)
{
    // Initialization of ports all unused pins as outputs with low-level

    // set all ports  to low on all pins
    PAOUT   =   0x0000;
    PASEL   =   0x0000;
    PADIR   =   0xFFFF;

    PBOUT   =   0x0000;
    PBSEL   =   0x0000;
    PBDIR   =   0xFFFF;

    PCOUT   =   0x0000;
    PCSEL   =   0x0000;
    PCDIR   =   0xFFFF;

#   ifndef __MSP430F550x
        PDOUT   =   0x0000;      //	If using a device other than: 
        PDSEL   =   0x0000;	     //	F5510, F5529, F5638, or F6638 
        PDDIR   =   0xFFFF;      //	you may need to comment out these lines 
#   endif 
    
#   if defined (__MSP430F563x_F663x)
        P9OUT   =   0x00;
        P9SEL   =   0x00;
        P9DIR   =   0xFF;
#   endif

    PJDIR   =   0xFFFF;
    PJOUT   =   0x0000;
}


//----------------------------------------------------------------------------

VOID Init_StartUp(VOID)
{
   unsigned short bGIE;
   bGIE  = (__get_SR_register() &GIE);  //save interrupt status

   __disable_interrupt();               // Disable global interrupts
    
#   ifdef __MSP430F6638    
        // only for F663x devices!
        while (BAKCTL & LOCKBAK)            // check if bit for backup subsystem is cleared
        {
            BAKCTL &= ~LOCKBAK;             // clear lock backup bit for backup subsystem 
        }
#   endif
    
    Init_Ports();                        // Init ports (do first ports because clocks do change ports)
    SetVCore(3);                         // USB core requires the VCore set to 1.8 volt, independ of CPU clock frequency
    Init_Clock();

    __bis_SR_register(bGIE); //restore interrupt status
}


#pragma vector = UNMI_VECTOR
__interrupt VOID UNMI_ISR(VOID)
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG))
    {
    case SYSUNIV_NONE:
      __no_operation();
      break;
    case SYSUNIV_NMIIFG:
      __no_operation();
      break;
    case SYSUNIV_OFIFG:
      UCSCTL7 &= ~(DCOFFG+0+0+0); // Clear OSC flaut Flags fault flags
      SFRIFG1 &= ~OFIFG;                                // Clear OFIFG fault flag
      break;
    case SYSUNIV_ACCVIFG:
      __no_operation();
      break;
    case SYSUNIV_BUSIFG:

      // This indicates a "bus error"; this is catastrophic for the USB connection, which must
      // now be shut down.  Generally this indicates a software bug -- see the Prog. Guide for more detail.  
      SYSBERRIV = 0;            // Clear bus error flag
      USB_disable();            // Disable
    }
}

/*----------------------------------------------------------------------------+
| End of source file                                                          |
+----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/

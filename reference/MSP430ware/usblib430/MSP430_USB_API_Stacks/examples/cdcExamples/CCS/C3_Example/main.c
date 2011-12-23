// (c)2010 by Texas Instruments Incorporated, All Rights Reserved.
/*----------------------------------------------------------------------------+
|                                                                             |
|                              Texas Instruments                              |
|                                                                             |
|                          MSP430 USB-Example (CDC/HID Driver)                |
|                                                                             |
+-----------------------------------------------------------------------------*/
/*  Source: main.c, v2.0 2009/08/03       
-------------------------------------------------------------------------------+
 Local Echo Demo:

 This USB demo example is to be used with a PC application (e.g. HyperTerminal)
 The demo application demonstartes a local echo; Characters that are 
 transmitted from PC are echoed back.

 NOTE: In order to see the local echo in Hyper Terminal goto File -> Propoerties 
 -> Settings -> ASCII Setup and check the "Echo Typed Characters Locally"

-------------------------------------------------------------------------------+
 Please refer to the MSP430 USB API Stack Programmer's Guide,located 
 in the root directory of this installation for more details.
------------------------------------------------------------------------------*/

#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/types.h"          // Basic Type declarations
#include "F5xx_F6xx_Core_Lib/HAL_UCS.h"
#include "F5xx_F6xx_Core_Lib/HAL_PMM.h"
#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/usb.h"        // USB-specific functions
#include "USB_API/USB_CDC_API/UsbCdc.h"

#include "usbConstructs.h"
#include <intrinsics.h>
#include <string.h>

// Function declarations
VOID Init_StartUp(VOID);
  
// Global flags set by events
volatile BYTE bCDCDataReceived_event = FALSE;          // Flag set by event handler to indicate data has been received into USB buffer

#define BUFFER_SIZE 130
char nl[2] = "\n";

/*----------------------------------------------------------------------------+
| Main Routine                                                                |
+----------------------------------------------------------------------------*/
VOID main(VOID)
{
    WDTCTL = WDTPW + WDTHOLD;	    // Stop watchdog timer
    
    Init_StartUp();                 //initialize device
    USB_init();                     // Init USB

    // Enable various USB event handling routines

    USB_setEnabledEvents(kUSB_VbusOnEvent+kUSB_VbusOffEvent+kUSB_receiveCompletedEvent
                          +kUSB_dataReceivedEvent+kUSB_UsbSuspendEvent+kUSB_UsbResumeEvent+kUSB_UsbResetEvent);
    
    // See if we're already attached physically to USB, and if so, connect to it
    // Normally applications don't invoke the event handlers, but this is an exception.  
    if (USB_connectionInfo() & kUSB_vbusPresent)
    {
      if (USB_enable() == kUSB_succeed)
      {
        USB_reset();
        USB_connect();
      }
    }

    while(1)
    {
        BYTE ReceiveError=0, SendError=0;
        WORD count;
        // Check the USB state and loop accordingly
        switch(USB_connectionState())
        {
           case ST_USB_DISCONNECTED:
                 __bis_SR_register(LPM3_bits + GIE); 	             // Enter LPM3 until USB is connected
                 __no_operation();
                break;
                
           case ST_USB_CONNECTED_NO_ENUM:
                break;
                
           case ST_ENUM_ACTIVE:
                __bis_SR_register(LPM0_bits + GIE); 	             // Enter LPM0 until awakened by an event handler

                // Exit LPM because of a data-receive event, and fetch the received data 
                if(bCDCDataReceived_event)
                {
				  char dataBuffer[BUFFER_SIZE] = "";
				  
                  bCDCDataReceived_event = FALSE;                                   // Clear flag early -- just in case execution breaks below because of an error
                  count = cdcReceiveDataInBuffer((BYTE*)dataBuffer,BUFFER_SIZE,0); // Count has the number of bytes received into dataBuffer
                  strcat(dataBuffer,nl);
                  if(cdcSendDataInBackground((BYTE*)dataBuffer,count,0,1))         // Echo is back to the host
                  {
                    SendError = 0x01;                                               // Something went wrong -- exit
                    break;
                  }                  
                }          
                break;

           case ST_ENUM_SUSPENDED:
                __bis_SR_register(LPM3_bits + GIE); 	// Enter LPM3 until a resume or VBUS-off event
                break;
                
           case ST_ENUM_IN_PROGRESS:
                break;
           
           case ST_NOENUM_SUSPENDED:
                __bis_SR_register(LPM3_bits + GIE);  
                _NOP();
                break;
           
           case ST_ERROR:
                _NOP();
                break;
                
           default:;                
        }
        if(ReceiveError || SendError)
        { 
          //TO DO: User can place code here to handle error
        }
      
    }  // while(1)
} //main()


// Initializes the clocks.  Starts the DCO at USB_MCLK_FREQ (the CPU freq set with the Desc 
// Tool), using the REFO as the FLL reference.  Configures the high-freq crystal, but 
// doesn't start it yet.  Takes some special actions for F563x/663x.  
VOID Init_Clock(VOID)
{
    #if defined (__MSP430F563x_F663x)
      while(BAKCTL & LOCKIO)                  // Unlock XT1 pins for operation
      BAKCTL &= ~(LOCKIO);                    // Enable XT1 pins
      // Workaround for USB7 chip errata
      UCSCTL6 &= ~XT1OFF;
    #endif
    if (USB_PLL_XT == 2)
    {
        // Enable XT2 pins
        #if defined (__MSP430F552x) || defined (__MSP430F550x)
          P5SEL |= 0x0C;                      
        #elif defined (__MSP430F563x_F663x)
          P7SEL |= 0x0C;
        #endif
          
        // Use the REFO oscillator as the FLL reference, and also for ACLK
        UCSCTL3 = (UCSCTL3 & ~(SELREF_7)) | (SELREF__REFOCLK);
        UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK);
        
        // Start the FLL, which will drive MCLK (not the crystal)
        Init_FLL(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768);  
    }
    else
    {
        // Enable XT1 pins
        #if defined (__MSP430F552x) || defined (__MSP430F550x)
          P5SEL |= 0x10;                    
        #endif 
        
        // Use the REFO oscillator as the FLL reference, and also for ACLK
        UCSCTL3 = SELREF__REFOCLK;             
        UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK); 
        
        // Start the FLL, which will drive MCLK (not the crystal)
        Init_FLL(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768); // set FLL (DCOCLK)
    }
}

//----------------------------------------------------------------------------
VOID Init_Ports(VOID)
{
    // Drive all I/O's as output-low, making sure there's no shoot-through current.  There 
    // should be no floating I/Os, to prevent unnecessary current draw during USB suspend.  
    PAOUT   =   0x0000;
    PASEL   =   0x0000;
    PADIR   =   0xFFFF;

    PBOUT   =   0x0000;
    PBSEL   =   0x0000;
    PBDIR   =   0xFFFF;

    PCOUT   =   0x0000;
    PCSEL   =   0x0000;
    PCDIR   =   0xFFFF;

	#ifndef __MSP430F550x
    PDOUT   =   0x0000;      //	If using a device other than: 
    PDSEL   =   0x0000;	     //	F5510, F5529, F5638, or F6638 
    PDDIR   =   0xFFFF;      //	you may need to comment out these lines 
    #endif 
    
    #if defined (__MSP430F563x_F663x)
    P9OUT   =   0x00;
    P9SEL   =   0x00;
    P9DIR   =   0xFF;
    #endif
    
    PJDIR   =   0xFFFF;
    PJOUT   =   0x0000;
}

//----------------------------------------------------------------------------

VOID Init_StartUp(VOID)
{
    __disable_interrupt();               // Disable global interrupts
    
    Init_Ports();                        // Init ports (do first ports because clocks do change ports)
    SetVCore(3);                         // USB core requires the VCore set to 1.8 volt, independ of CPU clock frequency
    Init_Clock();

    __enable_interrupt();                // enable global interrupts
}
//----------------------------------------------------------------------------
#pragma vector = UNMI_VECTOR
__interrupt VOID UNMI_ISR(VOID)
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_SYSBUSIV))
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
    case SYSUNIV_SYSBUSIV:
      SYSBERRIV = 0;            // clear bus error flag
      USB_disable();            // Disable
    }
}

/*----------------------------------------------------------------------------+
| End of source file                                                          |
+----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/

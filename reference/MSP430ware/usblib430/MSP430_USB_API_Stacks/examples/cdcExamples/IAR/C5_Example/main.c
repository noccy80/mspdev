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
 High-Bandwidth Sending Using sendData_waitTilDone Demo:

 The example shows how to implement high-bandwidth sending using 
 the post-call polling method, which doesn’t allow execution to proceed 
 until all the data has been sent. It prompts for any key to be pressed,
 and when this happens, the application sends a large amount of data 
 to the host

-------------------------------------------------------------------------------+ 
 Please refer to the MSP430 USB API Stack Programmer's Guide,located 
 in the root directory of this installation for more details.
------------------------------------------------------------------------------*/

#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/types.h"          
#include "F5xx_F6xx_Core_Lib/HAL_UCS.h"
#include "F5xx_F6xx_Core_Lib/HAL_PMM.h"

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/usb.h"        


#ifdef _CDC_
    #include "USB_API/USB_CDC_API/UsbCdc.h"
#endif
#ifdef _HID_
    #include "USB_API/USB_HID_API/UsbHid.h"
#endif

#include "usbConstructs.h"
#include <intrinsics.h>
#include <string.h>

VOID Init_StartUp(VOID);

volatile BYTE bCDCDataReceived_event = FALSE; // Indicates data has been received without an open rcv operation

char outString[32];
WORD x;                            // Dummy variable for use with abortSend()
WORD rounds=0;

#define MEGA_DATA_LENGTH 2046
BYTE dataBuf[MEGA_DATA_LENGTH];
WORD w;
BYTE y=0x21;

/*----------------------------------------------------------------------------+
| Main Routine                                                                |
+----------------------------------------------------------------------------*/
VOID main(VOID)
{
    WDTCTL = WDTPW + WDTHOLD;	    // Stop watchdog timer
    Init_StartUp();
    
    USB_init();
    USB_setEnabledEvents(kUSB_VbusOnEvent+kUSB_VbusOffEvent+kUSB_dataReceivedEvent+kUSB_UsbSuspendEvent+kUSB_UsbResumeEvent+kUSB_UsbResetEvent);
   
    
    // Pre-fill the buffers with visible ASCII characters (0x21 to 0x7E)

    for(w=0;w<MEGA_DATA_LENGTH;w++)
    {
      dataBuf[w] = y++;
      if(y>0x7E)
        y = 0x21;
    }
    
    // Check if we're already physically attached to USB, and if so, connect to it
    // This is the same function that gets called automatically when VBUS gets attached.  
    if (USB_connectionInfo() & kUSB_vbusPresent)
      USB_handleVbusOnEvent();
              
                 
    while(1)
    {
        switch(USB_connectionState())
        {
           case ST_USB_DISCONNECTED:
                 __bis_SR_register(LPM3_bits + GIE); 	  // Enter LPM3 w/interrupt
                break;
                
           case ST_USB_CONNECTED_NO_ENUM:
                break;
                
           case ST_ENUM_ACTIVE:
                if(!bCDCDataReceived_event)                          // Do this until a key is pressed
                {
                  strcpy(outString,"Press any key.\r");                             // Prepare the outgoing string
                  if(cdcSendDataWaitTilDone((BYTE*)outString,strlen(outString),0,0))  // Send it; no timeout
                  {                      
                    USBCDC_abortSend(&x,0);               // Operation may still be open; cancel it
                    break;                                
                  }
                }
                else
                {
                  bCDCDataReceived_event = FALSE;
                  USBCDC_rejectData(0);
                  for(rounds=0;rounds<600;rounds++)
                  {
                    if(cdcSendDataWaitTilDone(dataBuf,MEGA_DATA_LENGTH,0,0))     // Send all of RAM
                    {
                      USBCDC_abortSend(&x,0);               // Operation probably still open; cancel it
                      break;
                    }
                  }
                  strcpy(outString,"\r\n\r\n\r\nThe test is completed.\r\n");       // Prepare the outgoing string
                  if(cdcSendDataWaitTilDone((BYTE*)outString,strlen(outString),0,0))  // Send it; no timeout
                  {
                    USBCDC_abortSend(&x,0);                 // Operation may still be open; cancel it
                    break;                                 
                  }
                }
                break;
                
           case ST_ENUM_SUSPENDED:
                __bis_SR_register(LPM3_bits + GIE); 	 // Enter LPM3 w/interrupt
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
    }  // while(1) 
} //main()


//----------------------------------------------------------------------------


/*----------------------------------------------------------------------------+
| System Initialization Routines                                              |
+----------------------------------------------------------------------------*/

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
// To be robust, an application should handle fault events that invoke the NMI vector.  
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
      UCSCTL7 &= ~(DCOFFG+0+0+0); // Clear OSC fault source flags 
      SFRIFG1 &= ~OFIFG;                                // Clear OFIFG flag
      break;
    case SYSUNIV_ACCVIFG:
      __no_operation();
      break;
    case SYSUNIV_SYSBUSIV:
      
      // In the rare event of an internal system bus error - must clear the flag and re-initialize USB. 
      SYSBERRIV = 0;            // Clear flag
      USB_disable();            // Disable USB
      if (USB_connectionInfo() & kUSB_vbusPresent)
        USB_handleVbusOnEvent();
    }
}




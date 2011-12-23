// (c)2010 by Texas Instruments Incorporated, All Rights Reserved.
/*----------------------------------------------------------------------------+
|                                                                             |
|                              Texas Instruments                              |
|                                                                             |
|                          MSP430 USB-Example (CDC/HID Driver)                |
|                                                                             |
+-----------------------------------------------------------------------------*/
/*  Source: main.c, v2.0 2010/08/03       
-------------------------------------------------------------------------------+                                         
 Receive 1K bytes from Host Demo:

 This example implements a device whose only purpose is to receive a 1K chunk
 of data from the host.

 For the demonstration of this example use the UsbApp.exe. The UsbApp.exe GUI
 can send a maximum of 2028 bytes at a time. So after sending 1024 characters,
 it returns "Thanks for the data" 

Copy the contents "data.txt" present in the product folder and paste it in the
send text input field. 
+----------------------------------------------------------------------------+
 Please refer to the MSP430 USB API Stack Programmer's Guide,located 
 in the root directory of this installation for more details.
----------------------------------------------------------------------------*/

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

VOID Init_StartUp(VOID);

BYTE dataBuff[1024];

volatile BYTE bHIDDataReceived_event = FALSE;          // data received event
volatile BYTE bDataReceiveCompleted_event = FALSE;

volatile WORD USBEVIE = kUSB_VbusOnEvent+kUSB_VbusOffEvent+kUSB_receiveCompletedEvent
                          +kUSB_dataReceivedEvent+kUSB_UsbSuspendEvent+kUSB_UsbResumeEvent+kUSB_UsbResetEvent;
char outString[40] = "";
WORD i;
WORD x,y;
BYTE ret;
                
/*----------------------------------------------------------------------------+
| Main Routine                                                                |
+----------------------------------------------------------------------------*/
VOID main(VOID)
{
    WDTCTL = WDTPW + WDTHOLD;	    // Stop watchdog timer
    Init_StartUp();                 //initialize device
    USB_init();
    USB_setEnabledEvents(USBEVIE);
    
    // See if we're already attached physically to USB, and if so, connect to it
    // Normally applications don't invoke the event handlers, but this is an exception.  
    if (USB_connectionInfo() & kUSB_vbusPresent)
      USB_handleVbusOnEvent();
    
    
    while(1)
    {
        switch(USB_connectionState())
        {
           case ST_USB_DISCONNECTED:
                 __bis_SR_register(LPM3_bits + GIE); 	  // Enter LPM3 w/interrupt
                _NOP();
                break;
                
           case ST_USB_CONNECTED_NO_ENUM:
                break;
                
           case ST_ENUM_ACTIVE:
                __bis_SR_register(LPM0_bits + GIE); 	  // Enter LPM0 until an event occurs.  
                // This flag would have been set by the handleDataReceived event; this event is only enabled when waiting
                // for 'press any key'
                if(bHIDDataReceived_event) 
                {
                  bHIDDataReceived_event = FALSE;            

                  // Change the event flags, in preparation for receiving 1K data
                  USBEVIE &= ~kUSB_dataReceivedEvent;      // No more data-received.  We only used this for 'press any key'
                  USBEVIE |= kUSB_receiveCompletedEvent;   // But enable receive-completed; we want to be prompted when 1K data has been received
                  USB_setEnabledEvents(USBEVIE);
                  USBHID_rejectData(0);                    // We don't care what char the key-press was

                  // Prompt user for 1K data
                  strcpy(outString,"I'm ready to receive 1K of data.\r\n");          // Prepare the outgoing string
                  if(hidSendDataWaitTilDone((BYTE*)outString,strlen(outString),0,0))   // Send it over USB
                  {
                    USBHID_abortSend(&x,0);                                          // It failed for some reason; abort and leave the main loop
                    break;
                  }
                  
                  // Set up rcv operation for 1K data
                  if(USBHID_receiveData(dataBuff,1024,0) == kUSBHID_busNotAvailable) 
                  {
                    USBHID_abortReceive(&x,0);                                       // It failed because of surprise removal or suspended by host; 
                    break;                                                           // abort and leave the main loop
                  }                  
                }
                
                // This flag would have been set by the handleReceiveCompleted event; this event is only enabled  
                // while receiving 1K data, and signals that all 1K has been received
                if(bDataReceiveCompleted_event) 
                {
                  bDataReceiveCompleted_event = FALSE;
                  strcpy(outString,"Thanks for the data.\r\n");                     // Prepare the outgoing string
                  if(hidSendDataInBackground((BYTE*)outString,strlen(outString),0,0)) // Send the response over USB
                  {
                    USBHID_abortSend(&x,0);                                         // It failed for some reason; abort and leave the main loop
                    break;
                  }
                  
                  // Change the event flags, in preparation for 'press any key'
                  USBEVIE &= ~kUSB_receiveCompletedEvent;  // No more receive-completed.  
                  USBEVIE |= kUSB_dataReceivedEvent;       // This will tell us that data -- any data -- has arrived (i.e., a key-press)
                  USB_setEnabledEvents(USBEVIE);                
                } 
                    
                break;
                
           case ST_ENUM_SUSPENDED:
                __bis_SR_register(LPM3_bits + GIE); 	// Enter LPM3 w/interrupt
                break;
                
           case ST_ENUM_IN_PROGRESS:
                break;
                
           case ST_NOENUM_SUSPENDED:
                __bis_SR_register(LPM3_bits + GIE);                
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
    // Drive all I/O's as output-low; makes sure there's no shoot-through current.  There should be
    // no floating I/Os, to prevent unnecessary current draw during USB suspend.  
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

// To be robust, an application should handle fault events that invoke the NMI vector.  
//----------------------------------------------------------------------------

VOID Init_StartUp(VOID)
{
    __disable_interrupt();               // Disable global interrupts
    
    Init_Ports();                        // Init ports (do first ports because clocks do change ports)
    SetVCore(3);                         // USB core requires the VCore set to 1.8 volt, independ of CPU clock frequency
    Init_Clock();

    __enable_interrupt();                // enable global interrupts
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

      // If bus error occured - the cleaning of flag and re-initializing of USB is required.
      SYSBERRIV = 0;            // clear bus error flag
      USB_disable();            // Disable
    }
}


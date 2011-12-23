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
 Packet Protocol Demo:

 This USB demo example is to be used with a PC application (use "UsbApp.exe")
 
 To get the demo running, run UsbApp.exe and type any number 'x' 
 between 1-9, followed by 'x' number of charaters. Once all the 'x' characters 
 are received, the phrase " I received your packet with size of 'x' bytes" is 
 sent to the PC app. 
 E.g. TX --> 2
     TX --> ab
     RX --> I received your packet with size of 2 bytes.

 If any character other than 1-9 is entered, then the following phrase is 
 returned: "Enter a valid number between 1 and 9"


-------------------------------------------------------------------------------+ 
 Please refer to the MSP430 USB API Stack Programmer's Guide,located 
 in the root directory of this installation for more details.
------------------------------------------------------------------------------*/

#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/types.h"          // Basic Type declarations
#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/usb.h"        // USB-specific functions

#include "F5xx_F6xx_Core_Lib/HAL_UCS.h"
#include "F5xx_F6xx_Core_Lib/HAL_PMM.h"

#include "USB_API/USB_HID_API/UsbHid.h"

#include <intrinsics.h>
#include <string.h>
#include "usbConstructs.h"

VOID Init_StartUp(VOID);

volatile BYTE bCommandBeingProcessed = FALSE;
volatile BYTE bDataReceiveCompleted_event = FALSE;  // data receive completed event

WORD x,y;
BYTE size;
char c[2] = "";

#define bufferLen 10            // The "size" byte can only be a single ASCII numerical digit, which means 1-9
BYTE buffer[bufferLen];
char outString[65];       // Holds outgoing strings to be sent

/*----------------------------------------------------------------------------+
| Main Routine                                                                |
+----------------------------------------------------------------------------*/
VOID main(VOID)
{
    WDTCTL = WDTPW + WDTHOLD;	    // Stop watchdog timer
    Init_StartUp();
    USB_init();
    
    USB_setEnabledEvents(kUSB_VbusOnEvent + kUSB_VbusOffEvent + kUSB_UsbSuspendEvent + kUSB_UsbResumeEvent + kUSB_receiveCompletedEvent + kUSB_UsbResetEvent);

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
                if(!bCommandBeingProcessed)                  // If no command is being processed, then make sure there's a rcv operation 
                {                                            // open to receive the start of the "packet"
                  if(!(USBHID_intfStatus(0,&x,&y) & kUSBHID_waitingForReceive))      // Only open it if we haven't already done so
                    if(USBHID_receiveData(buffer,1,0) == kUSBHID_busNotAvailable) // Start a receive operation for a single byte -- the "size" byte of the "packet"
                    {
                      USBHID_abortReceive(&x,0);                                     // Abort receive
                      break;                                 // If bus is no longer available, escape out of the loop
                    }
                }
                __bis_SR_register(LPM0_bits + GIE);          // Wait in LPM0 until a receive operation has completed
                
                if(bDataReceiveCompleted_event)
                {
                  bDataReceiveCompleted_event = FALSE;
                  if(!bCommandBeingProcessed)                // This means that the incoming byte is the start of the "packet" -- the "size" byte
                  {
                     if ((buffer[0]>=0x31) &&  (buffer[0]<= 0x39))
                    {
                        size = buffer[0]-0x30;                   // It's in ASCII, so convert it to a number
                        
                        if(USBHID_receiveData(buffer,size,0) == kUSBHID_busNotAvailable)  // And then open a rcv operation for that size
                        {
                          USBHID_abortReceive(&x,0);                                      // Abort receive
                          break;                                 // If bus is no longer available, escape out of the loop
                        }
                        bCommandBeingProcessed = TRUE;           // Now we're waiting for the "data" part of the "packet"
                    }
                    
                    else 
                    {
                       strcpy(outString,"\r\nEnter a valid number between 1 and 9\r\n\r\n");     // Prepare the outgoing string
                       if(hidSendDataInBackground((BYTE*)outString,strlen(outString),0,0)) // Send the response over USB
                       {
                          USBHID_abortSend(&x,0);                                         // Operation may still be open; cancel it
                          break;                                                          // If the send fails, escape the main loop
                        }
                        bCommandBeingProcessed = FALSE;                                   // Now we're back to waiting for the "size" byte
                    }
                  }

                  else                                       // This means that the incoming data is the "data" part of the "packet"
                  {
                    strcpy(outString,"\r\nI received your packet with size of ");     // Prepare the outgoing string
                    c[0] = (char)(size+0x30);                                    // Convert the size back to ASCII
                    c[1] = 0;                                    // Convert the size back to ASCII
                    outString[64] = 0; 
                    strcat(outString,c);
                    strcat(outString," bytes.\r\n\r\n");                              
                    if(hidSendDataInBackground((BYTE*)outString,strlen(outString),0,0)) // Send the response over USB
                    {
                      USBHID_abortSend(&x,0);                                         // Operation may still be open; cancel it
                      break;                                                          // If the send fails, escape the main loop
                    }
                    bCommandBeingProcessed = FALSE;                                   // Now we're back to waiting for the "size" byte
                  }
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
      UCSCTL7 &= ~(DCOFFG+0+0+0); // Clear OSC flaut Flags fault flags
      SFRIFG1 &= ~OFIFG;                                // Clear OFIFG fault flag
      break;
    case SYSUNIV_ACCVIFG:
      __no_operation();
      break;
    case SYSUNIV_SYSBUSIV:
      
      // If bus error occured - the cleaning of flag and re-initializing of USB is required. 
      SYSBERRIV = 0;            // clear bus error flag
      USB_disable();            // Disable 
    }
}


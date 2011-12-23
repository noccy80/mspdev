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
 HID to HID Chat Demo:

 This USB demo example is to be used with two instances of a PC application
 (e.g. Hid Demo App.) The demo application demonstrates a simple chat program
 between the two terminals; Characters that are transmitted from one terminal 
 are sent to the other.


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

#include "main.h"
#include "usbConstructs.h"
#include <intrinsics.h>
#include <string.h>

VOID ASCII(char*);

volatile BYTE bDataReceived_event0 = FALSE;
volatile BYTE bDataReceived_event1 = FALSE;

#define BUFFER_SIZE 130
#define MAX_STR_LENGTH 60

char dataBuffer[BUFFER_SIZE];
char wholeString[MAX_STR_LENGTH] = "";

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

                __no_operation();                                    // For debugger
                
                // Exit LPM because of a data-receive event, and fetch the received data 
                if(bDataReceived_event0) //HID0
                {
                	bDataReceived_event0 = FALSE;
                	count = hidReceiveDataInBuffer((BYTE*)dataBuffer,BUFFER_SIZE,0);
                  	strncat(wholeString,(char*)dataBuffer,count);
                	if(hidSendDataInBackground((BYTE*)wholeString,strlen(wholeString),1,1)) // Send message to other CDC App
                	{
                		SendError = 0x01;
                		break;
                	}
                	memset(wholeString,0,MAX_STR_LENGTH);           // Clear wholeString         
                }
                if(bDataReceived_event1)  //HID1 
                {
                  	bDataReceived_event1 = FALSE;                                // Clear flag early -- just in case execution breaks below because of an error
					count = hidReceiveDataInBuffer((BYTE*)dataBuffer,BUFFER_SIZE,1);
                  	strncat(wholeString,(char*)dataBuffer,count);
                	if(hidSendDataInBackground((BYTE*)wholeString,strlen(wholeString),0,1)) // Send message to other CDC App
                	{
                		SendError = 0x01;
                		break;
                	}
                	memset(wholeString,0,MAX_STR_LENGTH);           // Clear wholeString
					         
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


// Some terminal apps (specifically Hyperterminal) aren't very careful about clearing the most significant bit of the ASCII byte.  
// As a result, other apps capable of extended character sets may display Hyperterminal-originated characters incorrectly.  This
// function fixes this by blanking the most significant bit.  
VOID ASCII(char* string)
{
  BYTE i=0;
  BYTE len = strlen(string);    
  while((string[i] != 0x0A) && (string[i] != 0x0D) && (i < len))
  {
    string[i] = string[i] & 0x7F;
    i++;
  }
}



VOID Init_Clock(VOID)
{
	#if defined (__MSP430F563x_F663x)
		while(BAKCTL & LOCKIO)                    // Unlock XT1 pins for operation
      	BAKCTL &= ~(LOCKIO);                    // enable XT1 pins
     	// Workaround for USB7
    	UCSCTL6 &= ~XT1OFF;
    #endif
    if (USB_PLL_XT == 2)
    {
    	#if defined (__MSP430F552x) || defined (__MSP430F550x)
        	P5SEL |= 0x0C;                        // enable XT2 pins for F5529
		#elif defined (__MSP430F563x_F663x)
			P7SEL |= 0x0C;
		#endif
        // Use the REFO oscillator to source the FLL and ACLK
        UCSCTL3 = (UCSCTL3 & ~(SELREF_7)) | (SELREF__REFOCLK);
        UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK);
        
        // MCLK will be driven by the FLL (not by XT2), referenced to the REFO
        Init_FLL(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768);  // Start the FLL, at the freq indicated by the config constant USB_MCLK_FREQ
        
        //XT2_Start(XT2DRIVE_3);                                        // Start the "USB crystal"
    }
    else
    {
    	#if defined (__MSP430F552x) || defined (__MSP430F550x)
        P5SEL |= 0x10;                    // enable XT1 pins
		#endif 
        // Use the REFO oscillator to source the FLL and ACLK
        UCSCTL3 = SELREF__REFOCLK;             
        UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK); 
        
        // MCLK will be driven by the FLL (not by XT2), referenced to the REFO
        Init_FLL(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768); // set FLL (DCOCLK)
        
        //XT1_Start(XT1DRIVE_3);                                       // Start the "USB crystal"
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


// (c)2010 by Texas Instruments Incorporated, All Rights Reserved.
/*----------------------------------------------------------------------------*
|                                                                             |
|                              Texas Instruments                              |
|                                                                             |
|                          MSP430 USB-Example (CDC/HID Driver)                |
|                                                                             |
+-----------------------------------------------------------------------------+
|  Source: main.c, v2.0 2011/02/06                                           |
------------------------------------------------------------------------------+   
Keyboard HID Demo:

This code implements a "keyboard" using a FET target board as hardware.  Pressing
S1 represents pressing an ordinary key on the keyboard.  Holding down S2 while
you do it represents holding down the SHIFT key.  Run Notepad, or any program
that accepts keyboard input, and attach the FET target board.  Pressing S1 results
in "msp430" being entered.  Holding S2 down at the same time results in "MSP$#)".  

A standard keyboard report descriptor is set up in descriptors.c.  The polling
interval for this report is 48ms.  Whenever S1 is pressed, the PORT1 ISR evaluates
whether S2 is also held down, then populates the HID report accordingly.  It 
then flags main() to send the report.  Immediately a blank report follows it, 
otherwise Windows takes this as an indication of repeating the text indefinitely.  

During USB attachment, the application spends its time in LPM0, until the button
is pressed.  When disconnected, or if attached to a powered hub without a host
(ST_NOENUM_SUSPENDED), or if suspended, the corresponding event handlers 
disable port interrupts, and the device enters LPM3.  Port interrupts are 
re-enabled at resume or attachment with the corresponding event handlers.  

+----------------------------------------------------------------------------+
 Please refer to the MSP430 USB API Stack Programmer's Guide,located 
 in the root directory of this installation for more details.
//----------------------------------------------------------------------------*/

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
#include "main.h"                  // HID key codes stored here

VOID Init_Ports(VOID);
VOID Init_Clock(VOID);
  
BYTE report[8];                    // Standard keyboard input report
BYTE buttonPressed=FALSE;

/*----------------------------------------------------------------------------+
| Main Routine                                                                |
+----------------------------------------------------------------------------*/
VOID main(VOID)
{
    WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer
    Init_Ports();             // Init ports (do first ports because clocks do change ports)
    Init_Clock();             // Init clocks
    
    USB_init();               // Init USB

    // Enable all USB-level events
    USB_setEnabledEvents(kUSB_VbusOnEvent+kUSB_VbusOffEvent+kUSB_UsbSuspendEvent+kUSB_UsbResumeEvent);

    // Configure pushbuttons
    // S1 will represent a key getting pressed; S2 will represent the SHIFT key
    P1OUT |= (BIT6 | BIT7);  // Enable the integrated pullup for P1.6 and P1.7
    P1REN |= (BIT6 | BIT7);  // Enable the integrated pullup for P1.6 and P1.7
    P1IFG = 0;               // Ensure no flags
    P1IE |= BIT6;            // Enable a pullup for S1 only
    
    __enable_interrupt();    // Enable interrupts 

    
    // In case USB is already attached (meaning no VBUS event will 
    // occur), manually start the connection 
    if (USB_connectionInfo() & kUSB_vbusPresent)
      USB_handleVbusOnEvent();
    
    
    while(1)
    {
      switch(USB_connectionState())
      {
         case (ST_USB_DISCONNECTED | ST_NOENUM_SUSPENDED):
               __bis_SR_register(LPM3_bits + GIE); 	// Enter LPM3 w/interrupt.  Nothing for us to do while disconnected.  

               break;
              
         case ST_USB_CONNECTED_NO_ENUM:
              break;
              
         case ST_ENUM_ACTIVE:
           
              __bis_SR_register(LPM0_bits + GIE); 	   // Enter LPM0 w/interrupt, until a keypress occurs
              
              if (buttonPressed)                       // Has a keypress really occurred?  
              {
                // Then send the report created in the PORT1 ISR
                USBHID_sendReport((void *)&report, 0); 
                
                // Send a blank report, to signal the end of the text
                BYTE i;
                for(i = 0; i < 8; i++)                 
                  report[i] = 0x00;
                USBHID_sendReport((void *)&report, 0);  

                // Clear the flag
                buttonPressed = FALSE;                 
              } 
              break;  
              
         case ST_ENUM_SUSPENDED:
              __bis_SR_register(LPM3_bits + GIE); 	// Enter LPM3 w/interrupt.  Nothing for us to do while 

              break;                                // suspended.  (Remote wakeup isn't enabled in this example.)
              
         case ST_ENUM_IN_PROGRESS:
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
  #if defined (__MSP430F563x_F663x)
  while(BAKCTL & LOCKIO)                    // Unlock XT1 pins for operation
    BAKCTL &= ~(LOCKIO);                  // enable XT1 pins
  // Workaround for USB7
  UCSCTL6 &= ~XT1OFF;
  #endif
  //Initialization of clock module
  if (USB_PLL_XT == 2)
  {
    #if defined (__MSP430F552x) || defined (__MSP430F550x)
    P5SEL |= 0x0C;                        // enable XT2 pins for F5529
    #elif defined (__MSP430F563x_F663x)
    P7SEL |= 0x0C;
    #endif

    // use REFO for FLL and ACLK
    UCSCTL3 = (UCSCTL3 & ~(SELREF_7)) | (SELREF__REFOCLK);
    UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK);

    Init_FLL(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768);             // set FLL (DCOCLK)
  }
  else
  {
    #if defined (__MSP430F552x) || defined (__MSP430F550x)
    P5SEL |= 0x10;                    // enable XT1 pins
    #endif 
    UCSCTL3 = SELREF__REFOCLK;            // run FLL mit REF_O clock
    UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK); // set ACLK = REFO
    Init_FLL(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768);       // set FLL (DCOCLK)
  }
}

//----------------------------------------------------------------------------

VOID Init_Ports(VOID)
{
  // Initialization of ports (all unused pins as outputs with low-level
  P2OUT = 0x00;
  P2DIR = 0xFF;

  // Initialize port 3
  P3OUT = 0x00;
  P3SEL = 0x03;                           // Assign I2C pins to USCI_B0
  P3DIR = 0xFF;

  // Initialize port 4
  P4OUT = 0x00;
  P4DIR = 0xFF;

  // Initialize all other port pins. Use word-access to initialize
  // two ports simultaneously.
  PCOUT = 0x0000;
  PCDIR = 0xFFFF;
  
  #ifndef __MSP430F550x
  PDOUT   =   0x0000;      //	If using a device other than: 
  PDDIR   =   0xFFFF;      //	F5510, F5529, F5638, or F6638 
                //	you may need to comment out these lines 
  #endif 
  
  #if defined (__MSP430F563x_F663x)
  P9OUT   =   0x00;
  P9DIR   =   0xFF;
  #endif
  
  PJOUT = 0x0000;
  PJDIR = 0xFFFF;
}


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
      UCSCTL7 &= ~(DCOFFG+0+0+XT2OFFG); // Clear OSC flaut Flags fault flags
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


#pragma vector=PORT1_VECTOR
__interrupt void Port1_ISR(void)
{ 
  WORD i;
  if(P1IFG & BIT6)
  {
    for(i=0x23FF;i>0;i--);   // Cheap debounce.  
    
    if(P1IN & BIT6)
    {
      if(!(P1IN & BIT7))
        report[0] = 0x02;    // This byte is a bitfield for modifier keys.  If S2 is pressed, 
      else                   // signal the "left shift" key; else no modifier keys
        report[0] = 0x00;    
      report[1] = 0x00;      // Reserved
      report[2] = usbUsageM; // The remaining six bytes are for entered text.  It allows up 
      report[3] = usbUsageS; // to six in a single report.  Since we don't have the hardware 
      report[4] = usbUsageP; // for a true keyboard, let's just fill it with a six-letter word.
      report[5] = usbUsage4; // A real keyboard app would put whatever keys had been pressed
      report[6] = usbUsage3; // since the last report.  
      report[7] = usbUsage0;
      
      // Set flag to wake main.  We can't call the USB API functions out of an interrupt context
      buttonPressed = TRUE;
      __bic_SR_register_on_exit(LPM3_bits);  // Wake main from LPMx
    }
    P1IFG = 0;
  }
}

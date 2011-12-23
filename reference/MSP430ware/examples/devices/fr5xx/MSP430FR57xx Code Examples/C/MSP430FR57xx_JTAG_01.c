//******************************************************************************
//  MSP430FR57x Demo - Secure JTAG access using a password
//
//  Description: The FR5739 JTAG interface can be secured to allow only password
//  protected access to the device. This is done by saving a special JTAG 
//  signature, the length of the password and the actual password in the JTAG 
//  signature location. The code example shows how this is done. 
//  Once this example is executed NO FURTHER ACCESS to the device is possible 
//  unless the password is proivded via the tool chain. 
//  IAR V5.10 or greater is required to provide the tool chain support for the 
//  password check. 
//  After the first time, use the JTAG password 0x22221111 via the tool chain to
//  access the device. The password can be supplied at the IAR project options 
//  menu by going to Project --> Options --> FET Debugger --> Download and 
//  entering the password in the 'JTAG password' window. 
//
//           MSP430FR5739
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2011
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************
#include "msp430fr5739.h"

//pointer init 

unsigned int *JTAG1 = 0;
unsigned int *JTAG2 = 0;
unsigned long *JTAGPWD = 0;

void main(void)
{  
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT  


  JTAG1 = (unsigned int *)0xFF80;          // JTAG signature 1
  JTAG2 = (unsigned int *)0xFF82;          // JTAG signature 2
  JTAGPWD = (unsigned long *)0xFF88;       // JTAG password location
   
  *JTAG1 = 0xAAAA;                          // Enable JTAG lock/unlock with pwd
  *JTAG2 = 0x0002;                          // Pwd length = 2 words
  *JTAGPWD = 0x11112222;                    // Pwd = 0x22221111
  
  // To disable the password mechanism write 0xFFFF to JTAG1 and JTAG2 locations
  // Also erase JTAGPWD location

  
  while(1);  

}
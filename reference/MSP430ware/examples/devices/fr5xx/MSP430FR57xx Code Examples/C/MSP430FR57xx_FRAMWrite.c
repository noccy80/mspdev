//******************************************************************************
//   MSP430FR57xx Demo - Long word writes to FRAM
//
//   Description: Use long word write to write to 512 byte blocks of FRAM.
//   Toggle LED after every 100 writes.
//   NOTE: Running this example for extended periods will impact the FRAM
//   endurance. 
//   ACLK = VLO, MCLK = SMCLK = 4MHz
// 
//           MSP430FR57x
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |               |  
//        |          P1.0 |---> LED
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************

#include "msp430fr5739.h"

void FRAMWrite(void);

unsigned char count = 0;
unsigned long *FRAM_write_ptr; 
unsigned long data;

#define FRAM_TEST_START 0xCA00


void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT  
  // Configure MCLK for 8MHz operation 
  CSCTL0_H = 0xA5;
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;            // Set max. DCO setting
  CSCTL2 = SELA_0 + SELS_3 + SELM_3;        // ACLK = VLO
  CSCTL3 = DIVA_0 + DIVS_1 + DIVM_1;        // MCLK = SMCLK = DCO/2
  
  // Turn off temp sensor
  REFCTL0 |= REFTCOFF; 
  REFCTL0 &= ~REFON;

  // Turn on LED 
  P1DIR |= BIT0;
  // Initialize dummy data
  data = 0x11111111;

  while(1)
  { 
  data += 0x00010001;
  FRAM_write_ptr = (unsigned long *)FRAM_TEST_START;   
  FRAMWrite();                              // Endless loop 
  count++;
  if (count > 100)
    {
      P1OUT ^= 0x01;                        // Toggle LED to show 512K bytes 
      count = 0;                            // ..have been written
      data = 0x11111111;
    }

  }
  
}


void FRAMWrite (void)

{
 unsigned int i=0;

  for ( i= 0; i<128; i++)
  {
    *FRAM_write_ptr++ = data;
  }
  
}



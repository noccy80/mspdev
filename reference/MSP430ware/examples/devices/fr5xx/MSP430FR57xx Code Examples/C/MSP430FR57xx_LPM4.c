//******************************************************************************
//   MSP430FR57xx Demo - Enters LPM4
//
//   Description: Device enters LPM4
// 
//           MSP430FR57x
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |               |  
//        |          P1.0 |---> Disconnect JP3 for power meas.
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************

#include "msp430fr5739.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT  
 
  P1DIR = 0; 
  P1OUT = 0; 
  P1REN = 0xFF;
  
  P2DIR = 0; 
  P2OUT = 0; 
  P2REN = 0xFF;
  
  P3DIR = 0; 
  P3OUT = 0; 
  P3REN = 0xFF;
  
  P4DIR = 0; 
  P4OUT = 0; 
  P4REN = 0xFF;
  
  CSCTL0_H = 0xA5;
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;             // Set max. DCO setting
  CSCTL2 = SELA_1 + SELS_3 + SELM_3;        // set ACLK = VLO; MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_1 + DIVM_1;        // set all dividers 
  
  CSCTL4 = XT1OFF + XT2OFF;
  CSCTL5 &= ~(XT1OFFG + XT2OFFG);
  
  PJDIR = 0;
  PJOUT = 0;
  PJREN = 0xFF;
  
  REFCTL0 |= REFTCOFF; 
  REFCTL0 &= ~REFON;

  __bis_SR_register(LPM4_bits);
  
}



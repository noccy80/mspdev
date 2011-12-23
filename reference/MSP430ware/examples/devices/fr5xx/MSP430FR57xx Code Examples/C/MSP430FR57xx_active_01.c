//******************************************************************************
//   MSP430FR57xx Demo - Stay in active mode with MCLK = 8MHz
//
//   Description: Configure ACLK = VLO, MCLK = 8MHz.
//   Note: On the FET board P1.0 drives an LED that can show high power numbers 
//   when turned ON. Measure current with LED jumper JP3 disconnected.
//   LED jumper disconnected.
//   ACLK = VLO, MCLK = SMCLK = 8MHz
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
void ACTIVE_MODE_TEST(void);

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
  
  PJDIR = 0xFF;
  PJOUT = 0;
   
  CSCTL0_H = 0xA5;
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;            // Set max. DCO setting
  CSCTL2 = SELA_0 + SELS_3 + SELM_3;        // ACLK = VLO
  CSCTL3 = DIVA_0 + DIVS_1 + DIVM_1;        // MCLK = SMCLK = DCO/2
  
  
  REFCTL0 |= REFTCOFF; 
  REFCTL0 &= ~REFON;

  // Turn on LED 
  P1DIR |= BIT0;
  
  ACTIVE_MODE_TEST();                       // Endless loop 
  
}

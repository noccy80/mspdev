//******************************************************************************
//   MSP430FR57xx Demo - Enters LPM3 with ACLK = LFXT1
//
//   Description: Configure ACLK = LFXT1 and enters LPM3. 
//   Note: On the FET board P1.0 drives an LED that can show high power numbers 
//   when turned ON. Measure current with LED jumper JP3 disconnected.
//   LED jumper disconnected.
//   ACLK = LFXT1 = 32kHz, MCLK = SMCLK = 4MHz
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
  WDTCTL = WDTPW + WDTTMSEL + WDTSSEL_1 + WDTIS_4; // ACLK, 1s interrupts
  SFRIE1 |= WDTIE;                          // Enable WDT interrupt
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
  
  // XT1 Setup 
  
  PJSEL0 |= BIT4 + BIT5; 
  
  CSCTL0_H = 0xA5;
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;             // Set max. DCO setting
  CSCTL2 = SELA_0 + SELS_3 + SELM_3;        // set ACLK = XT1; MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_1 + DIVM_1;        // set all dividers 
  CSCTL4 |= XT1DRIVE_0; 
  CSCTL4 &= ~XT1OFF;
  
  do
  {
    CSCTL5 &= ~XT1OFFG;
                                            // Clear XT1 fault flag
    SFRIFG1 &= ~OFIFG; 
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  
  // Turn off Temp sensor
  REFCTL0 |= REFTCOFF; 
  REFCTL0 &= ~REFON;

  // Turn on LED 
  P1DIR |= BIT0;
  __bis_SR_register(LPM3_bits+GIE);
  
}


// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0 (LED)
}
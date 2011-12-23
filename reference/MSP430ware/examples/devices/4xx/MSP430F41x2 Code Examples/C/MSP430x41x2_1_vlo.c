//******************************************************************************
//  MSP430x41x2 Demo - Software Toggle P1.0, MCLK = VLO/8
//
//  Description; Pulse P5.1 with a 1/100 active duty cycle using software.
//  Ultra-low frequency ~ 10kHz, ultra-low power active mode demonstrated. All 
//  the 7 I/O ports are configured as low outputs to eliminate floating inputs.
//  ACLK = VL0, MCLK = VLO ~ 10kHz, SMCLK = n/a
//
//               MSP430x41x2
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//            |        P1.1/MCLK|-->MCLK = VLO
//            |        P1.6/ACLK|-->ACLK = VLO
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************

#include  <msp430x41x2.h>


volatile unsigned int i;                    // volatile to prevent optimization

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL1 |= SELM0 + SELM1;                // MCLK = VLO
  FLL_CTL2 |= LF1XT1S_2;                    // LFXT1 = VLOCLK

  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  
  __bis_SR_register(SCG1 + SCG0);           // Stop DCO
 
  
  P1DIR = 0xFF;                             // All P1.x outputs
  P1OUT = 0;                                // All P1.x reset
  P2SEL = 0;                                // All P2.x GPIO function
  P2DIR = 0xFF;                             // All P2.x outputs
  P2OUT = 0;                                // All P2.x reset
  P3DIR = 0xFF;                             // All P3.x outputs
  P3OUT = 0;                                // All P3.x reset
  P4DIR = 0xFF;                             // All P4.x outputs
  P4OUT = 0;                                // All P4.x reset
  P5DIR = 0xFF;                             // All P5.x outputs
  P5OUT = 0;                                // All P5.x reset
  P6DIR = 0xFF;                             // All P6.x outputs
  P6OUT = 0;                                // All P6.x reset
  P7DIR = 0xFF;                             // All P7.x outputs
  P7OUT = 0;                                // All P7.x reset  
  
  P1SEL = BIT1+BIT6;                        // P1.1 & P1.6 to output MCLK & ACLK
  
  for (;;)
  {
    P5OUT |= 0x02;
    for (i = 10; i > 0; i--);               // Delay 1x
    P5OUT &= ~0x02;
    for (i = 1000; i > 0; i--);             // Delay 100x
  }
}

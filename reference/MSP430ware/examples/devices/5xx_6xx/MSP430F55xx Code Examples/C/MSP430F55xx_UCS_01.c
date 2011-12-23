//******************************************************************************
//   MSP430F552x Demo - Software Toggle P1.1 at Default DCO
//
//   Description: Toggle P1.0 by xor'ing P1.1 inside of a software loop.
//   ACLK is rought out on pin P1.0, SMCLK is brought out on P2.2, and MCLK
//   is brought out on pin P7.7.
//   ACLK = REFO = 32.768kHz, MCLK = SMCLK = Default 1MHz
//
//                 MSP430F552x
//             -----------------
//         /|\|                 |
//          | |             P1.0|-->ACLK
//          --|RST          P7.7|-->MCLK
//            |             P2.2|-->SMCLK
//            |                 |
//            |             P1.1|-->Port Pin
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5529.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P1DIR |= BIT1;                            // P1.1 output

  P1DIR |= BIT0;                            // ACLK set out to pins
  P1SEL |= BIT0;                            
  P2DIR |= BIT2;                            // SMCLK set out to pins
  P2SEL |= BIT2;                            
  P7DIR |= BIT7;                            // MCLK set out to pins
  P7SEL |= BIT7;                              

  while(1)
  {
    P1OUT ^= BIT1;
    __delay_cycles(60000);                  // Delay
  }
}

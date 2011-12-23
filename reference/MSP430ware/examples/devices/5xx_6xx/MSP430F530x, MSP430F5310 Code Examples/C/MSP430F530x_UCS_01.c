//******************************************************************************
//   MSP430F530x Demo - Software Toggle P1.1 at Default DCO
//
//   Description: Toggle P1.0 by xor'ing P1.1 inside of a software loop.
//   ACLK is brought out on pin P1.0, SMCLK is brought out on P2.2, and MCLK
//   is brought out on pin P7.7.
//   ACLK = REFO = 32.768kHz, MCLK = SMCLK = Default 1MHz
//
//                 MSP430F530x
//             -----------------
//         /|\|                 |
//          | |             P1.0|-->ACLK
//          --|RST          P7.7|-->MCLK
//            |             P2.2|-->SMCLK
//            |                 |
//            |             P1.1|-->Port Pin
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  
  PMAPPWD = 0x02D52;                        // Enable Write-access to modify port mapping registers
  P4MAP7 = PM_MCLK;
  PMAPPWD = 0;                              // Disable Write-Access to modify port mapping registers
  
  P1DIR |= BIT1;                            // P1.1 output

  P1DIR |= BIT0;                            // ACLK set out to pins
  P1SEL |= BIT0;                            
  P2DIR |= BIT2;                            // SMCLK set out to pins
  P2SEL |= BIT2;                            
  P4DIR |= BIT7;                            // MCLK set out to pins
  P4SEL |= BIT7;                              

  while(1)
  {
    P1OUT ^= BIT1;
    __delay_cycles(60000);                  // Delay
  }
}

//******************************************************************************
//  CC430F613x Demo - Timer_A3, Toggle P2.1/TA1.0, Up/Down Mode, DCO SMCLK
//
//  Description: Toggle P2.0 using hardware TA1.0 output. Timer1_A is configured
//  for up/down mode with CCR0 defining the period. In this example, CCR0 is 
//  loaded with 250. Thus the output frequency on P2.0 will be the TACLK/1000.
//  No CPU or software resources required.
//  As coded with TACLK = SMCLK, P2.0 output frequency is ~1.045M/1000.
//  SMCLK = MCLK = TACLK = default DCO ~1.045MHz
//
//                CC430F6137
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P2.0/TA1.0|--> SMCLK/1000
//
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x613x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P2MAP0 = PM_TA1CCR0A;                     // Map TA1CCR0 output to P2.0 
  PMAPPWD = 0;                              // Lock port mapping registers 
  
  P2DIR |= BIT0;                            // P2.0 output
  P2SEL |= BIT0;                            // P2.0 option select
  
  TA1CCTL0 = OUTMOD_4;                      // CCR0 toggle mode
  TA1CCR0 = 250;
  TA1CTL = TASSEL_2 + MC_3 + TACLR;         // SMCLK, up-downmode, clear TAR

  __bis_SR_register(LPM0_bits);             // Enter LPM0
  __no_operation();                         // For debugger
}

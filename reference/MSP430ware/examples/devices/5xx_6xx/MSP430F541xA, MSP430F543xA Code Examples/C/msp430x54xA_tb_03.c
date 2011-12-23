//******************************************************************************
//  MSP430F543xA Demo - Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and Timer_B overflow ISR.
//  In this example an ISR triggers when TB overflows.  TB overflow has the
//  lowest priority. Inside the TB overflow ISR P1.0 is toggled. Toggle rate is
//  approximatlely 7.822Hz = [1.045MHz/FFFFh]/2. Proper use of TBIV interrupt vector
//  generator is shown.
//  ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO ~1.045MHz.
//
//           MSP430F5438A
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |           P1.0|-->LED
//
//   M. Morales
//   Texas Instruments Inc.
//   June 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54xA.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  TBCTL = TBSSEL_2 + MC_2 + TBCLR + TBIE;   // SMCLK, contmode, clear TBR
                                            // enable interrupt

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
  __no_operation();                         // For debugger
}

// Timer_B7 Interrupt Vector (TBIV) handler
#pragma vector=TIMERB1_VECTOR
__interrupt void TIMERB1_ISR(void)
{
  /* Any access, read or write, of the TBIV register automatically resets the
  highest "pending" interrupt flag. */
  switch( __even_in_range(TBIV,14) )
  {
    case  0: break;                          // No interrupt
    case  2: break;                          // CCR1 not used
    case  4: break;                          // CCR2 not used
    case  6: break;                          // CCR3 not used
    case  8: break;                          // CCR4 not used
    case 10: break;                          // CCR5 not used
    case 12: break;                          // CCR6 not used
    case 14: P1OUT ^= 0x01;                  // overflow
            break;
    default: break;
  }
}


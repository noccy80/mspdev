//******************************************************************************
//  MSP430F51x2 Demo - TimerD0, Toggle P1.0, Overflow ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and TimerD0 overflow ISR.
//  In this example an ISR triggers when TD overflows. Inside the TD
//  overflow ISR P1.0 is toggled. Toggle rate is approximatlely 16Hz.
//  Proper use of the TDIV interrupt vector generator is demonstrated.
//  ACLK = n/a, MCLK = SMCLK = TDCLK = default DCO ~1.045MHz
//
//           MSP430F51x2
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |           P1.0|-->LED
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  TD0CTL0 = TDSSEL_2 + MC_2 + TDCLR + TDIE; // SMCLK, contmode, clear TDR
                                            // enable interrupt

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
  __no_operation();                         // For debugger
}

// Timer0_D1 Interrupt Vector (TDIV) handler
#pragma vector=TIMER0_D1_VECTOR
__interrupt void TIMER0_D1_ISR(void)
{
  switch(__even_in_range(TD0IV,30))
  {
    case  0: break;                          // No interrupt
    case  2: break;                          // CCR1 not used
    case  4: break;                          // CCR2 not used
    case  6: break;                          // reserved
    case  8: break;                          // reserved
    case 10: break;                          // reserved
    case 12: break;                          // reserved
    case 14: break;
    case 16: P1OUT ^= 0x01;                  // overflow
             break;
    case 18: break;                          // Clock fail low
    case 20: break;                          // Clock fail high
    case 22: break;                          // Hi-res freq locked
    case 24: break;                          // Hi-res freq unlocked
    case 26: break;                          // reserved
    case 28: break;                          // reserved
    case 30: break;                          // reserved       
    default: break; 
  }
}


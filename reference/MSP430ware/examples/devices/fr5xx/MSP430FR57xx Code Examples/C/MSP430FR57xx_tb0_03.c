//******************************************************************************
//  MSP430FR57x Demo - TimerB, Toggle P1.0, Overflow ISR, DCO SMCLK 
//
//  Description: Toggle P1.0 using software and the TimerB overflow ISR.
//  In this example an ISR triggers when TB overflows. Inside the ISR P1.0
//  is toggled.Proper use of the TBIV interrupt
//  vector generator is demonstrated.
//  
//  ACLK = n/a, MCLK = SMCLK = 1MHz
//
//
//           MSP430FR5739
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |           P1.0|-->LED
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
  
  CSCTL0_H = 0xA5;
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;             // Set max. DCO setting
  CSCTL2 = SELA_1 + SELS_3 + SELM_3;        // set ACLK = VLO; MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_3 + DIVM_3;        // set all dividers 
  
  P1DIR |= BIT0;
  P1OUT |= BIT0;
  
  TB0CTL = TBSSEL_2 + MC_2 + TBCLR + TBIE;  // SMCLK, contmode, clear TBR
                                            // enable interrupt

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM3, enable interrupts
  __no_operation();                         // For debugger
}

// TimerB Interrupt Vector (TBIV) handler
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void)
{
  switch(__even_in_range(TB0IV,14))
  {
    case  0: break;                          // No interrupt
    case  2: break;                          // CCR1 not used
    case  4: break;                          // CCR2 not used
    case  6: break;                          // reserved
    case  8: break;                          // reserved
    case 10: break;                          // reserved
    case 12: break;                          // reserved
    case 14: P1OUT ^= 0x01;                  // overflow
             break;
    default: break; 
  }
}


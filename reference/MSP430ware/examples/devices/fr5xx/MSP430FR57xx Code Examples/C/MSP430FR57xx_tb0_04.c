//******************************************************************************
//  MSP430FR57x Demo - TimerB, Toggle P1.0, Overflow ISR, 32kHz ACLK
//
//  Description: Toggle P1.0 using software and the TimerB overflow ISR.
//  In this example an ISR triggers when TB overflows. Inside the ISR P1.0
//  is toggled. Toggle rate is exactly 0.5Hz. Proper use of the TBIV interrupt
//  vector generator is demonstrated.
//  
//  ACLK = TACLK = 32768Hz, MCLK = SMCLK = 4MHz
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
  // setup XT1  
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

  P1DIR |= BIT0;
  P1OUT |= BIT0;
  
  TB0CTL = TBSSEL_1 + MC_2 + TBCLR + TBIE;  // ACLK, contmode, clear TBR
                                            // enable interrupt

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, enable interrupts
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


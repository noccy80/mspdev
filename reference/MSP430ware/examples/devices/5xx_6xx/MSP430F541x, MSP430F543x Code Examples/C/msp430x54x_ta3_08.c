//******************************************************************************
//  MSP430F5438 Demo - Timer_A3, Toggle P1.0;P2.1-3, Cont. Mode ISR, 32kHz ACLK
//
//  Description: Use Timer1_A CCRx units and overflow to generate four
//  independent timing intervals. For demonstration, CCR0, CCR1 and CCR2
//  output units are optionally selected with port pins P2.1, P2.2 and P2.3
//  in toggle mode. As such, these pins will toggle when respective CCRx
//  registers match the TAR counter. Interrupts are also enabled with all
//  CCRx units, software loads offset to next interval only - as long as
//  the interval offset is added to CCRx, toggle rate is generated in
//  hardware. Timer1_A overflow ISR is used to toggle P1.0 with software.
//  Proper use of the TAIV interrupt vector generator is demonstrated.
//  ACLK = TACLK = 32kHz, MCLK = SMCLK = default DCO ~1.045MHz
//
//  As coded and with TACLK = 32768Hz, toggle rates are:
//  P2.1= CCR0 = 32768/(2*4) = 4096Hz
//  P2.2= CCR1 = 32768/(2*16) = 1024Hz
//  P2.3= CCR2 = 32768/(2*100) = 163.84Hz
//  P1.0= overflow = 32768/(2*65536) = 0.25Hz
//
//               MSP430F5438
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P2.1/TA1.0|--> CCR0
//           |         P2.2/TA1.1|--> CCR1
//           |         P2.3/TA1.2|--> CCR2
//           |               P1.0|--> Overflow/software
//           |               P1.0|--> LED
//
//   M Smertneck / W. Goh
//   Texas Instruments Inc.
//   September 2008
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P2SEL |= 0x0E;                            // P1.1 - P1.3 option select
  P2DIR |= 0x0E;                            // P2.1 - P2.3 outputs
  P1DIR |= 0x01;                            // P1.0 - Outputs
  TA1CCTL0 = OUTMOD_4 + CCIE;               // CCR0 toggle, interrupt enabled
  TA1CCTL1 = OUTMOD_4 + CCIE;               // CCR1 toggle, interrupt enabled
  TA1CCTL2 = OUTMOD_4 + CCIE;               // CCR2 toggle, interrupt enabled
  TA1CTL = TASSEL_1 + MC_2 + TACLR + TAIE;  // ACLK, contmode, clear TAR,
                                            // interrupt enabled

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, interrupts enabled
  __no_operation();                         // For debugger
}

// Timer1 A0 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A0 (void)
{
  TA1CCR0 += 4;                             // Add Offset to CCR0
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void)
{
  switch(__even_in_range(TA1IV,14))
  {
    case 0: break;                  
    case 2:  TA1CCR1 += 16;                 // Add Offset to CCR1
             break;
    case 4:  TA1CCR2 += 100;                // Add Offset to CCR2
             break;
    case 6:  break;                         // CCR3 not used
    case 8:  break;                         // CCR4 not used
    case 10: break;                         // CCR5 not used
    case 12: break;                         // Reserved not used
    case 14: P1OUT ^= 0x01;                 // overflow
             break;
    default: break;
 }
}


//******************************************************************************
//  MSP430F22x4 Demo - Basic Clock, Implement Cont. SW FLL with Auto RSEL
//
//  Description: Set DCO clock to (Delta)*(4096) using software FLL. DCO clock
//  is output on P1.4 as SMCLK.  DCO clock, which is the selected SMCLK source
//  for timer_A is integrated over ACLK/8 (4096) continuously. CCR2 captures
//  ACLK/8.  To use this SW FLL, Timer_A must be operating in continous mode
//  with a watch crystal used for ACLK. Delta must be kept in a  range that
//  allows possible DCO speeds.  Minimum Delta must ensure
//  the AdjDCO ISR can complete. Maximum delta  can be calculated by
//  f(DCOx7) / 4096.  f(DCOx7) found in device specific datasheet.
//  ACLK = LFXT1/8 = 32768/8, MCLK = SMCLK = DCO = 4096xDelta
//  //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//           MSP430F22x4
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P2.1|--> SMLCK = target DCO
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

#define DELTA 2930                // target DCO = DELTA*(4096) = 12MHz
//#define DELTA 977                 // target DCO= DELTA*(4096) = 4MHz
//#define DELTA 900                 // target DCO= DELTA*(4096) = 3686400
//#define DELTA 256                 // target DCO= DELTA*(4096) = 1048576
//#define DELTA 70                  // target DCO = DELTA*(4096) = 286720

unsigned int Compare, Oldcapture;
volatile unsigned int i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  for (i = 0; i < 0xfffe; i++);             // Delay for XTAL stabilization
  BCSCTL1 |= DIVA_3;                        // ACLK= LFXT1CLK/8
  TACCTL2 = CM_1 + CCIS_1 + CAP + CCIE;     // CAP, ACLK, interrupt
  TACTL = TASSEL_2 + MC_2 + TACLR;          // SMCLK, cont-mode, clear
  P2DIR |= 0x02;                            // P2.1 output
  P2SEL |= 0x02;                            // P2.1 SMCLK output

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
  switch (TAIV)        // Efficient switch-implementation
  {
    case  2: break;                         // TACCR1 not used
    case  4:
      Compare = TACCR2;                     // Get current captured SMCLK
      Compare = Compare - Oldcapture;       // SMCLK difference
      Oldcapture = TACCR2;                  // Save current captured SMCLK
      if (DELTA == Compare) break;          // If equal, leave "While(1)"
      if (DELTA < Compare)
      {
        DCOCTL--;                           // DCO is too fast, slow it down
        if (DCOCTL == 0xFF)                 // Did DCO roll under?
          if (BCSCTL1 & 0x0f)
            BCSCTL1--;                      // Sel lower RSEL
      }
      else
      {
        DCOCTL++;                           // DCO is too slow, speed it up
        if (DCOCTL == 0x00)                 // Did DCO roll over?
          if ((BCSCTL1 & 0x0f) != 0x0f)
            BCSCTL1++;                      // Sel higher RSEL
      }
    case 10: break;                         // Overflow not used
  }
}


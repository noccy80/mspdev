//******************************************************************************
//  MSP430F22x4 Demo - Basic Clock, Implement Auto RSEL SW FLL
//
//  Description: Set DCO clock to (Delta)*(4096) using software FLL. DCO clock
//  is output on P1.4 as SMCLK.  DCO clock, which is the selected SMCLK source
//  for timer_A is integrated over LFXT1/8 (4096) until SMCLK is is equal
//  to Delta.  CCR2 captures ACLK.  To use Set_DCO Timer_A must be
//  operating in continous mode.  Watch crystal for ACLK is required for
//  this example.  Delta must be kept in a range that allows possible
//  DCO speeds.  Minimum Delta must ensure that Set_DCO loop
//  can complete within capture interval. Maximum delta can be calculated by
//  f(DCOx7) / 4096.  f(DCOx7) can be found in device specific datasheet.
//  ACLK = LFXT1/8 = 32768/8, MCLK = SMCLK = target DCO
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//
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
//#define DELTA 900                 // target DCO = DELTA*(4096) = 3686400
//#define DELTA 256                 // target DCO = DELTA*(4096) = 1048576
//#define DELTA 70                  // target DCO = DELTA*(4096) = 286720

volatile unsigned int i;

void Set_DCO(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  for (i = 0; i < 0xfffe; i++);             // Delay for XTAL stabilization
  P2DIR |= 0x02;                            // P2.1 output
  P2SEL |= 0x02;                            // P2.1 SMCLK output
  Set_DCO();                                // Set DCO

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

void Set_DCO(void)                          // Set DCO to selected frequency
{
  unsigned int Compare, Oldcapture = 0;

  BCSCTL1 |= DIVA_3;                        // ACLK= LFXT1CLK/8
  TACCTL2 = CM_1 + CCIS_1 + CAP;            // CAP, ACLK
  TACTL = TASSEL_2 + MC_2 + TACLR;          // SMCLK, cont-mode, clear

  while (1)
  {
    while (!(CCIFG & TACCTL2));             // Wait until capture occured
    TACCTL2 &= ~CCIFG;                      // Capture occured, clear flag
    Compare = TACCR2;                       // Get current captured SMCLK
    Compare = Compare - Oldcapture;         // SMCLK difference
    Oldcapture = TACCR2;                    // Save current captured SMCLK

    if (DELTA == Compare)
      break;                                // If equal, leave "while(1)"
    else if (DELTA < Compare)
    {
      DCOCTL--;                             // DCO is too fast, slow it down
      if (DCOCTL == 0xFF)                   // Did DCO roll under?
        if (BCSCTL1 & 0x0f)
          BCSCTL1--;                        // Select lower RSEL
    }
    else
    {
      DCOCTL++;                             // DCO is too slow, speed it up
      if (DCOCTL == 0x00)                   // Did DCO roll over?
        if ((BCSCTL1 & 0x0f) != 0x0f)
          BCSCTL1++;                        // Sel higher RSEL
    }
  }
  TACCTL2 = 0;                              // Stop TACCR2
  TACTL = 0;                                // Stop Timer_A
}

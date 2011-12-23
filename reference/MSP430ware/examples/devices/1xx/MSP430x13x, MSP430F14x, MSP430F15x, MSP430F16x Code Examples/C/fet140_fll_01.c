//******************************************************************************
//  MSP-FET430P140 Demo - Basic Clock, Implement Auto RSEL SW FLL
//
//  Description: Set DCO clock to (Delta)*(4096) using software FLL. DCO clock
//  is output on P5.5 as SMCLK.  DCO clock, which is the selected SMCLK source
//  for timer_A is integrated over LFXT1/8 (4096) until SMCLK is is equal
//  to Delta.  CCR2 captures ACLK.  To use Set_DCO Timer_A must be
//  operating in continous mode.  Watch crystal for ACLK is required for
//  this example.  Delta must be kept in a range that allows possible
//  DCO speeds.  Minimum Delta must ensure that Set_DCO loop
//  can complete within capture interval. Maximum delta can be calculated be
//  f(DCOx7) / 4096.  f(DCOx7) can be found in device specific datasheet.
//  ACLK = LFXT1/8 = 32768/8, MCLK = SMCLK = target DCO
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//	
//
//           MSP430F149
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P5.5|--> SMLCK = target DCO
//        |           P5.6|--> ALCK = 4096
//
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>

void Set_DCO (void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P5DIR |= 0x60;                            // P5.5,6 output
  P5SEL |= 0x60;                            // P5.5,6 SMCLK, ACLK output
  Set_DCO();                                // Set DCO

  while (1);
}

//------------------------------------------------------------------------------
void Set_DCO (void)                         // Set DCO to selected frequency
//------------------------------------------------------------------------------
{
//#define DELTA 900                           // target DCO = DELTA*(4096) = 3686400
#define DELTA 256                           // target DCO = DELTA*(4096) = 1048576
//#define DELTA 70                            // target DCO = DELTA*(4096) = 286720
  unsigned int Compare, Oldcapture = 0;

  BCSCTL1 |= DIVA_3;                        // ACLK= LFXT1CLK/8
  CCTL2 = CM_1 + CCIS_1 + CAP;              // CAP, ACLK
  TACTL = TASSEL_2 + MC_2 + TACLR;          // SMCLK, cont-mode, clear

  while (1)
  {
    while (!(CCIFG & CCTL2));               // Wait until capture occured
    CCTL2 &= ~CCIFG;                        // Capture occured, clear flag
    Compare = CCR2;                         // Get current captured SMCLK
    Compare = Compare - Oldcapture;         // SMCLK difference
    Oldcapture = CCR2;                      // Save current captured SMCLK

    if (DELTA == Compare) break;            // If equal, leave "while(1)"
    else if (DELTA < Compare)               // DCO is too fast, slow it down
    {
      DCOCTL--;
      if (DCOCTL == 0xFF)
      {
        if (!(BCSCTL1 == (XT2OFF + DIVA_3)))
        BCSCTL1--;                          // Did DCO roll under?, Sel lower RSEL
      }
    }
    else
    {
      DCOCTL++;
      if (DCOCTL == 0x00)
        {
          if (!(BCSCTL1 == (XT2OFF + DIVA_3 + 0x07)))
          BCSCTL1++;                        // Did DCO roll over? Sel higher RSEL
        }
    }
  }
  CCTL2 = 0;                                // Stop CCR2
  TACTL = 0;                                // Stop Timer_A
}

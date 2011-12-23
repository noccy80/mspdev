//*****************************************************************************
//  MSP430xG46x Demo - FLL+, Output 32kHz Xtal + HF Xtal + Internal DCO
//
//  Description:  This program demonstrates using an external 32kHz crystal to
//  supply ACLK, and using a high speed crystal or resonator to supply SMCLK.
//  MLCK for the CPU is supplied by the internal DCO.  The 32kHz crystal
//  connects between pins Xin and Xout. The high frequency crystal or
//  resonator connects between pins XT2IN and XT2OUT.  The DCO clock is
//  generated internally and calibrated from the 32kHz crystal.  ACLK is
//  brought out on pin P1.5, SMCLK is brought out on P1.4, and MCLK is
//  brought out on pin P1.1.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//  NOTE: External matching capacitors must be added for the high
//       speed crystal or resonator as required.
//
//                 MSP430xG461x
//             -----------------
//        /|\ |              XIN|-
//         |  |                 | 32kHz
//         ---|RST          XOUT|-
//            |                 |
//            |                 |
//            |            XT2IN|-
//            |                 | HF XTAL or Resonator (add capacitors)
//            |           XT2OUT|-
//            |                 |
//            |             P1.5|--> ACLK = 32kHz Crystal Out
//            |                 |
//            |             P1.4|--> SMCLK = High Freq Xtal or Resonator Out
//            |                 |
//            |             P1.1|--> MCLK = Default DCO Frequency
//            |                 |
//            |                 |
//
//  K. Quiring/ M. Mitchell
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//*****************************************************************************
#include  <msp430xG46x.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP18PF;                     // Set load capacitance
  FLL_CTL1 &= ~XT2OFF;                      // Turn on XT2

  // Loop until 32kHz crystal stabilizes
  do
  {
    IFG1 &= ~OFIFG;                         // Clear oscillator fault flag
    for (i = 50000; i; i--);                // Delay
  }
  while (IFG1 & OFIFG);                     // Test osc fault flag

  FLL_CTL1 = SELS;                          // Select SMCLK source as XT2CLK
  P1DIR = 0x32;                             // Set P1.1,4,5 as outputs
  P1SEL = 0x32;                             // Select P1.1,4,5 as clocks

  while(1);                                 // Loop in place
}

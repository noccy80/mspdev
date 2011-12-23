//*****************************************************************************
//  MSP430F54x Demo - LFXT1 HF Xtal + Internal DCO
//
//  Description:  This program demonstrates using an external high speed crystal
//  or resonator to supply ACLK and MCLK for the CPU. SMLCK is supplied by the
//  internal DCO.  The high speed crystal or resonator connects between pins
//  Xin and Xout. The DCO clock is generated internally and calibrated from REFO
//  ACLK is brought out on pin P11.0, SMCLK is brought out on P11.2, and MCLK is
//  brought out on pin P11.1.
//  ACLK = LFXT1 = HF XTAL, MCLK = HF XTAL, SMCLK = 32 x ACLK = 1048576Hz
//
//  NOTE: External matching capacitors must be added for the high
//       speed crystal or resonator as required.
//
//                MSP430F5438
//             -----------------
//        /|\ |              XIN|-
//         |  |                 | HF XTAL or Resonator (add capacitors)
//         ---|RST          XOUT|-
//            |                 |
//            |            P11.0|--> ACLK = High Freq Xtal or Resonator Out
//            |                 |
//            |            P11.2|--> SMCLK = Default DCO
//            |                 |
//            |            P11.1|--> MCLK = High Freq Xtal or Resonator Out
//            |                 |
//
//   W. Goh
//   Texas Instruments Inc.
//   February 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  P11DIR = BIT2 + BIT1 + BIT0;              // P11.2,1,0 to output direction
  P11SEL = BIT2 + BIT1 + BIT0;              // P11.2 to output SMCLK, P11.1
                                            // to output MCLK and P11.0 to
                                            // output ACLK
  P7SEL |= 0x03;                            // Port select XT1
  UCSCTL3 |= SELREF_2;                      // FLL Ref = REFO
  UCSCTL6 &= ~XT1OFF;                       // Set XT1 On
  UCSCTL6 |= XT1DRIVE_3 + XTS;              // Max drive strength, adjust
                                            // according to crystal frequency.
                                            // LFXT1 HF mode

  // Loop until XT1,XT2 & DCO stabilizes
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  UCSCTL4 = SELA_0 + SELS_4 + SELM_0;       // Select ACLK = LFXT1
                                            //       SMCLK = DCO
                                            //        MCLK = LFXT1
  while(1);                                 // Loop in place
}

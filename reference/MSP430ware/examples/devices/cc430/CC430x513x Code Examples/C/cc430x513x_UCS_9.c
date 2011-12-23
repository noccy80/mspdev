//*****************************************************************************
//  CC430F513x Demo - XT1 HF Xtal + Internal DCO
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
//                CC430F5137
//             -----------------
//        /|\ |              XIN|-
//         |  |                 | HF RF XTAL (26 - 27 MHz)
//         ---|RST          XOUT|-
//            |                 |
//            |            P2.0 |--> ACLK = High Freq Xtal or Resonator Out
//            |                 |
//            |            P2.2 |--> SMCLK = Default DCO
//            |                 |
//            |            P2.4 |--> MCLK = High Freq Xtal or Resonator Out
//            |                 |
//
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x513x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P2MAP0 = PM_ACLK;                         // Map ACLK output to P2.0 
  P2MAP2 = PM_MCLK;                         // Map MCLK output to P2.2 
  P2MAP4 = PM_SMCLK;                        // Map SMCLK output to P2.4 
  PMAPPWD = 0;                              // Lock port mapping registers  
   
  P2DIR |= BIT0 + BIT2 + BIT4;              // ACLK, MCLK, SMCLK set out to pins
  P2SEL |= BIT0 + BIT2 + BIT4;              // P2.0,2,4 for debugging purposes.

  P5SEL |= 0x03;                            // Port select XT1
  
  UCSCTL3 |= SELREF_2;                      // FLL Ref = REFO
  UCSCTL6 |= XT1DRIVE_3 + XTS;              // Max drive strength, adjust
                                            // according to crystal frequency.
                                            // LFXT1 HF mode

  // Loop until XT1 & DCO stabilizes
  do
  {
    UCSCTL7 &= ~(XT1HFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  UCSCTL4 = SELA__XT1CLK + SELS__DCOCLK + SELM__XT1CLK;
                                            // Select ACLK = LFXT1
                                            //       SMCLK = DCO
                                            //        MCLK = LFXT1
  while(1);                                 // Loop in place
}

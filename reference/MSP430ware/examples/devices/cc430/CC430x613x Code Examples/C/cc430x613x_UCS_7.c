//*****************************************************************************
//  CC430F613x Demo - FLL+, Output 32kHz Xtal + HF Xtal + Internal DCO
//
//  Description:  This program demonstrates using an external 32kHz crystal to
//  supply ACLK, and using a high speed crystal or resonator to supply SMCLK.
//  MLCK for the CPU is supplied by the internal DCO.  The 32kHz crystal
//  connects between pins Xin and Xout. The high frequency crystal or
//  resonator connects between pins RF_XIN and RF_XOUT.  The DCO clock is
//  generated internally and calibrated from the 32kHz crystal.  ACLK is
//  brought out on pin P2.0, SMCLK is brought out on P2.2, and MCLK is
//  brought out on pin P11.1.
//  ACLK = LFXT1 = 32768Hz, MCLK = default DCO = 32 x ACLK = 1048576Hz
//  SMCLK = HF XTAL
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//  NOTE: External matching capacitors must be added for the high
//       speed crystal or resonator as required.
//
//                CC430F6137
//             -----------------
//        /|\ |              XIN|-
//         |  |                 | 32kHz
//         ---|RST          XOUT|-
//            |                 |
//            |                 |
//            |            XT2IN|-
//            |                 | HF XTAL 
//            |           XT2OUT|-
//            |                 |
//            |            P2.0 |--> ACLK = 32kHz Crystal Out
//            |                 |
//            |            P2.2 |--> SMCLK = High Freq Xtal or Resonator Out
//            |                 |
//            |            P2.4 |--> MCLK = Default DCO Frequency
//            |                 |
//            |                 |
//
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x613x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P2MAP0 = PM_ACLK;                         // Map ACLK output to P2.0 
  P2MAP2 = PM_SMCLK;                        // Map MCLK output to P2.2 
  P2MAP4 = PM_MCLK;                         // Map SMCLK output to P2.4 
  PMAPPWD = 0;                              // Lock port mapping registers  
   
  P2DIR |= BIT0 + BIT2 + BIT4;              // ACLK, MCLK, SMCLK set out to pins
  P2SEL |= BIT0 + BIT2 + BIT4;              // P2.0,2,4 for debugging purposes.

  P5SEL |= 0x03;                            // Port select XT1
  UCSCTL6 |= XCAP_3;                        // Internal load cap
  UCSCTL6 &= ~XT2OFF;                       // Turn on XT2 even if RF core in SLEEP

  // Loop until XT1,XT2 & DCO stabilizes
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  // Select SMCLK, ACLK source and DCO source                                            
  UCSCTL4 = SELA__XT1CLK + SELS__XT2CLK + SELM__DCOCLKDIV;               

  while(1);                                 // Loop in place
}

//******************************************************************************
//  CC430F513x Demo - XT2 sources MCLK & SMCLK
//
//  Description: This program demonstrates using XT2 to source MCLK. XT1 is not
//  connected in this case.
//
//  By default, LFXT1 is requested by the following modules:
//     - FLL
//     - ACLK
//  If LFXT1 is NOT used and if the user does not change the source modules,
//  it causes the XT1xxOFIFG flag to be set because it is constantly looking
//  for LFXT1. OFIFG, global oscillator fault flag, will always be set if LFXT1
//  is set. Hence, it is important to ensure LFXT1 is no longer being sourced
//  if LFXT1 is NOT used.
//  MCLK = XT2
//
//               CC430F5137
//             -----------------
//        /|\ |                 |
//         |  |                 |
//         ---|RST              |
//            |            XT2IN|-
//            |                 | HF RF XTAL (26 - 27MHz)
//            |           XT2OUT|-
//            |                 |
//            |            P2.4 |--> MCLK = XT2
//            |            P2.2 |--> SMCLK = XT2
//
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x513x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P2MAP2 = PM_SMCLK;                        // Map SMCLK output to P2.2 
  P2MAP4 = PM_MCLK;                         // Map MCLK output to P2.4
  PMAPPWD = 0;                              // Lock port mapping registers  
   
  P2DIR |= BIT2 + BIT4;                     // MCLK, SMCLK set out to pins
  P2SEL |= BIT2 + BIT4;                     // P2.2, P2.4 for debugging 

  UCSCTL6 &= ~XT2OFF;                       // Enable XT2
  UCSCTL3 |= SELREF_2;                      // FLLref = REFO
                                            // Since LFXT1 is not used,
                                            // sourcing FLL with LFXT1 can cause
                                            // XT1OFFG flag to set

  // ACLK=REFO,SMCLK=DCO,MCLK=DCO
  UCSCTL4 = SELA__REFOCLK + SELS__DCOCLKDIV + SELM__DCOCLKDIV;
 
  // Loop until XT1,XT2 & DCO stabilizes
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                            // Clear XT2,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
                                            
  UCSCTL4 |= SELA__REFOCLK + SELS__XT2CLK + SELM__XT2CLK;   // SMCLK=MCLK=XT2

  while(1);                                 // Loop in place
}


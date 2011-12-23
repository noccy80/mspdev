//******************************************************************************
//  MSP430F552x Demo - XT2 sources MCLK & SMCLK
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
//               MSP430F552x
//             -----------------
//        /|\ |                 |
//         |  |                 |
//         ---|RST              |
//            |            XT2IN|-
//            |                 | HF XTAL (455kHz - 16MHz)
//            |           XT2OUT|-
//            |                 |
//            |             P7.7|--> MCLK = XT2
//            |             P2.2|--> SMCLK = XT2
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  P2DIR |= BIT2;                            // SMCLK set out to pins
  P2SEL |= BIT2;                            
  P7DIR |= BIT7;                            // MCLK set out to pins
  P7SEL |= BIT7;
  
  P5SEL |= BIT2+BIT3;                       // Port select XT2

  UCSCTL6 &= ~XT2OFF;                       // Enable XT2 
  UCSCTL3 |= SELREF_2;                      // FLLref = REFO
                                            // Since LFXT1 is not used,
                                            // sourcing FLL with LFXT1 can cause
                                            // XT1OFFG flag to set
  UCSCTL4 |= SELA_2;                        // ACLK=REFO,SMCLK=DCO,MCLK=DCO

  // Loop until XT1,XT2 & DCO stabilizes - in this case loop until XT2 settles
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  UCSCTL6 &= ~XT2DRIVE0;                    // Decrease XT2 Drive according to
                                            // expected frequency
  UCSCTL4 |= SELS_5 + SELM_5;               // SMCLK=MCLK=XT2

  while(1);                                 // Loop in place
}


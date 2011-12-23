//******************************************************************************
//  MSP430F543xA Demo - XT2 sources MCLK & SMCLK
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
//  PMMCOREV = 2 to support up to 20MHz clock
//
//  NOTE: if the SMCLK/HF XTAL frequency exceeds 8MHz, VCore must be set
//  accordingly to support the system speed. Refer to MSP430x5xx Family User's Guide
//  Section 2.2 for more information.
//
//               MSP430F5438A
//             -----------------
//        /|\ |                 |
//         |  |                 |
//         ---|RST              |
//            |            XT2IN|-
//            |                 | HF XTAL (455kHz - 16MHz)
//            |           XT2OUT|-
//            |                 |
//            |            P11.1|--> MCLK = XT2
//            |            P11.2|--> SMCLK = XT2
//
//   Note: 
//   In order to run the system at up to 20MHz, VCore must be set at 1.8V 
//   or higher. This is done by invoking function SetVCore(), which requires 
//   2 files, hal_pmm.c and hal_pmm.h, to be included in the project.
//   hal_pmm.c and hal_pmm.h are located in the same folder as the code 
//   example.
// 
//   D. Dang
//   Texas Instruments Inc.
//   December 2009
//   Built with CCS Version: 4.0.2 and IAR Embedded Workbench Version: 4.21.8
//******************************************************************************

#include "msp430x54xA.h"
#include "hal_pmm.h"
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  SetVCore(PMMCOREV_2);                     // Set VCore to 1.8MHz for 20MHz
       
  P11DIR = BIT1+BIT2;                       // P11.1-2 to output direction
  P11SEL |= BIT1+BIT2;                      // P11.1-2 to output SMCLK,MCLK
  P5SEL |= 0x0C;                            // Port select XT2

  UCSCTL6 &= ~XT2OFF;                       // Enable XT2
  UCSCTL3 |= SELREF_2;                      // FLLref = REFO
                                            // Since LFXT1 is not used,
                                            // sourcing FLL with LFXT1 can cause
                                            // XT1OFFG flag to set
  UCSCTL4 |= SELA_2;                        // ACLK=REFO,SMCLK=DCO,MCLK=DCO

  // Loop until XT1,XT2 & DCO stabilizes
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  UCSCTL6 &= ~XT2DRIVE0;                    // Decrease XT2 Drive according to
                                            // expected frequency
  UCSCTL4 |= SELS_5 + SELM_5;               // SMCLK=MCLK=XT2

  while(1);                                 // Loop in place
}


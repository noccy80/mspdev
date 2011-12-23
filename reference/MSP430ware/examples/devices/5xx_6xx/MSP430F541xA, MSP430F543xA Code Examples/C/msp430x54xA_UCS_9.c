//*****************************************************************************
//  MSP430F543xA Demo - LFXT1 HF Xtal + Internal DCO
//
//  Description:  This program demonstrates using an external high speed crystal
//  or resonator to supply ACLK and MCLK for the CPU. SMLCK is supplied by the
//  internal DCO.  The high speed crystal or resonator connects between pins
//  Xin and Xout. The DCO clock is generated internally and calibrated from REFO
//  ACLK is brought out on pin P11.0, SMCLK is brought out on P11.2, and MCLK is
//  brought out on pin P11.1.
//  ACLK = LFXT1 = HF XTAL, MCLK = HF XTAL, SMCLK = 32 x ACLK = 1048576Hz
//  PMMCOREV = 2 to support up to 20MHz clock
//
//  NOTE: if the SMCLK/HF XTAL frequency exceeds 8MHz, VCore must be set
//  accordingly to support the system speed. Refer to MSP430x5xx Family User's Guide
//  Section 2.2 for more information.
//  NOTE: External matching capacitors must be added for the high
//       speed crystal or resonator as required.
//
//                MSP430F5438A
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
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  SetVCore(PMMCOREV_2);                     // Set VCore to 1.8MHz for 20MHz
  
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

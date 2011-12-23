//*****************************************************************************
//  MSP430F543xA Demo - FLL+, Output 32kHz Xtal + HF Xtal + Internal DCO
//
//  Description:  This program demonstrates using an external 32kHz crystal to
//  supply ACLK, and using a high speed crystal or resonator to supply SMCLK.
//  MLCK for the CPU is supplied by the internal DCO.  The 32kHz crystal
//  connects between pins Xin and Xout. The high frequency crystal or
//  resonator connects between pins XT2IN and XT2OUT.  The DCO clock is
//  generated internally and calibrated from the 32kHz crystal.  ACLK is
//  brought out on pin P11.0, SMCLK is brought out on P11.2, and MCLK is
//  brought out on pin P11.1.
//  ACLK = LFXT1 = 32768Hz, MCLK = default DCO = 32 x ACLK = 1048576Hz
//  SMCLK = HF XTAL
//  PMMCOREV = 2 to support up to 20MHz clock
//
//  NOTE: if the SMCLK/HF XTAL frequency exceeds 8MHz, VCore must be set
//  accordingly to support the system speed. Refer to MSP430x5xx Family User's Guide
//  Section 2.2 for more information.
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//  NOTE: External matching capacitors must be added for the high
//       speed crystal or resonator as required.
//
//                MSP430F5438A
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
//            |            P11.0|--> ACLK = 32kHz Crystal Out
//            |                 |
//            |            P11.2|--> SMCLK = High Freq Xtal or Resonator Out
//            |                 |
//            |            P11.1|--> MCLK = Default DCO Frequency
//            |                 |
//            |                 |
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
  P5SEL |= 0x0C;                            // Port select XT2
  P7SEL |= 0x03;                            // Port select XT1

  UCSCTL6 &= ~(XT1OFF + XT2OFF);            // Set XT1 & XT2 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap

  // Loop until XT1,XT2 & DCO stabilizes
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  UCSCTL6 &= ~XT2DRIVE0;                    // Decrease XT2 Drive according to
                                            // expected frequency
  UCSCTL4 |= SELA_0 + SELS_5;               // Select SMCLK, ACLK source and DCO source

  while(1);                                 // Loop in place
}

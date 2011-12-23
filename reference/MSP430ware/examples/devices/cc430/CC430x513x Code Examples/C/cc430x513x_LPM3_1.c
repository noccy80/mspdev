//******************************************************************************
//   CC430x513x Demo - Enters LPM3 (ACLK = LFXT1)
//
//   Description: Configure ACLK = LFXT1 and enters LPM3. Measure current.
//   Note: SVS(H,L) & SVM(H,L) are disabled
//   ACLK = LFXT1 = 32kHz, MCLK = SMCLK = default DCO
//
//                 CC430x513x
//             -----------------
//        /|\ |              XIN|-
//         |  |                 | 32kHz
//         ---|RST          XOUT|-
//            |                 |
//
//   M. Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include  "cc430x513x.h"

void main(void)
{  
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  P5SEL |= BIT0 + BIT1;                     // Select XT1
  UCSCTL6 |= XCAP_3;                        // Internal load cap

  // Loop until XT1,XT2 & DCO stabilizes
  do
  {
    UCSCTL7 &= ~(XT1LFOFFG + DCOFFG);
                                            // Clear LFXT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1 & OFIFG);                   // Test oscillator fault flag

  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive
                                            // strength

  P1OUT = 0x00; P2OUT = 0x00; P3OUT = 0x00; P5OUT = 0x00;
  P1DIR = 0xFF; P2DIR = 0xFF; P3DIR = 0xFF; P5DIR = 0x03;
  
  PJOUT = 0x00;
  PJDIR = 0xFF;

  // Turn off SVSH, SVSM
  PMMCTL0_H = 0xA5;
  SVSMHCTL = 0; 
  SVSMLCTL = 0; 
  PMMCTL0_H = 0x00; 

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}

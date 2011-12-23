//******************************************************************************
//   MSP430F543xA Demo - Enters LPM3 (ACLK = LFXT1)
//
//   Description: Configure ACLK = LFXT1 and enters LPM3. Measure current.
//   ACLK = LFXT1 = 32kHz, MCLK = SMCLK = default DCO
//   Note: SVS(H,L) & SVM(H,L) not disabled
//
//                 MSP430x5438
//             -----------------
//        /|\ |              XIN|-
//         |  |                 | 32kHz
//         ---|RST          XOUT|-
//            |                 |
//
//   M. Morales
//   Texas Instruments Inc.
//   June 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  "msp430x54xA.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  P7SEL |= 0x03;                            // Select XT1
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap

  // Loop until XT1,XT2 & DCO stabilizes
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive
                                            // strength

  P1OUT = 0x00;
  P2OUT = 0x00;
  P3OUT = 0x00;
  P4OUT = 0x00;
  P5OUT = 0x00;
  P6OUT = 0x00;
  P7OUT = 0x00;
  P8OUT = 0x00;
  P9OUT = 0x00;
  P10OUT = 0x00;
  P11OUT = 0x00;
  PJOUT = 0x00;

  P1DIR = 0xFF;
  P2DIR = 0xFF;
  P3DIR = 0xFF;
  P4DIR = 0xFF;
  P5DIR = 0xFF;
  P6DIR = 0xFF;
  P7DIR = 0xFF;
  P8DIR = 0xFF;
  P9DIR = 0xFF;
  P10DIR = 0xFF;
  P11DIR = 0xFF;
  PJDIR = 0xFF;

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}

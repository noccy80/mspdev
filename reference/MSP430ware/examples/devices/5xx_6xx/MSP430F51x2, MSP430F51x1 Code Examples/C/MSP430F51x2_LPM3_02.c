//******************************************************************************
//   MSP430F51x2 Demo - Enters LPM3 (ACLK = VLO)
//
//   Description: Enters LPM3 with ACLK = VLO.
//   ACLK = MCLK = SMCLK = VLO = 12kHz
//   Note: SVS(H,L) & SVM(H,L) not disabled
//
//                MSP430F51x2
//             -----------------
//        /|\ |              XIN|-
//         |  |                 | 32kHz
//         ---|RST          XOUT|-
//            |                 |
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   Dec 2009
//   Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include  "msp430f5172.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  UCSCTL4 = SELA_1;                         // ACLK = VLO
  
  // Port Configuration
  P1OUT = 0x00;P2OUT = 0x00;P3OUT = 0x00;PJOUT = 0x00;
  P1DIR = 0xFF;P2DIR = 0xFF;P3DIR = 0xFF;PJDIR = 0xFF;  

  __bis_SR_register(LPM3_bits);       // Enter LPM3 
  __no_operation();
}



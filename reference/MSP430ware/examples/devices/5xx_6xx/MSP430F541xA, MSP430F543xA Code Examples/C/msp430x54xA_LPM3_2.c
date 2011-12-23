//******************************************************************************
//   MSP430F543xA Demo - Enters LPM3 (ACLK = VLO)
//
//   Description: Enters LPM3 with ACLK = VLO.
//   ACLK = MCLK = SMCLK = VLO = 12kHz
//   Note: SVS(H,L) & SVM(H,L) not disabled
//
//                 MSP430x5438
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
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
  WDTCTL = WDTPW + WDTHOLD;                 // Hold WDT
  UCSCTL4 = SELM_1 + SELS_1 + SELA_1;       // MCLK = SMCLK = ACLK = VLO

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
  __no_operation();
}

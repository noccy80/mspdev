//******************************************************************************
//   CC430x613x Demo - Enters LPM3 (ACLK = VLO)
//
//   Description: Enters LPM3 with ACLK = VLO
//   SVS(H,L) & SVM(H,L) are also disabled
//   ACLK = MCLK = SMCLK = VLO = 12kHz
//
//                 CC430x613x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//
//   M. Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  "cc430x613x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Hold WDT
  UCSCTL4 = SELM__DCOCLKDIV + SELS__DCOCLKDIV + SELA__VLOCLK; 
//  UCSCTL4 = SELM_1 + SELS_1 + SELA_1;       // MCLK = SMCLK = ACLK = VLO

  P1OUT = 0x00; P2OUT = 0x00; P3OUT = 0x00; P4OUT = 0x00; P5OUT = 0x00;
  P1DIR = 0xFF; P2DIR = 0xFF; P3DIR = 0xFF; P4DIR = 0xFF; P5DIR = 0xFF;

  PJOUT = 0x00;
  PJDIR = 0xFF;
  
  // Turn off SVSH, SVSM
  PMMCTL0_H = 0xA5;
  SVSMHCTL = 0; 
  SVSMLCTL = 0; 
  PMMCTL0_H = 0x00; 

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();
}

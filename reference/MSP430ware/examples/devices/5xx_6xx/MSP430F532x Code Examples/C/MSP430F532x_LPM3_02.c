//******************************************************************************
//   MSP430F532x Demo - Enters LPM3 (ACLK = VLO)
//
//   Description: Enters LPM3 with ACLK = VLO.
//   ACLK = MCLK = SMCLK = VLO = 12kHz
//   Note: SVS(H,L) & SVM(H,L) is disabled
//
//                MSP430F532x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Oct 2011
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 5.3
//******************************************************************************
#include <msp430f5328.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  
  // Clock Configuration
  UCSCTL4 = SELA_1;                         // ACLK = VLO
  
  // Port Configuration
  P1OUT = 0x00;P2OUT = 0x00;P3OUT = 0x00;P4OUT = 0x00;P5OUT = 0x00;P6OUT = 0x00;
  PJOUT = 0x00;
  P1DIR = 0xFF;P2DIR = 0xFF;P3DIR = 0xFF;P4DIR = 0xFF;P5DIR = 0xFF;P6DIR = 0xFF;
  PJDIR = 0xFF;
  
   // Disable SVS
  PMMCTL0_H = PMMPW_H;                // PMM Password
  SVSMHCTL &= ~(SVMHE+SVSHE);         // Disable High side SVS 
  SVSMLCTL &= ~(SVMLE+SVSLE);         // Disable Low side SVS

  __bis_SR_register(LPM3_bits);             // Enter LPM3 
  __no_operation();
}



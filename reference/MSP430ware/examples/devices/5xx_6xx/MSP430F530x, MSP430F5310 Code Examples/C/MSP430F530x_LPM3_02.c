//******************************************************************************
//   MSP430F530x Demo - Enters LPM3 (ACLK = VLO)
//
//   Description: Enters LPM3 with ACLK = VLO.
//   ACLK = MCLK = SMCLK = VLO = 12kHz
//   Note: SVS(H,L) & SVM(H,L) not disabled
//
//                MSP430F530x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->LED
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

#define SYS14_WORKAROUND                    // Comment this line if silicon revision has SYS14 bug fixed

#ifdef SYS14_WORKAROUND
    #define INIT_MEMORY_ADDR 0x0900
    unsigned int *Address = ((unsigned int*)INIT_MEMORY_ADDR); 
#endif
  
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
 
#ifdef SYS14_WORKAROUND  
  *Address = 0x9628;
  *(Address+4) = 0x0800;
  *Address = 0x9600;  
#endif
  
  // Clock Configuration
  UCSCTL4 = SELA_1;                         // ACLK = VLO
  
  // Port Configuration
  P1OUT = 0x00;P2OUT = 0x00;P3OUT = 0x00;P4OUT = 0x00;P5OUT = 0x00;P6OUT = 0x00;
  PJOUT = 0x00;
  P1DIR = 0xFF;P2DIR = 0xFF;P3DIR = 0xFF;P4DIR = 0xFF;P5DIR = 0xFF;P6DIR = 0xFF;
  PJDIR = 0xFF;

  __bis_SR_register(LPM3_bits);             // Enter LPM3 
  __no_operation();
}



//******************************************************************************
//   MSP430F534x Demo - Enters LPM3 (ACLK = VLO)
//
//   Description: Enters LPM3 with ACLK = VLO.
//   ACLK = MCLK = SMCLK = VLO = 12kHz
//   Note: SVS(H,L) & SVM(H,L) not disabled
//
//                MSP430F534x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->LED
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Jun 2011
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5342.h>

//#define SYS14_WORKAROUND_REVE              // Uncomment this line if using RevE silicon 

#define INIT_MEMORY_ADDR1 0x0206
unsigned int *Init_Addr1 = ((unsigned int*)INIT_MEMORY_ADDR1); 

#ifdef SYS14_WORKAROUND_REVE
    #define INIT_MEMORY_ADDR2 0x0900
    unsigned int *Init_Addr2 = ((unsigned int*)INIT_MEMORY_ADDR2);
#endif

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  
  // SYS14 Workaround
  *Init_Addr1 = 0x7F00;
  *(Init_Addr1+0x10) = 0x00E0;
  *(Init_Addr1+0x20) = 0xC140;
  *(Init_Addr1+0x30) = 0x07FF;
  
#ifdef SYS14_WORKAROUND_REVE  
  *Init_Addr2 = 0x9628;
  *(Init_Addr2+4) = 0x0000;
  *Init_Addr2 = 0x9600; 
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



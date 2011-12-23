//******************************************************************************
//   MSP430F552x Demo - Enters LPM3 (ACLK = VLO)
//
//   Description: Enters LPM3 with ACLK = VLO.
//   ACLK = MCLK = SMCLK = VLO = 12kHz
//   Note: SVS(H,L) & SVM(H,L) not disabled
//
//                MSP430F552x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->LED
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5529.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  UCSCTL4 = SELA_1;                         // ACLK = VLO
  
  // Port Configuration
  P1OUT = 0x00;P2OUT = 0x00;P3OUT = 0x00;P4OUT = 0x00;P5OUT = 0x00;P6OUT = 0x00;
  P7OUT = 0x00;P8OUT = 0x00; PJOUT = 0x00;
  P1DIR = 0xFF;P2DIR = 0xFF;P3DIR = 0xFF;P4DIR = 0xFF;P5DIR = 0xFF;P6DIR = 0xFF;
  P7DIR = 0xFF;P8DIR = 0xFF; PJDIR = 0xFF;

  // Disable VUSB LDO and SLDO
  USBKEYPID   =     0x9628;           // set USB KEYandPID to 0x9628 
                                      // access to USB config registers enabled  
  USBPWRCTL &= ~(SLDOEN+VUSBEN);      // Disable the VUSB LDO and the SLDO
  USBKEYPID   =    0x9600;            // access to USB config registers disabled 
  
  __bis_SR_register(LPM3_bits);       // Enter LPM3 
  __no_operation();
}



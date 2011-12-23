//******************************************************************************
//   MSP430x66xx Demo - Enters LPM3 with ACLK = LFXT1, REF0 disabled, 
//                      VUSB LDO and SLDO disabled, SVS default state
//
//   Description: Configure ACLK = LFXT1 and enters LPM3. Measure current.
//   ACLK = LFXT1 = 32kHz, MCLK = SMCLK = default DCO
//   NOTE: CONNECT VBAT TO VCC WHEN BACKUP SUPPLY IS NOT AVAILABLE.
// 
//           MSP430F663x
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |          Vbat |---
//        |               |  |
//        |          Vcc  |---
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   September 2009
//   Built with IAR Embedded Workbench Version: 4.20 & Code Composer Studio V4.0
//******************************************************************************

#include <msp430f6638.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  // Enable XT1
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap
  while(BAKCTL & LOCKIO)                    // Unlock XT1 pins for operation
     BAKCTL &= ~(LOCKIO);  

  
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive
                                            // strength
  UCSCTL4 &= ~(SELA0 + SELA1 + SELA2);      // Ensure XT1 is ACLK source
  
  // Port Configuration
  P1OUT = 0x00;P2OUT = 0x00;P3OUT = 0x00;P4OUT = 0x00;P5OUT = 0x00;P6OUT = 0x00;
  P7OUT = 0x00;P8OUT = 0x00;P9OUT = 0x00;PJOUT = 0x00;
  P1DIR = 0xFF;P2DIR = 0xFF;P3DIR = 0xFF;P4DIR = 0xFF;P5DIR = 0xFF;P6DIR = 0xFF;
  P7DIR = 0xFF;P8DIR = 0xFF;P9DIR = 0xFF;PJDIR = 0xFF;

    // Disable VUSB LDO and SLDO
  USBKEYPID   =     0x9628;                 // set USB KEYandPID to 0x9628 
                                            // enable access to USB config reg
  USBPWRCTL &= ~(SLDOEN+VUSBEN);            // Disable the VUSB LDO and the SLDO
  USBKEYPID   =    0x9600;                  // disable access to USB config reg

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}



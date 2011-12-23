//******************************************************************************
//   MSP430F51x2 Demo - Enters LPM3 with ACLK = LFXT1, REF0 disabled, 
//                      SVS disabled
//
//   Description: Configure ACLK = LFXT1 and enters LPM3. Measure current.
//   ACLK = LFXT1 = 32kHz, MCLK = SMCLK = default DCO
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
  
  // Enable XT1
  PJSEL |= BIT4+BIT5;                       // Port select XT1
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap

  // Loop until XT1 & DCO stabilizes
  do
  {
    UCSCTL7 &= ~(XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive
                                            // strength
  // Port Configuration
  P1OUT = 0x00;P2OUT = 0x00;P3OUT = 0x00;PJOUT = 0x00;
  P1DIR = 0xFF;P2DIR = 0xFF;P3DIR = 0xFF;PJDIR = 0xFF;  

  // Disable SVS
  PMMCTL0_H = PMMPW_H;                // PMM Password
  SVSMHCTL &= ~(SVMHE+SVSHE);         // Disable High side SVS 
  SVSMLCTL &= ~(SVMLE+SVSLE);         // Disable Low side SVS
  
  __bis_SR_register(LPM3_bits);       // Enter LPM3
  __no_operation();                   // For debugger
}


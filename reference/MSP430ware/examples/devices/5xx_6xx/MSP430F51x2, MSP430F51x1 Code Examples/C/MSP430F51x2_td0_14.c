//******************************************************************************
//  MSP430F51x2 Demo - TimerD0, Toggle P2.3/TD0.0, Up/Down Mode, 32kHz ACLK
//
//  Description: Toggle P1.6 using hardware TD0.0 output. TimerD0 is configured
//  for up/down mode with CCR0 defining period, TD0.0 also output on P1.6. In
//  this example, CCR0 is loaded with 5 and TD0.0 will toggle P2.3 at TDCLK/2*5.
//  Thus the output frequency on P1.6 will be the TDCLK/20. No CPU or software
//  resources required. Normal operating mode is LPM3.
//  As coded with TDCLK = ACLK, P2.3 output frequency = 32768/20 = 1.6384kHz
//  ACLK = TDCLK = LFXT1 = 32kHz, MCLK = default DCO ~1.045MHz
//
//               MSP430F51x2
//            -------------------
//        /|\ |              XIN|-
//         |  |                 | 32kHz
//         ---|RST          XOUT|-
//           |                   |
//           |         P1.6/TD0.0|-->ACLK/20
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  // Configure ports
  P1DIR |= BIT6;                            // P1.6 output
  P1SEL |= BIT6;                            // P1.6 option select

  // XT1 configure
  PJSEL |= BIT4+BIT5;                       // Port select XT1
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap
  UCSCTL3 = 0;                              // FLL Reference Clock = XT1

  // Loop until XT1 & DCO stabilizes - In this case loop until XT1 and DCo settle
  do
  {
    UCSCTL7 &= ~(XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag  
  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive strength
  UCSCTL4 |= SELA_0;                        // ACLK = LFTX1 (by default)

  // Configure TD0
  TD0CCTL0 = OUTMOD_4;                      // CCR0 toggle mode
  TD0CCR0 = 5;
  TD0CTL0 = TDSSEL_1 + MC_3 + TDCLR;        // ACLK, up-downmode, clear TDR

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}

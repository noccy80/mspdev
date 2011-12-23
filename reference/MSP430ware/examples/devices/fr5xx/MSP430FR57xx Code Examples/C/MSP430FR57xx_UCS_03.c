//******************************************************************************
//   MSP430FR57xx Demo - Output 32768Hz crystal on XT1 and observe failsafe 
//
//   Description: Configure ACLK = LFXT1 and enter LPM3. 
//   To observe failsafe behavior short the crytsal briefly on the target board.
//   This will cause an NMI to occur. P1.0 is toggled inside the NMI ISR. 
//   Once the fault flag is cleared XT1 operation continues from 32768Hz crystal
//   Otherwise ACLK defaults to VLO (~8KHz).
//   ACLK = LFXT1 = 32kHz, MCLK = SMCLK = 4MHz
// 
//           MSP430FR57x
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |          P2.0 |--->ACLK  
//        |          P1.0 |--->LED
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************

#include "msp430fr5739.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  // LED setup
  P1OUT = 0;
  P1DIR |= BIT0;
  // XT1 Setup   
  PJSEL0 |= BIT4 + BIT5; 
  
  CSCTL0_H = 0xA5;
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;             // Set max. DCO setting
  CSCTL2 = SELA_0 + SELS_3 + SELM_3;        // set ACLK = XT1; MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_1 + DIVM_1;        // set all dividers 
  CSCTL4 |= XT1DRIVE_0; 
  CSCTL4 &= ~XT1OFF;
  
  do
  {
    CSCTL5 &= ~XT1OFFG;
                                            // Clear XT1 fault flag
    SFRIFG1 &= ~OFIFG; 
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  
  // Now that osc is running enable fault interrupt
  SFRIE1 |= OFIE; 
  
  P2OUT = 0;                                // output ACLK
  P2DIR |= BIT0;
  P2SEL1 |= BIT0; 
  P2SEL0 |= BIT0;  
  
  __bis_SR_register(LPM3_bits+GIE);
  
}

#pragma vector=UNMI_VECTOR
__interrupt void UNMI_ISR(void)
{  
    do
  {
    // set a breakpoint on the line below to observe XT1 operating from VLO
    // when the breakpoint is hit during a crystal fault
    CSCTL5 &= ~XT1OFFG;                     // Clear XT1 fault flag
    SFRIFG1 &= ~OFIFG; 
    P1OUT |= BIT0;
    __delay_cycles(25000);                  // time for flag to get set again
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  
  P1OUT &= ~BIT0;


}

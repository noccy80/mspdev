//******************************************************************************
//  MSP430xG46x Demo - Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
//
//  Description: Toggle P1.1 using hardware TA0 output. Timer_A is configured
//  for up mode with TACCR0 defining period, TA0 also output on P1.1. In this
//  example, TACCR0 is loaded with 10-1 and TA0 will toggle P1.1 at TACLK/10.
//  Thus the output frequency on P1.1 will be the TACLK/20. No CPU or software
//  resources required. Normal operating mode is LPM3.
//  As coded with TACLK = ACLK, P1.1 output frequency = 32768/20 = 1.6384kHz.
//  ACLK = TACLK = 32kHz, MCLK = default DCO ~1048kHz
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//	
//
//              MSP430xG461x
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P1.0/TA0|--> ACLK/20
//
//  K. Quiring/ M. Mitchell
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************

#include  <msp430xG46x.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW +WDTHOLD;                  // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  // Wait for xtal to stabilize
  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0x47FF; i > 0; i--);             // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  P1DIR |= 0x01;                            // P1.1 output
  P1SEL |= 0x01;                            // P1.1 option select
  TACCTL0 = OUTMOD_4;                       // TACCR0 toggle mode
  TACCR0 = 10-1;
  TACTL = TASSEL_1 + MC_1;                  // ACLK, upmode

  _BIS_SR(LPM3_bits);                       // Enter LPM3 w/interrupt
}

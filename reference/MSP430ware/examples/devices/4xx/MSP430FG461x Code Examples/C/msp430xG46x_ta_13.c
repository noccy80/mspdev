//******************************************************************************
//  MSP430xG46x Demo - Timer_A, Toggle P1.0/TA0, Up/Down Mode, DCO SMCLK
//
//  Description: Toggle P1.0 using hardware TA0 output. Timer_A is configured
//  for up/down mode with TACCR0 defining period, TA0 also output on P1.0. In
//  this example, TACCR0 is loaded with 250 and TA0 will toggle P1.0 at
//  TACLK/2*250. Thus the output frequency on P1.0 will be the TACLK/1000.
//  No CPU or software resources required.
//  SMCLK = MCLK = TACLK = default DCO ~1048kHz
//
//                MSP430xG461x
//            -----------------
//        /|\|              XIN|-
//         | |                 |  32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P1.0/TA0|--> SMCLK/1000
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

  P1DIR |= 0x01;                            // P1.0 output
  P1SEL |= 0x01;                            // P1.0 option select
  TACCTL0 = OUTMOD_4;                       // TACCR0 toggle mode
  TACCR0 = 250;
  TACTL = TASSEL_2 + MC_3;                  // SMCLK, up-down mode

  _BIS_SR(LPM0_bits + GIE);                 // CPU off
}

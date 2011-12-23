//*****************************************************************************
//  MSP-FET430P140 Demo - Timer_A, Toggle P1.0, Overflow ISR, HF XTAL ACLK
//
//  Description: Toggle P1.0 using software and the Tmer_A overflow ISR.
//  In this example an ISR triggers when TA overflows. Inside the ISR P1.0
//  is toggled. Toggle rate is ~15Hz. Proper use of the TAIV interrupt
//  vector generator is demonstrated.
//  ACLK = 8MHz, TACLK = 8MHz/8 = 1MHz, MCLK = SMCLK = default DCO ~800kHz
//  //* An external resonator on XIN XOUT is required for ACLK *//	
//
//           MSP430F149
//         ---------------
//     /|\|            XIN|-
//      | |               | 8MHz
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
//
//  H. Grewal
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************

#include  <msp430x14x.h>

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output

  P5DIR |= 0x10;                            // P5.4= output direction
  P5SEL |= 0x10;                            // P5.4= MCLK option select
  BCSCTL1 |= XTS;                           // ACLK= LFXT1 = HF XTAL

  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0xFF; i > 0; i--);               // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  BCSCTL2 |= SELM_3;                        // MCLK= LFXT1 (safe)
  TACTL = TASSEL_1 + MC_2 + ID_3 + TAIE;    // ACLK, contmode, /8, interrupt

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
  switch( TAIV )
  {
    case  2:  break;                        // CCR1 not used
    case  4:  break;                        // CCR2 not used
    case 10:  P1OUT ^= 0x01;                // overflow
              break;
  }
}


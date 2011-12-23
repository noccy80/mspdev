//******************************************************************************
//  MSP-FET430P430 Demo - Timer_B, Toggle P5.1, Overflow ISR, DCO SMCLK
//
//  Description: This program toggles P5.1 using software and the Timer_B
//  overflow ISR. In this example an ISR triggers when TB overflows.
//  Inside the ISR P5.1 is toggled.  Toggle rate is 16Hz when using default
//  FLL+ register settings and an external 32kHz watch crystal.	
//  Proper use of TBIV interrupt vector generator is demonstrated.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//           MSP430FG439
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P5.1|-->LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include  <msp430xG43x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  P5DIR |= 0x02;                            // Set P5.1 to output direction
  TBCTL = TBSSEL1 + TBCLR + TBIE;           // SMCLK, clr. TBR, interrupt
  TBCTL |= MC1;                             // Start Timer_B in continous
  TBCTL = TBSSEL_2 + MC_2 + TBIE;           // SMCLK, contmode, interrupt

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer_B7 Interrupt Vector (TBIV) handler
#pragma vector=TIMERB1_VECTOR
__interrupt void Timer_B(void)
{
 switch( TBIV )
 {
   case  2: break;                          // CCR1 not used
   case  4: break;                          // CCR2 not used
   case 14: P5OUT ^= 0x02;                  // overflow
            break;
 }
}


//******************************************************************************
//  MSP430x26x Demo - Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and Timer_B overflow ISR.
//  In this example an ISR triggers when TB overflows.  TB overflow has the 
//  lowest priority. Inside the TB overflow ISR P1.0 is toggled. Toggle rate is 
//  approximatlely 7.822Hz = [1.045MHz/FFFFh]/2. Proper use of TBIV interrupt vector 
//  generator is shown.
//  ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO ~1.045MHz.
//
//           MSP430F261x/241x
//         ---------------
//     /|\|            XIN|-
//      | |               |
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************

#include  <msp430x26x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  TBCTL = TBSSEL_2 + MC_2 + TBIE;           // SMCLK, contmode, interrupt

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer_B7 Interrupt Vector (TBIV) handler
#pragma vector=TIMERB1_VECTOR
__interrupt void Timer_B(void)
{
 /* Any access, read or write, of the TBIV register automatically resets the 
 highest "pending" interrupt flag. */
  switch( TBIV )
 {
   case  2: break;                          // CCR1 not used
   case  4: break;                          // CCR2 not used
   case 14: P1OUT ^= 0x01;                  // overflow
            break;
 }
}


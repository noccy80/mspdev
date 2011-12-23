//******************************************************************************
//  MSP-FET430P120 Demo - WDT, Toggle P1.0, Interval Overflow ISR, HF XTAL ACLK
//
//  Description: Toggle P1.0 using software timed by the WDT ISR. In this
//  example the WDT is clocked with ACLK which is the same as the XTAL and
//  divided by the WDT by 512 triggering and ISR that will toggle P1.0.
//  ACLK = MCLK = LFXT1 = HF XTAL
//  //* HF XTAL REQUIRED AND NOT INSTALLED ON FET *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//	
//
//		 MSP430F123(2)
//             -----------------
//         /|\|              XIN|-
//          | |                 | HF XTAL (455k - 8MHz)
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x12x2.h>

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDT_ADLY_16;                     // ACLK / 512, interval timer
  BCSCTL1 |= XTS;                           // ACLK = LFXT1 = HF XTAL

  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0xFF; i > 0; i--);               // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  BCSCTL2 |= SELM_3;                        // MCLK = LFXT1 (safe)
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM3, enable interrupts
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0 using exclusive-OR
}


//******************************************************************************
//   MSP430x42x0 Demo - FLL+, LPM3 Using Basic Timer ISR, 32kHz ACLK
//
//   Description: System runs normally in LPM3 with basic timer clocked by
//   32kHz ACLK. At a 2 second interval the basic timer ISR wakes the
//   system and flashes the LED on P1.0 inside of the Mainloop.
//   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                MSP430F4270
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  L. Westlund / S. Karthikeyan
//  Texas Instruments Inc.
//  June 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//******************************************************************************
#include  <msp430x42x0.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  IE2 |= BTIE;                              // Enable BT interrupt
  BTCTL = BTDIV+BTIP2+BTIP1+BTIP0;          // 2s Interrupt
  P1DIR = 0xFF;                             // All P1.x outputs
  P1OUT = 0;                                // All P1.x reset
  P2DIR = 0xFF;                             // All P2.x outputs
  P2OUT = 0;                                // All P2.x reset
  P5DIR = 0xFF;                             // All P5.x outputs
  P5OUT = 0;                                // All P5.x reset
  P6DIR = 0xFF;                             // All P6.x outputs
  P6OUT = 0;                                // All P6.x reset

  while(1)
  {
    int i;
    _BIS_SR(LPM3_bits + GIE);               // Enter LPM3 w/ interrupts
    P1OUT |= 0x01;                          // Set P1.0 LED on
    for (i = 5000; i>0; i--);               // Delay
    P1OUT &= ~0x01;                         // Clear P1.0 LED off
  }
}

// Basic Timer interrupt service routine
#pragma vector=BASICTIMER_VECTOR
__interrupt void basic_timer(void)
{
    _BIC_SR_IRQ(LPM3_bits);             // Clear LPM3 bits from 0(SR)
}

//*****************************************************************************
//   MSP430x21x1 Demo - 21x1 Pull-up resistors demo
//
//   Description: This program demonstrates how to use the internal pull-ups
//   on the 21x1 device. P1.2 is configured for using the pull-up. P1.0
//   is configured as output to use the LED as an indicator. The P1.2 interrupt
//   is enabled and the device is put into LPM4. When P1.2 goes low, and
//   interrupt is generated and the P1_ISR executes. The ISR implements a
//   software debounce delay, toggles P1.0 and returns.
//   ACLK = n/a, MCLK = SMCLK = default DCO ~1.16MHz
//
//
//               MSP430F21x1
//            -----------------
//       /|\ |              XIN|-
//        |  |                 |
//        ---|RST          XOUT|-
//           |                 |
//           |             P1.2|---- \----
//           |                 |         |
//           |                 |        GND
//
//   M. Mitchell / A. Dannenberg
//   Texas Instruments, Inc
//   July 2004
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//*****************************************************************************

#include  <msp430x21x1.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR = 0x01;                             // P1.0 output for LED
  P1REN = 0x04;                             // Enable resistor on P1.2
  P1OUT = 0x04;                             // Select pull-up
  P1IE = 0x04;                              // Enable interrupt
  P1IFG = 0;                                // Clear IFG
  _BIS_SR(LPM4_bits+GIE);                   // Enable interrupts, LPM4
}

#pragma vector=PORT1_VECTOR
__interrupt void P1_ISR(void)
{
  volatile unsigned int i;

  for (i=0x1FFF; i > 0; i--);               // Debounce delay
  P1OUT ^= 0x01;                            // Toggle LED
  P1IFG = 0;                                // Clear IFG
}

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
//*****************************************************************************
/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

/*
 *  ======== main ========
 */
void main(int argc, char *argv[])
{
    CSL_init();

    _BIS_SR(LPM4_bits+GIE);                   // Enable interrupts, LPM4
}

void P1_ISR(void)
{
    volatile unsigned int i;

    for (i=0x1FFF; i > 0; i--);               // Debounce delay
    P1OUT ^= 0x01;                            // Toggle LED
    P1IFG = 0;                                // Clear IFG
}

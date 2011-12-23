//******************************************************************************
//   MSP430x24x Demo - Comparator A, Poll input CA0, interrupt triggered
//
//   Description:  Normal operation is in LPM3.  When Vcompare crosses the ref
//   voltage, an interrupt is generated, and the ISR toggles the LED.
//
//                 MSP430F249
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST      P2.3/CA0|<--Vcompare
//            |                 |
//            |             P1.0|-->I/O - LED
//******************************************************************************
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

    _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3, interrupts enabled
}

void Comp_A_ISR(void)
{
    CACTL1 ^= CAIES;                          // Toggles interrupt edge
    CACTL1 &= ~CAIFG;                         // Clear Interrupt flag
    P1OUT ^= 0x01;                            // Toggle P1.0
}

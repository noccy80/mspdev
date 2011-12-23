//******************************************************************************
//  MSP430G2x21/G2x31 Demo - SPI full-Duplex 3-wire Slave
//
//  Description: SPI Master communicates full-duplex with SPI Slave using
//  3-wire mode. The level on P1.4 is TX'ed and RX'ed to P1.0.
//  Master will pulse slave reset for synch start.
//  ACLK = n/a, MCLK = SMCLK = Default DCO
//
//                Slave                      Master
//             MSP430G2x21/G2x31          MSP430G2x21/G2x31
//             -----------------          -----------------
//            |              XIN|-    /|\|              XIN|-
//            |                 |      | |                 |
//            |             XOUT|-     --|RST          XOUT|-
//            |                 | /|\    |                 |
//            |          RST/NMI|--+<----|P1.2             |
//      LED <-|P1.0             |        |             P1.4|<-
//          ->|P1.4             |        |             P1.0|-> LED
//            |         SDI/P1.7|<-------|P1.6/SDO         |
//            |         SDO/P1.6|------->|P1.7/SDI         |
//            |        SCLK/P1.5|<-------|P1.5/SCLK        |
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
int main(int argc, char *argv[])
{
    CSL_init();                           // Activate Grace-generated configuration

    USICTL1 &= ~USIIFG;                   // Disable pending interrupt
    USISRL = P1IN;                        // init-load data
    USICNT = 8;                           // init-load counter

    _BIS_SR(LPM0_bits + GIE);             // Enter LPM0 w/ interrupt
}

void universal_serial_interface(void)
{
    if (0x10 & USISRL)
      P1OUT |= 0x01;
    else
      P1OUT &= ~0x01;
    USISRL = P1IN;
    USICNT = 8;                           // re-load counter
}

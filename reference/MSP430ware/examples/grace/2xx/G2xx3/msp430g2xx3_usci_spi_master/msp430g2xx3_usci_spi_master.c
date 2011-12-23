//******************************************************************************
//   MSP430G2xx3 Demo - USCI_A0, SPI 3-Wire Master Incremented Data
//
//   Description: SPI master talks to SPI slave using 3-wire mode. Incrementing
//   data is sent by the master starting at 0x01. Received data is expected to
//   be same as the previous transmission.  USCI RX ISR is used to handle
//   communication with the CPU, normally in LPM0. If high, P1.0 indicates
//   valid data reception.
//   ACLK = n/a, MCLK = SMCLK = DCO ~1.2MHz, BRCLK = SMCLK/2
//
//   Use with SPI Slave Data Echo code example. If slave is in debug mode, P3.6
//   slave reset signal conflicts with slave's JTAG; to work around, use IAR's
//   "Release JTAG on Go" on slave device.  If breakpoints are set in
//   slave RX ISR, master must stopped also to avoid overrunning slave
//   RXBUF.
//
//                    MSP430G2xx3
//                 -----------------
//             /|\|              XIN|-
//              | |                 |
//              --|RST          XOUT|-
//                |                 |
//                |             P1.2|-> Data Out (UCA0SIMO)
//                |                 |
//          LED <-|P1.0         P1.1|<- Data In (UCA0SOMI)
//                |                 |
//  Slave reset <-|P1.5         P1.4|-> Serial Clock Out (UCA0CLK)
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

unsigned char MST_Data, SLV_Data;
volatile unsigned int i;

void main(int argc, char *argv[])
{
    CSL_init();

    P1OUT &= ~BIT5;                           // Now with SPI signals initialized,
    P1OUT |= BIT5;                            // reset slave

    __delay_cycles(75);                 // Wait for slave to initialize

    MST_Data = 0x01;                          // Initialize data values
    SLV_Data = 0x00;

    UCA0TXBUF = MST_Data;                     // Transmit first character

    __bis_SR_register(LPM0_bits + GIE);       // CPU off, enable interrupts
}

void USCIA0RX_ISR(void)
{
    while (!(IFG2 & UCA0TXIFG));              // USCI_A0 TX buffer ready?

    if (UCA0RXBUF == SLV_Data)                // Test for correct character RX'd
      P1OUT |= BIT0;                          // If correct, light LED
    else
      P1OUT &= ~BIT0;                         // If incorrect, clear LED

    MST_Data++;                               // Increment master value
    SLV_Data++;                               // Increment expected slave value
    UCA0TXBUF = MST_Data;                     // Send next value

    __delay_cycles(50);                     // Add time between transmissions to
}                                           // make sure slave can keep up

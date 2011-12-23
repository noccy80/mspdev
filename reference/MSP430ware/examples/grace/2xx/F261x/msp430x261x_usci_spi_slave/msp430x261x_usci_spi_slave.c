//******************************************************************************
//   msp430x26x Demo - USCI_A0, SPI 3-Wire Slave Data Echo
//
//   Description: SPI slave talks to SPI master using 3-wire mode. Data received
//   from master is echoed back.  USCI RX ISR is used to handle communication,
//   CPU normally in LPM4.  Prior to initial data exchange, master pulses
//   slaves RST for complete reset.
//   ACLK = 32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz
//
//   Use with SPI Master Incremented Data code example.  If the slave is in
//   debug mode, the reset signal from the master will conflict with slave's
//   JTAG; to work around, use IAR's "Release JTAG on Go" on slave device.  If
//   breakpoints are set in slave RX ISR, master must stopped also to avoid
//   overrunning slave RXBUF.
//
//             MSP430F261x/241x
//             -----------------
//         /|\|              XIN|-
//          | |                 |   32kHz xtal
//          | |             XOUT|-
// Master---+-|RST              |
//            |             P3.4|<- Data In (UCA0SIMO)
//            |                 |
//            |             P3.5|-> Data Out (UCA0SOMI)
//            |                 |
//            |             P3.0|<- Serial Clock In (UCA0CLK)
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

volatile unsigned int i;

int main(int argc, char *argv[])
{
    WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
    if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)
    {
      while(1);                               // If calibration constants erased
                                              // do not load, trap CPU!!
    }

    while(!(P3IN&0x01));                      // If clock sig from mstr stays low,
                                              // it is not yet in SPI mode
    CSL_init();                               // Activate Grace-generated configuration

    _BIS_SR(LPM3_bits + GIE);                 // Enter LPM4, enable interrupts
}

void USCIA0RX_ISR(void)
{
    while (!(IFG2 & UCA0TXIFG));              // USCI_A0 TX buffer ready?
    UCA0TXBUF = UCA0RXBUF;
}

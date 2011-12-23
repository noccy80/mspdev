//******************************************************************************
//   MSP430x26x Demo - USCI_A0, 115200 UART Echo ISR, DCO SMCLK
//
//   Description: Echo a received character, RX ISR used. Normal mode is LPM0.
//   USCI_A0 RX interrupt triggers TX Echo.
//   Baud rate divider with 1MHz = 1MHz/115200 = ~8.7
//   ACLK = n/a, MCLK = SMCLK = CALxxx_1MHZ = 1MHz
//
//             MSP430F261x/241x
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |     P3.4/UCA0TXD|------------>
//            |                 | 115200 - 8N1
//            |     P3.5/UCA0RXD|<------------
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
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)
    {
      while(1);                               // If calibration constants erased
                                              // do not load, trap CPU!!
    }

    CSL_init();                     // Activate Grace-generated configuration

    __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled
}

void USCI0RX_ISR(void)
{
    while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
    UCA0TXBUF = UCA0RXBUF;                    // TX -> RXed character
}

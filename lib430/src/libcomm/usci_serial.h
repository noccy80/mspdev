#ifndef HW_SERIAL_H
#define HW_SERIAL_H

/**
 * Serial - simple access to USCI UART hardware
 *          code implements interrupt driven input
 *          and poll driven output.
 *
 * License: Do with this code what you want. However, don't blame
 * me if you connect it to a heart pump and it stops.  This source
 * is provided as is with no warranties. It probably has bugs!!
 * You have been warned!
 *
 * Author: Rick Kimball
 * email: rick@kimballsoftware.com
 * Version: 1.00 Initial version 05-12-2011
 */

template<typename T_STORAGE>
struct Serial {
    T_STORAGE &_recv_buffer;

    /**
     * init - setup the USCI UART hardware for 9600-8-N-1
     *        P1.1 = RX PIN, P1.2 = TX PIN
     */
    inline void init() {
        P1SEL = BIT1 + BIT2; // P1.1=RXD, P1.2=TXD
        P1SEL2 = BIT1 + BIT2; // P1.1=RXD, P1.2=TXD

        UCA0CTL1 |= UCSSEL_2; // use SMCLK for USCI clock
        UCA0BR0 = 130; // 16MHz 9600
        UCA0BR1 = 6; // 16MHz 9600
        UCA0MCTL = UCBRS1 + UCBRS0; // Modulation UCBRSx = 3
        UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
        IE2 |= UCA0RXIE; // Enable USCI0RX_ISR interrupt
    }

    inline bool empty() {
        return _recv_buffer.empty();
    }

    inline int recv() {
        return _recv_buffer.pop_front();
    }

    void xmit(uint8_t c) {
        while (!(IFG2 & UCA0TXIFG))
            ; // USCI_A0 TX buffer ready?

        UCA0TXBUF = (uint8_t) c; // TX -> RXed character
    }

    void xmit(const char *s) {
        while (*s) {
            xmit((uint8_t) *s);
            ++s;
        }
    }

};

#endif /* HW_SERIAL_H */

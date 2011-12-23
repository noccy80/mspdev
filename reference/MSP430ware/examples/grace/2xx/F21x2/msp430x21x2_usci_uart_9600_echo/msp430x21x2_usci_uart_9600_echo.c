//******************************************************************************
//   MSP430F21x2 Demo - USCI_A0, Ultra-Low Pwr UART 9600 RX/TX, 32kHz ACLK
//
//   Description: This program demonstrates a full-duplex 9600-baud UART using
//   USCI_A0 and a 32kHz crystal.  The program will wait in LPM3, and receive
//   a string1 into RAM, and echo back the complete string.
//   ACLK = BRCLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO ~1.2MHz
//   Baud rate divider with 32768Hz XTAL @9600 = 32768Hz/9600 = 3.41
//   //* An external watch crystal is required on XIN XOUT for ACLK *//
//
//                MSP430F21x2
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |     P3.4/UCA0TXD|------------>
//            |                 | 9600 - 8N1
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

char string1[8];
char i;
char j = 0;

void main(int argc, char *argv[])
{
    CSL_init();

    IE2 &= ~UCA0TXIE;                         // Explicitly disable since GRACE
                                              // enables to generate TX_ISR
    __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, interrupts enabled
}

void USCI0TX_ISR(void)
{
    UCA0TXBUF = string1[i++];                 // TX next character

    if (i == sizeof string1)                  // TX over?
      IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
}

void USCI0RX_ISR(void)
{
    string1[j++] = UCA0RXBUF;
    if (j > sizeof string1 - 1)
    {
      i = 0;
      j = 0;
      IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
      UCA0TXBUF = string1[i++];
    }
}

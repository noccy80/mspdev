//******************************************************************************
//   MSP430G2xx3 Demo - USCI_A0, UART 9600 Full-Duplex Transceiver, 32kHz ACLK
//
//   Description: USCI_A0 communicates continously as fast as possible full-
//   duplex with another device. Normal mode is LPM3, with activity only during
//   RX and TX ISR's. The TX ISR indicates the USCI_A0 is ready to send another
//   character. The RX ISR indicates the USCI_A0 has received a character. At
//   9600 baud, a full character is tranceived ~1ms.
//   The levels on P1.3/P1.4 are TX'ed. RX'ed value is displayed on P1.6/0.  
//   ACLK = BRCLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO ~1.2MHz
//   Baud rate divider with 32768Hz XTAL @9600 = 32768Hz/9600 = 3.41
//* An external watch crystal is required on XIN XOUT for ACLK *//
//
//                 MSP430G2xx3                  MSP430G2xx3
//              -----------------            -----------------
//             |              XIN|-      /|\|              XIN|-
//             |                 | 32kHz  | |                 | 32kHz
//             |             XOUT|-       --|RST          XOUT|-
//             |                 | /|\      |                 |
//             |              RST|---       |                 |
//             |                 |          |                 |
//           ->|P1.3             |          |             P1.0|-> LED
//           ->|P1.4             |          |             P1.6|-> LED
//       LED <-|P1.0             |          |             P1.3|<-
//       LED <-|P1.6             |          |             P1.4|<-
//             |     UCA0TXD/P1.2|--------->|P1.1             |
//             |                 |   9600   |                 |
//             |     UCA0RXD/P1.1|<---------|P1.2             |
//
//
//   D. Dang
//   Texas Instruments Inc.
//   February 2011
//   Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************
#include "msp430g2553.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1OUT = 0x00;                             // P1.0/6 setup for LED output
  P1DIR = BIT0 + BIT6;
  P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2;                      
  UCA0CTL1 |= UCSSEL_1;                     // CLK = ACLK
  UCA0BR0 = 0x03;                           // 32kHz/9600 = 3.41
  UCA0BR1 = 0x00;
  UCA0MCTL = UCBRS1 + UCBRS0;               // Modulation UCBRSx = 3
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE + UCA0TXIE;               // Enable USCI_A0 TX/RX interrupt

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts enabled
}

// USCI A0/B0 Transmit ISR
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
  unsigned char TxByte=0;
  if (P1IN & BIT3)
    TxByte |= BIT6;
  if (P1IN & BIT4)
    TxByte |= BIT0;
  UCA0TXBUF = TxByte;                       // Read, justify, and transmit
}

// USCI A0/B0 Receive ISR
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
  P1OUT = UCA0RXBUF;                        // Display RX'ed charater
}

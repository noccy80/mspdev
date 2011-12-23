//******************************************************************************
//   MSP430F41x2 Demo - USCI_A0, Ultra-Low Pwr UART 9600 String, 32kHz ACLK
//
//   Description: This program demonstrates a full-duplex 9600-baud UART using
//   USCI_A0 and a 32kHz crystal.  The program will wait in LPM3, and will
//   respond to a received 'u' character using 8N1 protocol. The response will
//   be the string 'Hello World'.
//   ACLK = BRCLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO ~1.045Mhz
//   Baud rate divider with 32768Hz XTAL @9600 = 32768Hz/9600 = 3.41
//   //* An external watch crystal is required on XIN XOUT for ACLK *//
//
//
//                 MSP430F41x2
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |     P6.5/UCA0RXD|------------>
//            |                 | 9600 - 8N1
//            |     P6.6/UCA0TXD|<------------
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************

#include  <msp430x41x2.h>
const char string1[] = { "Hello World\r\n" };
unsigned int j;

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSCFault flag
    for (i = 0x47FF; i > 0; i--);           // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  P6SEL |= BIT5+BIT6;                       // P6.5,6 = USCI_A0 RXD/TXD
  UCA0CTL1 |= UCSSEL_1;                     // CLK = ACLK
  UCA0BR0 = 0x03;                           // 32k/9600 - 3.41
  UCA0BR1 = 0x00;                           //
  UCA0MCTL = 0x06;                          // Modulation
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM0, interrupts enabled
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
  UCA0TXBUF = string1[j++];                 // TX next character

  if (j == sizeof string1 - 1)              // TX over?
    IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
  if (UCA0RXBUF == 'u')                     // 'u' received?
  {
    j = 0;
    IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
    UCA0TXBUF = string1[j++];
  }
}

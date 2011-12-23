//******************************************************************************
//  MSP-FET430P120 Demo - USART0, Ultra-Low Pwr UART 9600 String, 32kHz ACLK
//
//  Description: This program demonstrates a full-duplex 9600-baud UART using
//  USART0 and a 32kHz crystal.  The program will wait in LPM3, and will
//  respond to a received 'u' character using 8N1 protocol. The response will
//  be the string 'Hello World.
//  Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (0003h 4Ah )
//  ACLK = LFXT1 = UCLK0, MCLK = SMCLK = default DCO ~800KHz
//  //* An external watch crystal is required on XIN XOUT for ACLK *//	
//
//              MSP430F123(2)
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |             P3.4|----------->
//           |                 | 9600 - 8N1
//           |             P3.5|<-----------
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x12x2.h>

static char string1[] = { "Hello World\r\n" };

char i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P3SEL = 0x30;                             // P3.3,4 = USART0 TXD/RXD

  ME2 |= UTXE0 + URXE0;                     // Enabled USART0 TXD/RXD
  UCTL0 |= CHAR;                            // 8-bit character, SWRST=1
  UTCTL0 |= SSEL0;                          // UCLK = ACLK
  UBR00 = 0x03;                             // 9600 from 1Mhz
  UBR10 = 0x00;                             //
  UMCTL0 = 0x4A;                            // Modulation
  UCTL0 &= ~SWRST;                          // Initialize USART state machine
  IE2 |= URXIE0 + UTXIE0;                   // Enable USART0 RX/TX interrupt
  IFG2 &= ~UTXIFG0;                         // Clear inital flag on POR

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

// UART0 TX ISR
#pragma vector=USART0TX_VECTOR
__interrupt void usart0_tx (void)
{
  if (i < sizeof string1-1)
    TXBUF0 = string1[i++];
}

// UART0 RX ISR
#pragma vector=USART0RX_VECTOR
__interrupt void usart0_rx (void)
{
  if (RXBUF0 == 'u')                        // 'u' received?
  {
    i = 0;
    TXBUF0 = string1[i++];
  }


}



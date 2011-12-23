//******************************************************************************
//  MSP-FET430P140 Demo - USART1, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
//
//  Description: Echo a received character, RX ISR used. In the Mainloop UART1
//  is made ready to receive one character with interrupt active. The Mainloop
//  waits in LPM3. The UART1 ISR forces the Mainloop to exit LPM3 after
//  receiving one character which echo's back the received character.
//  ACLK = UCLK1 = LFXT1 = 32768, MCLK = SMCLK = DCO~ 800k
//  Baud rate divider with 32768hz XTAL @2400 = 32768Hz/2400 = 13.65 (000Dh)
//  //* An external watch crystal is required on XIN XOUT for ACLK *//	
//
//                MSP430F149
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |             P3.6|----------->
//           |                 | 2400 - 8N1
//           |             P3.7|<-----------
//
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL |= 0xC0;                            // P3.6,7 = USART1 option select
  ME2 |= UTXE1 + URXE1;                     // Enable USART1 TXD/RXD
  UCTL1 |= CHAR;                            // 8-bit character
  UTCTL1 |= SSEL0;                          // UCLK = ACLK
  UBR01 = 0x0D;                             // 32k/2400 - 13.65
  UBR11 = 0x00;
  UMCTL1 = 0x6B;                            // Modulation
  UCTL1 &= ~SWRST;                          // Initialize USART state machine
  IE2 |= URXIE1;                            // Enable USART1 RX interrupt

// Mainloop
  for (;;)
  {
  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/interrupt
  while (!(IFG2 & UTXIFG1));                // USART1 TX buffer ready?
  TXBUF1 = RXBUF1;                          // RXBUF1 to TXBUF1
  }
}

// UART1 RX ISR will for exit from LPM3 in Mainloop
#pragma vector=USART1RX_VECTOR
__interrupt void usart1_rx (void)
{
  _BIC_SR_IRQ(LPM3_bits);                   // Clear LPM3 bits from 0(SR)
}

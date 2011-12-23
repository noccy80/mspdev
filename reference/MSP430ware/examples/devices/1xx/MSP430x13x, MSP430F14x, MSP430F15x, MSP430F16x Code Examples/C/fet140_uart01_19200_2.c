//******************************************************************************
//  MSP-FET430P140 Demo - USART0, UART 19200 Echo ISR, XT2 HF XTAL ACLK
//
//  Description: Echo a received character, RX ISR used. Normal mode is LPM0,
//  USART0 RX interrupt triggers TX Echo. Though not required, MCLK = XT2.
//  ACLK = n/a, MCLK = SMCLK = UCLK0 = XT2 = 8MHz
//  Baud rate divider with 8Mhz XTAL @19200 = 8MHz/19200 = 416.66 ~ 417 (01A0h)
//  //* An external 8MHz XTAL on X2IN X2OUT is required for XT2CLK *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//		
//
//
//                MSP430F149
//             -----------------
//         /|\|            XT2IN|-
//          | |                 | 8Mhz
//          --|RST        XT2OUT|-
//            |                 |
//            |             P3.4|------------>
//            |                 | 19200 - 8N1
//            |             P3.5|<------------
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
  volatile unsigned int i;
  P3SEL |= 0x30;                            // P3.4,5 = USART0 TXD/RXD
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  BCSCTL1 &= ~XT2OFF;                       // XT2on

  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0xFF; i > 0; i--);               // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  BCSCTL2 |= SELM_2 + SELS;                 // MCLK = SMCLK = XT2 (safe)

  ME1 |= UTXE0 + URXE0;                     // Enable USART0 TXD/RXD
  UCTL0 |= CHAR;                            // 8-bit character
  UTCTL0 |= SSEL1;                          // UCLK = SMCLK
  UBR00 = 0xA0;                             // 8Mhz/19200 ~ 417
  UBR10 = 0x01;                             //
  UMCTL0 = 0x00;                            // no modulation
  UCTL0 &= ~SWRST;                          // Initialize USART state machine
  IE1 |= URXIE0;                            // Enable USART0 RX interrupt

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

#pragma vector=USART0RX_VECTOR
__interrupt void usart0_rx (void)
{
  while (!(IFG1 & UTXIFG0));                // USART0 TX buffer ready?
  TXBUF0 = RXBUF0;                          // RXBUF0 to TXBUF0
}

//******************************************************************************
//  MSP-FET430P140 Demo - USART1, UART 19200 Echo ISR, XT2 HF XTAL SMCLK
//
//  Description: Echo a received character, RX ISR used. Normal mode is LPM0,
//  USART1 RX interrupt triggers TX Echo. Though not required, MCLK= XT2.
//  ACLK =n/a, MCLK = SMCLK = UCLK1 = XT2 = 8MHz
//  Baud rate divider with 8Mhz XTAL @19200 = 8MHz/19200 = 416.66 ~ 417 (01A0h)
//  //* An external 8MHz XTAL on X2IN X2OUT is required for XT2CLK *//	
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//	
//
//               MSP430F149
//            -----------------
//        /|\|             X2IN|-
//         | |                 | 8Mhz
//         --|RST         X2OUT|-
//           |                 |
//           |             P3.6|------------>
//           |                 | 19200 - 8N1
//           |             P3.7|<------------
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
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL |= 0xC0;                            // P3.6,7 = USART1 option select

  BCSCTL1 &= ~XT2OFF;                       // XT2on

  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0xFF; i > 0; i--);               // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  BCSCTL2 |= SELM_2 + SELS;                 // MCLK= SMCLK= XT2 (safe)

  ME2 |= UTXE1 + URXE1;                     // Enable USART1 TXD/RXD
  UCTL1 |= CHAR;                            // 8-bit character
  UTCTL1 |= SSEL1;                          // UCLK = SMCLK
  UBR01 = 0xA0;                             // 8Mhz/19200 ~ 417
  UBR11 = 0x01;                             //
  UMCTL1 = 0x00;                            // no modulation
  UCTL1 &= ~SWRST;                          // Initialize USART state machine
  IE2 |= URXIE1;                            // Enable USART1 RX interrupt

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

#pragma vector=USART1RX_VECTOR
__interrupt void usart1_rx (void)
{
  while (!(IFG2 & UTXIFG1));                // USART1 TX buffer ready?
  TXBUF1 = RXBUF1;                          // RXBUF1 to TXBUF1
}

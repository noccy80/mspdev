//******************************************************************************
//  MSP-FET430P140 Demo - USART0, UART 115200 Echo ISR, HF XTAL ACLK
//
//  Description: Echo a received character, RX ISR used. Normal mode is LPM0,
//  USART0 RX interrupt triggers TX Echo.
//  ACLK = MCLK = UCLK0 = LFXT1 = 8MHz
//  Baud rate divider with 8Mhz XTAL = 8000000/115200 = 0069 (0045h)
//  //* An external 8Mhz XTAL on XIN XOUT is required for ACLK *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//	
//
//
//                MSP430F149
//             -----------------
//         /|\|              XIN|-
//          | |                 | 8MHz
//          --|RST          XOUT|-
//            |                 |
//            |             P3.4|------------>
//            |                 | 115200 - 8N1
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

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL |= 0x30;                            // P3.4,5 = USART0 TXD/RXD
  BCSCTL1 |= XTS;                           // ACLK= LFXT1= HF XTAL

  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0xFF; i > 0; i--);               // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  BCSCTL2 |= SELM_3;                        // MCLK = LFXT1 (safe)
  ME1 |= UTXE0 + URXE0;                     // Enable USART0 TXD/RXD
  UCTL0 |= CHAR;                            // 8-bit character
  UTCTL0 |= SSEL0;                          // UCLK= ACLK
  UBR00 = 0x45;                             // 8MHz 115200
  UBR10 = 0x00;                             // 8MHz 115200
  UMCTL0 = 0x00;                            // 8MHz 115200 modulation
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

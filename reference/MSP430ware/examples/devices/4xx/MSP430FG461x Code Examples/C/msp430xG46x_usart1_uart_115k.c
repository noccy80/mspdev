//******************************************************************************
//   MSP430xG46x Demo - USART1, 115200 UART Echo ISR, DCO SMCLK
//
//   Description: Echo a received character, RX ISR used. Normal mode is LPM0.
//   USART1 RX interrupt triggers TX Echo.
//   Baud rate divider with 1048576hz = 1048576/115200 = ~9.1 (009h|08h)
//   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                MSP430FG4619
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |       P4.0/UTXD1|------------>
//            |                 | 115200 - 8N1
//            |       P4.1/URXD1|<------------
//
//   K. Quiring
//   Texas Instruments Inc.
//   October 2005
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.39 beta
//******************************************************************************

#include  <msp430xG46x.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  P4SEL |= 0x03;                            // P4.1,0 = USART1 TXD/RXD

  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0x47FF; i > 0; i--);             // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  ME2 |= UTXE1 + URXE1;                     // Enable USART1 TXD/RXD
  U1CTL |= CHAR;                            // 8-bit character
  U1TCTL |= SSEL1;                          // UCLK= ACLK
  U1BR0 = 0x09;                             // 1MHz 115200
  U1BR1 = 0x00;                             // 1MHz 115200
  U1MCTL = 0x08;                            // 1MHz 115200 modulation
  U1CTL &= ~SWRST;                          // Initialize USART state machine
  IE2 |= URXIE1;                            // Enable USART1 RX interrupt

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

#pragma vector=USART1RX_VECTOR
__interrupt void USART1_rx (void)
{
  while (!(IFG2 & UTXIFG1));                // USART1 TX buffer ready?
  TXBUF1 = RXBUF1;                          // RXBUF1 to TXBUF1
}

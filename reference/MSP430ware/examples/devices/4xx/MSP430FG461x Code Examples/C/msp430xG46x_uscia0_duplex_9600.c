//******************************************************************************
//    MSP430xG46x Demo - USCI_A0, UART 9600 Full-Duplex Transceiver, 32K ACLK
//
//   Description: USCI_A0 communicates continuously as fast as possible
//   full-duplex with another device. Normal mode is LPM3, with activity only
//   during RX and TX ISR's. The TX ISR indicates the UART is ready to send
//   another character.  The RX ISR indicates the UART has received a character.
//   At 9600 baud, a full character is tranceived ~1ms.
//   The levels on P1.4/5 are TX'ed. RX'ed value is displayed on P1.0/1.
//   ACLK = BRCLK = LFXT1 = 32768, MCLK = SMCLK = DCO~ 1048k
//   Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (0003h 4Ah)
//   //* An external watch crystal is required on XIN XOUT for ACLK *//	
//
//                 MSP430xG461x                  MSP430xG461x
//              -----------------            -----------------
//             |              XIN|-      /|\|              XIN|-
//             |                 | 32KHz  | |                 | 32KHz
//             |             XOUT|-       --|RST          XOUT|-
//             |                 | /|\      |                 |
//             |              RST|---       |                 |
//             |                 |          |                 |
//           ->|P1.4             |          |             P1.0|-> LED
//           ->|P1.5             |          |             P1.1|-> LED
//       LED <-|P1.0             |          |             P1.4|<-
//       LED <-|P1.1             |          |             P1.5|<-
//             |     UCA0TXD/P4.6|--------->|P4.7             |
//             |                 |   9600   |                 |
//             |     UCA0RXD/P4.7|<---------|P4.6             |
//
//
//   K. Quiring/ M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include  <msp430xG46x.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0x47FF; i > 0; i--);             // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  P1OUT = 0x000;                            // P1.0/1 setup for LED output
  P1DIR |= 0x003;                           //
  P4SEL |= 0x0C0;                           // P4.7,6 UART option select
  UCA0CTL1 |= UCSSEL_1;                     // CLK = A0CLK
  UCA0BR0 = 0x03;                           // 32k/9600 - 3.41
  UCA0BR1 = 0x00;                           //
  UCA0MCTL = 0x06;                          // Modulation
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE+UCA0TXIE;                 // Enable USCI_A0 TX/RX interrupt

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupts enabled
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI_A0_rx (void)
{
  P1OUT = UCA0RXBUF;                        // RXBUF1 to TXBUF1
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI_A0_Tx (void)
{
  volatile unsigned int i;
  unsigned int delay;

  for(delay=240;delay>0;delay--);           // Add small gap between TX'ed bytes
  i = P1IN;
  i = i >> 4;
  UCA0TXBUF = i;                            // Transmit character
}

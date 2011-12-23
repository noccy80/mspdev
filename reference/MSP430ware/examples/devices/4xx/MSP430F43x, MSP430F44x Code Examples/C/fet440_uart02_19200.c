//******************************************************************************
//   MSP-FET430P440 Demo - USART0, 19200 UART Ultra-low Pwr Echo ISR, 32kHz ACLK
//
//  Description: Echo a received character, USART0 RX ISR at high-speed used
//  with ultra-low power techniques. Normal operation is LPM3. Use start-bit
//  edge detect - URXSE - to automatically (re)enable DCO and trigger ISR. ISR
//  must make sure DCO clock source remains enabled for the UART to receive
//  full character.
//  Software needs to make sure a character has been completely TX'ed, or RX'ed
//  before entering LPM3, which disables DCO required for the USART baud rate
//  generator. In the example, TX'ing is checked using the TXEPT bit directly.
//  RX'ing is checked using the SSEL0 clock select bit as a flag. This is
//  possible because UCLK0 = SMCLK when either both SSEL1 and SSEL0 or just
//  SSEL1 = 1. In the example, when SSEL1 = SSEL0 = 1, there is no RX'ing, and
//  LPM3 is allowed. When SSEL 1 = 1 and SSEL0 = 0, SMCLK is selected, but
//  RX'ing is active and the DCO is required, thus LPM3 is not allowed.
//  Baud rate divider with 1048576hz= 1048576Hz/19200 = ~54.61 (036h|6Bh)
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                 MSP430F449
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P2.4|----------->
//            |                 | 19200 - 8N1
//            |             P2.5|<-----------
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include <msp430x44x.h>

void main(void)
{
  unsigned i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP18PF;                     // Configure load caps
  for (i = 0xFFFF; i > 0; i--);             // Delay for FLL to set
  P2SEL |= 0x30;                            // P2.4,5 = USART0 TXD/RXD
  ME1 |= UTXE0 + URXE0;                     // Enabled USART0 TXD/RXD
  UCTL0 |= CHAR;                            // 8-bit character, SWRST = 1
  UTCTL0 |= SSEL1 + SSEL0 + URXSE;          // UCLK = SMCLK, start edge detect
  UBR00 = 0x36;                             // 19200 from 1Mhz
  UBR10 = 0x00;
  UMCTL0 = 0x6B;                            // Modulation
  UCTL0 &= ~SWRST;                          // Initialize USART state machine
  IE1 |= URXIE0;                            // Enable USART0 RX interrupt

  for (;;)
  {
    while (!(UTCTL0 & TXEPT));              // Confirm no TXing before --> LPM3
    _DINT();                                // Disable interrupts for flag test
    _NOP();
    if (!(UTCTL0 & SSEL0))
      _BIS_SR(LPM0_bits + GIE);             // RX'ing char, LPM0, int's active
    else
      _BIS_SR(LPM3_bits + GIE);             // Enter LPM3, int's active
  }
}

#pragma vector=USART0RX_VECTOR
__interrupt void usart0_rx (void)
{
  if ((IFG1 & URXIFG0))                     // Test URXIFG0
  {
    while (!(IFG1 & UTXIFG0));              // USART0 TX buffer ready?
    TXBUF0 = RXBUF0;                        // RXBUF0 to TXBUF0
    _BIC_SR_IRQ(LPM3_bits);                 // Exit LPM3 after reti
    UTCTL0 |= SSEL0;                        // SSEL0 = 1, no RX activity
  }
  else                                      // Start edge
  {
    UTCTL0 &= ~URXSE;                       // Clear URXS signal
    UTCTL0 |= URXSE;                        // Re-enable edge detect
    _BIC_SR_IRQ(SCG1 + SCG0);               // DCO reamins on after reti
    UTCTL0 &= ~SSEL0;                       // SSEL0= 0, RX activity
  }
}


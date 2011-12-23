//*****************************************************************************
//  MSP430xG46x Demo - USART1, Ultra-Low Pwr UART 19200 Echo ISR, 32kHz ACLK
//
//  Description: Echo a received character, USART1 RX ISR at high-speed used
//  with ultra-low power techniques. Normal operation in LPM3,
//  On valid RX character, character echoed back. Use start-bit
//  edge detect - URXSE - to automatically (re)enable DCO and trigger ISR. ISR
//  must make sure DCO clock source remains enabled for the UART to receive
//  full character.
//  Software needs to make sure a character has been completely TX'ed, or RX'ed
//  before entering LPM3, which disables DCO required for the USART baud rate
//  generator. In the example, TX'ing is checked using the TXEPT bit directly.
//  RX'ing is checked using the SSEL0 clock select bit as a flag. This is
//  possible because UCLK1 = SMCLK when either both SSEL1 and SSEL0 or just
//  SSEL1 = 1. In the example, when SSEL1 = SSEL0 = 1 there is no RX'ing, and
//  LPM3 is allowed. When SSEL 1 = 1 and  SSEL0 = 0 SMCLK is selected, but
//  RX'ing is active and the DCO is required, thus LPM3 is not allowed.
//  ACLK = LFXT1/8 = 32768/8,  MCLK = SMCLK = UCLK1 = DCOCLK = 1048576
//  Baud rate divider with 1048576hz= 1048576Hz/19200 ~ 55 (0036h)
//  //* An external 32kHz watch crystal on XIN XOUT is required for ACLK *//	
//
//
//                MSP430FG4619
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32768Hz
//          --|RST          XOUT|-
//            |                 |
//            |             P4.0|------------>
//            |                 | 19200 - 8N1
//            |             43.1|<------------
//
//
//  K. Quiring/ M. Mitchell
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//*****************************************************************************

#include  <msp430xG46x.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P4SEL |= 0x03;                            // P4.1,0 = USART1 TXD/RXD
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0x47FF; i > 0; i--);             // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  ME2 |= UTXE1 + URXE1;                     // Enable USART1 TXD/RXD
  U1CTL |= CHAR;                            // 8-bit character
  U1TCTL |= SSEL1 + SSEL0 + URXSE;          // UCLK = SMCLK, start edge detect
  U1BR0 = 0x36;                             // 1MHz 19200
  U1BR1 = 0x00;                             // 1MHz 19200
  U1MCTL = 0x6B;                            // 1MHz 19200 modulation
  U1CTL &= ~SWRST;                          // Initialize USART state machine
  IE2 |= URXIE1;                            // Enable USART1 RX interrupt

  for (;;)
  {
    while (!(U1TCTL & TXEPT));              // Confirm no TXing before --> LPM3
    _DINT();                                // Disable interrupts for flag test
    _NOP();
    if (!(U1TCTL & SSEL0))
     _BIS_SR(LPM0_bits + GIE);              // RX'ing char, LPM, int's active
    else
     _BIS_SR(LPM3_bits + GIE);              // Enter LPM3, int's active
  }
}

#pragma vector=USART1RX_VECTOR
__interrupt void usart1_rx (void)
{
  if ((IFG2 & URXIFG1))                     // Test URXIFG0
  {
    while (!(IFG2 & UTXIFG1));              // USART1 TX buffer ready?
    U1TXBUF = U1RXBUF;                      // RXBUF0 to TXBUF0
    _BIC_SR_IRQ(LPM3_bits);                 // Exit LPM3 after reti
    U1TCTL |= SSEL0;                        // SSEL0 = 1, no RX activity
  }
  else                                      // Start edge
  {
    U1TCTL &= ~URXSE;                       // Clear URXS signal
    U1TCTL |= URXSE;                        // Re-enable edge detect
    _BIC_SR_IRQ(SCG1 + SCG0);               // DCO reamins on after reti
    U1TCTL &= ~SSEL0;                       // SSEL0= 0, RX activity
  }
}

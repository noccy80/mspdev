//******************************************************************************
//  MSP-FET430P120 Demo - USART0, UART 19200 Echo ISR, 32kHz ACLK + DCO
//
//  Description: Echo a received character, USART0 RX ISR at high-speed using
//  32kHz XTAL and DCO. Normal operation in LMP0, DCO continuously stabilized,
//  interrupt driven using CCR2. DCO used for UART baud generation. On a valid
//  RX character, the character is echoed back.
//  Baud rate divider with 1048576hz = 1048576Hz/19200 ~ 55 (0036h)
//  ACLK = LFXT1/8 = 32768/8,  MCLK = SMCLK = UCLK0 = DCOCLK  = 1048576
//  //* An external 32kHz watch crystal on XIN XOUT is required for ACLK *//	
//
//
//               MSP430F123(2)
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32768Hz
//          --|RST          XOUT|-
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

#include  <msp430x12x2.h>

#define DELTA 256                           // target DCO = DELTA*(4096) ~ 1MHz

unsigned int Compare, Oldcapture;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL |= 0x30;                            // P3.4,5 = USART0 TXD/RXD
  BCSCTL1 |= DIVA_3;                        // ACLK = LFXT1CLK/8
  ME2 |= UTXE0 + URXE0;                     // Enabled USART0 TXD/RXD
  UCTL0 |= CHAR;                            // 8-bit character
  UTCTL0 |= SSEL1;                          // UCLK = SMCLK
  UBR00 = 0x36;                             // 1MHz 19200
  UBR10 = 0x00;                             //
  UMCTL0 = 0x6B;                            // Modulation
  UCTL0 &= ~SWRST;                          // Initialize USART state machine
  IE2 |= URXIE0;                            // Enabled USART0 RX interrupt
  P3DIR |= 0x10;                            // P3.4 output direction
  CCTL2 = CM_1 + CCIS_1 + CAP + CCIE;       // CAP, ACLK, interrupt
  TACTL = TASSEL_2 + MC_2 + TACLR;          // SMCLK, cont-mode, clear

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

#pragma vector=USART0RX_VECTOR
__interrupt void usart0_rx (void)
{
  while (!(IFG2 & UTXIFG0));                // USART0 TX buffer ready?
  TXBUF0 = RXBUF0;                          // RXBUF0 to TXBUF0
}


// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
  switch( TAIV )
  {
    case  2: break;                         // CCR1 not used
    case  4:
    {
    Compare = CCR2;                         // Get current captured SMCLK
    Compare = Compare - Oldcapture;         // SMCLK difference
    Oldcapture = CCR2;                      // Save current captured SMCLK
    if (DELTA < Compare)
      {
        DCOCTL--;
        if (DCOCTL == 0xFF)                 // DCO is too fast, slow it down
        {
          if (!(BCSCTL1 == (XT2OFF + DIVA_3)))
          BCSCTL1--;                        // Did DCO role under?, Sel lower RSEL
        }
      }
    else
      {
        DCOCTL++;                           // DCO is too slow, speed it down
        if (DCOCTL == 0x00)
        {
          if (!(BCSCTL1 == (XT2OFF + DIVA_3 + 0x07)))
          BCSCTL1++;                        // Did DCO role over? Sel higher RSEL
        }
      }
    }
  case 10: break;                           // not used
  }
}

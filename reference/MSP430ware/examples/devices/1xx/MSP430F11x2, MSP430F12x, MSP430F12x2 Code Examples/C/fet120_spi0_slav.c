//******************************************************************************
//   MSP-FET430P120 Demo - USART0, SPI 3-Wire Slave
//
//   Description: SPI slave talks to SPI master using 3-wire mode. Data is sent
//   to the master starting at 0xFF and decrements. Received data from the
//   master is expected to start at 0x00 and increments with each transmission.
//   USART0 RX ISR is used to handle communication, CPU normally in LPM4.
//   Prior to inital data exchange, master pulses slaves RST for complete reset.
//   ACLK = n/a, MCLK = SMCLK = DCO ~ 800kHz
//
//                MSP430F123(2)
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          | |             XOUT|-
// Master---+-|RST              |
//            |             P3.1|<- Data In (SIMO0)
//            |                 |
//            |             P3.2|-> Data Out (SOMI0)
//            |                 |
//            |             P3.3|<- Serial Clock In (UCLK)
//
//  Z. Albus
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x12x2.h>

char MST_Data = 0x00, SLV_Data = 0xFF;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL = 0x0E;                             // Setup P3 for SPI mode
  U0CTL = CHAR + SYNC + SWRST;              // 8-bit, SPI, Slave
  U0TCTL = CKPL + STC;                      // Polarity, UCLK, 3-wire
  ME2 = USPIE0;                             // Module enable
  U0CTL &= ~SWRST;                          // SPI enable
  IE2 |= URXIE0;                            // Receive interrupt enable
  _EINT();                                  // Enable interrupts

  while (1)
  {
    TXBUF0 = SLV_Data;                      // Ready TXBUF0 w/ 1st character
    LPM4;                                   // Enter LPM4
  }
} // End Main

#pragma vector=USART0RX_VECTOR
__interrupt void SPI0_rx (void)
{
  while ((IFG2 & UTXIFG0) == 0);            // USART0 TX buffer ready?
  if (U0RXBUF == MST_Data)                  // Test for correct character RX'd
  {
    SLV_Data = SLV_Data -1;                 // Decrement incoming data mask
    MST_Data = MST_Data +1;                 // Increment out-going data
    TXBUF0 = SLV_Data;
  }
  else
    TXBUF0 = SLV_Data;
}
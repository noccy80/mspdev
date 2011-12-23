//******************************************************************************
//   MSP430F(G)47x Demo - USCI_A0 IrDA External Loopback Test, 4MHz SMCLK
//
//  Description: This example transmits bytes through the USCI module
//  configured for IrDA mode, and receives them using an external loopback
//  connection. The transfered sequence is 00h, 01h, 02h, ..., ffh. The
//  received bytes are also stored in memory starting at address RxData.
//  In the case of an RX error the LED is lighted and program execution stops.
//  An external loopback connection has been used as it allows for the
//  connection of a scope to monitor the communication, which is not possible
//  when using the internal loopback.
//
//  MCLK = SMCLK = DCO = 4MHz, ACLK = 32kHz
//  //* An external 32kHz XTAL on XIN XOUT is required for ACLK *//
//
//              MSP430F(G)47x
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |          UCA0RXD|--+   external
//           |          UCA0TXD|--+   loopback connection
//           |                 |
//           |                 |
//           |             P4.6|--->  LED
//           |                 |
//
//  P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//******************************************************************************
#include "msp430xG47x.h"

unsigned char RxByte;
volatile unsigned char RxData[256];
unsigned char TxByte;
volatile unsigned int i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P2SEL |= 0x30;                            // Use P2.4/P2.5 for USCI_A0
  P4OUT &= ~0x40;                           // Clear P4.6
  P4DIR |= 0x40;                            // P4.6 output
  SCFQCTL = 121;                            // Set FLL to 3.998MHz
  SCFI0 = FLLD0 + FN_2;                     // Adjust range select
  UCA0CTL1 |= UCSWRST;                      // Set USCI_A0 SW Reset
  UCA0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
  UCA0BR0 = 26;                             // 4Mhz/26=153.8kHz
  UCA0BR1 = 0;
  UCA0MCTL = UCBRF_1 + UCOS16;              // Set 1st stage modulator to 1
                                            // 16-times oversampling mode
  UCA0IRTCTL = UCIRTXPL2 + UCIRTXPL0 + UCIRTXCLK + UCIREN;
                                            // Pulse length = 6 half clock cyc
                                            // Enable BITCLK16, IrDA enc/dec
  UCA0CTL1 &= ~UCSWRST;                     // Resume USCI_A0 operation
  IE2 |= UCA0RXIE;                          // Enable RX int

  TxByte = 0x00;                            // TX data and pointer, 8-bit

  while (1)
  {
    for (i = 1000; i; i--);                 // Small delay
    while (!(IFG2 & UCA0TXIFG));            // USCI_A0 TX buffer ready?
    UCA0TXBUF = TxByte;                     // TX character

    __disable_interrupt();
    IE2 |= UCA0RXIE;                        // Enable RX int
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts

    RxData[TxByte] = RxByte;                // Store RXed character in RAM
    if (TxByte != RxByte)                   // RX OK?
    {
      P4OUT |= 0x40;                        // LED P4.6 on
      while (1);                            // Trap PC here
    }
    TxByte++;                               // Next character to TX
  }
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
  RxByte = UCA0RXBUF;                       // Get RXed character
  IE2 &= ~UCA0RXIE;                         // Disable RX int
  __bic_SR_register_on_exit(CPUOFF);        // Exit LPM0
}

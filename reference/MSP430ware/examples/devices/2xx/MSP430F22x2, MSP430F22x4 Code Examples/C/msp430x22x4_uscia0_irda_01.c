//******************************************************************************
//  MSP430F22x4 Demo - USCI_A0 IrDA External Loopback Test, 8MHz SMCLK
//
//  Description: This example transmits bytes through the USCI module
//  configured for IrDA mode, and receives them using an external loopback
//  connection. The transfered sequence is 00h, 01h, 02h, ..., ffh. The
//  received bytes are also stored in memory starting at address RxData.
//  In the case of an RX error the LED is lighted and program execution stops.
//  An external loopback connection has been used as it allows for the
//  connection of a scope to monitor the communication, which is not possible
//  when using the internal loopback.
//  ACLK = n/a, MCLK = SMCLK = BRCLK = CALxxx_8MHZ = 8MHz
//
//              MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |     P3.5/UCA0RXD|--+   external
//           |     P3.4/UCA0TXD|--+   loopback connection
//           |                 |
//           |                 |
//           |             P1.0|--->  LED
//           |                 |
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

unsigned char RxByte;
volatile unsigned char RxData[256];
unsigned char TxByte;
volatile unsigned int i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  DCOCTL = CALDCO_8MHZ;                     // Load 8MHz constants
  BCSCTL1 = CALBC1_8MHZ;
  P1OUT &= ~0x01;                           // Clear P1.0
  P1DIR |= 0x01;                            // P1.0 output
  P3SEL |= 0x30;                            // Use P3.4/P3.5 for USCI_A0
  UCA0CTL1 |= UCSWRST;                      // Set SW Reset
  UCA0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
  UCA0BR0 = 52;                             // 8MHz/52=153.8KHz
  UCA0BR1 = 0;
  UCA0MCTL = UCBRF_1 + UCOS16;              // Set 1st stage modulator to 1
                                            // 16-times oversampling mode
  UCA0IRTCTL = UCIRTXPL2 + UCIRTXPL0 + UCIRTXCLK + UCIREN;
                                            // Pulse length = 6 half clock cyc
                                            // Enable BITCLK16, IrDA enc/dec
  UCA0CTL1 &= ~UCSWRST;                     // Resume operation

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
      P1OUT |= 0x01;                        // LED P1.0 on
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

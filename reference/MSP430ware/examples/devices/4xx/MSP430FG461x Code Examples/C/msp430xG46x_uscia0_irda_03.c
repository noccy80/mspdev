//******************************************************************************
//  MSP430xG461x Demo - USCI_A0 IrDA Physical Layer Comm, 4MHz SMCLK
//
//  Description: This example receives bytes through the USCI module
//  configured for IrDA mode, and sends them out using the USART1 module
//  to a PC running a terminal software. Likewise, data received from the PC
//  through the USART1 is transmitted via IrDA.
//
//  MCLK = SMCLK = DCO = 4MHz, ACLK = 32kHz
//  //* An external 32kHz XTAL on XIN XOUT is required for ACLK *//
//
//                                    MSP430xG461x
//                               -----------------------
//                              |                       |
//                           /|\|                    XIN|-
//                            | |                       | 32kHz
//                            --|RST                XOUT|-
//                              |                       |
//    GP2W0116YPS   /|\         |                       |
//      -------      |          |                       |
//     |    Vcc|-----+  IrDA    |                       |
//     #    LED|-----+ 9600 8N1 |                       |
//     #    TxD|<---------------|P2.4/UCA0TXD           |
//     #    RxD|--------------->|P2.5/UCA0RXD      UTXD1|--> 115,200 8N1
//     #     SD|-----+          |                  URXD1|<-- Terminal SW
//     |    GND|-----+          |                       |
//      -------      |           -----------------------
//                  ---
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  June 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430xG46x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P2SEL |= 0x30;                            // Use P2.4/P2.5 for USCI_A0
  P4SEL |= 0x03;                            // P4.0,1 = USART1 TXD/RXD
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
  UCA0IRRCTL = UCIRRXPL;                    // Light = low pulse
  UCA0CTL1 &= ~UCSWRST;                     // Resume USCI_A0 operation
  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX int
  U1CTL |= SWRST;                           // Set USART1 SW Reset
  ME2 |= UTXE1 + URXE1;                     // Enable USART1 TXD/RXD
  U1CTL = CHAR + SWRST;                     // 8-bit characters, keep SW reset
  U1TCTL = SSEL1;                           // BRCLK = SMCLK
  U1BR0 = 0x22;                             // 4MHz/115,200=34.72
  U1BR1 = 0x00;                             //
  U1MCTL = 0xdd;                            // Modulation
  U1CTL &= ~SWRST;                          // Release USART1 state machine
  IE2 |= URXIE1;                            // Enable UART1 RX int
  __bis_SR_register(CPUOFF + GIE);          // Enter LPM0 w/ interrupts
}

//------------------------------------------------------------------------------
// Read RX'd byte from UART1 and transmit using USCI_A0 IrDA
//------------------------------------------------------------------------------
#pragma vector = USART1RX_VECTOR
__interrupt void USART1RX_ISR(void)
{
  while (!(IFG2 & UCA0TXIFG));              // Ensure TX buffer is ready
  UCA0TXBUF = U1RXBUF;                      // Move RX'd character to USCI_A
}

//------------------------------------------------------------------------------
// Read RX'd IrDA byte from USCI_A0 and transmit to UART1
//------------------------------------------------------------------------------
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
  while (!(IFG2 & UTXIFG1));                // Ensure TX buffer is ready
  U1TXBUF = UCA0RXBUF;                      // Move RX'd character to UART1
}

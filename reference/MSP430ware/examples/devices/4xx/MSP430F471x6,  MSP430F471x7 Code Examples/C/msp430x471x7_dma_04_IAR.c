//******************************************************************************
//  MSP430x471xx Demo - DMA0, Block Mode UART0 9600, ACLK
//
//   Description: DMA0 is used to transfer a string as a block to U0TXBUF.
//  UTXIFG1 WILL trigger DMA0. "Hello World" is TX'd via 9600 baud on UART1.
//   Watchdog in interval mode triggers block transfer every 1000ms.
//  Level senstive trigger used for UTXIFG1 to prevent loss of inital edge
//  sensitive triggers - UTXIFG0 which is set at POR.
//   ACLK = UCLK 32768Hz, MCLK = SMCLK = default DCO 1048576Hz
//   Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (0003h)
//
//                MSP430x471xx
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32768Hz
//          --|RST          XOUT|-
//            |                 |
//            |     P2.4/UCA0TXD|------------> "Hello World"
//            |                 | 9600 - 8N1
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include "msp430x471x7.h"

const char String1[13] = "Hello World\n";

void main(void)
{
  WDTCTL = WDT_ADLY_1000;                   // WDT 1000ms, ACLK, interval timer
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P2SEL |= BIT4+BIT5;                       // P2.4,5 = USCIA0 TXD/RXD
  //Configure USCIA0, UART
  UCA0CTL1 = UCSSEL_1;                      // ACLK
  /* baud rate = 9600 */
  UCA0BR0 = 0x3;                            // 32768Hz 9600 32k/9600=3.41
  UCA0BR1 = 0x0;
  UCA0MCTL = UCBRS_3;                       // Modulation UCBRSx = 3
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  
  // Configure DMA0
  DMACTL0 = DMA0TSEL_4;                     // UTXIFG0 trigger
  DMA0SA = (int)String1;                    // Source block address
  DMA0DA = (int)&UCA0TXBUF;                 // Destination single address
  DMA0SZ = sizeof String1-1;                // Block size
  DMA0CTL = DMASRCINCR_3 + DMASBDB + DMALEVEL;  // Repeat, inc src, byte transfer
  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts
  _NOP();                                   // Reqd only for debugger
}

#pragma vector = WDT_VECTOR                 // Trigger DMA block transfer
__interrupt void WDT_ISR(void)
{
  DMA0CTL |= DMAEN;                         // Enable
}



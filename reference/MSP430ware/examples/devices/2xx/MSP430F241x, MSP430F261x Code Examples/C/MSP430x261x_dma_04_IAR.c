//******************************************************************************
//   MSP430x26x Demo - DMA0, single transfer Mode UART1 9600, ACLK
//
//   Description: DMA0 is used to transfer a string as a block to U1TXBUF.
//  UTXIFG1 WILL trigger DMA0. "Hello World" is TX'd via 9600 baud on UART1.
//   Watchdog in interval mode triggers block transfer every 1000ms.
//  Level senstive trigger used for UTXIFG1 to prevent loss of inital edge
//  sensitive triggers - UTXIFG1 which is set at POR.
//   ACLK = UCLK 32768Hz, MCLK = SMCLK = default DCO 1048576Hz
//   Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (0003h)
//
//                MSP430x2618
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32768Hz
//          --|RST          XOUT|-
//            |                 |
//            |     P3.6/UCA1TXD|------------> "Hello World"
//            |                 | 9600 - 8N1
//
//   B. Nisarga
//   Texas Instruments Inc.
//   September 2007
//   Built with IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x26x.h"

const char String1[13] = "\nHello World";

void main(void)
{
  WDTCTL = WDT_ADLY_1000;                   // WDT 1000ms, ACLK, interval timer
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P3SEL |= BIT6 + BIT7;                     // P3.6,7 = USART1 TXD/RXD
  //Configure USCIA1, UART
  UCA1CTL1 = UCSSEL_1;                      // ACLK
  /* baud rate = 9600 */
  UCA1BR0 = 03;                             // 32768Hz 9600 32k/9600=3.41
  UCA1BR1 = 0x0;
  UCA1MCTL = UCBRS_3;                       // Modulation UCBRSx = 3
  UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  
  // Configure DMA0
  DMACTL0 = DMA0TSEL_10;                    // UTXIFG1 trigger
  DMA0SA = (int)String1;                    // Source block address
  DMA0DA = (int)&UCA1TXBUF;                 // Destination single address
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



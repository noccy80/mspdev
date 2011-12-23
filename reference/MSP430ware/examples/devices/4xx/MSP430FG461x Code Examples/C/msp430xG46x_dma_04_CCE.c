//******************************************************************************
//   MSP430xG461x Demo - DMA0, Block Mode UART1 9600, ACLK
//
//   Description: DMA0 is used to transfer a string as a block to U1TXBUF.
//   UTXIFG1 WILL trigger DMA0. "Hello World" is TX'd via 9600 baud on UART1.
//   Watchdog in interval mode triggers block transfer every 1000ms.
//   Level senstive trigger used for UTXIFG1 to prevent loss of inital edge
//   sensitive triggers - UTXIFG1 which is set at POR.
//   ACLK = UCLK 32768Hz, MCLK = SMCLK = default DCO 1048576Hz
//   Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (000Dh 4Ah)
//
//                MSP430xG461x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32768Hz
//          --|RST          XOUT|-
//            |                 |
//            |             P4.0|------------> "Hello World"
//            |                 | 9600 - 8N1
//
//   A. Dannenberg/ M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0
//******************************************************************************
#include "msp430xG46x.h"

const char String1[13] = "\nHello World"; 

void main(void)
{
  WDTCTL = WDT_ADLY_1000;                   // WDT 1000ms, ACLK, interval timer
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P4SEL |= 0x03;                            // P4.0,1 = USART1 TXD/RXD
  ME2 |= UTXE1 + URXE1;                     // Enable USART1 TXD/RXD
  UCTL1 |= CHAR;                            // 8-bit characters
  UTCTL1 = SSEL0;                           // BRCLK = ACLK
  UBR01 = 0x03;                             // 32k/9600=3.41
  UBR11 = 0x00;
  UMCTL1 = 0x04A;                           // Modulation
  UCTL1 &= ~SWRST;                          // Release USART state machine
  DMACTL0 = DMA0TSEL_10;                    // UTXIFG1 trigger
  DMA0SA = (void (*)())String1;             // Source block address
  DMA0DA = (void (*)())&TXBUF1;             // Destination single address
  DMA0SZ = 0014;                            // Block size
  DMA0CTL = DMASRCINCR_3 + DMASBDB + DMALEVEL;  // Repeat, inc src
  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts
}

#pragma vector = WDT_VECTOR                 // Trigger DMA block transfer
__interrupt void WDT_ISR(void)
{
  DMA0CTL |= DMAEN;                         // Enable
}



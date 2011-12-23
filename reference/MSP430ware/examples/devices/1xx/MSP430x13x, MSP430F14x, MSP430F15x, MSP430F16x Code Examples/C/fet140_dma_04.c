//******************************************************************************
//  MSP-FET430P140 Demo - DMA0, Block Mode UART1 9600, 32kHz ACLK
//
//  Description: DMA0 is used to transfer a string as a block to U1TXBUF.
//  UTXIFG1 WILL trigger DMA0. "Hello World" is TX'd via 9600 baud on UART1.
//  Watchdog in interval mode triggers block transfer every 1000ms.
//  Level senstive trigger used for UTXIFG1 to prevent loss of inital edge
//  sensitive triggers - UTXIFG1 which is set at POR.
//  ACLK = UCLK 32768Hz, MCLK = SMCLK = default DCO ~ 800k
//  Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (000Dh 4Ah )
//  //* An external watch crystal on XIN XOUT is required for ACLK  *//	
//  //* Final Production MSP430F169 Device Required *//
//
//               MSP430F169
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32768Hz
//         --|RST          XOUT|-
//           |                 |
//           |             P3.6|------------> "Hello World"
//           |                 | 9600 - 8N1
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x16x.h>

// Definition necessary to compile with CCEv3.2
// Workaround for &U1TXBUF
#define _U1TXBUF_ 0x007F					// Physical address of U1TXBUF

static char string1[] = { "Hello World\r\n" };

void main(void)
{
  WDTCTL = WDT_ADLY_1000;                   // WDT 1000ms, ACLK, interval timer
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P3SEL = 0xC0;                             // P3.6,7 = USART1 TXD/RXD
  ME2 |= UTXE1;                             // Enabled UART1 TXD
  UCTL1 |= CHAR;                            // 8-bit char, SWRST=1
  UTCTL1 |= SSEL0;                          // UCLK = ACLK
  UBR01 = 0x03;                             // 9600 from 32768Hz
  UBR11 = 0x00;
  UMCTL1 = 0x4A;                            // Modulation
  UCTL1 &= ~SWRST;                          // Enable USART
  DMACTL0 = DMA0TSEL_10;                    // UTXIFG1
  DMA0SA = (unsigned int)string1;           // Source block address
  DMA0DA = (unsigned int)&U1TXBUF;          // Dest single address
  DMA0SZ = sizeof string1-1;                // Block size
  DMA0CTL = DMASRCINCR_3 + DMASBDB + DMALEVEL; // inc src, byte

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  DMA0CTL |= DMAEN;                         // Enable
}


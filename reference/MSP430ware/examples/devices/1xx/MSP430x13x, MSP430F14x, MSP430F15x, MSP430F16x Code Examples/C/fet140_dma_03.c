//******************************************************************************
//  MSP-FET430P140 Demo - DMA0, Repeated Block UART1 9600, TACCR2, ACLK
//
//  Description: DMA0 is used to transfer a string byte-by-byte as a repeating
//  block to U1TXBUF. Timer_A operates continuously at 32768Hz with CCR2IFG
//  triggering DMA0. "Hello World" is TX'd via 9600 baud UART1.
//  ACLK= TACLK 32768Hz, MCLK= SMCLK= default DCO ~ 800k
//  Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (000Dh 4Ah )
//  //* An external watch crystal on XIN XOUT is required for ACLK *//	
//  //* MSP430F169 Device Required *//
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
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P3SEL = 0xC0;                             // P3.6,7 = USART1 TXD/RXD
  ME2 |= UTXE1;                             // Enabled UART1 TXD
  UCTL1 |= CHAR;                            // 8-bit char, SWRST=1
  UTCTL1 |= SSEL0;                          // UCLK = ACLK
  UBR01 = 0x03;                             // 9600 from 32768Hz
  UBR11 = 0x00;
  UMCTL1 = 0x4A;                            // Modulation
  UCTL1 &= ~SWRST;                          // Enable USART

  DMACTL0 = DMA0TSEL_1;                     // 0-CCR2IFG
  DMA0SA = (unsigned int)string1;           // Source block address
  DMA0DA = (unsigned int)&U1TXBUF;                        // Dest single address
  DMA0SZ = sizeof string1-1;                // Block size
  DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMASBDB + DMAEN;// Rpt, inc src, enable

  TACCR0 = 8192;                            // Char freq = TACLK/CCR0
  TACCR2 = 1;                               // For DMA0 trigger
  TACTL = TASSEL_1 + MC_1;                  // ACLK, up-mode

  _BIS_SR(LPM3_bits);                       // Enter LPM3
}


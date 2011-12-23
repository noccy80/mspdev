//******************************************************************************
//   MSP430x471xx Demo - DMA0, Repeated Block UCA1UART 9600, TACCR2, ACLK
//
//  Description: DMA0 is used to transfer a string byte-by-byte as a repeating
//  block to UCA0TXBUF. Timer_A operates continuously at 32768Hz with CCR2IFG
//  triggering DMA0. "Hello World" is TX'd via 9600 baud UART1.
//  ACLK= TACLK 32768Hz, MCLK= SMCLK= default DCO ~ 1048576Hz
//  Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (000Dh 4Ah )
//  //* An external watch crystal on XIN XOUT is required for ACLK *//	
//
//              MSP430x471xx
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32768Hz
//         --|RST          XOUT|-
//           |                 |
//           |             P2.4|------------> "Hello World"
//           |                 | 9600 - 8N1
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x471x7.h"

static char string1[] = { "Hello World\r\n" };

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P2SEL = BIT4+BIT5;                        // P2.4,5 = USCI A0 TXD/RXD
  // configure USCIA0 UART
  UCA0CTL1 = UCSSEL_1;                      // ACLK
  /* baud rate = 9600 */
  UCA0BR0 = 0x3;                             // 32768Hz 9600 32k/9600=3.41
  UCA0BR1 = 0x0;
  UCA0MCTL = UCBRS_3;                       // Modulation UCBRSx = 3
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  // configure DMA0
  DMACTL0 = DMA0TSEL_1;                     // 0-CCR2IFG
  DMA0SA = (unsigned int)string1;           // Source block address
  DMA0DA = (int)&UCA0TXBUF;                 // Dest single address
  DMA0SZ = sizeof string1-1;                // Block size
  DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMASBDB + DMAEN;// Rpt, inc src, enable

  TACCR0 = 8192;                            // Char freq = TACLK/CCR0
  TACCR2 = 1;                               // For DMA0 trigger
  TACTL = TASSEL_1 + MC_1;                  // ACLK, up-mode

  _BIS_SR(LPM3_bits);                       // Enter LPM3
}


//******************************************************************************
//  MSP430x26x Demo - DMA1/0, single transfer Mode UART1 9600 Auto RX/TX String, ACLK
//
//  Description: DMA1 is used to capture a 16 byte string from USART1. The
//  DMA1 interrupt is used to trigger DMA0 to echo back the received string.
//  USART1 is configured at 96008N1.
//  Level senstive trigger used for UTXIFG1 to prevent loss of initial edge
//  sensitive triggers - UTXIFG1 which is set at POR.
//  ACLK = 32768Hz = UCLK1, MCLK = SMCLK = default DCO ~1.045MHz
//  Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (000Dh 4Ah )
//  //* An external watch crystal on XIN XOUT is required for ACLK *//	
//
//             MSP430F261x
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32768Hz
//         --|RST          XOUT|-
//           |                 |
//           |             P3.6|------------>
//           |                 | 9600 - 8N1
//           |             P3.7|<------------
//
//   B. Nisarga
//   Texas Instruments Inc.
//   September 2007
//   Built with CCE Version: 3.2.0
//******************************************************************************
#include "msp430x26x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P3SEL = 0xC0;                             // P3.6,7 = USART1 TXD/RXD
  // configure USCIA1 UART
  UCA1CTL1 = UCSSEL_1;                      // ACLK
  /* baud rate = 9600 */
  UCA1BR0 = 03;                             // 32768Hz 9600 32k/9600=3.41
  UCA1BR1 = 0x0;
  UCA1MCTL = UCBRS_3;                       // Modulation UCBRSx = 3
  UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

  DMACTL0 = DMA1TSEL_9 + DMA0TSEL_10;       // DMA1=URXIFG1, DMA0=UTXIFG1

// Playback
  DMA0SA = (void (*)())0x220;               // Src = RAM memory
  DMA0DA = (void (*)())&UCA1TXBUF;          // Dest single address
  DMA0SZ = 0x10;                            // Block size
  DMA0CTL = DMASRCINCR_3 + DMASBDB + DMALEVEL; // inc src, enable, byte access

// Record
  DMA1SA = (void (*)())&UCA1RXBUF;          // Dest single addr = UART RX Buffer
  DMA1DA = (void (*)())0x220;               // Dst address = RAM memory
  DMA1SZ = 0x10;                            // Size in bytes
  DMA1CTL = DMADSTINCR_3 + DMASBDB + DMAIE + DMAEN; // Sng, config, byte access

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

// DMA interrupt service routine
#pragma vector = DMA_VECTOR
__interrupt void DMA_ISR(void)
{
  DMA1CTL &= ~DMAIFG;                       // Clear DMA1 interrupt flag
  DMA0CTL |= DMAEN;                         // Enable
  DMA1CTL |= DMAEN;                         // (re)Enable
}

//******************************************************************************
//  MSP-FET430P430 Demo - DMA0, Repeat Single to UART 19200, TACCR2, DCO
//
//  Description: DMA0 is used to transfer the string "Hello World"
//  byte-by-byte to the USART0 TXBUF. Timer_A operates in continuous mode from
//  SMCLK/4 and TACCR2_CCIFG is used to trigger DMA0. After each complete
//  string transfer, source and DMA size are reset to inital setting
//  automatically using DMA transfer mode 4.
//  Baud rate divider with 1048576Hz = 1048576Hz/19200 = ~54.61 (036h|6Bh)
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//               MSP430FG439
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |       P2.4/UTXD0|------------> "Hello World"
//            |                 | 19200 - 8N1
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************
#include  <msp430xG43x.h>

static char string1[] = { "Hello World\r\n" };

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  FLL_CTL0 |= XCAP18PF;                     // Set load capacitance for xtal
  P2SEL = 0x10;                             // P2.4 = USART0 TXD

  ME1 |= UTXE0;                             // Enabled USART0 TXD
  UCTL0 |= CHAR;                            // 8-bit character, SWRST=1
  UTCTL0 |= SSEL1;                          // UCLK = SMCLK
  UBR00 = 0x36;                             // 19200 from ~1Mhz
  UBR10 = 0x00;                             //
  UMCTL0 = 0x6B;                            // Modulation
  UCTL0 &= ~SWRST;                          // Initialize USART state machine

  DMA0SA = (int)string1;                    // Source string address
  DMA0DA = (unsigned int)&U0TXBUF;          // Destination single address
  DMA0SZ = sizeof string1 - 1;              // Block size (discard trailing 0)
  DMACTL0 = DMA0TSEL_1;                     // TACCR2 trigger
  DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMASBDB + DMAEN; // Rpt, inc src
  TACTL = TASSEL_2 + ID_2 + MC_2;           // SMCLK/4, continuous mode

  _BIS_SR(CPUOFF);                          // Enter LPM0
}

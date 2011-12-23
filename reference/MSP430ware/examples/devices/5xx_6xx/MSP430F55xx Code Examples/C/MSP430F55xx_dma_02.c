//******************************************************************************
//  MSP430x552x Demo - DMA0, Repeated Block UCA1UART 9600, TACCR2, ACLK
//
//  Description: DMA0 is used to transfer a string byte-by-byte as a repeating
//  block to UCA1TXBUF. Timer_A operates continuously at 32768Hz with CCR2IFG
//  triggering DMA0. "Hello World" is TX'd via 9600 baud UART1.
//  ACLK= TACLK 32768Hz, MCLK= SMCLK= default DCO ~ 1048576Hz
//  Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (000Dh 4Ah )
//  //* An external watch crystal on XIN XOUT is required for ACLK *//	
//  //* MSP430F169 Device Required *//
//
//              MSP430x552x
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32768Hz
//         --|RST          XOUT|-
//           |                 |
//           |             P4.4|------------> "Hello World"
//           |                 | 9600 - 8N1
//
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>
static char String1[] = { "Hello World\r\n" };

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
//.......................
  P5SEL |= BIT4+BIT5;                       // Select XT1

  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap
  UCSCTL3 = 0;                              // FLL Reference Clock = XT1

  // Loop until XT1,XT2 & DCO stabilizes - In this case loop until XT1 and DCo settle
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  
  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive strength

  UCSCTL4 |= SELA_0 + SELS_4 + SELM_4;      // ACLK = LFTX1
                                            // SMCLK = default DCO
                                            // MCLK = default DCO
//................

  P4SEL = BIT4+BIT5;                        // P4.4,5 = UART1 TXD/RXD
  // configure USCI_A1 UART
  UCA1CTL1 = UCSSEL_1;                      // ACLK
  UCA1BR0 = 0x03;                           // 32768Hz 9600 32k/9600=3.41
  UCA1BR1 = 0x0;
  UCA1MCTL = UCBRS_3+UCBRF_0;               // Modulation UCBRSx = 3
  UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  // configure DMA0
  DMACTL0 = DMA0TSEL_1;                     // 0-CCR2IFG
  __data16_write_addr((unsigned short) &DMA0SA,(unsigned long) String1);
                                            // Source block address
  __data16_write_addr((unsigned short) &DMA0DA,(unsigned long) &UCA1TXBUF);
                                            // Destination single address  
  DMA0SZ = sizeof String1-1;                // Block size
  DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMASBDB + DMAEN;// Rpt, inc src, enable

  TA0CCR0 = 8192;                            // Char freq = TACLK/CCR0
  TA0CCR2 = 1;                               // For DMA0 trigger
  TA0CTL = TASSEL_1 + MC_1;                  // ACLK, up-mode

  _BIS_SR(LPM3_bits);                       // Enter LPM3
}


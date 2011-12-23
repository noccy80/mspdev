//******************************************************************************
//  MSP430F530x Demo - SPI TX & RX using DMA0 & DMA1 Single Transfer in Fixed
//                     Address Mode
//
//  Description: This code has to be used with MSP430x530x_uscia0_spi_10.c 
//  (slave SPI). DMA0 is used to transfer a single byte while DMA1 is used to
//  RX from slave SPI at the same time. This code will set P1.0 if RX character
//  is correct and clears P1.0 if received character is wrong. Watchdog in
//  interval mode triggers block transfer every 1000ms.
//  ACLK = REFO = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
//  This is the SPI master code
//
//                MSP430F530x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32768Hz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-> LED
//            |                 |
//            |             P3.3|-> Data Out (UCA0SIMO)
//            |                 |
//            |             P3.4|<- Data In (UCA0SOMI)
//            |                 |
//            |             P2.7|-> Serial Clock Out (UCA0CLK)
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

char TxString;
char RxString;

void main(void)
{
  WDTCTL = WDT_ADLY_1000;                   // WDT 1000ms, ACLK, interval timer
  SFRIE1 |= WDTIE;                          // Enable WDT interrupt
  P1OUT &= ~0x01;                           // Clear P1.0 LED
  P1DIR |= BIT0;
  P3SEL |= BIT3+BIT4;                       // P3.3,4 = USCI_A0 SPI Option
  P2DIR |= BIT7;                            // P2.7 UCA0CLK       
  P2SEL |= BIT7;

  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL0 = UCMST+UCSYNC+UCCKPL+UCMSB;     // 3-pin, 8-bit SPI master
                                            // Clock polarity high, MSB
  UCA0CTL1 = UCSSEL_2;                      // SMCLK
  UCA0BR0 = 0x02;                           // /2
  UCA0BR1 = 0x00;                           //
  UCA0MCTL = 0x00;                          // No modulation
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

  DMACTL0 = DMA1TSEL_16+DMA0TSEL_17;        // DMA0 - UCA0TXIFG
                                            // DMA1 - UCA0RXIFG
  // Setup DMA0
  __data16_write_addr((unsigned short) &DMA0SA,(unsigned long) &TxString);
                                            // Source block address
  __data16_write_addr((unsigned short) &DMA0DA,(unsigned long) &UCA0TXBUF);
                                            // Destination single address
  DMA0SZ = 1;                               // Block size
  DMA0CTL = DMASRCINCR_3+DMASBDB+DMALEVEL;  // inc src

  // Setup DMA1
  __data16_write_addr((unsigned short) &DMA1SA,(unsigned long) &UCA0RXBUF);
                                            // Source block address
  __data16_write_addr((unsigned short) &DMA1DA,(unsigned long) &RxString);
                                            // Destination single address
  DMA1SZ = 1;                               // Block size
  DMA1CTL = DMADSTINCR_3+DMASBDB+DMALEVEL;  // inc dst

  TxString = RxString = 0;                  // Clear TxString
                                            // Clear RxString
 
  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts
  __no_operation();                         // Required only for debugger
}

//------------------------------------------------------------------------------
// Trigger DMA0 & DMA1 block transfer.
//------------------------------------------------------------------------------
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
  if(TxString-1 == RxString)
    P1OUT |= 0x01;                          // Set P1.0 if True
  else
    P1OUT &= ~0x01;                         // Clear P1.0 if False

  TxString++;                               // Increment TxString counter
  DMA1CTL |= DMAEN;                         // DMA1 Enable
  DMA0CTL |= DMAEN;                         // DMA0 Enable
}

//******************************************************************************
//  CC430x513x Demo - SPI TX & RX using DMA0 & DMA1 Single Transfer in Fixed
//                     Address Mode
//
//  Description: This code has to be used with CC430x513x_uscia0_spi_10.c as
//  slave SPI. DMA0 is used to transfer a single byte while DMA1 is used to
//  RX from slave SPI at the same time. This code will set P1.0 if RX character
//  is correct and clears P1.0 if received character is wrong. Watchdog in
//  interval mode triggers block transfer every 1000ms.
//  ACLK = REFO = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
//
//                   CC430F5137
//                 -----------------
//             /|\|                 |
//              | |                 |
//              --|RST          P1.0|-> LED
//                |                 |
//                |             P2.0|-> Data Out (UCA0SIMO)
//                |                 |
//                |             P2.2|<- Data In (UCA0SOMI)
//                |                 |
//                |             P2.4|-> Serial Clock Out (UCA0CLK)
//
//  M Morales
//  Texas Instruments Inc.
//  April 2009
//  Built with CCE v3.1 Build 3.2.3.6.4 & IAR Embedded Workbench Version: 4.11B
//******************************************************************************
 
#include "cc430x513x.h"

char TxString;
char RxString;

void main(void)
{
  WDTCTL = WDT_ADLY_1000;                   // WDT 1000ms, ACLK, interval timer
  SFRIE1 |= WDTIE;                          // Enable WDT interrupt
  
  P1OUT &= ~0x01;                           // Clear P1.0
  P1DIR |= 0x01;                            // P1.0 = Output
  
  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P2MAP0 = PM_UCA0SIMO;                     // Map UCA0SIMO output to P2.0 
  P2MAP2 = PM_UCA0SOMI;                     // Map UCA0SOMI output to P2.2 
  P2MAP4 = PM_UCA0CLK;                      // Map UCA0CLK output to P2.4 
  PMAPPWD = 0;                              // Lock port mapping registers  
   
  P2DIR |= BIT0 + BIT2 + BIT4;              // ACLK, MCLK, SMCLK set out to pins
  P2SEL |= BIT0 + BIT2 + BIT4;              // P2.0,2,4 for debugging purposes.

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

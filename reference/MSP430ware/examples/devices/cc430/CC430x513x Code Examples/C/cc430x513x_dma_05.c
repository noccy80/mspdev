//******************************************************************************
//   CC430F513x Demo - USCI_A0, 115200 UART RX & TX, DMA enabled
//
//   Description: Send a TX character once a second using the DMA. 
//   Receive the RX character into the RxString variable. 
//   Baud rate divider with 1048576hz = 1048576/115200 = ~9.1 (009h|01h)
//   ACLK = REFO = ~32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//   See User Guide for baud rate divider table
//
//                 CC430F5137
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |     P2.7/UCA0TXD|------------>
//            |                 | 115200 - 8N1
//            |     P2.6/UCA0RXD|<------------
//
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x513x.h"

char TxString = 0;
char RxString = 0;

void main(void)
{
  WDTCTL = WDT_ADLY_1000;                   // WDT 1000ms, ACLK, interval timer
  SFRIE1 |= WDTIE;                          // Enable WDT interrupt

  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P2MAP6 = PM_UCA0RXD;                      // Map UCA0RXD output to P2.6 
  P2MAP7 = PM_UCA0TXD;                      // Map UCA0TXD output to P2.7 
  PMAPPWD = 0;                              // Lock port mapping registers 
  
  P2DIR |= BIT7;                            // Set P2.7 as TX output
  P2SEL |= BIT6 + BIT7;                     // Select P2.6 & P2.7 to UART function
  
  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 9;                              // 1MHz 115200 (see User's Guide)
  UCA0BR1 = 0;                              // 1MHz 115200
  UCA0MCTL |= UCBRS_1 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

  DMACTL0 = DMA1TSEL_16+DMA0TSEL_17;        // DMA0 - UCA0TXIFG
                                            // DMA1 - UCA0RXIFG
  // Setup DMA0
  __data16_write_addr((unsigned short) &DMA0SA,(unsigned long) &TxString);
                                            // Source block address
  __data16_write_addr((unsigned short) &DMA0DA,(unsigned long) &UCA0TXBUF);
                                            // Destination single address
  DMA0SZ = 1;                               // Block size
  DMA0CTL = DMASRCINCR_0+DMASBDB+DMALEVEL;  // src does not change

  // Setup DMA1
  __data16_write_addr((unsigned short) &DMA1SA,(unsigned long) &UCA0RXBUF);
                                            // Source block address
  __data16_write_addr((unsigned short) &DMA1DA,(unsigned long) &RxString);
                                            // Destination single address
  DMA1SZ = 1;                               // Block size
  DMA1CTL = DMADSTINCR_0+DMASBDB+DMALEVEL+DMADT_4+DMAEN;  // dst does not change

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled
  __no_operation();                         // For debugger
}

//------------------------------------------------------------------------------
// Trigger DMA0 & DMA1 block transfer.
//------------------------------------------------------------------------------
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
  TxString++;                               // Increment TxString counter
  DMA0CTL |= DMAEN;                         // DMA0 Enable   
}

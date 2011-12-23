//******************************************************************************
//   CC430x613x Demo - DMA0, Single Transfer in Block Mode UART1 9600, ACLK
//
//   Description: DMA0 is used to transfer a string as a block to USCI_A0.
//   USCIA0TXIFG WILL trigger DMA0. "Hello World" is TX'd via 9600 baud on
//   USCI_A0. Watchdog in interval mode triggers block transfer every 1000ms.
//   Level senstive trigger used for USCIA0TXIFG to prevent loss of inital edge
//   sensitive triggers - USCIA0TXIFG which is set at POR.
//   ACLK = UCLK 32768Hz, MCLK = SMCLK = default DCO 1048576Hz
//   Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (0003h 4Ah)
//
//                 CC430x613x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32768Hz
//          --|RST          XOUT|-
//            |                 |
//            |             P2.7|------------> "Hello World"
//            |                 | 9600 - 8N1
//
//  M Morales
//  Texas Instruments Inc.
//  April 2009
//  Built with CCE v3.1 Build 3.2.3.6.4 & IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x613x.h"

const char String1[13] = "Hello World\r\n";

void main(void)
{
  WDTCTL = WDT_ADLY_1000;                   // WDT 1000ms, ACLK, interval timer
  SFRIE1 |= WDTIE;                          // Enable WDT interrupt
  
  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P2MAP7 = PM_UCA0TXD;                      // Map UCA0TXD output to P2.7 
  PMAPPWD = 0;                              // Lock port mapping registers 
  
  P2DIR |= BIT7;                            // Set P2.7 as TX output
  P2SEL |= BIT7;                            // Select P2.6 & P2.7 to UART function
  
  UCA0CTL1 |= UCSWRST;                      // 8-bit characters
  UCA0CTL1 = UCSSEL_1;                      // CLK = ACLK
  UCA0BR0 = 0x03;                           // 32k/9600=3.41
  UCA0BR1 = 0x00;
  UCA0MCTL = UCBRS_3+UCBRF_0;               // Modulation
  UCA0CTL1 &= ~UCSWRST;                     // Release USCI state machine

  DMACTL0 = DMA0TSEL_17;                    // USCI_A0 TXIFG trigger
  __data16_write_addr((unsigned short) &DMA0SA,(unsigned long) String1);
                                            // Source block address
  __data16_write_addr((unsigned short) &DMA0DA,(unsigned long) &UCA0TXBUF);
                                            // Destination single address
  DMA0SZ = sizeof(String1);                 // Block size
  DMA0CTL = DMASRCINCR_3+DMASBDB+DMALEVEL;  // Repeat, inc src

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts
  __no_operation();                         // Required only for debugger
}

//------------------------------------------------------------------------------
// Trigger DMA block transfer
//------------------------------------------------------------------------------
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
  DMA0CTL |= DMAEN;                         // Enable
}

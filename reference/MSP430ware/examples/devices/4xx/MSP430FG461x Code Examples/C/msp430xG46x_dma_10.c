//******************************************************************************
//   MSP430xG461x Demo - DMA0 triggers DMA1, DMA 1 triggers DMA2, DMA2 makes 
//   single transfer
//
//   Description: DMA0 is triggered via software, Next DMA0 triggers DMA1, 
//   DMA1 triggers DMA2, and finally DMA2 performs a single transfer 
//   
//
//                MSP430xG461x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |                 |
//            |                 |
//
//  R. B. Elliott /H. Grewal
//  Texas Instruments Inc.
//  Oct 2007
//  Built with IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430xG46x.h"
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P1DIR |= 0x01;                            // P1.0  output
 
  DMA0SA = 0x0230;                          // Start block address
  DMA1SA = 0x0231;
  DMA2SA = 0x0232;

  DMA0DA = 0x0240;                          // Destination block address
  DMA1DA = 0x0241;
  DMA2DA = 0x0242;
  
  DMA0SZ = 0x001;                           // Block size
  DMA1SZ = 0x001;
  DMA2SZ = 0x001;

  DMACTL0 |= DMA1TSEL_14 + DMA2TSEL_14;     // Software triggers DMA0, 
                                            // DMA0 triggers DMA1, 
                                            // DMA1 triggers DMA2, 
                                            // DMA2 single xfer
  
  DMA0CTL |= DMAEN+DMASBDB;                 // single xfer
  DMA1CTL |= DMAEN+DMASBDB;                 // single xfer
  DMA2CTL |= DMAIE+DMAEN+DMASBDB;           // interrupt on completion
 
  P1OUT |= 0x01;                            // Set P1.0 (LED on)
  DMA0CTL |= DMAREQ;                        // Trigger DMA0
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0
  P1OUT &= ~0x01;                           // Clear P1.0 (LED off)
  while(1);
}

// DMA interrupt service routine
#pragma vector = DMA_VECTOR
__interrupt void DMA_ISR(void)
{ 
 DMA0CTL &= ~DMAIFG;
 DMA1CTL &= ~DMAIFG;
 DMA2CTL &= ~DMAIFG;
 __bic_SR_register_on_exit(LPM0_bits);       // Exit LPMx, interrupts enabled

}

//******************************************************************************
//  MSP430F51x2 Demo - ADC10, DMA Sample A11 32x to Flash, Int Ref, DCO
//
//  Description: Sample A11 (AVCC/2) 32x, Int reference, and transfer
//  code via DMA to Flash. Software writes to ADC10SC to trigger sample burst.
//  Each ADC10 sample & convert = (32+13)*2/SMCLK = 90/SMCLK = 75us
//  Enough time is provided between ADC10 conversions for each word moved by
//  the DMA to Flash to program. DMA transfers ADC10 code to Flash 1800h-183Fh.
//  In the Mainloop, the MSP430 waits in LPM0 during conversion and programming,
//  DMA_ISR will force exit from LPM0 in Mainloop.
//
//               MSP430F51x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |A10              |
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  // Configure ADC10; 
  ADC10CTL0 = ADC10SHT_3 + ADC10MSC + ADC10ON;// 32ADCclks, ADC on
  ADC10CTL1 = ADC10SHP + ADC10CONSEQ_2 + ADC10SSEL_3 + ADC10DIV_1; // SMCLK/2    
                                            // Sampling timer, rpt single ch
  ADC10CTL2 = ADC10RES;                     // 10-bit resolution
  ADC10MCTL0 = ADC10INCH_11 + ADC10SREF_1;  // Vref+, A10
  
 // Configure internal reference
  while(REFCTL0 & REFGENBUSY);              // If ref generator busy, WAIT
  REFCTL0 |= REFVSEL_0+REFON;               // Select internal ref = 1.5V 
                                            // Internal Reference ON   
  __delay_cycles(75);                       // Delay (~75us) for Ref to settle

  // Configure DMA (ADC10IFG trigger)
  DMACTL0 = DMA0TSEL_24;                    // ADC10IFG trigger
  __data16_write_addr((unsigned short) &DMA0SA,(unsigned long) &ADC10MEM0);
                                            // Source single address  
  __data16_write_addr((unsigned short) &DMA0DA,(unsigned long) 0x1800);
                                            // Destination array address  
  DMA0SZ = 0x20;                            // 32 conversions 
  DMA0CTL = DMADT_4 + DMADSTINCR_3 + DMAEN + DMAIE; // Rpt, inc dest, word access, 
                                            // enable int after 32 conversions   

  while(1)
  {
    FCTL3 = FWKEY;                          // Lock = 0
    FCTL1 = FWKEY + ERASE;                  // Erase bit = 1
    *(unsigned int *)0x1800 = 0;            // Dummy write to erase Flash seg
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    FCTL1 = FWKEY + WRT;                    // Write bit = 1
    ADC10CTL0 |= ADC10ENC + ADC10SC;        // Start sampling
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    FCTL3 = FWKEY + LOCK;                   // Lock = 1
    __no_operation();                       // << SET BREAKPOINT HERE
    __delay_cycles(5000);                   // Delay between conversions
  }
}

#pragma vector=DMA_VECTOR
__interrupt void DMA0_ISR (void)
{
  switch(__even_in_range(DMAIV,16))
  {
    case  0: break;                          // No interrupt
    case  2: 
      // 32 conversions complete
      ADC10CTL0 &= ~ADC10ENC;
      __bic_SR_register_on_exit(CPUOFF);     // exit LPM
      break;                                 // DMA0IFG
    case  4: break;                          // DMA1IFG
    case  6: break;                          // DMA2IFG
    case  8: break;                          // Reserved
    case 10: break;                          // Reserved
    case 12: break;                          // Reserved
    case 14: break;                          // Reserved
    case 16: break;                          // Reserved
    default: break; 
  }   
}


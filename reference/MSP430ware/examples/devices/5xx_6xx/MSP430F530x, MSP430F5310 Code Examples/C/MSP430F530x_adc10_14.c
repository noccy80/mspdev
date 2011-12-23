//******************************************************************************
//  MSP430F530x Demo - ADC10, DMA Sample A1-0 32x, AVcc, Repeat Seq, DCO
//
//  Description: Use DMA to sample A1/A0 repeat sequence 32x(64 total samples)
//  with reference to AVcc.  Software sets ADC10SC to trigger sample burst.
//  In Mainloop MSP430 waits in LPM0 to save power until ADC10 conversion
//  complete, DMA_ISR will force exit from LPM0 in Mainloop.
//  ADC10 internal oscillator times sample period (16x) and conversion (13x).
//  DMA transfers conversion code to ADC_Result.  
//
//               MSP430F530x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//       >---|P6.1/A1          |
//       >---|P6.0/A0          |
//
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

unsigned int ADC_Result[64];                // ADC conversion result array

void main(void)
{
  unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  // Configure ADC10; pulse sample mode, s/w trigger, rpt seq of channels
  ADC10CTL0 = ADC10SHT_2 + ADC10MSC + ADC10ON;  // 16ADCclks, ADC on
  ADC10CTL1 = ADC10SHP + ADC10CONSEQ_3;     // Sampling timer, rpt seq of ch
  ADC10CTL2 = ADC10RES;                     // 10-bit resolution
  ADC10MCTL0 = ADC10INCH_1;                 // AVCC ref, A0, A1(EOS)
  
  // Configure DMA0 (ADC10IFG trigger)
  DMACTL0 = DMA0TSEL_24;                    // ADC10IFG trigger
  __data16_write_addr((unsigned short) &DMA0SA,(unsigned long) &ADC10MEM0);
                                            // Source single address  
  DMA0SZ = 0x02;                            // 2x32 conversions 
  DMA0CTL = DMADT_4 + DMADSTINCR_3 + DMAEN + DMAIE; 
                                            // Rpt, inc dest, byte access, 
                                            // enable int after seq of convs
  while(1)
  {
    for(i=0;i<32;i++)
    {
        __data16_write_addr((unsigned short) &DMA0DA,(unsigned long) &ADC_Result[i*2]);
                                            // Update destination array address         
        while (ADC10CTL1 & ADC10BUSY);      // Wait if ADC10 core is active
        ADC10CTL0 |= ADC10ENC + ADC10SC;    // Sampling and conversion ready
        __bis_SR_register(CPUOFF + GIE);    // LPM0, ADC10_ISR will force exit
    }
    __delay_cycles(5000);               // Delay between sequence convs    
    __no_operation();                   // BREAKPOINT; check ADC_Result    
  }
}

#pragma vector=DMA_VECTOR
__interrupt void DMA0_ISR (void)
{
  switch(__even_in_range(DMAIV,16))
  {
    case  0: break;                          // No interrupt
    case  2: 
      // sequence of conversions complete
      ADC10CTL0 &= ~ADC10ENC;                // Disable ADC conversion
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

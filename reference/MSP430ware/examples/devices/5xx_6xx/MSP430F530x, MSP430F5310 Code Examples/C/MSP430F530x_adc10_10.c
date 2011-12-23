//******************************************************************************
//  MSP430F530x Demo - ADC10, DMA Sample A2-0, 8-bit Res, Single Sequence, DCO
//
//  Description: Sample A2/A1/A0 as single sequence with reference to AVcc.
//  Software sets ADC10SC to trigger sample sequence. In Mainloop MSP430 waits
//  in LPM0 to save power until ADC10 conversion complete, DMA_ISR will
//  force exit from any LPMx. ADC10 internal oscillator times sample period 
//  (16x) and conversion (13x). DMA transfers conv results ADC_Result variable. 
//
//               MSP430F530x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//       >---|P6.2/A2          |
//       >---|P6.1/A1          |
//       >---|P6.0/A0          |
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

unsigned char ADC_Result[3];                // 8-bit ADC conversion result array

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  // Configure ADC10
  ADC10CTL0 = ADC10SHT_2 + ADC10MSC + ADC10ON;// 16ADCclks, MSC, ADC ON
  ADC10CTL1 = ADC10SHP + ADC10CONSEQ_1;     // sampling timer, s/w trig.,single sequence
  ADC10CTL2 &= ~ADC10RES;                   // 8-bit resolution
  ADC10MCTL0 = ADC10INCH_2;                 // A0,A1,A2(EoS), AVCC reference
  
  // Configure DMA0 (ADC10IFG trigger)
  DMACTL0 = DMA0TSEL_24;                    // ADC10IFG trigger
  __data16_write_addr((unsigned short) &DMA0SA,(unsigned long) &ADC10MEM0);
                                            // Source single address  
  __data16_write_addr((unsigned short) &DMA0DA,(unsigned long) &ADC_Result[0]);
                                            // Destination array address  
  DMA0SZ = 0x03;                            // 3 conversions 
  DMA0CTL = DMADT_4 + DMADSTINCR_3 + DMASRCBYTE + DMADSTBYTE + DMAEN + DMAIE; 
                                            // Rpt, inc dest, byte access, 
                                            // enable int after seq of convs   
  while(1)
  {
    while (ADC10CTL1 & ADC10BUSY);          // Wait if ADC10 core is active
    ADC10CTL0 |= ADC10ENC + ADC10SC;        // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    __delay_cycles(5000);                   // Delay between sequence convs    
    __no_operation();                       // BREAKPOINT; check ADC_Result
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


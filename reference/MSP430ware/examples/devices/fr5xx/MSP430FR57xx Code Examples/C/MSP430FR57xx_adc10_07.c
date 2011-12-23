//******************************************************************************
//  MSP430FR57xx Demo - ADC10, DMA Sample A1 64x, AVcc, Repeat Single, DCO
//
//  Description: Sample A1 64 times with AVcc ref. Software writes to ADC10SC
//  to trigger sample burst. In Mainloop MSP430 waits in LPM0 to save power
//  until ADC10 conversion burst complete, DMA_IFG will force exit from LPM0
//  in Mainloop on reti. ADC10 internal oscillator times sample period (16x)
//  and conversion (13x). DMA transfers conversion result in ADC10MEM0 to array
//  ADC_Result. P1.0 set at start of conversion burst, reset on completion.
//
//                MSP430FR5739
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|P1.1/A1          |
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************
#include "msp430fr5739.h"

unsigned int ADC_Result[64];
unsigned char i;
unsigned int ADC_Result_sum;
unsigned int ADC_Result_Average;

void main(void)
{  
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  // Configure ADC pins
  P1SEL1 |= BIT1; 
  P1SEL0 |= BIT1; 

  // Configure ADC10 - pulse sample mode; software trigger; 
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10MSC; // 16ADCclks, ADC on
  ADC10CTL1 = ADC10SHP + ADC10CONSEQ_2;     // pulse sample mode, rpt single ch
  ADC10CTL2 = ADC10RES;                     // 10-bits of resolution
  ADC10MCTL0 = ADC10INCH_1;                 // AVCC ref, A1
  
  // Configure DMA (ADC10IFG trigger)
  DMACTL0 = DMA0TSEL__ADC10IFG;                     // ADC10IFG trigger
  __data16_write_addr((unsigned short) &DMA0SA,(unsigned long) &ADC10MEM0);
                                            // Source single address  
  __data16_write_addr((unsigned short) &DMA0DA,(unsigned long) &ADC_Result[0]);
                                            // Destination array address  
  DMA0SZ = 64;                              // 64 conversions 
  // Rpt, inc dest, word access, 
  DMA0CTL = DMADT_4 + DMADSTINCR_3 + DMAEN + DMAIE + DMALEVEL; 
                                         // enable int after 64 conversions  
  while(1)
  {
    ADC10CTL0 |= ADC10ENC + ADC10SC;        // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    __no_operation();                       // For debug only

    ADC_Result_sum = 0x0;                   // clear accumulate register
    for(i=0;i<64;i++)                       // BREAKPOINT HERE; View ADC_Result 
      ADC_Result_sum += ADC_Result[i];    
    
    ADC_Result_Average = ADC_Result_sum>>6; // Average of 64 conversions results  
    __delay_cycles(50000);                   // delay before next 64 conversions
  }  
}

#pragma vector=DMA_VECTOR
__interrupt void DMA0_ISR (void)
{
  switch(__even_in_range(DMAIV,16))
  {
    case  0: break;                          // No interrupt
    case  2: 
      // 64 conversions complete
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
  

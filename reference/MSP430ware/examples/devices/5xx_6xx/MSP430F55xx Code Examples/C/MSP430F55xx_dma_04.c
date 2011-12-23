//******************************************************************************
//  MSP430F552x Demo - DMA0, Single transfer using ADC12 triggered by TimerB
//
//  Description: This software uses TBCCR1 as a sample and convert input into
//  the A0 of ADC12. ADC12IFG is used to trigger a DMA transfer and DMA
//  interrupt triggers when DMA transfer is done. TB1 is set as an output and
//  P1.0 is toggled when DMA ISR is serviced.
//  ACLK = REFO = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
//
//                 MSP430F552x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//            |             P5.7|-->TB1 output
//            |                 |
//            |             P6.0|<--A0
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>

unsigned int DMA_DST;						// ADC conversion result is stored in this variable 

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Hold WDT

  P1OUT &= ~BIT0;                           // P1.0 clear
  P1DIR |= BIT0;                            // P1.0 output
  P5SEL |= BIT7;                            // P5.7/TB1 option select
  P5DIR |= BIT7;                            // Output direction
  P6SEL |= BIT0;                            // Enable A/D channel A0  

  //Setup Timer B0
  TBCCR0 = 0xFFFE;
  TBCCR1 = 0x8000;
  TBCCTL1 = OUTMOD_3;                       // CCR1 set/reset mode
  TBCTL = TBSSEL_2+MC_1+TBCLR;              // SMCLK, Up-Mode

  // Setup ADC12
  ADC12CTL0 = ADC12SHT0_15+ADC12MSC+ADC12ON;// Sampling time, MSC, ADC12 on
  ADC12CTL1 = ADC12SHS_3+ADC12CONSEQ_2;     // Use sampling timer; ADC12MEM0
                                            // Sample-and-hold source = CCI0B =
                                            // TBCCR1 output
                                            // Repeated-single-channel
  ADC12MCTL0 = ADC12SREF_0+ADC12INCH_0;     // V+=AVcc V-=AVss, A0 channel
  ADC12CTL0 |= ADC12ENC;

  // Setup DMA0
  DMACTL0 = DMA0TSEL_24;                    // ADC12IFGx triggered
  DMACTL4 = DMARMWDIS;                      // Read-modify-write disable
  DMA0CTL &= ~DMAIFG;
  DMA0CTL = DMADT_4+DMAEN+DMADSTINCR_3+DMAIE; // Rpt single tranfer, inc dst, Int
  DMA0SZ = 1;                               // DMA0 size = 1

  __data16_write_addr((unsigned short) &DMA0SA,(unsigned long) &ADC12MEM0);
                                            // Source block address
  __data16_write_addr((unsigned short) &DMA0DA,(unsigned long) &DMA_DST);
                                            // Destination single address    
  __bis_SR_register(LPM0_bits + GIE);       // LPM0 w/ interrupts
  __no_operation();                         // used for debugging
}

//------------------------------------------------------------------------------
// DMA Interrupt Service Routine
//------------------------------------------------------------------------------
#pragma vector=DMA_VECTOR
__interrupt void DMA_ISR(void)
{
  switch(__even_in_range(DMAIV,16))
  {
    case 0: break;
    case 2:                                 // DMA0IFG = DMA Channel 0
      P1OUT ^= BIT0;                        // Toggle P1.0 - PLACE BREAKPOINT HERE AND CHECK DMA_DST VARIABLE
      break;
    case 4: break;                          // DMA1IFG = DMA Channel 1
    case 6: break;                          // DMA2IFG = DMA Channel 2
    case 8: break;                          // DMA3IFG = DMA Channel 3
    case 10: break;                         // DMA4IFG = DMA Channel 4
    case 12: break;                         // DMA5IFG = DMA Channel 5
    case 14: break;                         // DMA6IFG = DMA Channel 6
    case 16: break;                         // DMA7IFG = DMA Channel 7
    default: break;
  }
}

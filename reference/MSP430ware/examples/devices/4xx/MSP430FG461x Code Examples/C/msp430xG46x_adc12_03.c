//******************************************************************************
//   MSP430xG461x Demo - ADC12, Sample A10 Temp, Set P5.1 if Temp ++ ~2C
//
//   Description: Use ADC12 and the integrated temperature sensor to detect
//   temperature gradients. The temperature sensor output voltage is sampled
//   ~ every 80ms and compared with the defined delta values using an ISR.
//   (ADC12OSC/256)/ determines sample time which needs to be greater than
//   30us for temperature sensor.
//   ADC12 is operated in repeat-single channel mode with the sample and
//   convert trigger sourced from Timer_A CCR1. The ADC12MEM0_IFG at the end
//   of each conversion will trigger an ISR.
//   ACLK = 32kHz, MCLK = SMCLK = default DCO 1048576Hz, ADC12CLK = ADC12OSC
//
//               MSP430xG461x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//
//   A. Dannenberg/ M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430xG46x.h"

#define ADC_DELTA_ON  12                    // ~ 2 Deg C delta for LED on
unsigned int ADCResult;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  ADC12CTL1 = SHS_1 + SHP + CONSEQ_2;       // TA trig., rpt conv
  ADC12MCTL0 = SREF_1 + INCH_10;            // Channel A10, Vref+
  ADC12IE |= 0x001;                         // Enable ADC12IFG.0
  ADC12CTL0 = SHT0_8 + REF2_5V + REFON + ADC12ON; // Config ADC12
  TACCR0 = 13600;                           // Delay for reference start-up
  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
  TACTL = TACLR + MC_1 + TASSEL_2;          // up mode, SMCLK
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, Enable interrupts
  TACCTL0 &= ~CCIE;                         // Disable timer interrupt
  __disable_interrupt();                    // Disable Interrupts
  ADC12CTL0 |= ENC;                         // Config ADC12
  TACCTL1 = OUTMOD_4;                       // Toggle on EQU1 (TAR = 0)
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, cont-mode
  while (!(ADC12IFG & 0x0001));             // First conversion?

  ADCResult = ADC12MEM0;                    // Read out 1st ADC value
  ADCResult += ADC_DELTA_ON;
  P5OUT = 0;                                // Clear P5
  P5DIR |= 0x02;                            // P5.1 as output

  __bis_SR_register(LPM0_bits + GIE);       // LPM0
}

#pragma vector = TIMERA0_VECTOR
__interrupt void TA0_ISR(void)
{
  TACTL = 0;                                // Clear Timer_A control registers
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPM0
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
  if (ADC12MEM0 >= ADCResult)               // ADC12MEM = A0 > ADCResult?
    P5OUT |= 0x02;                          // P5.1 = 1
  else
    P5OUT &= ~0x02;                         // P5.1 = 0
}

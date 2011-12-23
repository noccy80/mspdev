//******************************************************************************
//  MSP430F552x Demo - ADC12, Sample A10 Temp and Convert to oC and oF
//
//  Description: A single sample is made on A10 with reference to internal
//  1.5V Vref. Software sets ADC12SC to start sample and conversion - ADC12SC
//  automatically cleared at EOC. ADC12 internal oscillator times sample
//  and conversion. In Mainloop MSP430 waits in LPM4 to save power until
//  ADC10 conversion complete, ADC12_ISR will force exit from any LPMx in
//  Mainloop on reti.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~ 1.045MHz, ADC12CLK = ADC12OSC
//
//  Uncalibrated temperature measured from device to devive will vary do to
//  slope and offset variance from device to device - please see datasheet.
//
//  NOTE:REFMSTR bit in REFCTL0 regsiter is reset to allow the ADC12_A reference
//    control regsiters handle the reference setting. Upon resetting the REFMSTR
//    bit, all the settings in REFCTL are 'dont care' and the legacy ADC12
//    control bits (ADC12REFON, ADC12REF2_5, ADC12TCOFF and ADC12REFOUT) control
//    the reference system.
//
//                MSP430F552x
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |A10              |
//
//   Bhargavi Nisarga / W. Goh
//   Texas Instruments Inc.
//   November 2010
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>

long temp;
volatile long IntDegF;
volatile long IntDegC;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  REFCTL0 &= ~REFMSTR;                      // Reset REFMSTR to hand over control to
                                            // ADC12_A ref control registers
  ADC12CTL0 = ADC12SHT0_8 + ADC12REFON + ADC12ON;
                                            // Internal ref = 1.5V
  ADC12CTL1 = ADC12SHP;                     // enable sample timer
  ADC12MCTL0 = ADC12SREF_1 + ADC12INCH_10;  // ADC i/p ch A10 = temp sense i/p
  ADC12IE = 0x001;                          // ADC_IFG upon conv result-ADCMEMO
  __delay_cycles(75);                       // 75us delay to allow Ref to settle
  ADC12CTL0 |= ADC12ENC;

  while(1)
  {
    ADC12CTL0 |= ADC12SC;                   // Sampling and conversion start

    __bis_SR_register(LPM4_bits + GIE);     // LPM0 with interrupts enabled
    __no_operation();

    // Temperature in Celsius
    // ((A10/4096*1500mV) - 680mV)*(1/2.25mV) = (A10/4096*667) - 302
    // = (A10 - 1855) * (667 / 4096)
    IntDegC = ((temp - 1855) * 667) / 4096;

    // Temperature in Fahrenheit
    // ((A10/4096*1500mV) - 640mV)*(1/1.25mV) = (A10/4096*1200) - 512
    // = (A10 - 1748) * (1200 / 4096)
    IntDegF = ((temp - 1748) * 1200) / 4096;
    __no_operation();                       // SET BREAKPOINT HERE
  }
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6:                                  // Vector  6:  ADC12IFG0
    temp = ADC12MEM0;                       // Move results, IFG is cleared
    __bic_SR_register_on_exit(LPM4_bits);   // Exit active CPU
    break;
  case  8: break;                           // Vector  8:  ADC12IFG1
  case 10: break;                           // Vector 10:  ADC12IFG2
  case 12: break;                           // Vector 12:  ADC12IFG3
  case 14: break;                           // Vector 14:  ADC12IFG4
  case 16: break;                           // Vector 16:  ADC12IFG5
  case 18: break;                           // Vector 18:  ADC12IFG6
  case 20: break;                           // Vector 20:  ADC12IFG7
  case 22: break;                           // Vector 22:  ADC12IFG8
  case 24: break;                           // Vector 24:  ADC12IFG9
  case 26: break;                           // Vector 26:  ADC12IFG10
  case 28: break;                           // Vector 28:  ADC12IFG11
  case 30: break;                           // Vector 30:  ADC12IFG12
  case 32: break;                           // Vector 32:  ADC12IFG13
  case 34: break;                           // Vector 34:  ADC12IFG14
  default: break;
  }
}

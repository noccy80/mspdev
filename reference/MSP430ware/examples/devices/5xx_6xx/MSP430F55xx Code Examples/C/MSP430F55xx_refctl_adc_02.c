//******************************************************************************
//  MSP430F552x Demo - ADC12, Using REFCTL0 control register to configure internal reference
//
//  Description: This example shows how to configure the internal reference of 
//  REF module using the REFCTL0 control register. 
//  The ADC12 uses the internal 2.5V reference and performs a single conversion
//  on channel A0. The conversion results are stored in ADC12MEM0. Test by
//  applying a voltage to channel A0, then setting and running to a break point
//  at the "__no_operation()" instruction. To view the conversion results,
//  open an ADC12 register window in debugger and view the contents of ADC12MEM0
//
//  NOTE:REFMSTR bit in REFCTL0 regsiter is by default set to 1. This allows the 
//    REFCTL0 control regsiters to configure the reference setting. The legacy
//    ADC12 reference control bits ADC12REFON, ADC12REF2_5, ADC12TCOFF and 
//    ADC12REFOUT are dont care in this case. 
//
//                MSP430F552x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//     Vin -->|P6.0/A0      |
//            |                 |
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P6SEL |= 0x01;                            // Enable A/D channel A0
  
  // By default, REFMSTR=1 => REFCTL is used to configure the internal reference
  while(REFCTL0 & REFGENBUSY);              // If ref generator busy, WAIT                                          
  REFCTL0 |= REFVSEL_2+REFON;               // Select internal ref = 2.5V 
                                            // Internal Reference ON
  // Configure ADC12
  ADC12CTL0 = ADC12ON+ADC12SHT02;
                                            // Turn on ADC12, Sampling time
  ADC12CTL1 = ADC12SHP;                     // Use sampling timer
  ADC12MCTL0 = ADC12SREF_1;                 // Vr+=Vref+ and Vr-=AVss

  for ( i=0; i<0x30; i++);                  // Delay for reference start-up

  ADC12CTL0 |= ADC12ENC;                    // Enable conversions

  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversion
    while (!(ADC12IFG & BIT0));
    __no_operation();                       // SET BREAKPOINT HERE

  }
}


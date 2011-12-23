//******************************************************************************
//  MSP430xG461x Demo - ADC12, Sample A10 Temp and Convert to oC and oF
//
//  This example shows how to use the intergrated temperature sensor to measure
//  temperature. When the temperature diode channel (A10) is selected for
//  conversion, the internal reference is automatically turned on as the source
//  for the sensor. Note however, that it is NOT automatically selected for the
//  conversion.  Any available reference can be used for the conversion.  In
//  this example, a single conversion is performed of the temperature diode.
//  The temperature is then calculated in degrees C and F, based on the A/D
//  conversion value. Test by setting and running to a break point at
//  "__no_operation()".  To view the temperature open a watch window with the
//  debugger and view DegC and DegF.
//
//  Note: This example does not perform a calibration on the temperature sensor
//  A calibration of the temperature senosr may be necessary in an application.
//  see the device datasheet for the temperature sensor specification.
//  ACLK = 32kHz, MCLK = SMCLK = default DCO 1048576Hz, ADC12CLK = ADC12OSC
//
//                MSP430xG461x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//
//
//   A. Dannenberg/ M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430xG46x.h"

volatile unsigned int i;
volatile unsigned int ADCresult;
volatile unsigned long int DegC, DegF;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  ADC12CTL0 = ADC12ON + REFON + REF2_5V + SHT0_6;
                                            // Setup ADC12, ref., sampling time
  ADC12CTL1 = SHP;                          // Use sampling timer
  ADC12MCTL0 = INCH_10 + SREF_1;            // Select channel A10, Vref+
  ADC12IE = 0x01;                           // Enable ADC12IFG.0
  for (i = 0; i < 0x3600; i++);             // Delay for reference start-up
  ADC12CTL0 |= ENC;                         // Enable conversions
  __enable_interrupt();                     // Enable interrupts

  while(1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversion
    __bis_SR_register(LPM0_bits);           // Enter LPM0

    //  DegC = (Vsensor - 986mV)/3.55mV
    //  Vsensor = (Vref)(ADCresult)/4095)
    //  DegC -> ((ADCresult - 1615)*704)/4095
    DegC = ((((long)ADCresult-1615)*704)/4095);
    DegF = ((DegC * 9/5)+32);               // Calculate DegF
    __no_operation();                       // SET BREAKPOINT HERE
  }
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR(void)
{
  ADCresult = ADC12MEM0;                    // Move results, IFG is cleared
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPM0
}

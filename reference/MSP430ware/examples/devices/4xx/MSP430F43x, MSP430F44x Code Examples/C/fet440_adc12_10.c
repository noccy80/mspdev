//******************************************************************************
//  MSP-FET430P440 Demo - ADC12, Using the Temperature Sensor
//
//  This example shows how to use the intergrated temperature sensor to measure
//  temperature. When the temperature diode channel (A10) is selected for
//  conversion, the internal reference is automatically turned on as the source
//  for the sensor. Note however, that it is NOT automatically selected for the
//  conversion.  Any available reference can be used for the conversion.  In
//  this example, a single conversion is performed of the temperature diode.
//  The temperature is then calculated in degrees C and F, based on the A/D
//  conversion value. Test by setting and running to a break point at "_NOP()".
//  To view the temperature open a watch window with the debugger and view DegC
//  and DegF.
//  ACLK = n/a, MCLK = SMCLK = default DCO, ADC12CLK = ADC12OSC
//
//  Note: This example does not perform a calibration on the temperature sensor
//  A calibration of the temperature senosr may be necessary in an application.
//  see the device datasheet for the temperature sensor specification.
//
//                MSP430F449
//             ---------------
//            |               |
//            |A0 (Temp)      |
//            |               |
//
//  M. Mitchell
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************
#include  <msp430x44x.h>

static unsigned int ADCresult;
static unsigned long int DegC, DegF;

void main(void)
{
  unsigned int i;
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  ADC12CTL0 = ADC12ON+REFON+REF2_5V+SHT0_6; // Setup ADC12, ref., sampling time
  ADC12CTL1 = SHP;                          // Use sampling timer
  ADC12MCTL0 = INCH_10+SREF_1;              // Select channel A10, Vref+
  ADC12IE = 0x01;                           // Enable ADC12IFG.0

  for (i=0; i<0x3600; i++)                  // Delay for reference start-up
  {
  }

  ADC12CTL0 |= ENC;                         // Enable conversions
  _EINT();                                  // Enable interrupts

  while(1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversion
    _BIS_SR(LPM0_bits);                     // Enter LPM0

    //  DegC = (Vsensor - 986mV)/3.55mV
    //  Vsensor = (Vref)(ADCresult)/4095)
    //  DegC -> ((ADCresult - 1615)*704)/4095
    DegC = ((((long)ADCresult-1615)*704)/4095);
    DegF = ((DegC * 9/5)+32);               // Calculate DegF
    _NOP();                                 // SET BREAKPOINT HERE
  }
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  ADCresult = ADC12MEM0;                    // Move results, IFG is cleared
  _BIC_SR_IRQ(LPM0_bits);                   // Clear LPM0
}

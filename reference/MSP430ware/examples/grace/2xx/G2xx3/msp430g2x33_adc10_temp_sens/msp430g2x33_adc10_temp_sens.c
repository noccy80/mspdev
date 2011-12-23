//******************************************************************************
//  MSP430G2x33/G2x53 Demo - ADC10, Sample A10 Temp and Convert to oC and oF
//
//  Description: A single sample is made on A10 with reference to internal
//  1.5V Vref. Software sets ADC10SC to start sample and conversion - ADC10SC
//  automatically cleared at EOC. ADC10 internal oscillator/4 times sample
//  (64x) and conversion. In Mainloop MSP430 waits in LPM0 to save power until
//  ADC10 conversion complete, ADC10_ISR will force exit from any LPMx in
//  Mainloop on reti. Temperaure in oC stored in IntDegC, oF in IntDegF.
//  Uncalibrated temperature measured from device to device will vary with
//  slope and offset - please see datasheet.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz, ADC10CLK = ADC10OSC/4
//
//                MSP430G2x33/G2x53
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |A10              |
//******************************************************************************
/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

/*
 *  ======== main ========
 */

long temp;
long IntDegF;
long IntDegC;

void main(int argc, char *argv[])
{
    CSL_init();

    while(1)
    {
      ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
      __bis_SR_register(CPUOFF + GIE);        // LPM0 with interrupts enabled

      // oF = ((A10/1024)*1500mV)-923mV)*1/1.97mV = A10*761/1024 - 468
      temp = ADC10MEM;
      IntDegF = ((temp - 630) * 761) / 1024;

      // oC = ((A10/1024)*1500mV)-986mV)*1/3.55mV = A10*423/1024 - 278
      temp = ADC10MEM;
      IntDegC = ((temp - 673) * 423) / 1024;

      __no_operation();                       // SET BREAKPOINT HERE
    }
}

void ADC10_ISR(void)
{
}

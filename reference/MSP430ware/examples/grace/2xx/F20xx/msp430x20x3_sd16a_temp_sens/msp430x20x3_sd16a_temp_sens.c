//******************************************************************************
//  MSP430F20x3 Demo - SD16, Using the Integrated Temperature Sensor
//
//  Description: Use SD16 and it's integrated temperature sensor to detect
//  temperature delta. The temperature sensor output voltage is sampled
//  ~ every 240ms and compared with the last value and if more than ~0.5C
//  delta, P1.0 is set, else reset.
//  SD16 Internal VRef, Bipolar offset binary output format used.
//  Watchdog used as interval time and ISR used to start next SD16 conversion.
//  ACLK = n/a, MCLK = default DCO, SMCLK = SD16CLK = default DCO/8
//
//                MSP430F20x3
//             ------------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |A6+              |
//            |A6-          P1.0|-->LED
//            |                 |
/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

#define ADCDeltaOn 31                       // ~0.5 Deg C delta
static unsigned int LastADCVal;             // holds ADC temperature result

/*
 *  ======== main ========
 */
void main(int argc, char *argv[])
{
    CSL_init();

    _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 with interrupt
}

void SD16ISR(void)
{
	  if (SD16MEM0 <= LastADCVal + ADCDeltaOn)
	    P1OUT &= ~0x01;                         // LED off
	  else
	    P1OUT |= 0x01;                          // LED on
	  LastADCVal = SD16MEM0;                    // Store value
}

void watchdog_timer(void)
{
	 SD16CCTL0 |= SD16SC;                      // Start SD16 conversion
}

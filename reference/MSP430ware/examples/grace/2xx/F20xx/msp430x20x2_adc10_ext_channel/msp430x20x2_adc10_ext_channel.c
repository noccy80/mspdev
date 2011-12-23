//******************************************************************************
//  MSP430F20x2 Demo - ADC10, Sample A1, Signed, Set P1.0 if > 0.5*AVcc
//
//  Description: A single sample is made on A1 with SIGNED reference to AVcc.
//  Software sets ADC10SC to start sample and conversion - ADC10SC
//  automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
//  and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
//  conversion complete, ADC10_ISR will force exit from any LPMx in Mainloop on
//  reti. If A1 > 0.5*AVcc, P1.0 set, else reset.
//
//                MSP430F20x2
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|A1/P.1           |
//
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
void main(int argc, char *argv[])
{
    CSL_init();
    for (;;)
    {
      ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
      __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
      if ((int)ADC10MEM  < 0)
        P1OUT &= ~0x01;                       // Clear P1.0 LED off
      else
        P1OUT |= 0x01;                        // Set P1.0 LED on
    }

}

void ADC10_ISR(void)
{
}

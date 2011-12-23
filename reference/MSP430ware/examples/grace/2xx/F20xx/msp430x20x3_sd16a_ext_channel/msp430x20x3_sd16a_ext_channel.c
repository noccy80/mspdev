//******************************************************************************
//  MSP430F20x3 Demo - SD16A, Sample A1+ Continuously, Set P1.0 if > 0.3V
//
//  Description: A continuous single-ended sample is made on A1+ using internal
//  VRef Unipolar output format used.
//  Inside of SD16 ISR, if A1 > 1/2VRef (0.3V), P1.0 set, else reset.
//  ACLK = n/a, MCLK = SMCLK = SD16CLK = default DCO
//
//                MSP430F20x3
//             ------------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//    Vin+ -->|A1+ P1.2         |
//            |A1- = VSS    P1.0|-->LED
//            |
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
    SD16CCTL0 |= SD16SC;                      // Set bit to start conversion
    _BIS_SR(LPM0_bits + GIE);
}

void SD16ISR(void)
{
	  if (SD16MEM0 < 0x7FFF)           	    // SD16MEM0 > 0.3V?, clears IFG
	    P1OUT &= ~0x01;
	  else
	    P1OUT |= 0x01;
}

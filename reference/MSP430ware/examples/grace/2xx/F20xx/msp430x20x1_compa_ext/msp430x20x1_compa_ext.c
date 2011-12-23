//******************************************************************************
//   MSP430F20x1 Demo - Comp_A, Detect Threshold, Set P1.0 if P1.1 > 0.25*Vcc
//
//   Description: Use Comparator_A to detect a voltage threshold.
//   Using an external potentiometer, an unknown voltage is applied to P1.1.
//   Comparator_A compares the unknown voltage to an internal reference
//   voltage, in this example 0.25*VCC. If the unknown voltage is higher
//   than 0.25*VCC, P1.0 is set, if not, P1.0 is reset.
//   ACLK = n/a, MCLK = SMCLK = default DCO
//
//          MSP430F20x1
//       -----------------
//   /|\ |            XIN|-
//    |  |               |
//    ---|RST        XOUT|-
//    |  |               |
//    R<-|P1.1/CA1   P1.0|-->LED
//    |  |               |
//    ---|VSS
/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

/*
 *  ======== cbrtest_done ========
 *
 *  Place holder function so that test script can set a breakpoint after
 *  Grace init function is done.
 */
void cbrtest_done()
{
    while (1);
}

/*
 *  ======== main ========
 */
void main(int argc, char *argv[])
{
    CSL_init();

    while (1)                                 // Test comparator_A output
    {
      if ((CAOUT & CACTL2))
        P1OUT |= 0x01;                        // if CAOUT set, set P1.0
      else P1OUT &= ~0x01;                    // else reset
    }
}
void Timer_A(void)
{
}

//******************************************************************************
//  MSP430F22x4 Demo - OA0, Non-Inverting PGA Mode
//
//  Description: Configure OA0 for Non-Inverting PGA mode. In this mode,
//  the "-" terminal is connected to the R ladder tap and the OAFBRx bits
//  select the gain.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430F22x4
//             -------------------
//         /|\|                XIN|-
//          | |                   |
//          --|RST            XOUT|-
//            |                   |
//     "+" -->|P2.0/A0/OA0I0      |
//            |                   |
//            |       P2.1/A1/OA0O|--> OA0 Output
//            |                   |    Gain is 8
//******************************************************************************
/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace and RTSC related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

/*
 *  ======== main ========
 */
void main(int argc, char *argv[])
{
    CSL_init();

    _bis_SR_register(LPM3_bits);       // Enter LPM3
}

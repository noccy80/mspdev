//******************************************************************************
//  MSP430F20xx Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430F20xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
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
int main(int argc, char *argv[])
{
    CSL_init();                     // Activate Grace-generated configuration
    
    // >>>>> Fill-in user code here <<<<<
    while(1)
    {
      volatile unsigned int i;

      P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR

      i = 50000;                              // Delay
      do (i--);
      while (i != 0);
    }
}

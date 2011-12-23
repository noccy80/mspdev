//******************************************************************************
//  MSP430x21x1 Demo - Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
//
//  Description: This program operates MSP430 normally in LPM3, pulsing P1.0
//  at 4 second intervals. WDT ISR used to wake-up system. All I/O configured
//  as low outputs to eliminate floating inputs. Current consumption does
//  increase when LED is powered on P1.0. Demo for measuring LPM3 current.
//  ACLK = LFXT1/4 = 32768/4, MCLK = SMCLK = default DCO ~ 800kHz
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//
//
//
//           MSP430F2131
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
//*****************************************************************************
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

    while(1)
    {
      int i;
      _BIS_SR(LPM3_bits + GIE);               // Enter LPM3
      P1OUT |= 0x01;                          // Set P1.0 LED on
      for (i = 5000; i>0; i--);               // Delay
      P1OUT &= ~0x01;                         // Reset P1.0 LED off
    }
}

void watchdog_timer(void)
{
}

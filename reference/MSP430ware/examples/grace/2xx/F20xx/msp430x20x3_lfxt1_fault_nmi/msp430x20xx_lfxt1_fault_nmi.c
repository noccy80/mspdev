/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

volatile unsigned int i;
/*
 *  ======== main ========
 */
void main(int argc, char *argv[])
{
    CSL_init();

    while(1)
    {
       P1OUT ^= 0x01;                           // Toggle P1.0 using exclusive-OR
      _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/interrupt
    }
}
void watchdog_timer(void)
{
}

void nmi_(void)
{
	 do
	  {
		IFG1 &= ~OFIFG;                         // Clear OSCFault flag
		for (i = 0xFFF; i > 0; i--);            // Time for flag to set
		P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR
	  }
	  while (IFG1 & OFIFG);                     // OSCFault flag still set?
	  IE1 |= OFIE;                              // Enable Osc Fault
}

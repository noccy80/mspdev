//******************************************************************************
//   MSP430F22x4 Demo - Timer_B, Toggle P4.0-2, Cont. Mode ISR, DCO SMCLK
//
//   Description: Use Timer_B CCRx units and overflow to generate four
//   independent timing intervals. For demonstration, TBCCR0-2 output
//   units are optionally selected with P4.0-2 respectively in toggle
//   mode. As such, these pins will toggle when respective TBCCRx registers
//   match the TBR counter. Interrupts are also enabled with all TBCCRx units,
//   software only adds offset to next interval - as long as the interval
//   offset is aded to TBCCRx, toggle rate is generated in hardware. Timer_B
//   overflow is used to toggle P1.0 with software. Proper use of the TBIV
//   interrupt vector generator is demonstrated.
//   MCLK = SMCLK = TBCLK = DCO ~1.2MHz
//
//   As coded with TBCLK ~1.2MHz DCO, toggle rates are:
//   P4.0 = TBCCR0 = 1200000/(2*200) = 3000Hz
//   P4.1 = TBCCR1 = 1200000/(2*400) = 1500Hz
//   P4.2 = TBCCR2 = 1200000/(2*600) = 1000Hz
//   P1.0 = overflow = 1200000/(2*65536) = 9Hz
//
//                MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |         P4.0/TB0|--> TBCCR0
//            |         P4.1/TB1|--> TBCCR1
//            |         P4.2/TB2|--> TBCCR2
//            |             P1.0|--> Overflow/software
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

    __bis_SR_register(CPUOFF + GIE);          // CPU off, interrupts enabled
}
void TimerB_ISR (void)
{
    switch (TBIV)        // Efficient switch-implementation
    {
    case  2:                                // TBCCR1
      TBCCR1 += 400;                        // Offset until next interrupt
      break;
    case  4:                                // TBCCR2
      TBCCR2 += 600;                        // Offset until next interrupt
      break;
    case 14:                                // Overflow
      P1OUT ^= 0x01;                        // Toggle P1.0
      break;
    }
}
void TimerB_CCR0_ISR (void)
{
    TBCCR0 += 200;                            // Offset until next interrupt
}

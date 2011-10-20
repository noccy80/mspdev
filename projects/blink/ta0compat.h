#ifndef __TA0COMPAT_H__
#define __TA0COMPAT_H__

/**
 *
 * Compatibility defines for mapping timers to work for a wider number of
 * microcontrollers without modifications.
 *
 *   Define             Mapping
 *   ------             -------
 *   TA0CTL          -> TACTL
 *   TA0CCTL0        -> TACCTL0
 *   TIMERA0_VECTOR  -> TIMER0_A0_VECTOR
 */

#ifndef TACTL
#define TACTL TA0CTL
#define TACCTL0 TA0CCTL0
#define TIMERA0_VECTOR TIMER0_A0_VECTOR
#endif // TACTL

#endif // __TA0COMPAT_H__

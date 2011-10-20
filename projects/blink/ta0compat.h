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
 */

#ifndef TACTL
#define TACTL TA0CTL
#define TACCTL0 TA0CCTL0
#endif // TACTL

#endif // __TA0COMPAT_H__

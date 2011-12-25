#ifndef __WDT_H__
#define __WDT_H__

inline void WDT_halt() { WDTCTL = WDTPW + WDTHOLD; }

#endif // __WDT_H__

//******************************************************************************
//  MSP430F543xA Demo - RTC in Counter Mode toggles P1.0 every 1s
//
//  This program demonstrates RTC in counter mode configured to source from ACLK
//  to toggle P1.0 LED every 1s.
//
//                MSP430F5438A
//             -----------------
//        /|\ |                 |
//         |  |                 |
//         ---|RST              |
//            |                 |
//            |             P1.0|-->LED
//
//   M. Morales
//   Texas Instruments Inc.
//   June 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54xA.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;

  P1OUT |= 0x01;
  P1DIR |= 0x01;

  // Setup RTC Timer
  RTCCTL01 = RTCTEVIE + RTCSSEL_2 + RTCTEV_0; // Counter Mode, RTC1PS, 8-bit ovf
                                            // overflow interrupt enable
  RTCPS0CTL = RT0PSDIV_2;                   // ACLK, /8, start timer
  RTCPS1CTL = RT1SSEL_2 + RT1PSDIV_3;       // out from RT0PS, /16, start timer

  __bis_SR_register(LPM3_bits + GIE);
}

#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void)
{
  switch(__even_in_range(RTCIV,16))
  {
    case 0: break;                          // No interrupts
    case 2: break;                          // RTCRDYIFG
    case 4:                                 // RTCEVIFG
      P1OUT ^= 0x01;
      break;
    case 6: break;                          // RTCAIFG
    case 8: break;                          // RT0PSIFG
    case 10: break;                         // RT1PSIFG
    case 12: break;                         // Reserved
    case 14: break;                         // Reserved
    case 16: break;                         // Reserved
    default: break;
  }
}

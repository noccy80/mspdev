//******************************************************************************
//  MSP430x471xx Demo - Real Time Clock, Toggle P5.1 Inside ISR, 32kHz ACLK
//
//  Description: This program toggles P5.1 by xor'ing P5.1 inside of
//  a Real Time Clock ISR. The Real Time Clock ISR is called once a minute using
//  the Alarm function provided by the RTC. ACLK used to clock basic timer.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//
//
//                MSP430x471xx
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include  <msp430x471x7.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;             // Stop Watchdog Timer

  FLL_CTL0 = XCAP14PF;                  // Configure load caps
  RTCCTL = RTCBCD+RTCHOLD+RTCMODE_3+RTCTEV_0+RTCIE;
                                        // RTC enable, BCD mode,
                                        // alarm every Minute,
                                        // enable RTC interrupt
  // Init time
  RTCSEC =  0x00;                       // Set Seconds
  RTCMIN =  0x00;                       // Set Minutes
  RTCHOUR = 0x08;                       // Set Hours

  // Init date
  RTCDOW =  0x02;                       // Set DOW
  RTCDAY =  0x23;                       // Set Day
  RTCMON =  0x08;                       // Set Month
  RTCYEAR = 0x2005;                     // Set Year

  RTCCTL &= ~RTCHOLD;                   // Enable RTC

  P5DIR |= BIT1;                        // Set P5.1 to output direction

  __bis_SR_register(LPM3_bits + GIE);   // Enter LPM3 w/ interrupt
}

// Basic Timer interrupt service routine
#pragma vector=BASICTIMER_VECTOR
__interrupt void basic_timer(void)
{
  P5OUT ^= BIT1;                        // Toggle P5.1 using exclusive-OR
}

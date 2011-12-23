//******************************************************************************
//  MSP430F54xA Demo - RTC_A in real time clock mode
//
//  Description: This program demonstrates the RTC mode by triggering an
//  interrupt every second and minute. This code toggles P1.0 every second.
//  This code recommends an external LFXT1 crystal for RTC accuracy.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//
//                MSP430F54xA
//             -----------------
//        /|\ |              XIN|-
//         |  |                 | 32kHz
//         ---|RST          XOUT|-
//            |                 |
//            |            P1.0 |--> Toggles every second
//            |                 |
//
//  W. Goh
//  Texas Instruments Inc.
//  April 2010
//  Built with CCS version 4.2 and IAR Embedded Workbench Version: 4.21.8
//******************************************************************************

#include <msp430x54xA.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop Watchdog Timer
  P1DIR |= BIT0;                            // Set P1.0 as output

  // Initialize LFXT1
  P7SEL |= 0x03;                            // Select XT1
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap

  // Loop until XT1,XT2 & DCO fault flag is cleared
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  // Configure RTC_A
  RTCCTL01 |= RTCTEVIE + RTCRDYIE + RTCBCD + RTCHOLD + RTCMODE;
                                            // RTC enable, BCD mode, RTC hold
                                            // enable RTC read ready interrupt
                                            // enable RTC time event interrupt

  RTCYEAR = 0x2010;                         // Year = 0x2010
  RTCMON = 0x4;                             // Month = 0x04 = April
  RTCDAY = 0x05;                            // Day = 0x05 = 5th
  RTCDOW = 0x01;                            // Day of week = 0x01 = Monday
  RTCHOUR = 0x10;                           // Hour = 0x10
  RTCMIN = 0x32;                            // Minute = 0x32
  RTCSEC = 0x45;                            // Seconds = 0x45

  RTCADOWDAY = 0x2;                         // RTC Day of week alarm = 0x2
  RTCADAY = 0x20;                           // RTC Day Alarm = 0x20
  RTCAHOUR = 0x10;                          // RTC Hour Alarm
  RTCAMIN = 0x23;                           // RTC Minute Alarm

  RTCCTL01 &= ~(RTCHOLD);                   // Start RTC calendar mode

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 mode with interrupts
                                            // enabled
  __no_operation();
}

#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void)
{
  switch(__even_in_range(RTCIV,16))
  {
    case RTC_NONE:                          // No interrupts
      break;
    case RTC_RTCRDYIFG:                     // RTCRDYIFG
      P1OUT ^= 0x01;                        // Toggles P1.0 every second
      break;
    case RTC_RTCTEVIFG:                     // RTCEVIFG
      __no_operation();                     // Interrupts every minute
      break;
    case RTC_RTCAIFG:                       // RTCAIFG
      break;
    case RTC_RT0PSIFG:                      // RT0PSIFG
      break;
    case RTC_RT1PSIFG:                      // RT1PSIFG
      break;
    case 12: break;                         // Reserved
    case 14: break;                         // Reserved
    case 16: break;                         // Reserved
    default: break;
  }
}

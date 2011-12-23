//******************************************************************************
//  MSP430x471xx Demo - Real Time Clock, Toggle P5.1 Inside ISR, 32kHz ACLK
//                      and send Time via UART
//
//  Description: This program toggles P5.1 by xor'ing P5.1 inside of
//  a Real Time Clock ISR. The Real Time Clock ISR is called once a minute using
//  the Alarm function provided by the RTC. ACLK used to clock basic timer.
//  The actual time is send send via UART
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
//            |                 |
//            |      P2.4/UC0TXD|----------->
//            |                 | 2400 - 8N1
//            |      P2.5/UC0RXD|<-----------
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  <msp430x471x7.h>

void tx_char(char c);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;             // Stop Watchdog Timer

  FLL_CTL0 = XCAP14PF;                  // Configure load caps

  P2SEL = BIT4+BIT5;                         // P2.4,5 = USART0 TXD/RXD
  P5DIR |= BIT1;                        // Set P5.1 to output direction

  // SetupUSCI0:
  UCA0CTL1 = UCSWRST;                   // To set hold the module in reset
  UCA0CTL1 = UCSSEL0;                   // ACLK
  UCA0BR0 = 13;                         // 32k - 2400 baudrate control setting
  UCA0BR1 = 0;
  UCA0MCTL = UCBRS2+UCBRS1;             // Second modulation stage values
  UCA0STAT = UCFE+UCOE+UCPE+UCBRK+UCRXERR;

  // RTC
  RTCCTL = RTCBCD+RTCHOLD+RTCMODE_3+RTCTEV_0+RTCIE;
                                        // RTC enable, BCD mode,
                                        // alarm every Minute,
                                        // enable RTC interrupt
  // Init time
  RTCSEC =  0x00;                       // Set Seconds
  RTCMIN =  0x58;                       // Set Minutes
  RTCHOUR = 0x08;                       // Set Hours

  // Init date
  RTCDOW =  0x02;                       // Set DOW
  RTCDAY =  0x23;                       // Set Day
  RTCMON =  0x08;                       // Set Month
  RTCYEAR = 0x2005;                     // Set Year

  RTCCTL &= ~RTCHOLD;                   // Enable RTC

  while (1)
  {
    __bis_SR_register(LPM3_bits + GIE); // Enter LPM3 w/ interrupt
    __no_operation();                   // Required for debugger

    tx_char((RTCHOUR>>4)+0x30);         // Send high nibble of hour
    tx_char((RTCHOUR&0x0F)+0x30);       // Send low nibble of hour
    tx_char(':');                       // Send ':'
    tx_char((RTCMIN>>4)+0x30);          // Send high nibble of minute
    tx_char((RTCMIN&0x0F)+0x30);        // Send low nibble of minute
    tx_char('\n');                      // Send new line
  }
}

void tx_char(char c)
{
  while ((IFG2 & UCA0TXIFG)==0){}       // wait till TXbuf empty
  UCA0TXBUF = c;                        // TX char
}
// Basic Timer interrupt service routine
#pragma vector=BASICTIMER_VECTOR
__interrupt void basic_timer(void)
{
  P5OUT ^= BIT1;                        // Toggle P5.1 using exclusive-OR
  LPM3_EXIT;                            // Exit LPM after interrupt
}

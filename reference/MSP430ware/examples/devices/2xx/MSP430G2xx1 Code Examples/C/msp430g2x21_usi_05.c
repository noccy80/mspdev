//******************************************************************************
//  MSP430G2x21/G2x31 Demo - USI SPI Interface to TLC549 8-bit ADC
//
//   Description: This program demonstrates the USI in SPI mode interface to a
//   TLC549 8-bit ADC. If AIN > 0.5(REF+ - REF-), P1.0 set, else reset.
//   ACLK = n/a, MCLK = SMCLK = default DCO, UCICLK = SMCLK/4
//   //** VCC must be at least 3v for TLC549 **//
//
//                       MSP430G2x21/G2x31
//                       -----------------
//                   /|\|              XIN|-
//        TLC549      | |                 |
//    -------------   --|RST          XOUT|-
//   |           CS|<---|P1.1             |
//   |      DATAOUT|--->|P1.7/SOMI    P1.0|-->LED
// ~>|AIN   I/O CLK|<---|P1.5/SCLK        |
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include <msp430g2221.h>


void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1OUT = 0;
  P1DIR |= 0x03;
  USICTL0 |= USIPE7 + USIPE5 + USIMST + USIOE; // Port, SPI master
  USICTL1 |= USIIE;                         // Counter interrupt, flag remains set
  USICKCTL = USIDIV_2 + USISSEL_2;          // /4 SMCLK
  USICTL0 &= ~USISWRST;                     // USI released for operation
  USICNT = 8;                               // init-load counter
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// USI interrupt service routine
#pragma vector=USI_VECTOR
__interrupt void universal_serial_interface(void)
{
  P1OUT |= 0x02;                            // Disable TLC549
  if (USISRL > 0x7F)
    P1OUT |= 0x01;
  else
    P1OUT &= ~0x01;
  P1OUT &= ~0x02;                            // Enable TLC549
  USICNT = 8;                                // re-load counter
}

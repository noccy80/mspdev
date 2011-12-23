//******************************************************************************
//  MSP430G2x21/G2x31 Demo - SPI full-Duplex 3-wire Master
//
//  Description: SPI Master communicates full-duplex with SPI Slave using
//  3-wire mode. The level on P1.4 is TX'ed and RX'ed to P1.0.
//  Master will pulse slave reset for synch start.
//  ACLK = n/a, MCLK = SMCLK = Default DCO
//
//                Slave                      Master
//             MSP430G2x21/G2x31          MSP430G2x21/G2x31
//             -----------------          -----------------
//            |              XIN|-    /|\|              XIN|-
//            |                 |      | |                 |
//            |             XOUT|-     --|RST          XOUT|-
//            |                 | /|\    |                 |
//            |          RST/NMI|--+<----|P1.2             |
//      LED <-|P1.0             |        |             P1.4|<-
//          ->|P1.4             |        |             P1.0|-> LED
//            |         SDI/P1.7|<-------|P1.6/SDO         |
//            |         SDO/P1.6|------->|P1.7/SDI         |
//            |        SCLK/P1.5|<-------|P1.5/SCLK        |
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include <msp430g2221.h>


void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
  P1OUT =  0x10;                        // P1.4 set, else reset
  P1REN |= 0x10;                        // P1.4 pullup
  P1DIR = 0x01;                         // P1.0 output, else input
  USICTL0 |= USIPE7 +  USIPE6 + USIPE5 + USIMST + USIOE; // Port, SPI master
  USICTL1 |= USIIE;                     // Counter interrupt, flag remains set
  USICKCTL = USIDIV_4 + USISSEL_2;      // /16 SMCLK
  USICTL0 &= ~USISWRST;                 // USI released for operation
  USISRL = P1IN;                        // init-load data

  P1DIR |= 0x04;                        // Reset Slave
  P1DIR &= ~0x04;
  for (i = 0xFFF; i > 0; i--);          // Time for slave to ready
  USICNT = 8;                           // init-load counter
  _BIS_SR(LPM0_bits + GIE);             // Enter LPM0 w/ interrupt
}

// USI interrupt service routine
#pragma vector=USI_VECTOR
__interrupt void universal_serial_interface(void)
{
  if (0x10 & USISRL)
    P1OUT |= 0x01;
  else
    P1OUT &= ~0x01;
  USISRL = P1IN;
  USICNT = 8;                           // re-load counter
}

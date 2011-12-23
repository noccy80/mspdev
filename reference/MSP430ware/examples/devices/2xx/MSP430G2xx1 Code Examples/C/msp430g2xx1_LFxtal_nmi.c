//******************************************************************************
//  MSP430G2xx1 Demo - LFXT1 Oscillator Fault Detection
//
//  Description: System runs normally in LPM3 with WDT timer clocked by
//  32kHz ACLK with a 1x4 second interrupt. P1.0 is normally pulsed every
//  second inside WDT interrupt. If an LFXT1 oscillator fault occurs,
//  NMI is requested forcing exit from LPM3. P1.0 is toggled rapidly by software
//  as long as LFXT1 oscillator fault is present. Assumed only LFXT1 as NMI
//  source - code does not check for other NMI sources.
//  ACLK = LFXT1 = 32768, MCLK = SMCLK = Default DCO
//
//  //*External watch crystal on XIN XOUT is required for ACLK*//	
//
//
//           MSP430G2xx1
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include <msp430g2231.h>

volatile unsigned int i;

void main(void)
{
  WDTCTL = WDT_ADLY_1000;                   // WDT 1s interval timer
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P1DIR = 0xFF;                             // All P1.x outputs
  P1OUT = 0;                                // All P1.x reset
  P2DIR = 0xFF;                             // All P2.x outputs
  P2OUT = 0;                                // All P2.x reset
// An immedate Osc Fault will occur next
  IE1 |= OFIE;                              // Enable Osc Fault

  while(1)
  {
   P1OUT ^= 0x01;                           // Toggle P1.0 using exclusive-OR
  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/interrupt
  }
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer (void)
{
    _BIC_SR_IRQ(LPM3_bits);                 // Clear LPM3 bits from 0(SR)
}

#pragma vector=NMI_VECTOR
__interrupt void nmi_ (void)
{
  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSCFault flag
    for (i = 0xFFF; i > 0; i--);            // Time for flag to set
    P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR
  }
  while (IFG1 & OFIFG);                     // OSCFault flag still set?
  IE1 |= OFIE;                              // Enable Osc Fault
}

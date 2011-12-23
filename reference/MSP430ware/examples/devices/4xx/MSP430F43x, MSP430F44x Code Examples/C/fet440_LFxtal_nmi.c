//******************************************************************************
//  MSP-FET430P440 Demo - LFXT1 Oscillator Fault Detection
//
//  Description: System runs normally in LPM3 with with basic timer clocked by
//  32kHz ACLK with a 1 second interrupt. P5.1 is normally toggled every
//  1 second inside basic timer interrupt. If an LFXT1 oscillator fault occurs,
//  NMI is requested forcing exit from LPM3. P5.1 is toggled rapidly by
//  software as long as LFXT1 oscillator fault is present. Assuumed only
//  LFXT1 as NMI source - code does not check for other NMI sources.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//
//            MSP430F449
//         ---------------
//     /|\|            XIN|-
//      | |               | 32KHz
//      --|RST        XOUT|-
//        |               |
//        |           P5.1|-->LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************
#include <msp430x44x.h>

volatile unsigned int i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  P5DIR |= 0x02;                            // P5.1 outputs
  BTCTL = BT_ADLY_1000;                     // 1s Interrupt
  IE2 |= BTIE;                              // Enable BT interrupt

  // An immedate Osc Fault will occur next
  IE1 |= OFIE;                              // Enable Osc Fault

  while(1) {
    _BIS_SR(LPM3_bits + GIE);               // Enter LPM3 w/ interrupts
    P5OUT ^= 0x02;                          // Toggle P5.1 using exclusive-OR
  }
}

// Basic Timer interrupt service routine
#pragma vector=BASICTIMER_VECTOR
__interrupt void basic_timer(void)
{
  P5OUT ^= 0x02;                            // Toggle P5.1 using exclusive-OR
}

#pragma vector=NMI_VECTOR
__interrupt void nmi_ (void)
{
  do
  {
    IFG1 &= ~OFIFG;                   // Clear OSC Fault flag
    for (i = 0xFFF; i > 0; i--);      // Time for flag to set
    P5OUT ^= 0x02;                    // Toggle P5.2 using exclusive-OR
  }
  while (IFG1 & OFIFG);               // OSC Fault flag still set?
  IE1 |= OFIE;                        // Enable Osc Fault
}




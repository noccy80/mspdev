//******************************************************************************
//   MSP430F(G)47x Demo - LFXT1 Oscillator Fault Detection
//
//   Description: System runs normally in LPM3 with the basic timer clocked by
//   32kHz ACLK with a 1 second interrupt. P1.0 is normally toggled every
//   1 second inside basic timer interrupt. If an LFXT1 oscillator fault occurs,
//   NMI is requested forcing exit from LPM3. P1.0 is toggled rapidly by software
//   as long as LFXT1 oscillator fault is present. Assumed only LFXT1 as NMI
//   source - code does not check for other NMI sources.
//   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//   //* An external watch crystal between XIN & XOUT is required for ACLK *//
//
//                MSP430F(G)47x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P4.6|-->LED
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//******************************************************************************
#include "msp430xG47x.h" 

volatile unsigned int i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  IE2 |= BTIE;                              // Enable BT interrupt
  BTCTL = BT_ADLY_1000;                     // 1s Interrupt
  P4DIR |= 0x40;                            // P4.6 output

  // An immedate Osc Fault will occur next
  IE1 |= OFIE;                              // Enable Osc Fault  
  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts
}

// Basic Timer interrupt service routine
#pragma vector=BASICTIMER_VECTOR
__interrupt void basic_timer(void)
{
  P4OUT ^= 0x40;                            // Toggle P4.6 using exclusive-OR
}

#pragma vector=NMI_VECTOR
__interrupt void nmi_ (void)
{
  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSCFault flag
    for (i = 0xFFF; i > 0; i--);            // Time for flag to set
    P4OUT ^= 0x40;                          // Toggle P4.6 using exclusive-OR
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?
  IE1 |= OFIE;                              // Enable Osc Fault
}


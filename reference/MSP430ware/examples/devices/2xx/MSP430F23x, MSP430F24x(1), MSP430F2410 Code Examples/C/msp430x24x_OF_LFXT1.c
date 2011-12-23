//******************************************************************************
//  MSP430x249 Demo - LFXT1 Oscillator Fault Detection
//
//  Description: System runs normally in LPM3 with Timer A clocked by 32kHz 
//  ACLK with a 1 second interrupt. P1.0 is normally toggled every 1 sec
//  inside Timer A0 interrupt. If an LFXT1 oscillator fault occurs, NMI is 
//  requested forcing exit from LPM3. And P1.0 is toggled rapidly by software as 
//  long as LFXT1 oscillator fault is present. Assuumed only LFXT1 as NMI source
//   - code does not check for other NMI sources. ACLK is buffered on P5.6.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//            MSP430x249
//         ---------------
//     /|\|            XIN|-
//      | |               | 32KHz
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
//        |      P5.6/ACLK|-->ACLK = LFXT1
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include <msp430x24x.h>

volatile unsigned int i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  P1DIR |= 0x01;                            // P1.0 outputs - LED
  
  //Initialize Timer A to generate one-second interrupt
  TACCTL0 = CCIE;                           // TACCR0 interrupt enabled
  TACCR0 = 32767;                           // Set CCR0 to 32767(ACLK=32.768Hz)                                      
  TACTL = TASSEL_1 + MC_1;                  // ACLK, up mode                            

  P5DIR |= 0x40;                            // P5.6= output direction
  P5SEL |= 0x40;                            // P5.6= ACLK option select
  
  // An immedate Osc Fault will occur next
  IE1 |= OFIE;                              // Enable Osc Fault

  while(1) {
    _BIS_SR(LPM3_bits + GIE);               // Enter LPM3 w/ interrupts
    P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR
  }
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR 
__interrupt void Timer_A (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0 using exclusive-OR
}

#pragma vector=NMI_VECTOR
__interrupt void nmi_ (void)
{
  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSC Fault flag
    for (i = 0x47FF; i > 0; i--);           // Time for flag to set
    P1OUT ^= 0x01;                          // Toggle P1.0
  }
  while (IFG1 & OFIFG);                     // OSC Fault flag still set?
  IE1 |= OFIE;                              // Enable Osc Fault
}




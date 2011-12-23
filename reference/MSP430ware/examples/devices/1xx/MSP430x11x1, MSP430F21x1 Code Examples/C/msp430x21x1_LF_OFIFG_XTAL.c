//******************************************************************************
//  MSP430x21x1 Demo - OFIFG ISR for LF Failsafe Operation
//
//  Description: Toggle P1.0 using software timed by the WDT ISR. Toggle rate
//  is approximately 250ms based on 32768Hz ACLK when present. When the LFXT1
//  input signal faults during operation, the NMI ISR is entered and the fault
//  is serviced. During this time the LED will flash at a faster rate indicating
//  an ACLK fault. During this time the CPU is held in the NMI ISR.
//
//  ACLK = 32768 Hz, MCLK = SMCLK = ~1.16 MHz
//
//                MSP430F21x1
//             -----------------
//         /|\|              XIN|-
//          | |                 |  32.768kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  H. Grewal / A. Dannenberg
//  Texas Instruments, Inc
//  June 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: V3.30A
//******************************************************************************
#include  <msp430x21x1.h>

void main(void)
{
  WDTCTL = WDT_ADLY_250;                    // Set WDT interval to ~250ms from ACLK
  IE1 |= OFIE;                              // Enable osc fault int (NMI)
  IE1 |= WDTIE;                             // Enable WDT interrupt

  P1OUT = 0x00;
  P1DIR |= 0x01;

  while(1)
  {
    _BIS_SR(LPM3_bits+GIE);                 // Enter LPM3 with ints
  }
}

// NMI interrupt service routine
#pragma vector=NMI_VECTOR
__interrupt void osc_fault(void)
{
  volatile unsigned int i;

  do                                        // Loop until flag is clear
  {
    IFG1 &= ~OFIFG;                         // Clear fault flag
    for (i = 0xFFF; i; i--);                // Delay for crystal to start
    P1OUT ^= 0x01;                          // Toggle LED: rate is faster
  }
  while (IFG1 & OFIFG);                     // Test LF oscillator fault flag
  IE1 |= OFIE;                              // Re-enable osc fault int
}

// WDT interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P1OUT ^= 0x01;                            // Toggle LED
}

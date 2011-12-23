//******************************************************************************
//  MSP430F20x3 Demo - SD16A, Sample A1+ Continuously, Set P1.0 if > 0.3V
//
//  Description: A continuous single-ended sample is made on A1+ using internal
//  VRef Unipolar output format used.
//  Inside of SD16 ISR, if A1 > 1/2VRef (0.3V), P1.0 set, else reset.
//  ACLK = n/a, MCLK = SMCLK = SD16CLK = default DCO
//
//                MSP430F20x3
//             ------------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//    Vin+ -->|A1+ P1.2         |
//            |A1- = VSS    P1.0|-->LED
//            |                 |
//
//  M. Buccini / L. Westlund
//  Texas Instruments Inc.
//  October 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.40A
//******************************************************************************
#include  <msp430x20x3.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  SD16CTL = SD16REFON + SD16SSEL_1;         // 1.2V ref, SMCLK
  SD16INCTL0 = SD16INCH_1;                  // A1+/-
  SD16CCTL0 =  SD16UNI + SD16IE;            // 256OSR, unipolar, interrupt enable
  SD16AE = SD16AE2;                         // P1.1 A1+, A1- = VSS
  SD16CCTL0 |= SD16SC;                      // Set bit to start conversion

  _BIS_SR(LPM0_bits + GIE);
}

#pragma vector = SD16_VECTOR
__interrupt void SD16ISR(void)
{
  if (SD16MEM0 < 0x7FFF)           	    // SD16MEM0 > 0.3V?, clears IFG
    P1OUT &= ~0x01;
  else
    P1OUT |= 0x01;
}

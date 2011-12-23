//******************************************************************************
//  MSP-FET430P120 Demo - ADC10, DTC Sample A0 64x, 1.5V, Repeat Single, DCO
//
//  Description: Use DTC to sample A0 64 times with reference to internal 1.5v.
//  Vref Software writes to ADC10SC to trigger sample burst. In Mainloop MSP430
//  waits in LPM0 to save power until ADC10 conversion complete, ADC10_ISR(DTC)
//  will force exit from any LPMx in Mainloop on reti. ADC10 internal
//  oscillator times sample period (16x) and conversion (13x). DTC transfers
//  conversion code to RAM 200h - 280h. P1.0 set at start of conversion burst,
//  reset on completion.
//  //* MSP430F1232 or MSP430F1132 Device Required *//
//
//                MSP430F1232
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|A0           P1.0|-->LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x12x2.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL1 = CONSEQ_2;                     // Repeat single channel
  ADC10CTL0 = SREF_1 + ADC10SHT_2 + MSC + REFON + ADC10ON + ADC10IE;
  _EINT();                                  // Enable interrupts.
  TACCR0 = 30;                              // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
  TACTL = TASSEL_2 | MC_1;                  // TACLK = SMCLK, Up mode.
  LPM0;                                     // Wait for delay.
  TACCTL0 &= ~CCIE;                         // Disable timer Interrupt
  _DINT();
  ADC10DTC1 = 0x40;                         // 64 conversions
  ADC10AE |= 0x01;                          // P2.0 ADC option select
  P1DIR |= 0x01;                            // Set P1.0 output

  for (;;)
  {
    ADC10CTL0 &= ~ENC;
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    ADC10SA = 0x200;                        // Data buffer start
    P1OUT |= 0x01;                          // Set P1.0 LED on
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    _BIS_SR(CPUOFF + GIE);                  // LPM0, ADC10_ISR will force exit
    P1OUT &= ~0x01;                         // Clear P1.0 LED off
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
    _BIC_SR_IRQ(CPUOFF);                    // Clear CPUOFF bit from 0(SR)
}

#pragma vector=TIMERA0_VECTOR
__interrupt void ta0_isr(void)
{
  TACTL = 0;
  LPM0_EXIT;                                // Exit LPM0 on return
}// ta0_isr()
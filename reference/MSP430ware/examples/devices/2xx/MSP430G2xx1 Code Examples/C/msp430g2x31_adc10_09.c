//******************************************************************************
//  MSP430G2x31 Demo - ADC10, DTC Sample A10 32x, 1.5V, Repeat Single, DCO
//
//  Description: Use DTC to sample A10 32 times with reference to internal 1.5v.
//  Vref Software writes to ADC10SC to trigger sample burst. In Mainloop MSP430
//  waits in LPM0 to save power until ADC10 conversion complete, ADC10_ISR(DTC)
//  will force exit from any LPMx in Mainloop on reti. (ADC10OSC/4)/64
//  determines sample time which needs to be greater than 30us for temperature
//  sensor. DTC transfers conversion code to RAM 200h - 240h. P1.0 set at start
//  of conversion burst, reset oncompletion. Temperature sensor offset and slope
//  will vary from device to device per datasheet tolerance.
//
//                MSP430G2x31
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |A10          P1.0|-->LED
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************
#include  "msp430g2231.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL1 = INCH_10 + ADC10DIV_3 + CONSEQ_2;
  ADC10CTL0 = SREF_1 + ADC10SHT_3 + MSC + REFON + ADC10ON + ADC10IE;
  __enable_interrupt();                     // Enable interrupts.
  TACCR0 = 30;                              // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
  TACTL = TASSEL_2 + MC_1;                  // TACLK = SMCLK, Up mode.
  LPM0;                                     // Wait for delay.
  TACCTL0 &= ~CCIE;                         // Disable timer Interrupt
  __disable_interrupt();
  ADC10DTC1 = 0x20;                         // 32 conversions
  P1DIR |= 0x01;                            // Set P1.0 output

  for (;;)
  {
    ADC10CTL0 &= ~ENC;                      //
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    ADC10SA = 0x200;                        // Data buffer start
    P1OUT |= 0x01;                          // P1.0 = 1
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    P1OUT &= ~0x01;                         // P1.0 = 0
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

#pragma vector=TIMERA0_VECTOR
__interrupt void ta0_isr(void)
{
  TACTL = 0;
  LPM0_EXIT;                                // Exit LPM0 on return
}

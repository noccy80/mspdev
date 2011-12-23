//******************************************************************************
//  MSP430F22x4 Demo - ADC10, DTC Sample A10 32x to Flash, Int Ref, DCO
//
//  Description: Use DTC to sample A10 32x, Int reference, and transfer
//  code directly to Flash. Software writes to ADC10SC to trigger sample
//  burst. Timing for Flash programming is important and must meet the device
//  f(FTG) datasheet specification ~ 257kHz - 476kHz
//  Assume default DCO = SMCLK ~1.2MHz.
//  As programmed;
//  Each ADC10 sample & convert = (64+13)*2/SMCLK = 154/SMCLK = 128us
//  Flash write per word = 30/(SMCLK/3) = 90/SMCLK = 75us
//  Enough time is provided between ADC10 conversions for each word moved by
//  the DTC to Flash to program. DTC transfers ADC10 code to Flash 1080h-10BEh.
//  In the Mainloop, the MSP430 waits in LPM0 during conversion and programming,
//  ADC10_ISR(DTC) will force exit from LPM0 in Mainloop on reti.
//
//               MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |A10              |
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL1 = INCH_10 + ADC10DIV_1 + ADC10SSEL_3 + CONSEQ_2;
  ADC10CTL0 = SREF_1 + ADC10SHT_3 + MSC + REFON + ADC10ON + ADC10IE;
  TACCR0 = 1500;                            // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt
  TACTL = TASSEL_2 + MC_1;                  // TACLK = SMCLK, Up mode
  __bis_SR_register(CPUOFF + GIE);          // LPM0, TA0_ISR will force exit
  TACCTL0 &= ~CCIE;                         // Disable timer Interrupt
  ADC10DTC1 = 0x20;                         // 32 conversions
  FCTL2 = FWKEY + FSSEL_2 + FN1;            // SMCLK/3

  for (;;)
  {
    FCTL3 = FWKEY;                          // Lock = 0
    FCTL1 = FWKEY + ERASE;                  // Erase bit = 1
    *(unsigned int *)0x1080 = 0;            // Dummy write to erase Flash seg
    ADC10CTL0 &= ~ENC;
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    ADC10SA = 0x1080;                       // Data buffer start
    FCTL1 = FWKEY + WRT;                    // Write bit = 1
    ADC10CTL0 |= ENC + ADC10SC;             // Start sampling
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    FCTL3 = FWKEY + LOCK;                   // Lock = 1
    __no_operation();                       // << SET BREAKPOINT HERE
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

#pragma vector=TIMERA0_VECTOR
__interrupt void TA0_ISR(void)
{
  TACTL = 0;                                // Clear Timer_A control registers
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

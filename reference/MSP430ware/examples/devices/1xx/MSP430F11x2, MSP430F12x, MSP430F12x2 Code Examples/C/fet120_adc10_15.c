//******************************************************************************
//  MSP-FET430P120 Demo - ADC10, DTC Sample A10 32x to Flash, Int Ref, DCO
//
//  Description: Use DTC to sample A10 32x, Int reference, and transfer
//  code directly to Flash. Software writes to ADC10SC to trigger sample
//  burst. Timing for Flash programming is important and must meet the device
//  f(FTG) datasheet specification ~ (257kHz)/35 - (476kHz)/35
//  Assume default DCO = SMCLK ~ 800kHz.
//  As programmed;
//  Each ADC10 sample & convert = (SMCLK)/(64+13) = SMCLK/77 = 96us
//  Flash write per word = (SMCLK/2)/35 = SMCLK/70 = 88us
//  Enough time is provided between ADC10 conversions for each word moved by
//  the DTC to Flash to program. DTC transfers ADC10 code to Flash 1080h-10BEh.
//  In the Mainloop, MSP430 waits in LPM0 durring conversion and programming,
//  ADC10_ISR(DTC) will force exit from any LPMx in Mainloop on reti.
//  //* MSP430F12x2 or MSP430F11x2 Device Required *//
//
//               MSP430F1232
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |A10              |
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
  ADC10CTL1 = INCH_10 + ADC10SSEL_3 + CONSEQ_2;
  ADC10CTL0 = SREF_1 + ADC10SHT_3 + MSC + REFON + ADC10ON + ADC10IE;
  _EINT();                                  // Enable interrupts.
  TACCR0 = 1500;                            // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
  TACTL = TASSEL_2 | MC_1;                  // TACLK = SMCLK, Up mode.
  LPM0;                                     // Wait for delay.
  TACCTL0 &= ~CCIE;                         // Disable timer Interrupt
  _DINT();
  ADC10DTC1 = 0x20;                         // 32 conversions
  FCTL2 = FWKEY + FSSEL_2 + FN0;            // SMCLK/2

  for (;;)
  {
   FCTL3 = FWKEY;                           // Lock = 0
   FCTL1 = FWKEY+ERASE;                     // Erase bit = 1
   *(unsigned int *)0x1080 = 0;             // Dummy write to erase Flash segment

    ADC10CTL0 &= ~ENC;
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    ADC10SA = 0x1080;                       // Data buffer start
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion ready

    FCTL1 = FWKEY + WRT;                    // Write bit = 1
    ADC10CTL0 |= ENC + ADC10SC;             // Start sampling
    _BIS_SR(CPUOFF + GIE);                  // LPM0, ADC10_ISR will force exit
    FCTL3 = FWKEY + LOCK;                   // Lock = 1
    _NOP();                                 // << SET BREAKPOINT HERE
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
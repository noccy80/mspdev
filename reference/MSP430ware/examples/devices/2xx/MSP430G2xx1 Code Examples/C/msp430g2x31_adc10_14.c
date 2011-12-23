//******************************************************************************
//   MSP430G2x31 Demo - ADC10, DTC Sample A1-0 16x, AVcc, Repeat Seq, DCO
//
//  Description: Use DTC to sample A1/A0 repeat sequence 16x(32 total samples)
//  with reference to AVcc.  Software sets ADC10SC to trigger sample burst.
//  In Mainloop MSP430 waits in LPM0 to save power until ADC10 conversion
//  complete, ADC10_ISR will force exit from any LPMx in Mainloop on reti.
//  ADC10 internal oscillator times sample period (16x) and conversion (13x).
//  DTC transfers conversion code to RAM 200h - 240h.  ADC10(DTC) interrupt
//  will return system active. P1.0 set at start of conversion burst, reset
//  on completion.
//
//               MSP430G2x31
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//       >---|P1.1/A1          |
//       >---|P1.0/A0          |
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
  ADC10CTL1 = INCH_1 + CONSEQ_3;            // A1/A0, repeat multi channel
  ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE;
  ADC10AE0 = 0x03;                          // P1.0,1 ADC option select
  ADC10DTC1 = 0x20;                         // 16 conversions

  for (;;)
  {
    ADC10CTL0 &= ~ENC;
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    ADC10SA = 0x200;                        // Data buffer start
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion ready
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    _NOP();                                 // space for debugger
    _NOP();                                 // Set Breakpoint here to read ADC
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

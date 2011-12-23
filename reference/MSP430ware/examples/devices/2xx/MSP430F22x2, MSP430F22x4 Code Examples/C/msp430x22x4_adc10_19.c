//******************************************************************************
//   MSP430F22x4 Demo - ADC10, DTC Sample A0 64x, AVcc, HF XTAL
//
//   Description: For non-low power applications HF XTAL can source ACLK and be
//   used also for CPU MCLK, as in this example. DTC always uses MCLK for data
//   transfer. Though not required, ADC10 can also clock from HF XTAL as in this
//   example using ACLK.
//   MCLK = ACLK = ADC10CLK = HF XTAL in this example.
//   DTC Used to sample A0 64 times with reference to AVcc. Software writes to
//   ADC10SC to trigger sample burst. In Mainloop MSP430 waits in LPM0 to save
//   power until ADC10 conversion burst complete, ADC10_ISR(DTC) will force
//   exit from LPM0 in Mainloop on reti. In this example ACLK times sample
//   period (16x) and conversion (13x). DTC transfers conversion code to RAM
//   200h - 280h. P1.0 set at start of conversion burst, reset on completion.
//   //* HF XTAL NOT INSTALLED ON FET *//
//
//                MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 | HF XTAL (3 – 16MHz crystal or resonator)
//          --|RST          XOUT|-
//            |                 |
//        >---|P2.0/A0      P1.0|-->LED
//
//   A. Dannenberg
//   Texas Instruments Inc.
//   April 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

volatile unsigned int i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BCSCTL1 |= XTS;                           // LFXT1 = HF XTAL
  BCSCTL3 |= LFXT1S1;                       // LFXT1S1 = 3-16Mhz
  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSC fault flag
    i = 0xFF;                               // i = Delay
    while (i--);                            // Additional delay to ensure start
  }
  while (OFIFG & IFG1);                     // OSC fault flag set?
  BCSCTL2 |= SELM_3;                        // MCLK = LFXT1

  ADC10CTL1 = ADC10SSEL_1 + CONSEQ_2;
  ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE;
  ADC10AE0 |= 0x01;                         // P2.0 ADC option select
  ADC10DTC1 = 0x040;                        // 64 conversions
  P1DIR |= 0x001;                           // P1.0 output

  while(1)
  {
    P1OUT |= 0x01;                          // P1.0 = 1
    ADC10CTL0 &= ~ENC;
    while (BUSY & ADC10CTL1);
    ADC10SA = 0x0200;                       // Data buffer start
    ADC10CTL0 |= ENC + ADC10SC;             // Start sampling
    __bis_SR_register(LPM0_bits + GIE);     // LPM0, ADC12 ISR will force exit
    P1OUT &= ~0x01;                         // P1.0 = 0
  }
}

#pragma vector = ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPM0, interrupts enabled
}


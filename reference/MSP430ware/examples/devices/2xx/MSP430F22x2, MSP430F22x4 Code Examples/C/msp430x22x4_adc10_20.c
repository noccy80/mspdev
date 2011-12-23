//******************************************************************************
//   MSP430F22x4 Demo - ADC10, DTC Sample A0 2-Blk Cont. Mode, AVcc, HF XTAL
//
//   Description: For non-low power applications HF XTAL can source ACLK and be
//   used also for CPU MCLK, as in this example. DTC always uses MCLK for data
//   transfer. Though not required, ADC10 can also clock from HF XTAL as in this
//   example using MCLK.
//   MCLK = ACLK = ADC10CLK = HF XTAL in this example.
//   DTC used to sample A0 with reference to AVcc. Software writes once to
//   ADC10SC to trigger continous sampling. DTC configured to transfer code
//   into two 16-word blocks at RAM 200h - 240h. Mainloop jumps to itself.
//   MCLK times sample period (8x) and conversion (13x). For demostration
//   puspose, ADC10_ISR(DTC) used to set P1.1 at completion of first block
//   transfer, reset at completion of second block transfer. Toggle rate on P1.1
//   is then calculated as MCLK/(21*16*2)
//   //* HF XTAL NOT INSTALLED ON FET *//
//   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//
//                MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 | HF XTAL (3 – 16MHz crystal or resonator)
//          --|RST          XOUT|-
//            |                 |
//        >---|P2.0/A0      P1.1|-->MCLK/672
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

  ADC10CTL1 = ADC10SSEL_2 + CONSEQ_2;
  ADC10CTL0 = ADC10SHT_1 + MSC + ADC10ON + ADC10IE;
  ADC10AE0 |= 0x01;                         // P2.0 ADC option select
  ADC10DTC0 |= ADC10TB + ADC10CT;           // Continous two block transfers
  ADC10DTC1 = 0x010;                        // 16*2 conversions
  P1DIR |= 0x02;                            // P1.1 output
  ADC10SA = 0x0200;                         // Data buffer start
  ADC10CTL0 |= ENC + ADC10SC;               // Start sampling continously
  __enable_interrupt();                     // Enable interrupts
  while(1);                                 // Do nothing (and keep MCLK alive)
}

#pragma vector = ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  if (ADC10DTC0 & ADC10B1)
    P1OUT &= ~0x002;                        // P1.1 = 0
  else
    P1OUT |= 0x002;                         // P1.1 = 1
}

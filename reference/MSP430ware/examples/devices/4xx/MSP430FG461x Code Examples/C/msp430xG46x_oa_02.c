//*****************************************************************************
//  MSP430xG46x Demo - OA0, Comparator in General-Purpose Mode
//
//  Description: Use OA0 as a comparator in general-purpose mode. In this
//  example, OA0 is configured for general-purpose mode, but used as a
//  comparator. The reference is supplied by DAC12_0 on the "-" input.
//  The "+" terminal is connected to OA0I0.
//  ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                MSP430xG461x
//             -------------------
//         /|\|                XIN|-
//          | |                   |
//          --|RST            XOUT|-
//            |                   |
//     "+" -->|P6.0/OA0I0         |
//            |                   |
//            |          P6.1/OA0O|--> OA0 Output
//            |                   |    Output goes high when
//            |                   |    Input > 1.5V
//
// K. Quiring / A. Dannenberg
// Texas Instruments Inc.
// June 2007
// Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//*****************************************************************************
#include  <msp430xG46x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  ADC12CTL0 = REFON + REF2_5V;              // Reference = 2.5V for DAC0
  DAC12_0CTL = DAC12IR + DAC12AMP_2 + DAC12ENC;
  DAC12_0DAT = 0x099a;                      // Reference level = 1.5V

  OA0CTL0 = OAN_2 + OAPM_1;                 // Select inputs, power mode
  OA0CTL1 = OARRIP;                         // General purpose (default),
                                            // limited range (see datasheet)

  __bis_SR_register(LPM3_bits + GIE);       // LPM3
}

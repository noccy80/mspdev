//*****************************************************************************
//  MSP-FET430P430 Demo - OA1, Comparator in General-Purpose Mode
//
//  Description: Use OA1 as a comparator in general-purpose mode. In this
//  example, OA1 is configured for general-purpose mode, but used as a
//  comparator. The reference is supplied by DAC12_0 on the "-" input.
//  The "+" terminal is connected to OA1I0.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430FG439
//             -------------------
//         /|\|                XIN|-
//          | |                   |
//          --|RST            XOUT|-
//            |                   |
//     "+" -->|P6.4/OA1I0         |
//            |                   |
//            |          P6.3/OA1O|--> OA1 Output
//            |                   |    Output goes high when
//            |                   |    Input > 1.5V
//
//  M. Mitchell
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include  <msp430xG43x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  ADC12CTL0 = REFON + REF2_5V;              // Reference = 2.5V for DAC0
  DAC12_0CTL = DAC12IR + DAC12AMP_2 + DAC12ENC;
  DAC12_0DAT = 0x099A;                      // Reference level = 1.5 V

  OA1CTL0 = OAN_2 + OAPM_1;                 // Select inputs, power mode
  OA1CTL1 = OARRIP;                         // Mode, rail-to-rail input

  LPM3;                                     // LPM3
}


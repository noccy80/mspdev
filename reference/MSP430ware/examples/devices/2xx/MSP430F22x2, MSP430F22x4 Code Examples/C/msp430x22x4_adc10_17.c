//******************************************************************************
//   MSP430F22x4 Demo - ADC10, DTC Sample A0 -> TA1, AVcc, HF XTAL
//
//   Description: Use DTC to sample A0 with reference to AVcc continously and
//   directly transfer code to Timer_A CCR1 output unit. Timer_A has been
//   configured for 10-bit PWM mode. CCR1 duty cycle is automatically
//   proportional to ADC10 A0. No CPU resources are required and in this
//   example the CPU is turned off. ADC10 A0 sampling and transfer to TA1 done
//   continuously and automatically by the DTC.
//   MCLK = SMCLK = HF XTAL = 8MHz, ACLK = (HF XTAL)/8
//   As coded, ADC10CLK = ACLK/8 = 125kHz, and each A0 sample and transfer to
//   TA1 requires 77 ADC10CLK. With an 8MHz HF XTAL, loop transfer rate is
//   125k/77 = 1623/second.
//   //* An external HF XTAL on XIN XOUT is required for ACLK *//
//
//                MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 | HF XTAL (3 – 16MHz crystal or resonator)
//          --|RST          XOUT|-
//            |                 |
//        >---|P2.0/A0      P1.2|--> TACCR1 - 0-1024 PWM
//
//   A. Dannenberg
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

volatile unsigned int i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BCSCTL1 |= XTS + DIVA_3;                  // ACLK = (LFXT1 = HF XTAL)/8
  BCSCTL3 |= LFXT1S1;                       // LFXT1S1 = 3-16Mhz
  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSC fault flag
    i = 0xFF;                               // i = Delay
    while (i--);                            // Additional delay to ensure start
  }
  while (OFIFG & IFG1);                     // OSC fault flag set?
  BCSCTL2 |= SELM_3 + SELS;                 // MCLK = SMCLK = LFXT1

  P1DIR |= 0x04;                            // P1.2 = output
  P1SEL |= 0x04;                            // P1.2 = TA1 outputs
  TACCR0 = 1024 - 1;                        // PWM Period
  TACCTL1 = OUTMOD_7;                       // TACCR1 reset/set
  TACCR1 = 512;                             // TACCR1 PWM Duty Cycle
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode
  ADC10CTL1 = ADC10DIV_7 + ADC10SSEL_1 + CONSEQ_2; // ACLK
  ADC10CTL0 = ADC10SHT_3 + MSC + ADC10ON;   // 64x, multi conv.
  ADC10AE0 |= 0x01;                         // P2.0 ADC option select
  ADC10DTC0 |= ADC10CT;                     // Continous transfers
  ADC10DTC1 = 0x001;                        // 1 conversion location
  ADC10SA = (unsigned int)&TACCR1;          // Data trasfer location
  ADC10CTL0 |= ENC + ADC10SC;               // Start sampling
  __bis_SR_register(LPM0_bits);             // CPU not required
}

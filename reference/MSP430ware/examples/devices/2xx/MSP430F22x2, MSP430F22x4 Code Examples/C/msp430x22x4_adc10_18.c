//******************************************************************************
//   MSP430F22x4 Demo - ADC10, DTC Sample A1/0 -> TA1/2, 2.5V, HF XTAL
//
//   Description: Use DTC to sample both A1 and A0 with reference to internal
//   2.5V Vref continously and directly transfer codes to Timer_A CCR1 and CCR2
//   output units. Timer_A has been configured for 10-bit PWM mode. TACCR1 and
//   TACCR2 duty cycles are automatically proportional to ADC10 A1 and A0
//   respectively. No CPU resources are required and in this example the CPU is
//   turned off. ADC10 A1/A0 sampling and transfers to TA1/TA2 done continously
//   and automatically by the DTC.
//   MCLK = SMCLK = HF XTAL = 8MHz, ACLK = (HF XTAL)/8
//   As coded, ADC10CLK = ACLK/8 = 125kHz, and each Ax sample and transfer to
//   TAx requires 77 ADC10CLK. With an 8MHz HF XTAL, loop transfer rate is
//   125k/(2*77) = 812/second.
//   //* An external 8MHz XTAL on XIN XOUT is required for ACLK *//
//   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//
//                MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 | HF XTAL (3 – 16MHz crystal or resonator)
//          --|RST          XOUT|-
//            |                 |
//        >---|P2.1/A1      P1.2|--> TACCR1 - 0-1024 PWM
//        >---|P2.0/A0      P1.3|--> TACCR2 - 0-1024 PWM
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

  P1DIR |= 0x0C;                            // P1.2/P1.3 = outputs
  P1SEL |= 0x0C;                            // P1.2/P1.2 = TA1/TA2 outputs
  TACCTL1 = OUTMOD_7;                       // TACCR1 reset/set
  TACCR1 = 512;                             // TACCR1 PWM Duty Cycle
  TACCTL2 = OUTMOD_7;                       // TACCR2 reset/set
  TACCR2 = 512;                             // TACCR2 PWM Duty Cycle
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode
  ADC10CTL1 = INCH_1 + ADC10DIV_7 + ADC10SSEL_1 + CONSEQ_3; // ACLK
  ADC10CTL0 = SREF_1 + ADC10SHT_3 + MSC + REF2_5V + REFON + ADC10ON;
  TACCR0 = 30;                              // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
  TACTL = TACLR + MC_1 + TASSEL_2;          // up mode, SMCLK
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0,enable interrupts
  TACCTL0 &= ~CCIE;                         // Disable timer interrupt
  TACCR0 = 1024 - 1;                        // PWM Period
  ADC10AE0 |= 0x03;                         // P2.0/P2.1 ADC option select
  ADC10DTC0 |= ADC10CT;                     // Continous transfers
  ADC10DTC1 = 0x02;                         // 2 conversion locations
  ADC10SA = (unsigned int)&TACCR1;          // First data trasfer location
  ADC10CTL0 |= ENC + ADC10SC;               // Start sampling
  __bis_SR_register(LPM0_bits);             // CPU not required
}

#pragma vector = TIMERA0_VECTOR
__interrupt void TA0_ISR(void)
{
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPM0, interrupts enabled
}

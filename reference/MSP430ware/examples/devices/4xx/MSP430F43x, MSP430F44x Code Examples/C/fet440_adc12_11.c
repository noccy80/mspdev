//******************************************************************************
//  MSP-FET430P440 Demo - ADC12, Sample A10 Temp and Convert to oC, TA1 Trigger
//
//  Description: Use the ADC12's integrated temperature sensor to measure
//  temperature. Sample time is set for 125 ADC12CLK cycles to allow 30us for
//  the integrated temperature sensor (see datasheet). ADC12 is operated in
//  repeat-single-channel mode with the sample and convert trigger sourced
//  from Timer_A CCR1. Timer_A is configured for continuous mode and is clocked
//  by SMCLK. TA1 is set for toggle mode triggering the ADC12 every 125ms.
//  The ADC12MEM0_IFG bit set at the end of each conversion triggers an ISR.
//  Normal mode is LPM0.
//  ACLK = LFXT1 = 32768, MCLK = SMCLK = DCO = 32xACLK = 1048576Hz,
//  ADC12CLK = ADC12OSC
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//  Uncalibrated temperature measured from device to devive will vary do to
//  slope and offset variance from device to device - please see datasheet.
//
//                MSP430F449
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32KHZ
//          --|RST          XOUT|-
//            |                 |
//            |A10 (Temp)   P5.1|-->LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include  <msp430x44x.h>

int long temp;
int long IntDegC;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P5DIR = 0x02;                             // Set P5.2 as output
  ADC12CTL1 = SHS_1 + SHP + CONSEQ_2;       // TA1, samp timer, rpt
  ADC12MCTL0 = SREF_1 + INCH_10;            // VRef+, A10
  ADC12IE = 0x01;                           // Enable ADC12MEM0 interrupt
  ADC12CTL0 = SHT0_7 + REFON + ADC12ON + ENC; // sample for 192 ADC12CLK cycles
  TACCTL1 = OUTMOD_4;                       // Toggle
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, cont-mode

  while(1)
  {
    _BIS_SR(LPM0_bits + GIE);
    //  oC = ((x/4096)*1500mV)-986mV)*1/3.55mV = x*423/4096 - 278
    IntDegC = (temp - 2692) * 423;
    IntDegC = IntDegC / 4096;
    _NOP();                                 // SET BREAKPOINT HERE
  }
 }

// ADC12 Interrupt Service Routine
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  temp = ADC12MEM0;                         // IFG is cleared
  _BIC_SR_IRQ(CPUOFF);                      // Exit LPM0
  P5OUT ^= 0x02;                            // Toggle LED
}

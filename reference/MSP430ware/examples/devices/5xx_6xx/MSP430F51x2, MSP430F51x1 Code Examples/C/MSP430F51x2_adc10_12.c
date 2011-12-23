//******************************************************************************
//  MSP430F51x2 Demo - ADC10, Sample A5, 1.5V Ref, TA0.0 Trig, Ultra-Low Pwr
//
//  Description: A5 is sampled 1024/second (32xACLK) with Vref = internal 1.5V.
//  All activity is interrupt driven with proper usage of MSP430 low-power
//  modes, ADC10 and Vref demonstrated. Timer_A0 used in upmode to drive ADC10 
//  conversion (continuous mode can also be used).
//  Inside of TA0_ISR software will enable ADC10 and internal reference and
//  allow > 75us delay for Vref to stabilize prior to sample start. Sample
//  start is automatically triggered by TA0 every 32 ACLK cycles. ADC10_ISR
//  will disable ADC10 and Vref and compare ADC10 conversion code. Internal
//  oscillator times sample (16x) and conversion (13x). If A5 > 0.2V, P1.0 is
//  set, else reset. Standy mode is LPM3.
//  //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//                    +-----(0.9766us)---------\\------------------>+
//    TA0_ISR        TA0.0      ADC10_ISR             TA0_ISR        TA0.0
//  -----+------------+------------+-----------\\------+------------+----->
//   Enable ADC    Trigger ADC  Disable ADC, 
//   and Vref                   Ref; Compare
//       +-( ~75us--->+
//
//               MSP430F51x2
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//       >---|P1.5/A5     P1.0 |--> LED
//           |             P3.7|-->TA0.0 (ADC trigger signal)

//
//  B. Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  // Port I/O config
  P1DIR |= BIT0;                            // Set P1.0 to output direction
  P1OUT &= ~BIT0;
  P3DIR |= BIT7;                            // P3.7/TA0.0 output
  P3SEL |= BIT7;                            // TA0.0 options select  
  
  // Configure XT1
  PJSEL |= BIT4+BIT5;                       // Port select XT1
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap
  UCSCTL3 = 0;                              // FLL Reference Clock = XT1
  
  // Loop until XT2 & DCO stabilizes - In this case loop until XT1 and DCo settle
  do
  {
    UCSCTL7 &= ~(XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag  
  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive strength
  UCSCTL4 |= SELA_0;                        // ACLK = LFTX1 (by default)
  
  // Configure ADC
  ADC10CTL1 |= ADC10SHS_1;                  // TA0.0 trigger sample start
  ADC10CTL2 |= ADC10RES;                    // 10-bit conversion results
  ADC10MCTL0 |= ADC10INCH_5;                // A5 ADC input select;  
 
  // By default, REFMSTR=1 => REFCTL is used to configure the internal reference
  while(REFCTL0 & REFGENBUSY);              // If ref generator busy, WAIT                                          
  REFCTL0 |= REFVSEL_0;                     // Select internal ref = 1.5V 
                                               
  // Configure Timer (TA0.0 - see device specific d/s) -> ADC conversion trigger
  TA0CCR0 = 32-1;                            // PWM Period
  TA0CCTL0 = OUTMOD_4 + CCIE;                // TACCR1 toggle; enable interrupt
  TA0CTL = TASSEL_1 + MC_1 + TACLR;          // ACLK, up mode
  __bis_SR_register(LPM3_bits + GIE);        // Enter LPM3, enable interrupts
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  ADC10CTL0 &= ~ADC10ENC;                    // ADC10 ENC reset in order to 
                                             // modify ADC10CTL and MCTL registers
  switch(__even_in_range(ADC10IV,12))
  {
    case  0: break;                          // No interrupt
    case  2: break;                          // conversion result overflow
    case  4: break;                          // conversion time overflow
    case  6: break;                          // ADC10HI
    case  8: break;                          // ADC10LO
    case 10: break;                          // ADC10IN
    case 12: 
      ADC10CTL0 &= ~ADC10ON;                 // ADC10 disabled completely
      ADC10MCTL0 &= ~ADC10SREF_1;            // Clear internal Reference Vref+ select
      REFCTL0 &= ~REFON;                     // Turn off internal shared reference
      if (ADC10MEM0 < 0x88)                  // ADC10MEM0 = A5 < 0.2V?
         P1OUT &= ~0x01;                     // Clear P1.0 LED off
      else
         P1OUT |= 0x01;                      // Set P1.0 LED on                                         
      break;                                 // Clear CPUOFF bit from 0(SR)                         
    default: break; 
  }   
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
  ADC10MCTL0 |= ADC10SREF_1;                // reference = Vref+
  ADC10CTL0 |= ADC10SHT_2 + ADC10ON;        // 16xADC clock cycles, ADC10ON 
  while(REFCTL0 & REFGENBUSY);              // If ref generator busy, WAIT                                          
  REFCTL0 |= REFON;                         // Internal Reference ON  
  __delay_cycles(80);                       // Reference settling time
  ADC10IE |= ADC10IE0;                      // Enable ADC conv complete interrupt
  ADC10CTL0 |= ADC10ENC;                    // ADC10 enable 
}
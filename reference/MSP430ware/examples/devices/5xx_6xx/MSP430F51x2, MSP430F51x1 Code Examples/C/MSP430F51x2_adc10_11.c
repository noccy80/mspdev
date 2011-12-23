//******************************************************************************
//  MSP430F51x2 Demo - ADC10, Sample A1, 1.5V Ref, TA0 Trig, Set P1.0 if A1>0.5V
//
//  Description: A1 is sampled 16/second (ACLK/1024) with reference to 1.5V.
//  Timer_A is run in upmode and TA0.0 is used to automatically trigger
//  ADC10 conversion. Internal oscillator times sample (16x) and conversion 
//  (13x).Inside ADC10_ISR if A1 > 0.5V, P1.0 is set, else reset. Normal mode 
//  is LPM3.
//  //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//               MSP430F51x2
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//       >---|P1.1/A1     P1.0 |--> LED
//           |             P3.7|--> TA0.0 (ADC trigger signal)
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
  P1DIR |= BIT0;                            // Set P1.0 to output direction
  P1OUT &= ~BIT0;                           // Clear P1.0
  
  P3DIR |= BIT7;                            // P3.7/TA0.0 output                            
  P3SEL |= BIT7;                            // TA0.0 function select
  
  // Configure Xt1
  PJSEL |= BIT4+BIT5;                       // Port select XT1
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap
  UCSCTL3 = 0;                              // FLL Reference Clock = XT1
  // Loop until XT1 & DCO stabilizes - In this case loop until XT1 and DCo settle
  do
  {
    UCSCTL7 &= ~(XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag  
  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive strength
  UCSCTL4 |= SELA_0;                        // ACLK = LFTX1 (by default)

  // Configure ADC10 
  ADC10CTL0 |= ADC10ON + ADC10MSC;                     // ADC10ON
  ADC10CTL1 |= ADC10SHS_1 + ADC10CONSEQ_2;  // rpt single ch; TA0 trig sample start
  ADC10CTL2 |= ADC10RES;                    // 10-bit conversion results
  ADC10MCTL0 |= ADC10INCH_1 + ADC10SREF_1;  // A1 ADC input select; Vref=1.5V

  // By default, REFMSTR=1 => REFCTL is used to configure the internal reference
  while(REFCTL0 & REFGENBUSY);              // If ref generator busy, WAIT                                          
  REFCTL0 |= REFVSEL_0+REFON;               // Select internal ref = 1.5V 
                                            // Internal Reference ON   
  // Reference settling time ~ 75us
  TA0CCR0 = 80;                              // Delay to allow Ref to settle
  TA0CCTL0 |= CCIE;                          // Compare-mode interrupt
  TA0CTL = TASSEL_2 + MC_1;                  // TACLK = SMCLK, Up mode
  __bis_SR_register(CPUOFF + GIE);           // LPM0, TA0_ISR will force exit
  TA0CCTL0 &= ~CCIE;                         // Disable timer Interrupt
  
  ADC10CTL0 |= ADC10ENC;                     // ADC10 Enable
  ADC10IE |= ADC10IE0;                       // Enable ADC conv complete interrupt
  
  // ADC conversion trigger signal - TimerA0.0 (32ms ON-period)
  TA0CCR0 = 1024-1;                          // PWM Period
  TA0CCTL0 = OUTMOD_4;                       // TA0CCR0 toggle
  TA0CTL = TASSEL_1 + MC_1 + TACLR;          // ACLK, up mode

  __bis_SR_register(LPM3_bits + GIE);        // Enter LPM3 w/ interrupts
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  switch(__even_in_range(ADC10IV,12))
  {
    case  0: break;                          // No interrupt
    case  2: break;                          // conversion result overflow
    case  4: break;                          // conversion time overflow
    case  6: break;                          // ADC10HI
    case  8: break;                          // ADC10LO
    case 10: break;                          // ADC10IN
    case 12: if (ADC10MEM0 < 0x155)          // ADC10MEM = A0 < 0.5V?
                P1OUT &= ~BIT0;              // Clear P1.0 LED off
             else
                P1OUT |= BIT0;               // Set P1.0 LED on                                           
             break;                          // Clear CPUOFF bit from 0(SR)                         
    default: break; 
  }   
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR(void)
{
  // Internal Reference settling time delay elapsed
  TA0CTL = 0;                                // Clear Timer_A control registers
  __bic_SR_register_on_exit(CPUOFF);         // Clear CPUOFF bit from 0(SR)
}


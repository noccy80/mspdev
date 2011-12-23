//******************************************************************************
//  MSP430F51x2 Demo - ADC10, Window Comparator, 2.5V Timer trigger, DCO
//
//  Description; A1 is sampled in every 0.5s using the TA0.0 trigger in single 
//  ch/conversion mode. Window comparator is used to generate interrupts to
//  indicate when the input voltage goes above the High_Threshold or below the 
//  Low_Threshold or is inbetween the high and low thresholds. TimerD0 is used 
//  as an interval timer used to control the LED at P1.0 to toggle slow/fast 
//  or turn off according to the ADC10 Hi/Lo/IN interupts.
//  ADC10 is configured in pulse sample mode and is triggered by the TA0.0
//
//               MSP430F51x2
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//       >---|P1.1/A1     P1.0 |--> LED 
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

#define High_Threshold 818
#define Low_Threshold 409

unsigned int SlowToggle_Period = 20000-1;
unsigned int FastToggle_Period = 1000-1;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                  // Stop WDT
  
  // Configure ADC10; 
  ADC10CTL0 = ADC10SHT_2 + ADC10ON;         // ADC10ON
  ADC10CTL1 = ADC10SHP + ADC10SHS_1 + ADC10CONSEQ_2;  // rpt single ch; TA0 trig sample start
  ADC10CTL2 = ADC10RES;                     // 10-bit conversion results
  ADC10MCTL0 = ADC10INCH_1 + ADC10SREF_1;   // Vref+, A1
  ADC10HI = High_Threshold;                 // Window Comparator Hi-threshold 
  ADC10LO = Low_Threshold;                  // Window Comparator Lo-threshold
  
 // Configure internal reference
  while(REFCTL0 & REFGENBUSY);              // If ref generator busy, WAIT
  REFCTL0 |= REFVSEL_2+REFON;               // Select internal ref = 2.5V 
                                            // Internal Reference ON   
  __delay_cycles(75);                       // Delay (~75us) for Ref to settle

 
  P1DIR |= BIT0;                            // Set P1.0 output direction
  P1OUT &= ~BIT0;                           // Clear P1.0
  
  // Configure TD0 period-timer
  TD0CCTL0 = CCIE;                          // CCR0 interrupt enabled
  TD0CTL0 = TDSSEL_1 + TDCLR;               // ACLK, clear TAR
  
  // Configure ADC10 timer trigger TA0.0
  TA0CCR0 = 16384-1;                        // PWM Period
  TA0CCTL0 = OUTMOD_4;                      // TA0CCR0 toggle
  TA0CTL = TASSEL_1 + MC_1 + TACLR;         // ACLK, up mode
  
  ADC10IE |= ADC10HIIE + ADC10LOIE + ADC10INIE; // Interrupt enable   
  ADC10CTL0 |= ADC10ENC;                    // Enable conversion
  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  switch(__even_in_range(ADC10IV,12))
  {
    case  0: break;                         // No interrupt
    case  2: break;                         // conversion result overflow
    case  4: break;                         // conversion time overflow
    case  6:                                // ADC10HI
      ADC10IFG &= ~ADC10HIIFG;              // Clear interrupt flag
      TD0CTL0 &= ~MC_1;                     // Turn off Timer                      
      TD0CCR0 = FastToggle_Period;          // Set Timer Period for slow LED toggle
      TD0CTL0 |= MC_1;      
      break;                          

    case  8:                                // ADC10LO
      ADC10IFG &= ~ADC10LOIFG;              // Clear interrupt flag   
      TD0CTL0 &= ~MC_1;                     // Turn off Timer
      P1OUT &= ~BIT0;       
      break;                          
    
    case 10:                                // ADC10IN
      ADC10IFG &= ~ADC10INIFG;              // Clear interrupt flag
      TD0CTL0 &= ~MC_1;                     // Turn off Timer                      
      TD0CCR0 = SlowToggle_Period;          // Set Timer Period for slow LED toggle
      TD0CTL0 |= MC_1;        
      break;                          
    case 12: break;                          // ADC10IFG0                    
    default: break; 
  }   
}

// Timer1 A0 interrupt service routine
#pragma vector=TIMER0_D0_VECTOR
__interrupt void TIMER0_D0_ISR(void)
{
  P1OUT ^= BIT0;                            // Toggle LED P1.0
}

//******************************************************************************
//  MSP430FR57xx Demo - ADC10, Window Comparator, 2.5V ref, Timer trigger, DCO
//
//  Description; A1 is sampled in every 0.5s using the TA0.1 trigger in single 
//  ch/conversion mode. Window comparator is used to generate interrupts to
//  indicate when the input voltage goes above the High_Threshold or below the 
//  Low_Threshold or is inbetween the high and low thresholds. TimerB0 is used 
//  as an interval timer used to control the LED at P1.0 to toggle slow/fast 
//  or turn off according to the ADC10 Hi/Lo/IN interupts.
//  ADC10 is configured in pulse sample mode and is triggered by the TA0.0
//
//               MSP430FR5739
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//       >---|P1.1/A1     P1.0 |--> LED 
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************
#include "msp430fr5739.h"

#define High_Threshold 818 //~2V
#define Low_Threshold 409  //~1V

unsigned int SlowToggle_Period = 20000-1;
unsigned int FastToggle_Period = 1000-1;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                  // Stop WDT
  // Configure SMCLK = 1MHz
  // XT1 Setup 
  PJSEL0 |= BIT4 + BIT5;   
  CSCTL0_H = 0xA5;
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;            // Set max. DCO setting
  CSCTL2 = SELA_0 + SELS_3 + SELM_3;        // set ACLK = XT1; MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_3 + DIVM_3;        // set all dividers 
  CSCTL4 |= XT1DRIVE_0; 
  CSCTL4 &= ~XT1OFF;  
  do
  {
    CSCTL5 &= ~XT1OFFG;
                                            // Clear XT1 fault flag
    SFRIFG1 &= ~OFIFG; 
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  
  // Configure ADC10; 
  ADC10CTL0 = ADC10SHT_2 + ADC10ON;         // ADC10ON
  ADC10CTL1 = ADC10SHP + ADC10SHS_1 + ADC10CONSEQ_2;  // rpt single ch; TA0.1 trigger 
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
  
  // Configure TB0 period-timer
  TB0CCTL0 = CCIE;                          // CCR0 interrupt enabled
  TB0CTL = TBSSEL_1 + TBCLR;                // ACLK, clear TBR
  
  // Configure ADC10 timer trigger TA0.1
  TA0CCR0 = 16384-1;                        // PWM Period
  TA0CCR1 = 8192-1;                         // Dutycycle TA0.1
  TA0CCTL1 = OUTMOD_4;                      // TA0CCR1 toggle
  TA0CTL = TASSEL_1 + MC_1 + TACLR;         // ACLK, up mode
  
  ADC10IE |= ADC10HIIE + ADC10LOIE + ADC10INIE; // Interrupt enable   
  ADC10CTL0 |= ADC10ENC;                    // Enable conversion
  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts
  __no_operation();                         // for debugger
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
    case  6:                                // ADC10HI; A1> 2V
      ADC10IFG &= ~ADC10HIIFG;              // Clear interrupt flag
      TB0CTL &= ~MC_1;                      // Turn off Timer                      
      TB0CCR0 = FastToggle_Period;          // Set Timer Period for slow LED toggle
      TB0CTL |= MC_1;      
      break;                          

    case  8:                                // ADC10LO; A1 < 1V
      ADC10IFG &= ~ADC10LOIFG;              // Clear interrupt flag   
      TB0CTL &= ~MC_1;                      // Turn off Timer
      P1OUT &= ~BIT0;       
      break;                          
    
    case 10:                                // ADC10IN; 1V < A1 < 2V
      ADC10IFG &= ~ADC10INIFG;              // Clear interrupt flag
      TB0CTL &= ~MC_1;                      // Turn off Timer                      
      TB0CCR0 = SlowToggle_Period;          // Set Timer Period for slow LED toggle
      TB0CTL |= MC_1;        
      break;                          
    case 12: break;                          // ADC10IFG0                    
    default: break; 
  }   
}

// Timer1 A0 interrupt service routine
#pragma vector=TIMER0_B0_VECTOR
__interrupt void TIMER0_B0_ISR(void)
{
  P1OUT ^= BIT0;                            // Toggle LED P1.0
}

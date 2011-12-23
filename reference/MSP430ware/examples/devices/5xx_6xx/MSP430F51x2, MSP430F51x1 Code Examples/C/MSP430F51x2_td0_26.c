//******************************************************************************
//  MSP430F51x2 Demo - TimerD0, Dual Input Capture mode, Normal Timer Mode, 
//                                Input Dutycycle measurement
//  Description: This code example implements input capture in dual capture 
//  mode using TimerD in normal timer mode. TD1.1 is configured to output PWM  
//  of 25% dutycycle, that is used as capture input to TD0.1. TD0.1 is 
//  configured as timer input capture and is triggered by both the rising and 
//  falling edges. An external connection between TD1.1 and TD0.1 is required. 
//  Rising and Falling edges are captured in the dual capture mode and the 
//  Period and Dutycycle is computed. If the measured dutycycle is != 25%, then 
//  LED on P1.0 is set. 
//
//  ACLK = LFXT1 = 32kHz; SMCLK = MCLK = 2.45MHz; 
//
//                 MSP430F51x2
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |       P1.7/TD0.1|<-- CCI1A <-| 
//            |       P2.2/TD1.1|--> CCR1 -->| 
//            |                 |
//            |             P1.0|--> LED "ON" if measured Dutycycle != 25%
//            |                 |

//
//  B. Nisarga
//  Texas Instruments Inc.
//  Nov 2010
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include  "msp430f5172.h"

unsigned char Count = 0x0;
unsigned int REdge1, REdge2, FEdge1, FEdge2;

void main(void)
{
  unsigned int Period, ON_Period;
  unsigned char DutyCycle;
  
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer 

  P1DIR |= BIT0;                            // P1.0/LED Output
  P1OUT &= ~BIT0;                           // LED off
  
  // Configure XT1
  PJSEL |= BIT4+BIT5;                       // Port select XT1  
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap
  
  // Loop until XT1 fault flag is cleared
  do
  {
    UCSCTL7 &= ~XT1LFOFFG;                  // Clear XT1 fault flags
  }while (UCSCTL7&XT1LFOFFG);               // Test XT1 fault flag

  // Initialize DCO to 2.45MHz
  __bis_SR_register(SCG0);                  // Disable the FLL control loop
  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
  UCSCTL1 = DCORSEL_3;                      // Set RSELx for DCO = 4.9 MHz
  UCSCTL2 = FLLD_1 + 74;                    // Set DCO Multiplier for 2.45MHz
                                            // (N + 1) * FLLRef = Fdco
                                            // (74 + 1) * 32768 = 2.45MHz
                                            // Set FLL Div = fDCOCLK/2
  __bic_SR_register(SCG0);                  // Enable the FLL control loop

  // Worst-case settling time for the DCO when the DCO range bits have been
  // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
  // UG for optimization.
  // 32 x 32 x 2.45 MHz / 32,768 Hz = 76563 = MCLK cycles for DCO to settle
  __delay_cycles(76563);

  // Loop until XT1 & DCO fault flag is cleared
  do
  {
    UCSCTL7 &= ~(XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  
  // Configure Port Pins
  P2DIR |= BIT2;                            // P2.2/TD1.1 Output
  P2SEL |= BIT2;                            // TD1.1 Option select
  P1DIR &= ~BIT7;                           // P1.7/TD0.1 Input Capture
  P1SEL |= BIT7;                            // TD0.1 option select
  
  // Configure TD1.1 to output PWM signal 
  // Period = 82/32khz = 2.5ms ~ 400Hz Freq
  TD1CCR0 = 82-1;                          // Period Register
  TD1CCR1 = 21;                            // TD1.1 25% dutycycle
  TD1CCTL1 |= OUTMOD_7;                    // TD1CCR1, Reset/Set
  TD1CTL0 = TDSSEL_1 + MC_1 + TDCLR;       // ACLK, upmode, clear TDR  
  
  // Configure the TD0CCR0 to do input capture
  TD0CTL2 |= TDCAPM1;                      // Channel 1; dual capture mode
  TD0CCTL1 = CAP + CM_3 + CCIE + SCS + CCIS_0;  
                                           // TD0CCR1 Capture mode; CCI1A; Both Rising
                                           // and Falling Edge trigger; interrupt enable
  TD0CTL0 |= TDSSEL_2 + MC_2 + TDCLR;      // SMCLK, Cont Mode; start timer  
  
  while(1)
  {
      __bis_SR_register(LPM0_bits + GIE);   // Enter LPM0
      __no_operation();                     // For debugger  
      // On exiting LPM0
      if (TD0CCTL1 & COV)                   // Check for Capture Overflow
          while(1);                         // Loop Forever
      
      Period = REdge2 - REdge1;             // Calculate Period
      ON_Period = FEdge1-REdge1;             // On period
      DutyCycle = ((unsigned long)ON_Period*100/Period);
      if(DutyCycle!= 25)
      {
          P1OUT |= BIT0;
      }
  }
}

// TD0_D1 Interrupt vector
#pragma vector = TIMER0_D1_VECTOR
__interrupt void TIMER0_D1_ISR (void)
{
  switch(__even_in_range(TD0IV,0x1E))
  {
      case  0x0: break;                     // Vector  0:  No interrupt
      case  0x2:                            // Vector  2:  TDCCR1 CCIFG
        if(!Count)
        {
             FEdge1 = TD0CCR1;				// 1st falling edge
             REdge1 = TD0CL1; 				// 1st rising edge               
             Count++;
        }
        else
        {
              REdge2 = TD0CL1;				// 2nd rising edge
              FEdge2 = TD0CCR1;             // Dummy Read 
              Count = 0x0;
              __bic_SR_register_on_exit(LPM0_bits + GIE);  // Exit LPM0 on return to main 
         }        
         break;                            
      case 0x4: break;                      // Vector  4:  TDCCR2 CCIFG                                            
      case 0x6: break;                      // Vector  6:  TDCCR3 CCIFG
      case 0x8: break;                      // Vector  8:  TDCCR4 CCIFG
      case 0xA: break;                      // Vector 10:  TDCCR5 CCIFG
      case 0xC: break;                      // Vector 12:  TDCCR5 CCIFG
      case 0xE: break;                      // Vector 14:  -
      case 0x10:break;                      // Vector 16:  TDIFG 
      case 0x12:break;                      // Vector 18:  TDHINT TDHFLIFG 
      case 0x14:break;                      // Vector 20:  TDHINT TDHFHIFG 
      case 0x16:break;                      // Vector 22:  TDHINT TDHLKIFG 
      case 0x18:break;                      // Vector 24:  TDHINT TDHUNLKIFG
      case 0x1A:break;                      // Vector 26:  -
      case 0x1C:break;                      // Vector 28:  - 
      case 0x1E:break;                      // Vector 28:  - 
      default: 	break;
  }
}


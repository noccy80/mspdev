//******************************************************************************
//  MSP430x11x1 Demo - Comp_A, Slope ADC to Detect Temp Lvl, Set P1.0 > 25C
//
//  Description: Comparator_A is used to detect a resistance threshold.
//  Discharge times of a 0.1uf capacitor through a 10k-NTC (25C) and 10k ohm
//  reference resistor are compared. If the NTC discharge time is is lower
//  than the 10k referece, P1.0 is set. If the NTC discharge time is higher
//  than reference, P1.0 is reset. The LED is ON if the temperature is greater
//  than 25C.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~800k
//
//               MSP430F1121
//            -----------------
//       /|\ |              XIN|-
//        |  |                 |
//        ---|RST          XOUT|-
//           |                 |
//     +-10k-|P2.0             |
//     |     |                 |	
//     +-NTC-|P2.1             |
//     |     |                 |
//     +-----|P2.3/CA0     P1.0|-->LED
//     |     |                 |
//    ===.1uf|                 |
//     |     |                 |			
//     ------|Vss
//
//           NTC = 10k @25C, (P/N 271-110A Radio Shack)
//
unsigned int sensor_time;
unsigned int ref_time;
unsigned int timer_count;
unsigned int measure(int);                  // measures the time to discharge the capacitor

#define Ref     (0x01)                      // P2.0 = Reference
#define Sensor  (0x02)                      // P2.1 = Sensor
//
//  N. Brenner
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include <msp430x11x1.h>

void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1OUT &= ~0x01;                           // P1.0 reset
  P1DIR |= 0x01;                            // P1.0 output direction
  P2OUT &= ~(Ref + Sensor);                 // Ref set
  P2DIR |= Ref + Sensor;                    // Ref output
  CAPD  |= 0x08;                            // Disconnect port pins
  CACTL1 = CARSEL + CAREF0 + CAON;          // -Comp = 0.25*Vcc - on
  CACTL2 = P2CA0;                           // +Comp = 2.3
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, clear TAR
  _EINT();                                  // Enable interrupts

  while (1)                                 // Mainloop
  {
     sensor_time = measure(Sensor);         // Measure discharge time through sensor
     ref_time = measure(Ref);               // Measure discharge time through Ref
     if (sensor_time < ref_time)            // if sensor time < ref time ( >25c )
      P1OUT |= 0x01;                        // LED on - Set P1.0
     else P1OUT &= ~0x01;                   // LED off - Reset P1.0
  }
}

unsigned int measure(int source) {
  P2OUT |= Ref;                             // Ref Set
  P2DIR |= Ref;                             // Ref output
  CCR1 = TAR + 5000;                        // CCR1 ~ TAR+5ms
  CCTL1 = CCIE;                             // Comp,interrupt
  LPM0;                                     // Wait for CCR1 interrupt
  P2DIR &= ~Ref;                            // Ref = HiZ, Charge complete
  P2OUT &= ~Ref;                            // Ref = Reset
  CCTL1 = CM_2 + CCIS_1 + CAP + CCIE;       // Neg, CCIB,Cap,interrupt
  timer_count = TAR;                        // TAR at before discharge
  P2DIR |= source;                          // Temp = Sensor or Ref
  LPM0;                                     // Wait for CCR1 interrupt
  timer_count = CCR1 - timer_count;         // timer_count = discharge time
  P2DIR &= ~(Sensor + Ref);                 // Disable Sensor or Ref
  CCTL1 = 0x00;                             // Disable CCTL1
  return(timer_count);
}

// Timer A1 interrupt service routine
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
 switch( TAIV )
 {
   case  2: LPM0_EXIT;                      // CCR1
            break;
 }
}

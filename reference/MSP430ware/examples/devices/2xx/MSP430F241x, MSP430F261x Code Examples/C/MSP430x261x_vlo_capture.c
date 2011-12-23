//******************************************************************************
//  MSP430x26x Demo - Basic Clock, VLO-Driven Timer with VLO Compensation
//
//  This example toggles P1.0 approx. every second, using a timer driven by the
//  VLO.  The VLO freq can vary between 4kHz-20kHz, so the timer compare value 
//  must be adjusted to compensate, in order to produce a one-second interval.  
//  So in effect, this code performs a kind of "calibration" of the VLO.  This 
//  is done by counting the number of 1MHz DCO pulses in one ACLK=VLO/8 period, 
//  assigned to dco_delta.  VLO is /8 in order to increase the number of DCO 
//  pulses in one ACLK pulse, increasing the resolution of the measurement, 
//  and therefore the accuracy of the one-second interval.  Since 1,000,000 
//  DCO pulses at 1MHz are required to produce a one-second interval, the 
//  number of VLO/8 pulses in one second is given by 1M/dco_delta.  This value 
//  is loaded into TACCR0 as the timer compare value.  
 
//  MSP430x2xx devices are shipped with calibration values in info memory that,
//  when used by software, allow the DCO to operate within approx. +/-1% of 
//  common values such as 1MHz.  (See the datasheet for add'l information.)  
//  Through the algorithm shown here, this accuracy is extended to the VLO.  An
//  additional source of error in this algorithm is that the VLO/8 freq will 
//  most likely not be evenly divisible by the DCO freq, and therefore up to 
//  one DCO pulse may be lost.  At nominal values, there are 400 1MHz DCO 
//  pulses in one 2.5kHz VLO/8 pulse, so losing one clock pulse produces 
//  ~0.25% error, in addition to the error tolerance of the calibrated DCO.  
//  ACLK = VLO/8, MCLK = SMCLK = 1MHz
//
//                MSP430F261x/241x
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |                 | 
//            |        P1.0/ACLK|-->LED 1 second interrupt
//
//  
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include <msp430x26x.h> 

unsigned int dco_delta;

// Function Prototype
unsigned int  measureVLO( void );

void main(void)
{
  WDTCTL = WDTPW +WDTHOLD;                  // Stop Watchdog Timer
  P1DIR |= 0x01;                            // P1.0 output
 
  dco_delta = measureVLO();                 // dco delta = number of
                                            // 1MHz cycles in 8 VLO cycles
  //Clock settings: DCO freq = 1MHz; ACLK = VLO/8
  
  // Timer A interval interrupt setup
  TACCTL0 = CCIE;                           // TACCR0 interrupt enabled
  TACCR0 = (1000000 / dco_delta);             
  TACTL = TASSEL_1 + MC_1;                  // ACLK, upmode
  P1OUT = 0x01;
  
  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt

}

// Timer_A0 Interrupt Vector 
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}

// This function measures the number of 1MHz clock pulses in 8 VLO cycles
unsigned int  measureVLO( void )
{
  static unsigned int start_count, stop_count;
  // Clock settings to achieve the good resolution for VLO freq measurement
  BCSCTL1 = CALBC1_1MHZ;                    // Set range
  DCOCTL = CALDCO_1MHZ;                     // Set DCO step + modulation
  TACCTL2 = CM_1+CCIS_1+CAP;                // CAP, ACLK
  TACTL = TASSEL_2+MC_2+TACLR;              // SMCLK, cont-mode, clear
  BCSCTL3 |= LFXT1S_2;                      // ACLK = VLO  
  BCSCTL2 = 0x0;
  BCSCTL1 |= DIVA_3;                        // ACLK = VLO/8
  
  TACCTL2 &= ~CCIFG;                        // Clear capture flag
  while (!(CCIFG & TACCTL2));               // Test capture flag to skip 1st cycle
  TACCTL2 &= ~CCIFG;                        // Clear capture flag
  
  while (!(CCIFG & TACCTL2));               // Test capture flag to skip 2nd cycle
  start_count = TACCR2;                     // save hardware captured value
  TACCTL2 &= ~CCIFG;                        // Clear capture flag
  
  while (!(CCIFG & TACCTL2));               // Test capture flag to capture a good clock
  TACTL &= ~MC_3;                           // Stop timer
  stop_count = TACCR2;
  return(stop_count - start_count);         // return
}

//******************************************************************************
//  MSP430G2xx3 Demo - Capacitive Touch, Pin Oscillator Method, 4-buttons
//
//  Description: Basic 4-button input using the built-in pin oscillation feature
//  on GPIO input structure. PinOsc signal feed into TA0CLK. WDT interval is used
//  to gate the measurements. Difference in measurements indicate button touch.
//  LEDs flash if input is touched.
//
//  Input 1: LED1 (LED2 off)
//  Input 2: LED2 (LED1 off)
//  Input 3: Both LEDs on
//  Input 4: Both LEDs flash on/off
//
//  ACLK = VLO = 12kHz, MCLK = SMCLK = 1MHz DCO
//
//               MSP430G2xx3
//             -----------------
//         /|\|              XIN|-
//          | |                 | 
//          --|RST          XOUT|-
//            |                 |
//            |             P1.1|<--Capacitive Touch Input 1
//            |                 |
//  LED 2  <--|P1.6         P1.2|<--Capacitive Touch Input 2
//            |                 |
//  LED 1  <--|P1.0         P1.4|<--Capacitive Touch Input 3
//            |                 |
//            |             P1.5|<--Capacitive Touch Input 4
//
//   Brandon Elliott/D. Dang
//  Texas Instruments Inc.
//  November 2010
//   Built with IAR Embedded Workbench Version: 5.10
//******************************************************************************


#include  "msp430g2553.h"

/* Define User Configuration values */
/*----------------------------------*/
/* Defines WDT SMCLK interval for sensor measurements*/
#define WDT_meas_setting (DIV_SMCLK_512)
/* Defines WDT ACLK interval for delay between measurement cycles*/
#define WDT_delay_setting (DIV_ACLK_512)

/* Sensor settings*/
#define NUM_SEN     4                       // Defines number of sensors
#define KEY_LVL     220                     // Defines threshold for a key press
/*Set to ~ half the max delta expected*/

/* Definitions for use with the WDT settings*/
#define DIV_ACLK_32768  (WDT_ADLY_1000)     // ACLK/32768
#define DIV_ACLK_8192   (WDT_ADLY_250)      // ACLK/8192 
#define DIV_ACLK_512    (WDT_ADLY_16)       // ACLK/512 
#define DIV_ACLK_64     (WDT_ADLY_1_9)      // ACLK/64 
#define DIV_SMCLK_32768 (WDT_MDLY_32)       // SMCLK/32768
#define DIV_SMCLK_8192  (WDT_MDLY_8)        // SMCLK/8192 
#define DIV_SMCLK_512   (WDT_MDLY_0_5)      // SMCLK/512 
#define DIV_SMCLK_64    (WDT_MDLY_0_064)    // SMCLK/64 

#define LED_1   (0x01)                      // P1.0 LED output
#define LED_2   (0x40)                      // P1.6 LED output

// Global variables for sensing
unsigned int base_cnt[NUM_SEN];
unsigned int meas_cnt[NUM_SEN];
int delta_cnt[NUM_SEN];
unsigned char key_press[NUM_SEN];
char key_pressed;
int cycles;
const unsigned char electrode_bit[NUM_SEN]={BIT1, BIT2, BIT4, BIT5};
/* System Routines*/
void measure_count(void);                   // Measures each capacitive sensor
void pulse_LED(void);                       // LED gradient routine

/* Main Function*/
void main(void)
{ 
  unsigned int i,j;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO to 1MHz
  DCOCTL =  CALDCO_1MHZ; 
  BCSCTL3 |= LFXT1S_2;                      // LFXT1 = VLO
  IE1 |= WDTIE;                             // enable WDT interrupt
  P2SEL = 0x00;                             // No XTAL 
  P1DIR = LED_1 + LED_2;                    // P1.0 & P1.6 = LEDs
  P1OUT = 0x00;                             

   __bis_SR_register(GIE);                  // Enable interrupts

  measure_count();                          // Establish baseline capacitance
  for (i = 0; i<NUM_SEN; i++)
    base_cnt[i] = meas_cnt[i];

  for(i=15; i>0; i--)                       // Repeat and avg base measurement
  { 
    measure_count();
    for (j = 0; j<NUM_SEN; j++)
      base_cnt[j] = (meas_cnt[j]+base_cnt[j])/2;
  }
  

  /* Main loop starts here*/
  while (1)
  {
    j = KEY_LVL;
    key_pressed = 0;                        // Assume no keys are pressed

    measure_count();                        // Measure all sensors

    for (i = 0; i<NUM_SEN; i++)
    { 
      delta_cnt[i] = base_cnt[i] - meas_cnt[i];  // Calculate delta: c_change

      /* Handle baseline measurment for a base C decrease*/
      if (delta_cnt[i] < 0)                 // If negative: result increased
      {                                     // beyond baseline, i.e. cap dec
          base_cnt[i] = (base_cnt[i]+meas_cnt[i]) >> 1; // Re-average quickly
          delta_cnt[i] = 0;                 // Zero out for pos determination
      }
      if (delta_cnt[i] > j)                 // Determine if each key is pressed 
      {                                     // per a preset threshold
        key_press[i] = 1;                   // Specific key pressed
        j = delta_cnt[i];
        key_pressed = i+1;                  // key pressed
      }
      else
        key_press[i] = 0;
    }

    /* Delay to next sample, sample more slowly if no keys are pressed*/
    if (key_pressed)
    {
      BCSCTL1 = (BCSCTL1 & 0x0CF) + DIVA_0; // ACLK/(0:1,1:2,2:4,3:8)
      cycles = 20;
    }
    else
    {
      cycles--;
      if (cycles > 0)
        BCSCTL1 = (BCSCTL1 & 0x0CF) + DIVA_0; // ACLK/(0:1,1:2,2:4,3:8)
      else
      {
        BCSCTL1 = (BCSCTL1 & 0x0CF) + DIVA_3; // ACLK/(0:1,1:2,2:4,3:8)
        cycles = 0;
      }
    }
    WDTCTL = WDT_delay_setting;             // WDT, ACLK, interval timer

    /* Handle baseline measurment for a base C increase*/
    if (!key_pressed)                       // Only adjust baseline down 
    {                                       // if no keys are touched
      for (i = 0; i<NUM_SEN; i++)
        base_cnt[i] = base_cnt[i] - 1;      // Adjust baseline down, should be 
    }                                       // slow to accomodate for genuine 
     pulse_LED();                           // changes in sensor C
   
    __bis_SR_register(LPM3_bits);
  }
}                                           // End Main

/* Measure count result (capacitance) of each sensor*/
/* Routine setup for four sensors, not dependent on NUM_SEN value!*/

void measure_count(void)
{ 
  char i;
                     
  TA0CTL = TASSEL_3+MC_2;                   // TACLK, cont mode
  TA0CCTL1 = CM_3+CCIS_2+CAP;               // Pos&Neg,GND,Cap

  for (i = 0; i<NUM_SEN; i++)
  {
    /*Configure Ports for relaxation oscillator*/
    /*The P2SEL2 register allows Timer_A to receive it's clock from a GPIO*/
    /*See the Application Information section of the device datasheet for info*/
    P1DIR &= ~ electrode_bit[i];
    P1SEL &= ~ electrode_bit[i];
    P1SEL2 |= electrode_bit[i];
    
    /*Setup Gate Timer*/
    WDTCTL = WDT_meas_setting;              // WDT, ACLK, interval timer
    TA0CTL |= TACLR;                        // Clear Timer_A TAR
    __bis_SR_register(LPM0_bits+GIE);       // Wait for WDT interrupt
    TA0CCTL1 ^= CCIS0;                      // Create SW capture of CCR1
    meas_cnt[i] = TACCR1;                   // Save result
    WDTCTL = WDTPW + WDTHOLD;               // Stop watchdog timer
    P1SEL2 &= ~electrode_bit[i];
  }

}

void pulse_LED(void)
{ 
  switch (key_pressed){
  case 0: P1OUT &= ~(LED_1 + LED_2);
          break;
  case 1: P1OUT = LED_1;
          break;
  case 2: P1OUT = LED_2;
          break;
  case 3: P1OUT = LED_1 + LED_2;
          break;
  case 4: P1OUT ^= LED_1 + LED_2;
          break;
          
    }
}
/* Watchdog Timer interrupt service routine*/
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  TA0CCTL1 ^= CCIS0;                        // Create SW capture of CCR1
  __bic_SR_register_on_exit(LPM3_bits);     // Exit LPM3 on reti
}

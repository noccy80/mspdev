//******************************************************************************
//  MSP430G2xx3 Demo - Capacitive Touch, Pin Oscillator Method, 5 buttons, UART
//
//  Description: Basic 8-button input using the built-in pin oscillation feature
//  on GPIO input structure. PinOsc signal feed into TA0CLK. WDT interval is used
//  to gate the measurements. Difference in measurements indicate button touch.
//  Pins used for inputs listed in the diagram below. 
//  After each scan, one UART byte identifying the key# being pressed is 
//  transmitted via TimerA UART at port pin P1.1.
//
//
//  ACLK = VLO = 12kHz, MCLK = SMCLK = 1MHz DCO
//
//               MSP430G2xx3
//             -----------------
//         /|\|                 |  
//          | |                 | 
//          --|RST              |
//            |                 |
//  input 1-->|P2.0         P1.1|--> TA UART output TXD
//            |                 |
//  input 2-->|P2.1             |
//            |                 |
//  input 3-->|P2.2             | 
//            |                 |
//  input 4-->|P2.3             |
//            |                 |
//  input 5-->|P2.4             |
//            |                 |
//             -----------------      All five inputs are capacitive touch inputs      
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
#define NUM_SEN        5                    // Total number of sensors
#define KEY_LVL     190                     // Defines threshold for a key press
/* Set to ~ half the max delta expected*/

/* Definitions for use with the WDT settings*/
#define DIV_ACLK_32768  (WDT_ADLY_1000)     // ACLK/32768
#define DIV_ACLK_8192   (WDT_ADLY_250)      // ACLK/8192 
#define DIV_ACLK_512    (WDT_ADLY_16)       // ACLK/512 
#define DIV_ACLK_64     (WDT_ADLY_1_9)      // ACLK/64 
#define DIV_SMCLK_32768 (WDT_MDLY_32)       // SMCLK/32768
#define DIV_SMCLK_8192  (WDT_MDLY_8)        // SMCLK/8192 
#define DIV_SMCLK_512   (WDT_MDLY_0_5)      // SMCLK/512 
#define DIV_SMCLK_64    (WDT_MDLY_0_064)    // SMCLK/64 

/* Global variables for sensing*/
unsigned int base_cnt[NUM_SEN];
unsigned int meas_cnt[NUM_SEN];
int delta_cnt[NUM_SEN];
unsigned char key_press[NUM_SEN];
char key_pressed;
int cycles;

const unsigned char electrode_bit_P2[NUM_SEN]={BIT0, BIT1, BIT2, BIT3, BIT4};
/* System Routines*/
void measure_count(void);                   // Measures each capacitive sensor
void TX_Byte (char);                        // Transmits key pressed via UART
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
    measure_count();                        // Measure all sensors

    for (i = 0; i<NUM_SEN; i++)
    { 
      /* Handle baseline measurment for a base C decrease*/
      if (base_cnt[i] < meas_cnt[i])        // If negative: result increased
      {                                     // beyond baseline, cap decreased
          base_cnt[i] = (base_cnt[i]+meas_cnt[i]) >> 1; // Re-average up quickly
          delta_cnt[i] = 0;                 // Zero out for position determination
      }
       else 
      {
        delta_cnt[i] = base_cnt[i] - meas_cnt[i];  // Calculate delta: c_change
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
      TX_Byte(key_pressed);
      BCSCTL1 = (BCSCTL1 & 0x0CF) + DIVA_0; // ACLK/(0:1,1:2,2:4,3:8)
      cycles = 20;
    }
    else
    {
      cycles--;
      if (cycles > 0)                       // ACLK/(0:1,1:2,2:4,3:8)
        BCSCTL1 = (BCSCTL1 & 0x0CF) + DIVA_0; 
      else
      {                                     // ACLK/(0:1,1:2,2:4,3:8)  
        BCSCTL1 = (BCSCTL1 & 0x0CF) + DIVA_3; 
        cycles = 0;
      }
    }
    WDTCTL = WDT_delay_setting;             // WDT, ACLK, interval timer

    /* Handle baseline measurment for a base C increase*/
    if (!key_pressed)                       // adjust down if no keys touched
    {
      for (i = 0; i<NUM_SEN; i++)
        base_cnt[i] = base_cnt[i] - 1;      // Adjust baseline down, should be 
    }                                       // slow to accomodate for genuine 
   __bis_SR_register(LPM3_bits);            // changes in sensor C
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
    P2DIR &= ~ electrode_bit_P2[i];         
    P2SEL &= ~ electrode_bit_P2[i];         
    P2SEL2 |= electrode_bit_P2[i];          // input oscillation feeds TACLK
    /*  Setup Gate Timer */
    WDTCTL = WDT_meas_setting;              // WDT, ACLK, interval timer
    TA0CTL |= TACLR;                        // Clear Timer_A TAR
    __bis_SR_register(LPM0_bits+GIE);       // Wait for WDT interrupt
    TA0CCTL1 ^= CCIS0;                      // Create SW capture of CCR1
    meas_cnt[i] = TACCR1;                   // Save result
    WDTCTL = WDTPW + WDTHOLD;               // Stop watchdog timer
    P2SEL2 &= ~electrode_bit_P2[i];
  }
    TA0CTL = 0;                             // Stop Timer_A
}

/* Watchdog Timer interrupt service routine*/
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  TA0CCTL1 ^= CCIS0;                        // Create SW capture of CCR1
  __bic_SR_register_on_exit(LPM3_bits);     // Exit LPM3 on reti
}
 

/* UART Information: Conditions for 9600 Baud SW TX-only UART, SMCLK = 8MHz */
#define Bitime    0x0341                    // x us bit length ~ x baud
#define TXD       BIT1                      // TXD on P1.1
unsigned int RXTXData;
unsigned char BitCnt;
void TX_Byte (char TX_DATA)
{
  BCSCTL1 = CALBC1_8MHZ;                    // Set DCO to 8MHz
  DCOCTL =  CALDCO_8MHZ; 
  TX_DATA += '0';                           // Convert key# to ASCII character
  CCTL0 = OUT;                              // TXD Idle as Mark
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, continuous mode
  P1SEL |= TXD;
  P1DIR |= TXD;
  BitCnt = 0xA;                             // Load Bit counter, 8data + ST/SP
  CCR0 = TAR;                               // Current state of TA counter
  CCR0 += Bitime;                           // Some time till first bit
  RXTXData = TX_DATA;
  RXTXData |= 0x100;                        // Add mark stop bit to RXTXData
  RXTXData = RXTXData << 1;                 // Add space start bit
  CCTL0 = CCIS0 + OUTMOD0 + CCIE;           // TXD = mark = idle
  while ( CCTL0 & CCIE )
  {
    __bis_SR_register(LPM0_bits);           // Enter LPM0
  }
  BCSCTL1 = CALBC1_1MHZ;                    // return DCO to 1MHz
  DCOCTL =  CALDCO_1MHZ; 
  P1SEL &= ~TXD;
  TACTL = 0;                                // Stop Timer
}

/* Timer A0 interrupt service routine*/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{
    if (CCTL0 & CCIS0)                  // TX on CCI0B?
    {
      CCR0 += Bitime;                   // Add Offset to CCR0
      if ( BitCnt == 0)
        CCTL0 &= ~ CCIE;                // All bits TXed, disable interrupt
      else
      {
        if (RXTXData & 0x01)
          CCTL0 &= ~ OUTMOD2;           // TX Mark
        else
          CCTL0 |=  OUTMOD2;            // TX Space
        RXTXData = RXTXData >> 1;
        BitCnt --;
      }
      CCTL0 &= ~ CCIFG;
    }
    else                                // for LED gradient only
      TACCTL0 &= ~CCIE;                 // interrupt disbled

    __bic_SR_register_on_exit(LPM0_bits);
}

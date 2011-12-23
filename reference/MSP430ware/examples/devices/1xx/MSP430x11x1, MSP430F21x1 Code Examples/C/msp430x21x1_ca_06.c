//*******************************************************************************
//  MSP430x21x1 Demo - Comp_A, Slope ADC to measure temperature
//
//  Description: This example uses the slope A/D method to measure a thermistor
//  resistance and converts that resistance to temperature. The thermistor is
//  connected to pin P2.1, the reference resistor to P2.0, and the capacitor
//  to P2.3. For the measurement, the capacitor is first charged up fully.
//  Then it is discharged through the reference resistor. The capacitor voltage
//  is tied to the comparator_A's + input with it's minus input tied to the
//  .25Vcc reference of the comparator. The time for the capacitor to discharge
//  through the reference resistor to .25Vcc is measured with Timer_A. The output
//  of the comparator is used to automatically trigger a capture of the Timer_A
//  count value. The capacitor is then fully charged again and discharged through
//  the thermistor in the same way. The ratio of the two discharge times is
//  equivalent to the ratio of the two resistors (thermistor and reference).
//  Since the value of the reference resistor is known, the value of the thermistor
//  can be calculated, and therefore the temperature is known.
//  ACLK = LFXT1 = 32768, MCLK = SMCLK = default DCO
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//	
//
//
//             MSP430F21x1/11x1
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//    +-10K--|P2.0             |
//    |      |                 |
//    +-NTC--|P2.1             |
//    |      |                 |
//    +------|P2.3             |
//    |      |                 |
//   ===2.2  |                 |
//    |      |                 |
//    ------ |VSS              |
//
//   M. Mitchell / A. Dannenberg
//   Texas Instruments, Inc
//   July 2005
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//*******************************************************************************

#include  <msp430x11x1.h>

// Define Inputs/Outputs
#define Ref    (0x01)                       // Reference resistor on P2.0
#define Sensor (0x02)                       // Thermistor on P2.1

// Global variables
unsigned int port_pin, TEMP_SOURCE;         // Temporary holder for passing port pin locations
volatile int TEMP_FTHERM;                   // TEMP_FTHERM = Thermistor temperature reading
long int REF_RES, THERM_RES;                // REF_RES = discharge count for Reference resistor
long int RTHERM;                            // THERM_RES = discharge count for Thermistor
                                            // RTHERM = Thermistor resistance value

// System Routines
void initialize(void);                      // Configure modules and control Registers
unsigned int measure_count(unsigned int);   // measure count value for Thermistor, Reference
                                            // resistor

// Temperature table: Resistance/100 values for 110 deg. F down to 10 deg. F, according
// to the values for the type of thermistor used.
const unsigned int RES_TAB[101] = {47, 48, 49, 50, 51, 52, 53, 56, 57, 58, 60 ,61, 62, 64, 65,
                           67, 68, 70, 72, 73, 75, 77, 79, 81, 82, 84, 86, 89, 91, 93,
                           95, 98, 100, 102, 105, 108, 110, 113, 116, 119, 122, 125, 128,
                           131, 135, 138, 142, 145, 149, 153, 157, 161, 165, 170, 174,
                           179, 183, 188, 193, 199, 204, 210, 215, 221, 227, 233, 240,
                           246, 253, 260, 268, 275, 283, 291, 299, 308, 316, 325, 335,
                           344, 354, 365, 375, 386, 398, 409, 422, 434, 447, 460, 474,
                           488, 503, 518, 534, 550, 567, 585, 603, 622};

// Main Function
void main(void)
{
  int i, j;

  initialize();                             // Initialize system

  for (;;)                                  //
  {
  port_pin = Ref;                           // Set temp holder to Ref resistor pin
  REF_RES = measure_count(port_pin);        // Measure REF_RES discharge count
  port_pin = Sensor;                        // Set temp holder to Sensor (thermistor) pin
  THERM_RES = measure_count(port_pin);      // Measure THERM_RES discharge count
  P2DIR |= Ref;                             // Change Ref to output to hold other inputs low -
                                            // uses less power than to leave floating

  RTHERM = (100 * THERM_RES) / REF_RES;     // Calculate Thermistor

  // obtaining Thermistor temperature reading from table...
  i=0;
  j=110;
  while ((RTHERM - RES_TAB[i]) > 0)
  {
    i++;
    j=j-1;                                  // j = value of Thermistor temperature + 1
  }
  TEMP_FTHERM = j-1;                        // TEMP_FTHERM = Thermistor temperature reading
  _NOP();                                   // PUT BREAKPOINT HERE. Watch TEMP_FTHERM in watch window
  }
}

// setup ports, Timers, and variables - run once at start
void initialize(void)
{
  volatile int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  for(i=0;i<10000;i++);                     // Delay for XTAL to stabilize
  P1OUT = 0x00;                             // Setup P1
  P1DIR = 0xCF;                             // Outputs = P1.0,1,2,3,6,7
                                            // Inputs = P1.4,5
  P2OUT = 0x00;                             // Setup P2
  P2DIR = 0x00;                             // All pins are outputs
  CAPD =  Ref+Sensor;                       // Disable input buffers for sensor inputs
  CACTL2 = P2CA0;                           // Setup CA:  +comp = P2.3
  _EINT();                                  // Enable interrupts
}

// measure count value for Thermistor, Reference resistor, and Potentiometer
unsigned int measure_count(unsigned int TEMP_SOURCE)
{
  unsigned int TIMERCCR_COUNT;              // Temporary holder for CCR count on measure routine
  unsigned int TIMERA_COUNT;                // Temporary holder for TA discharge count

  CCR1 = 3605;                              // CCR1 ~ TAR+5ms (5tau)
  CAPD &= ~Ref;                             // Must be enabled for output function
  P2OUT |= Ref;                             // Ref Set
  P2DIR |= Ref;                             // Ref Output
  CCTL1 = CCIE;                             // Compare mode, interrupt
  TACTL = TASSEL0+TACLR+MC1;                // ACLK, TA clear, continuous mode
  LPM0;                                     // enter LPM0, wait for CCR1 interrupt
  P2DIR &= ~Ref;                            // Ref = HiZ, charge complete
  CAPD |= Ref;                              // Input buffer disabled for tri-state
  P2OUT &= ~Ref;                            // Ref = reset
  TIMERA_COUNT = TAR;                       // Store TAR count in temporary holder at start
                                            // of conversion
  CACTL1 = CARSEL+CAREF0+CAON;              // -comp = 0.25*Vcc, comp on
  CCTL1 = CM1+CCIS0+CAP+CCIE;               // Neg, CCIB, cap, interrupt
  P2DIR |= TEMP_SOURCE;                     // Select Thermistor or Reference
  CAPD &= ~TEMP_SOURCE;                     // Must be enabled for output function
  LPM0;                                     // Enter LPM0, wait for CCR1 interrupt
  TIMERCCR_COUNT = CCR1;                    // TIMERCCR_COUNT = TAR (CCR1) at EOC
  TIMERCCR_COUNT -= TIMERA_COUNT;           // TIMERCCR_COUNT = discharge time count
  P2DIR &= ~TEMP_SOURCE;                    // Disable selection
  CAPD |= TEMP_SOURCE;                      // Input buffer disabled for tri-state
  CACTL1 = 0x00;                            // Disable comparator
  CCTL1 = 0x00;                             // Disable CCTL1
  TACTL = 0x00;                             // Disable timer_A
  return(TIMERCCR_COUNT);                   // Return discharge time count
}

// Timer A1 interrupt service routine
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void)
{
  LPM0_EXIT;                                // Exit LPM0
  CCTL1 &= ~CCIFG;                          // Clear CCR1 interrupt flag
}


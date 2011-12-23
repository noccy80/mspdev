//*****************************************************************************
//  MSP-FET430P410 Demo - SD16, Using the Integrated Temperature Sensor
//
//  Description: This example shows how to use the SD16 module's integrated
//  temperature sensor (connected to input channel 6) to measure temperature.
//  A single conversion is initiated and then the CPU is disabled by entering
//  LPM0. Once the conversion has completed, a SD16 interrupt occurs and
//  stores the result in variable "ADCresult". Next, the CPU wakes up and
//  converts this value into two temperature values, one in degrees Celcius
//  and one in degrees Farenheit. Test by setting a breakpoint at the line
//  indicated below and running the program. Upon reaching the breakpoint,
//  use the debugger's watch window to view degrees C (DegC) and degrees F
//  (DegF).
//  ACLK = LFXT1 = 32768 Hz, MCLK = SMCLK = DCO = 32 x ACLK = 1048576 Hz
//  //* An external watch crystal on XIN XOUT is required for ACLK     *//	
//  //* Minimum Vcc is required for SD16 module - see datasheet        *//
//  //* 100nF cap btw Vref and AVss is recommended when using 1.2V ref *//
//
//  Sensor's temperature coefficient is 1.32mV/K (from 'F42x datasheet)
//  Sensor's offset voltage ranges from -100mv to 100mV (assume 0)
//  DegC =  DegK - 273
//  DegF = (DegC * 9/5) + 32
//  Vref = 1200mV
//  Vsensor = 1.32mV * DegK + Vsensor_offset (assuming 0mv for offset)
//  Vsensor = (SD16MEM2-32768)/32768 * Vref/2
//  DegK = (SD16MEM2 - 32768)/65536 * 1200/1.36
//  DegK = (SD16MEM2 * 909)/65536 - 454
//  DegC = (SD16MEM2 * 909)/65536 - 727   ( No need to simplify further,    )
//  DegF = (SD16MEM2 * 1636)/65536 - 1276 ( take advantage of HW multiplier )
//                                        ( and simple binary division      )
//
//                MSP430F427
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |A2.6+            | ( A2.6+, A2.6- connected internally )
//            |A2.6-            | ( to SD16's temperature sensor      )
//            |                 |
//            |            VREF |---+
//            |                 |   |
//            |                 |  -+- 100nF
//            |                 |  -+-
//            |                 |   |
//            |            AVss |---+
//            |                 |
//
//  H. Grewal
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include  <msp430x42x.h>

static unsigned int ADCresult;
static unsigned long DegC = 0;
static unsigned long DegF = 0;

void main(void)
{
  volatile unsigned int i;                  // Use volatile to prevent removal
                                            // by compiler optimization

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  for (i = 0; i < 10000; i++);              // Delay for 32 kHz crystal to
                                            // stabilize

  SD16CTL = SD16REFON+SD16SSEL0;            // 1.2V ref, SMCLK
  SD16CCTL2 |= SD16SNGL+SD16IE ;            // Single conv, enable interrupt
  SD16INCTL2 |= SD16INCH_6;                 // Select Channel A6
  for (i = 0; i < 0x3600; i++);             // Delay for 1.2V ref startup

  _EINT();                                  // Enable general interrupts

  while (1)
  {
    SD16CCTL2 |= SD16SC;                    // Set bit to start conversion
    _BIS_SR(LPM0_bits);                     // Enter LPM0

    DegC = ((unsigned long)ADCresult * 909)/65536 - 727;
                                            // Calculate degrees Celcius
    DegF = ((unsigned long)ADCresult * 1636)/65536 - 1276;
                                            // Calculate degrees Farenheit
    _NOP();                                 //SET BREAKPOINT HERE
  }
}

#pragma vector=SD16_VECTOR
__interrupt void SD16ISR(void)
{
  switch (SD16IV)
  {
  case 2:                                   // SD16MEM Overflow
    break;
  case 4:                                   // SD16MEM0 IFG
    break;
  case 6:                                   // SD16MEM1 IFG
    break;
  case 8:                                   // SD16MEM2 IFG
    ADCresult = SD16MEM2;                   // Save CH2 results (clears IFG)
    break;
  }

  _BIC_SR_IRQ(LPM0_bits);                   // Exit LPM0
}



//-----------------------------------------------------------------------------
//  MSP-FET430P140 Demo - I2C, Slave TMP100 Emulation II
//
//  Description: Uses ADC12 and I2C modules to emulate behaviour of the TMP100
//  temperature sensor.
//
//  //* An external 32kHz watch crystal on XIN XOUT is required *//	
//
//  - DMA services I2C module (transmit and receive)
//  - Timer_A triggers ADC12 temperature conversion every 1/10s
//
//   +--------------------+
//   |                    |
//   |                    |
//   |                    |
//   |               P3.1 +<------> I2C SDA
//   |               P3.3 +<------- I2C SCL
//   |  MSP430F169        |
//   |                    |
//   |                    |
//   |                    |
//   |                    |
//   |                    |
//   +--------------------+
//
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//-----------------------------------------------------------------------------
#include <msp430x16x.h>
//-----------------------------------------------------------------------------
#define TMPADDR              0x4E           // TMP100 Slave Address with
                                            // A0=A1=A2=1

void Init_Sys(void);                        // Function prototype

static unsigned int ADCResult;              // Holds the last ADC result
static unsigned int CurrentTmp;             // Holds current temperature
                                            // to be transmitted
static unsigned int ReceivedWord;           //
//-----------------------------------------------------------------------------
// ADC12 Module Temperature Table
//
// These values assume nominal values for the temp diode and
// temperature coefficient. They also assume the 2.5V internal
// reference is used for the conversion. The transfer function out
// of Figure 17-10 of the MSP430x1xx Family User's Guide (SLAU049C)
// has been used.
//-----------------------------------------------------------------------------
static const unsigned int Temp_Tab[] =
{
  0x064F,                                   // 0C
  0x0655,
  0x065B,
  0x0660,
  0x0666,
  0x066C,                                   // 5C
  0x0672,
  0x0678,
  0x067D,
  0x0683,
  0x0689,                                   // 10C
  0x068F,
  0x0695,
  0x069B,
  0x06A0,
  0x06A6,                                   // 15C
  0x06AC,
  0x06B2,
  0x06B8,
  0x06BD,
  0x06C3,                                   // 20C
  0x06C9,
  0x06CF,
  0x06D5,
  0x06DB,
  0x06E0,                                   // 25C
  0x06E6,
  0x06EC,
  0x06F2,
  0x06F8,
  0x06FD,                                   // 30C
  0x0703,
  0x0709,
  0x070F,
  0x0715,
  0x071B,                                   // 35C
  0x0720,
  0x0726,
  0x072C,
  0x0732,
  0x0738,                                   // 40C
  0x073D,
  0x0743,
  0x0749,
  0x074F,
  0x0755,                                   // 45C
  0x0FFF                                    // Too high
};
//-----------------------------------------------------------------------------
void main(void)
{
  unsigned int i;

  Init_Sys();                               // Initialize system
  _EINT();                                  // Enable interrupts

  while (1)                                 // Repeat forever
  {
    _BIS_SR(LPM3_bits);                     // Wait for ADC conversion
                                            // completion

    for (i = 0; i < sizeof Temp_Tab; i++)   // Get temperature value out
      if (ADCResult < Temp_Tab[i])          // of table
        break;

    _DINT();                                // Protect next statement
    CurrentTmp = i;                         // Save current temperature
    _EINT();
  }
}
//-----------------------------------------------------------------------------
// setup system and peripherals
//-----------------------------------------------------------------------------
void Init_Sys(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  BCSCTL1 = XT2OFF + RSEL2 + RSEL0;         // Adjust DCO frequ

  // D169 specific initialisation
  P1OUT = 0x10;                             // Disable audio output stage
  P1DIR = 0x3f;                             // P1.6/P1.7 inp, all other outp
  P2OUT = 0x00;                             // Clear P2 output register
  P2DIR = 0xff;                             // Unused pins as outp
  P3SEL = 0x0a;                             // Assign I2C pins to module
  P3OUT = 0x00;                             // Clear P3 output register
  P3DIR = 0xff;                             // Unused pins as outp
  P4OUT = 0x00;                             // Clear P4 output register
  P4DIR = 0xff;                             // Unused pins as outp
  P5OUT = 0x00;                             // Clear P5 output register
  P5DIR = 0xff;                             // Unused pins as outp
  P6OUT = 0x00;                             // Clear P6 output register
  P6DIR = 0xfe;                             // Unused pins as outp

  // Setup I2C module
  U0CTL |= I2C + SYNC;                      // Switch USART0 to I2C mode

  U0CTL &= ~I2CEN;

  U0CTL |= RXDMAEN + TXDMAEN;               // Enable I2C DMA triggers
  I2COA = TMPADDR;                          // Own address = TMP100 device addr
  I2CTCTL = I2CWORD + I2CSSEL1;             // Select SMCLK, word mode
  U0CTL |= I2CEN;                           // Enable I2C module, 7 bit addr,
                                            // Slave mode

  // Setup DMA
  DMACTL0 = DMA0TSEL2 + DMA1TSEL1 + DMA1TSEL0; // I2C transmit ready -> DMA0
                                               // I2C receive ready -> DMA1
  DMA0SA = (int)&CurrentTmp;
  DMA0DA = (unsigned int)&I2CDRW;
  DMA0CTL = DMADT2 + DMAEN;                 // Repeated single transfer
  DMA1SA = (unsigned int)&I2CDRW;
  DMA1DA = (int)&ReceivedWord;
  DMA1CTL = DMADT2 + DMAEN;                 // Repeated single transfer

  // Setup Timer_A
  CCR0 = 3277;                              // 1/10s w/ 32kHz ACLK
  CCR1 = 3276;                              // ADC12 start-of-conversion
  TACCTL1 = OUTMOD_3;                       // set on EQU1, reset on EQU0
  TACTL = TASSEL_1 + MC0;                   // ACLK, start timer in up-mode

  // Setup ADC12
  ADC12CTL0 = ADC12ON + REFON + REF2_5V + SHT0_6;// Turn on ADC12, 2.5Vref, set SHT0
                                            // for longer sampling required by
                                            // temp diode.
  ADC12CTL1 = SHS_1 + SHP + CONSEQ_2;       // Use sampling timer, Timer_A.OUT1
                                            // triggers conversion, rep. single
                                            // channel
  ADC12MCTL0 = INCH_10 + SREF_1;            // Select channel A10, Vref+
  ADC12IE = 0x01;                           // enable ADC12IFG.0 for ADC12MEM0
  ADC12CTL0 |= ENC;                         // Enable conversions
}
//-----------------------------------------------------------------------------
// Interrupt Service Routine for ADC12
//-----------------------------------------------------------------------------
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR(void)
{
  ADCResult = ADC12MEM0;                    // Move result, IFG is cleared
  _BIC_SR_IRQ(LPM3_bits);                   // Return active
}

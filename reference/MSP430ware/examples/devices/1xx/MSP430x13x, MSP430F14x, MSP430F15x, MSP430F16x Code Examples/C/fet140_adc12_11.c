//*****************************************************************************
//  MSP-FET430P140 Demo - ADC12, Single Channel Rpt Mode, TA1 as Sample Trigger
//
//  Description: Sample and convert A0 using Timer_A as sample trigger in
//  Pulse Sample mode. Put "Num_of_Results" ADC12MEM0 values in results[]
//  and Light LED (P1.0) when done.
//
//               MSP430F149
//             ---------------
//            |               |
//     Vin -->|P6.0/A0        |
//            |               |
//
//  H. Grewal
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include  <msp430x14x.h>

#define   Num_of_Results   512
int results[Num_of_Results] = {0};

void ADC_Init(void);

void main(void)
{
  WDTCTL = WDTPW | WDTHOLD;                 // Disable the Watchdog.
  ADC_Init();                               // Initialize ADC12
  ADC12CTL0 |= ENC;                         // Start conversion
  _BIS_SR(LPM0_bits);                       // Enter LPM0
}


void ADC_Init(void)
{
  P1DIR = 0xff;                             // set port to outputs
  P1OUT = 0;                                // reset port outputs
  P6SEL |= 0x01;                            // select A0 input
  ADC12CTL0 = ADC12ON+SHT0_1+REF2_5V+REFON; // Setup ADC12
  ADC12CTL1 = SHP+CONSEQ_2+SHS_1;           // Timer triggers sampling
  ADC12MCTL0 = INCH_0 + SREF_1;
  ADC12IE = 0x0001;                         // Enable ADC12IFG.0


  TACCR0 = 1500;                            // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
  TACTL = TASSEL_1 | MC_1;                  // TACLK = ACLK, Up mode.
  _BIS_SR(LPM3_bits + GIE);                 // Wait for delay, Enable interrupts
  TACCTL0 &= ~CCIE;                         // Disable timer

  P2SEL |= BIT3;                            // Set for Timer A1
  P2DIR |= 0x08;
  TACCR0 = 7;                               // Init TACCR0 w/ sample prd=CCR0+1
  TACCR1 = 4;                               // Trig for ADC12 sample & convert
  TACCTL1 = OUTMOD_3;                       // Set/reset
  TACTL = TACLR | MC_1 | TASSEL_1;          // ACLK, clear TAR, up mode
}

// Timer_A0 Interrupt Service Routine
#pragma vector=TIMERA0_VECTOR
__interrupt void ta0_isr(void)
{
  TACTL = 0;
  LPM3_EXIT;                                // Exit LPM3 on return
}


// ADC12 Interrupt Service Routine
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  static unsigned int index = 0;

  results[index++] = ADC12MEM0;             // Move results

  if (index == 512)
  {
    ADC12CTL0 &= ~ENC;                      // Stop conversion
    index = 0;
    P1OUT |= 0x01;
    _BIS_SR(LPM3_bits);                     // Enter LPM3
  }
}


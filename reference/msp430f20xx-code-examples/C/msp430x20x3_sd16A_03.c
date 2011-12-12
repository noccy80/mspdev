//******************************************************************************
//  MSP430F20x3 Demo - SD16A Sequence of conversions
//
//  The SD16A takes a sample of a single sequence of channels: A0, A1, then A2. 
//  Sampling begins with ch A0.  The 4th conversion result of each channel is 
//  stored in memory.
//
//
//                MSP430F20x3
//             ------------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//    Vin+ -->|A0+ P1.0         |
//            |A01- = VSS       |
//            |                 |
//    Vin+ -->|A1+ P1.2         |
//            |A1- = VSS        |
//            |                 |
//    Vin+ -->|A2+ P1.4         |
//            |A2- = VSS        |
//            |                 |
//            |            VREF |---+
//            |                 |   |
//            |                 |  -+- 100nF
//            |                 |  -+-
//            |                 |   |
//            |            AVss |---+
//            |                 |
//
//
//  R. B. Elliott  / H. Grewal
//  Texas Instruments
//  April 2007
//  Built with IAR Embedded Workbench Version 3.42A and CCE V3.0
//******************************************************************************
#include  <msp430x20x3.h>

/* Arrays to store SD16 conversion results */
/* NOTE: arrays need to be global to       */
/*       prevent removal by compiler       */
static unsigned int ChA0results = 0x00;
static unsigned int ChA1results = 0x00;
static unsigned int ChA2results = 0x00;
static unsigned int ch_counter=0;
  
void main(void)
{
  
  volatile unsigned int i;                  // Use volatile to prevent removal
                                            // by compiler optimization
  
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  BCSCTL2 |= DIVS_3;                        // SMCLK/8
  
  SD16CTL = SD16REFON + SD16SSEL_1;         // 1.2V ref, SMCLK
  SD16INCTL0 = SD16INCH0;                   // Set channel A0+/-
  SD16CCTL0 |= SD16SNGL + SD16UNI + SD16IE; 
                                            // Single conv, 256OSR, unipolar, 
                                            // enable interrupt
  SD16INCTL0 |= SD16INTDLY_0;               // Interrupt on 4th sample 
  SD16AE = SD16AE0;                         // P1.0 A0+, A0- = VSS
  
  for (i = 0; i < 0x3600; i++);             // Delay for 1.2V ref startup
 
  while(1)
  {
    SD16CCTL0 |= SD16SC;                    // Set bit to start conversion
    _BIS_SR(LPM0_bits + GIE);               // Enter LPM0
  }
}

#pragma vector = SD16_VECTOR
__interrupt void SD16ISR(void)
{
  switch (SD16IV)
  { case 2:                                 // SD16MEM Overflow
    break;
  
  case 4:                                   // SD16MEM0 IFG
        
    switch(ch_counter)
    {  
    case 0:
        ChA0results = SD16MEM0;             // Save CH0 results (clears IFG)
        SD16AE &= ~SD16AE0;                 // Disable external input A0+, A0
        SD16INCTL0 &= ~SD16INCH_0;          // Disable channel A0+/-
        ch_counter++;
        
        SD16INCTL0 |= SD16INCH_1;           // Enable channel A1+/-                          
        SD16AE |= SD16AE2;                  // Enable external input on A1+ 
        break;
        
    case 1:
        ChA1results = SD16MEM0;             // Save CH1 results (clears IFG)
        SD16AE &= ~SD16AE2;                 // Disable external input A1+, A1
        SD16INCTL0 &= ~SD16INCH_1;          // Disable channel A1+/-
        ch_counter++;

        SD16INCTL0 |= SD16INCH_2;           // Enable channel A2+/-                       
        SD16AE |= SD16AE4;                  // Enable external input on A2+
        break;
        
    case 2:
        ChA2results = SD16MEM0;             // Save CH2 results (clears IFG)
        ch_counter = 0;                     // Reset channel count (end of seq)
        SD16AE = SD16AE0;                   // Reset external input to A0+/-
        SD16INCTL0 = SD16INCH_0;            // Reset channel observed
        break;
    }
    
     _BIC_SR_IRQ(LPM0_bits);                // Exit LPM0
    
  }
}

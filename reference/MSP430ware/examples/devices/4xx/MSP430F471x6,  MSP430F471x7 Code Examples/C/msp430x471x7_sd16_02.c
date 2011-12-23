//*****************************************************************************
//  MSP430x471x7 Demo - SD16, Single Conversion on a Group of 7 Channels
//
//  Description: This program uses the SD16 module to perform a single
//  conversion on a group of 7 channels (0 to 6). A SD16 interrupt 
//  occurs when the conversions have completed. Test by applying voltages 
//  to the four input channels and setting a breakpoint at the line indicated
//  below. Run program until it reaches the breakpoint, then use the
//  debugger's watch window to view the conversion results. Results for all
//  seven channels are stored in the array "results". NOTE: array won't
//  contain values until after reaching breakpoint for the second time.
//  ACLK = LFXT1 = 32768 Hz, MCLK = SMCLK = DCO = 32 x ACLK = 1048576 Hz
//  //* An external watch crystal on XIN XOUT is required for ACLK     *//	
//  //* For minimum Vcc required for SD16 module - see datasheet        *//
//  //* 100nF cap btw Vref and AVss is recommended when using 1.2V ref *//
//
//                MSP430x471x7
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//   Vin1+ -->|A0.0+            |
//   Vin1- -->|A0.0-            |
//   Vin2+ -->|A1.0+            |
//   Vin2- -->|A1.0-            |
//   Vin3+ -->|A2.0+            |
//   Vin3- -->|A2.0-            |
//   Vin4+ -->|A3.0+            |
//   Vin4- -->|A3.0-            |
//   Vin5+ -->|A4.0+            |
//   Vin5- -->|A4.0-            |
//   Vin6+ -->|A5.0+            |
//   Vin6- -->|A5.0-            |
//   Vin7+ -->|A6.0+            |
//   Vin7- -->|A6.0-            |
//            |            VREF |----
//            |                 |   |
//            |                 |  -+- 100nF
//            |                 |  -+-
//            |                 |   |
//            |            AVss |---+
//            |                 |
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  <msp430x471x7.h>

/* Array to store SD16 conversion results  */
unsigned int results[7];

void main(void)
{
  volatile unsigned int i;                  // Use volatile to prevent removal
                                            // by compiler optimization

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  for (i = 0; i < 10000; i++);              // Delay for 32 kHz crystal to
                                            // stabilize

  SD16CTL   = SD16REFON+SD16SSEL0;          // 1.2V ref, SMCLK
  SD16CCTL0 = SD16SNGL+SD16GRP;             // Single conv, group with CH1
  SD16CCTL1 = SD16SNGL+SD16GRP;             // Single conv, group with CH2
  SD16CCTL2 = SD16SNGL+SD16GRP;             // Single conv, group with CH3
  SD16CCTL3 = SD16SNGL+SD16GRP;             // Single conv, group with CH4
  SD16CCTL4 = SD16SNGL+SD16GRP;             // Single conv, group with CH5
  SD16CCTL5 = SD16SNGL+SD16GRP;             // Single conv, group with CH6
  SD16CCTL6 = SD16SNGL+SD16IE;              // Single conv, enable interrupt
  
    for (i = 0; i < 0x3600; i++);             // Delay for 1.2V ref startup

  while (1)
  {
    SD16CCTL6 |= SD16SC;                    // SET BREAKPOINT HERE
                                            // Set bit to start conversion
    __bis_SR_register(LPM0_bits+GIE);       // Enter LPM0 w/ interrupts
  }
}

#pragma vector=SD16A_VECTOR
__interrupt void SD16AISR(void)
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
    break;
  case 10:                                  // SD16MEM3 IFG
    break;
  case 12:                                  // SD16MEM4 IFG
    break;
  case 14:                                  // SD16MEM5 IFG   
    break;
  
  case 16:                                  // SD16MEM6 IFG   
    results[0] = SD16MEM0;                  // Save CH0 results (clears IFG)
    results[1] = SD16MEM1;                  // Save CH1 results (clears IFG)
    results[2] = SD16MEM2;                  // Save CH2 results (clears IFG)
    results[3] = SD16MEM3;                  // Save CH3 results (clears IFG)
    results[4] = SD16MEM4;                  // Save CH4 results (clears IFG)
    results[5] = SD16MEM5;                  // Save CH5 results (clears IFG)
    results[6] = SD16MEM6;                  // Save CH6 results (clears IFG)
    break;
    
  }

  __bic_SR_register_on_exit(LPM0_bits);        // Exit LPM0
}

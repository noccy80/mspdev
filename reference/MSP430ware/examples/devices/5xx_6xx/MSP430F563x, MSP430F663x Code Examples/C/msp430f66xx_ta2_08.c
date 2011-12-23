//******************************************************************************
//  MSP430F66x Demo - Timer2_A3, Toggle P1.0;P2.3-5, Cont. Mode ISR, 32kHz ACLK
//
//  Description: Use Timer1_A CCRx units and overflow to generate four
//  independent timing intervals. For demonstration, CCR0, CCR1 and CCR2
//  output units are optionally selected with port pins P3.5,6,7
//  in toggle mode. These pins toggle when respective CCRx
//  registers match the TAR counter. Interrupts are also enabled with all
//  CCRx units, software loads offset to next interval only - as long as
//  the interval offset is added to CCRx, toggle rate is generated in
//  hardware. Timer1_A overflow ISR is used to toggle P1.0 with software.
//  Proper use of the TAIV interrupt vector generator is demonstrated.
//  ACLK = TACLK = 32kHz, MCLK = SMCLK = default DCO ~1.045MHz
//
//  As coded and with TACLK = 32768Hz, toggle rates are:
//  P3.5= CCR0 = 32768/(2*4) = 4096Hz
//  P3.6= CCR1 = 32768/(2*16) = 1024Hz
//  P3.7= CCR2 = 32768/(2*100) = 163.84Hz
//  P1.0= overflow = 32768/(2*65536) = 0.25Hz
//
//               MSP430F66x
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P3.5/TA2.0|--> CCR0
//           |         P3.6/TA2.1|--> CCR1
//           |         P3.7/TA2.2|--> CCR2
//           |               P1.0|--> Overflow/software
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   Nov 2009
//   Built with IAR Embedded Workbench Version: 4.20 & Code Composer Studio V4.0
//******************************************************************************
#include <msp430f6638.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  while(BAKCTL & LOCKIO)                    // Unlock XT1 pins for operation
     BAKCTL &= ~(LOCKIO); 
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap 
  // Loop until XT1 fault flag is cleared
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  
  P3SEL |= BIT5+BIT6+BIT7;                  // P3.5,6,7 option select
  P3DIR |= BIT5+BIT6+BIT7;                  // P3.5,6,7 outputs
  P1DIR |= 0x01;                            // P1.0 - Outputs
  TA2CCTL0 = OUTMOD_4 + CCIE;               // CCR0 toggle, interrupt enabled
  TA2CCTL1 = OUTMOD_4 + CCIE;               // CCR1 toggle, interrupt enabled
  TA2CCTL2 = OUTMOD_4 + CCIE;               // CCR2 toggle, interrupt enabled
  TA2CTL = TASSEL_1 + MC_2 + TACLR + TAIE;  // ACLK, contmode, clear TAR,
                                            // interrupt enabled

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, interrupts enabled
  __no_operation();                         // For debugger
}

// Timer2 A0 interrupt service routine
#pragma vector=TIMER2_A0_VECTOR
__interrupt void Timer2_A0 (void)
{
  TA2CCR0 += 4;                             // Add Offset to CCR0
}

// Timer2_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMER2_A1_VECTOR
__interrupt void TIMER2_A1_ISR(void)
{
  switch(__even_in_range(TA2IV,14))
  {
    case 0: break;                  
    case 2:  TA2CCR1 += 16;                 // Add Offset to CCR1
             break;
    case 4:  TA2CCR2 += 100;                // Add Offset to CCR2
             break;
    case 6:  break;                         // CCR3 not used
    case 8:  break;                         // CCR4 not used
    case 10: break;                         // CCR5 not used
    case 12: break;                         // Reserved not used
    case 14: P1OUT ^= 0x01;                 // overflow
             break;
    default: break;
 }
}


//******************************************************************************
//  MSP430F530x Demo - Timer2_A3, Toggle P1.0;P2.3-5, Cont. Mode ISR, 32kHz ACLK
//
//  Description: Use Timer1_A CCRx units and overflow to generate four
//  independent timing intervals. For demonstration, CCR0, CCR1 and CCR2
//  output units are optionally selected with port pins P2.3, P2.4 and P2.5
//  in toggle mode. As such, these pins will toggle when respective CCRx
//  registers match the TAR counter. Interrupts are also enabled with all
//  CCRx units, software loads offset to next interval only - as long as
//  the interval offset is added to CCRx, toggle rate is generated in
//  hardware. Timer1_A overflow ISR is used to toggle P1.0 with software.
//  Proper use of the TAIV interrupt vector generator is demonstrated.
//  ACLK = TACLK = 32kHz, MCLK = SMCLK = default DCO ~1.045MHz
//
//  As coded and with TACLK = 32768Hz, toggle rates are:
//  P2.3= CCR0 = 32768/(2*4) = 4096Hz
//  P2.4= CCR1 = 32768/(2*16) = 1024Hz
//  P2.5= CCR2 = 32768/(2*100) = 163.84Hz
//  P1.0= overflow = 32768/(2*65536) = 0.25Hz
//
//               MSP430F530x
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P2.3/TA2.0|--> CCR0
//           |         P2.4/TA2.1|--> CCR1
//           |         P2.5/TA2.2|--> CCR2
//           |               P1.0|--> Overflow/software
//           |               P1.0|--> LED
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P2SEL |= BIT3+BIT4+BIT5;                  // P2.3 - P2.5 option select
  P2DIR |= BIT3+BIT4+BIT5;                  // P2.3 - P2.5 outputs
  P1DIR |= 0x01;                            // P1.0 - Outputs
  
  // Configure XT1
  P5SEL |= BIT4+BIT5;                       // Port select XT1
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap
  UCSCTL3 = 0;                              // FLL Reference Clock = XT1
  // Loop until XT1,XT2 & DCO stabilizes - In this case loop until XT1 and DCo settle
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag  
  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive strength
  UCSCTL4 |= SELA_0;                        // ACLK = LFTX1 (by default)

  // Configure TimerA2  
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


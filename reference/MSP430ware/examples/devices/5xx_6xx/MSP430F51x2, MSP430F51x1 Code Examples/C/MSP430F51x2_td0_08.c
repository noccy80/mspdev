//******************************************************************************
//  MSP430F51x2 Demo - TimerD0, Toggle P1.0;P2.3-5, Cont. Mode ISR, 32kHz ACLK
//
//  Description: Use TimerD0 CCRx units and overflow to generate four
//  independent timing intervals. For demonstration, CCR0, CCR1 and CCR2
//  output units are optionally selected with port pins P2.3, P2.4 and P2.5
//  in toggle mode. As such, these pins will toggle when respective CCRx
//  registers match the TDR counter. Interrupts are also enabled with all
//  CCRx units, software loads offset to next interval only - as long as
//  the interval offset is added to CCRx, toggle rate is generated in
//  hardware. TimerD0 overflow ISR is used to toggle P1.0 with software.
//  Proper use of the TDIV interrupt vector generator is demonstrated.
//  ACLK = TDCLK = 32kHz, MCLK = SMCLK = default DCO ~1.045MHz
//
//  As coded and with TDCLK = 32768Hz, toggle rates are:
//  P1.6= CCR0 = 32768/(2*4) = 4096Hz
//  P1.7= CCR1 = 32768/(2*16) = 1024Hz
//  P2.0= CCR2 = 32768/(2*100) = 163.84Hz
//  P1.0= overflow = 32768/(2*65536) = 0.25Hz
//
//               MSP430F51x2
//            -------------------
//        /|\ |              XIN|-
//         |  |                 | 32kHz
//         ---|RST          XOUT|-
//           |                   |
//           |         P1.6/TD0.0|--> CCR0
//           |         P1.7/TD0.1|--> CCR1
//           |         P2.0/TD0.2|--> CCR2
//           |               P1.0|--> Overflow/software (LED)
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  // Configure ports
  P1SEL |= BIT6+BIT7;                       // P1.6,7 - option select
  P1DIR |= BIT6+BIT7;                       // P1.6,7 - outputs
  P2SEL |= BIT0;                            // P2.0 option select
  P2DIR |= BIT0;                            // P2.0 outputs
  P1DIR |= 0x01;                            // P1.0 - Outputs

  // XT1 configure
  PJSEL |= BIT4+BIT5;                       // Port select XT1
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap
  UCSCTL3 = 0;                              // FLL Reference Clock = XT1

  // Loop until XT1 & DCO stabilizes - In this case loop until XT1 and DCo settle
  do
  {
    UCSCTL7 &= ~(XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag  
  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive strength
  UCSCTL4 |= SELA_0;                        // ACLK = LFTX1 (by default)
  
  // Configure TD0
  TD0CCTL0 = OUTMOD_4 + CCIE;               // CCR0 toggle, interrupt enabled
  TD0CCTL1 = OUTMOD_4 + CCIE;               // CCR1 toggle, interrupt enabled
  TD0CCTL2 = OUTMOD_4 + CCIE;               // CCR2 toggle, interrupt enabled
  TD0CTL0 = TDSSEL_1 + MC_2 + TDCLR + TDIE; // ACLK, contmode, clear TDR,
                                            // interrupt enabled

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, interrupts enabled
  __no_operation();                         // For debugger
}

// Timer0_D0 interrupt service routine
#pragma vector=TIMER0_D0_VECTOR
__interrupt void TIMER0_D0_ISR(void)
{
  TD0CCR0 += 4;                             // Add Offset to CCR0
}

// Timer0_D1 Interrupt Vector (TDIV) handler
#pragma vector=TIMER0_D1_VECTOR
__interrupt void TIMER0_D1_ISR(void)
{
  switch(__even_in_range(TD0IV,30))
  {
    case 0: break;                  
    case 2:  TD0CCR1 += 16;                  // Add Offset to CCR1
             break;
    case 4:  TD0CCR2 += 100;                 // Add Offset to CCR2
             break;
    case 6:  break;                          // CCR3 not used
    case 8:  break;                          // CCR4 not used
    case 10: break;                          // reserved
    case 12: break;                          // reserved
    case 14: break;
    case 16: P1OUT ^= 0x01;                  // overflow
             break;
    case 18: break;                          // Clock fail low
    case 20: break;                          // Clock fail high
    case 22: break;                          // Hi-res freq locked
    case 24: break;                          // Hi-res freq unlocked
    case 26: break;                          // reserved
    case 28: break;                          // reserved
    case 30: break;                          // reserved       
    default: break; 

 }
}


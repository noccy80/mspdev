//******************************************************************************
//   MSP430F66x Demo - USCI_A0, SPI 3-Wire Slave Data Echo
//
//   Description: SPI slave talks to SPI master using 3-wire mode. Data received
//   from master is echoed back.  USCI RX ISR is used to handle communication,
//   CPU normally in LPM0.  Prior to initial data exchange, master pulses
//   slaves USCI RST using an interrupt on P1.4.
//
//   ACLK = ~32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz
//
//   Use with SPI Master Incremented Data code example.  
//
//   Note that UCB0CLK, UCB0SIMO and UCB0SOMI need to be assigned pins via the 
//   PMAP controller.
//
//                   MSP430F66x
//                 -----------------
//            /|\ |                 |
//             |  |                 |
//             +->|RST              |
//                |             P1.4|<-Lo/Hi interrupt from mstr
//                |                 |
//                |             P2.1|-> Data Out (UCA0SIMO)
//                |                 |
//                |             P2.1|<- Data In (UCA0SOMI)
//                |                 |
//                |             P2.0|-> Serial Clock Out (UCA0CLK)
//
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   Nov 2009
//   Built with IAR Embedded Workbench Version: 4.20 & Code Composer Studio V4.0
//******************************************************************************
#include <msp430f6638.h>

void Port_Mapping(void);

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  
  Port_Mapping();
  
  P2SEL |= BIT0+BIT1+BIT2;                  // Assign P2.0 to UCB0CLK and...
  P2DIR |=  BIT0+BIT1+BIT2;                 // P2.1 UCB0SOMI P2.2 UCB0SIMO
  
  P1REN |= BIT4;                            // Enable P1.4 internal resistance
  P1OUT |= BIT4;                            // Set P1.4 as pull-Up resistance
  P1IES &= ~BIT4;                           // P1.4 Lo/Hi edge
  P1IFG &= ~BIT4;                           // P1.4 IFG cleared
  P1IE |= BIT4;                             // P1.4 interrupt enabled

  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL0 |= UCSYNC+UCCKPL+UCMSB;          // 3-pin, 8-bit SPI slave,
                                            // Clock polarity high, MSB
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
                                            // Interrupts enabled in Port ISR

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
}

// Echo character
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
  switch(__even_in_range(UCA0IV,4))
  {
    case 0:break;                             // Vector 0 - no interrupt
    case 2:                                   // Vector 2 - RXIFG
      while (!(UCA0IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
      UCA0TXBUF = UCA0RXBUF;
      break;
    case 4:break;                             // Vector 4 - TXIFG
    default: break;
  }
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  P1IFG &= ~BIT4;                           // Clear P1.4 IFG
  P1IE &= ~ BIT4;                           // Clear P1.4 IE
  UCA0CTL1 |= UCSWRST;                      // Master is ready 
  UCA0CTL1 &= ~UCSWRST;                     // Re-init slave state machine
  UCA0IE |= UCRXIE;                         // Enable RX interrupt
}

void Port_Mapping(void)
{
  // Disable Interrupts before altering Port Mapping registers
  __disable_interrupt();     
  // Enable Write-access to modify port mapping registers
  PMAPPWD = 0x02D52;                        
  
  #ifdef PORT_MAP_RECFG                    
  // Allow reconfiguration during runtime
  PMAPCTL = PMAPRECFG;                     
  #endif  
  
  P2MAP0 = PM_UCA0CLK;
  P2MAP1 = PM_UCA0SOMI;
  P2MAP2 = PM_UCA0SIMO;

  // Disable Write-Access to modify port mapping registers
  PMAPPWD = 0;                              
  #ifdef PORT_MAP_EINT
  __enable_interrupt();                     // Re-enable all interrupts
  #endif  
}

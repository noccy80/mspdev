//******************************************************************************
//   MSP430x530x Demo - Enters LPM3 with ACLK = LFXT1, REF0 disabled, 
//                      VUSB LDO and SLDO disabled, SVS disabled
//
//   Description: Configure ACLK = LFXT1 and enters LPM3. Measure current.
//   ACLK = LFXT1 = 32kHz, MCLK = SMCLK = default DCO
//
//                MSP430F530x
//             -----------------
//        /|\ |              XIN|-
//         |  |                 | 32kHz
//         ---|RST          XOUT|-
//            |                 |
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

#define SYS14_WORKAROUND                    // Comment this line if silicon revision has SYS14 bug fixed

#ifdef SYS14_WORKAROUND
    #define INIT_MEMORY_ADDR 0x0900
    unsigned int *Address = ((unsigned int*)INIT_MEMORY_ADDR); 
#endif

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  
#ifdef SYS14_WORKAROUND  
  *Address = 0x9628;
  *(Address+4) = 0x0800;
  *Address = 0x9600;  
#endif  
  
  // Enable XT1
  P5SEL |= BIT4+BIT5;                       // Port select XT1
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap

  // Loop until XT1 & DCO stabilizes
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive
                                            // strength
  // Port Configuration
  P1OUT = 0x00;P2OUT = 0x00;P3OUT = 0x00;P4OUT = 0x00;P5OUT = 0x00;P6OUT = 0x00;
  PJOUT = 0x00;
  P1DIR = 0xFF;P2DIR = 0xFF;P3DIR = 0xFF;P4DIR = 0xFF;P5DIR = 0xFF;P6DIR = 0xFF;
  PJDIR = 0xFF;

  // Disable SVS
  PMMCTL0_H = PMMPW_H;                // PMM Password
  SVSMHCTL &= ~(SVMHE+SVSHE);         // Disable High side SVS 
  SVSMLCTL &= ~(SVMLE+SVSLE);         // Disable Low side SVS
  
  __bis_SR_register(LPM3_bits);       // Enter LPM3
  __no_operation();                   // For debugger
}


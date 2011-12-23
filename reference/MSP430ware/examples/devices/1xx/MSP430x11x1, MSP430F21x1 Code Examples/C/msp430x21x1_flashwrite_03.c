//******************************************************************************
//  MSP430x21x1 Demo - Flash In-System Programming, Copy SegC to SegD
//
//  Description: This program first erases flash seg C, then it increments all
//  values in seg C, then it erases seg D, then copies seg C to seg D.
//  The EEI bit is set for the Flash Erase Cycles. This does allow the Timer_A
//  Interrupts to be handled also during the Segment erase time.
//  ACLK = n/a, MCLK = SMCLK = saved DCO 1Mhz
//  //* Set Breakpoint on NOP in the Mainloop to avoid Stressing Flash *//
//
//               MSP430F21x1
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//
//  S. Schauer / A. Dannenberg
//  Texas Instruments Inc.
//  July 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//******************************************************************************

#include <msp430x21x1.h>

char  value;                                // 8-bit value to write to segment C

// Function prototypes
void write_SegC (char value);
void copy_C2D (void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;

  P1DIR |= 0x01;                            // P1.0 output
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 50000;
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode

  _EINT();                                  // enable interrupts

  FCTL2 = FWKEY + FSSEL0 + FN1;             // MCLK/3 for Flash Timing Generator
  value = 0;                                // initialize value

  while(1)                                  // Repeat forever
  {
    write_SegC(value++);                    // Write segment C, increment value
    copy_C2D();                             // Copy segment C to D
    _NOP();                                 // SET BREAKPOINT HERE
  }
}

void write_SegC (char value)
{
  char *Flash_ptr;                          // Flash pointer
  unsigned int i;

  Flash_ptr = (char *) 0x1040;              // Initialize Flash pointer
  FCTL1 = FWKEY + ERASE + EEI;              // Set Erase bit, allow interrupts
  FCTL3 = FWKEY;                            // Clear Lock bit
  *Flash_ptr = 0;                           // Dummy write to erase Flash segment

  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i=0; i<64; i++)
  {
    *Flash_ptr++ = value;                   // Write value to flash
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}


void copy_C2D (void)
{
  char *Flash_ptrC;                         // Segment C pointer
  char *Flash_ptrD;                         // Segment D pointer
  unsigned int i;

  Flash_ptrC = (char *) 0x1040;             // Initialize Flash segment C pointer
  Flash_ptrD = (char *) 0x1000;             // Initialize Flash segment D pointer
  FCTL1 = FWKEY + ERASE + EEI;              // Set Erase bit, allow interrupts
  FCTL3 = FWKEY;                            // Clear Lock bit
  *Flash_ptrD = 0;                          // Dummy write to erase Flash segment D
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i=0; i<64; i++)
  {
    *Flash_ptrD++ = *Flash_ptrC++;          // copy value segment C to segment D
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}


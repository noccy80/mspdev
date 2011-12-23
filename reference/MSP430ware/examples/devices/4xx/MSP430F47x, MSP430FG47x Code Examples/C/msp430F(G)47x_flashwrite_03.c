//******************************************************************************
//  MSP430F(G)47x Demo - Flash In-System Programming w/ EEI, Copy SegC to SegD
//
//  Description: This program first erases flash seg C, then it increments all
//  values in seg C, then it erases seg D, then copies seg C to seg D.
//  The EEI bit is set for the Flash Erase Cycles. This does allow the Timer_A
//  Interrupts to be handled also during the Segment erase time.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//  //* Set Breakpoint on NOP in the Mainloop to avoid Stressing Flash *//
//
//            MSP430F(G)47x
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P5.1|-->LED
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//******************************************************************************
#include  <msp430xG47x.h>

char value;                                 // 8-bit value to write to seg C

// Function prototypes
void write_SegC(char value);
void copy_C2D(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  FCTL2 = FWKEY + FSSEL0 + FN1;             // MCLK/3 for Flash Timing Generator
  P5DIR |= BIT1;                            // P5.1 output
  TACCTL0 = CCIE;                           // TACCR0 interrupt enabled
  TACCR0 = 50000;
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode
  value = 0;                                // initialize value
  __enable_interrupt();                     // enable interrupts

  while(1)                                  // Repeat forever
  {
    write_SegC(value++);                    // Write segment C, increment value
    copy_C2D();                             // Copy segment C to D
    __no_operation();                       // SET BREAKPOINT HERE
  }
}

void write_SegC(char value)
{
  char *Flash_ptr;                          // Flash pointer
  unsigned int i;

  Flash_ptr = (char *)0x1040;               // Initialize Flash pointer
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY + ERASE + EEI;              // Set Erase bit, allow interrupts
  *Flash_ptr = 0;                           // Dummy write to erase Flash seg

  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i = 0; i < 64; i++)
  {
    *Flash_ptr++ = value;                   // Write value to flash
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

void copy_C2D(void)
{
  char *Flash_ptrC;                         // Segment C pointer
  char *Flash_ptrD;                         // Segment D pointer
  unsigned int i;

  Flash_ptrC = (char *)0x1040;              // Initialize Flash segment C ptr
  Flash_ptrD = (char *)0x1000;              // Initialize Flash segment D ptr
  FCTL1 = FWKEY + ERASE + EEI;              // Set Erase bit, allow interrupts
  FCTL3 = FWKEY;                            // Clear Lock bit
  *Flash_ptrD = 0;                          // Dummy write to erase Flash seg D
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i = 0; i < 64; i++)
  {
    *Flash_ptrD++ = *Flash_ptrC++;          // copy value segment C to seg D
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

// Timer A0 interrupt service routine
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A(void)
{
  P5OUT ^= BIT1;                            // Toggle P5.1
}


//******************************************************************************
//  MSP430F22x4 Demo - Flash In-System Programming w/ EEI, Copy SegD to A/B/C
//
//  Description: This program first erases flash seg D, then it increments all
//  values in seg D, then it erases segs A,B,C and copies D to those locations
//  The EEI bit is set for the Flash Erase Cycles. This does allow the Timer_A
//  Interrupts to be handled also during the Segment erase time.
//  ACLK = n/a, MCLK = SMCLK = CALxxx_1MHZ = 1MHz
//  //* Set Breakpoint on NOP in the Mainloop to avoid Stressing Flash *//
//
//               MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

char  value;                                // 8-bit value to write to seg D

// Function prototypes
void write_SegD(char value);
void copy_D2A(void);
void copy_D2B(void);
void copy_D2C(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO to 1MHz
  DCOCTL = CALDCO_1MHZ;
  FCTL2 = FWKEY + FSSEL0 + FN1;             // MCLK/3 for Flash Timing Generator
  P1DIR |= 0x01;                            // P1.0 output
  TACCTL0 = CCIE;                           // TACCR0 interrupt enabled
  TACCR0 = 50000;
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode
  value = 0;                                // Initialize value
  __enable_interrupt();                     // Enable interrupts

  while(1)                                  // Repeat forever
  {
    write_SegD(value++);                    // Write segment D, increment value
    copy_D2A();                             // Copy segment D to A
    copy_D2B();                             // Copy segment D to B
    copy_D2C();                             // Copy segment D to C
    __no_operation();                       // Set breakpoint here
  }
}

void write_SegD(char value)
{
  char *Flash_ptr;                          // Flash pointer
  unsigned int i;

  Flash_ptr = (char *)0x1000;               // Initialize Flash pointer
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

// Warning: When this function is called, it MUST complete or
// DCO calibration constants will be lost
void copy_D2A(void)
{
  char *Flash_ptrA;                         // Segment A pointer
  char *Flash_ptrD;                         // Segment D pointer
  unsigned int i;
  char CAL_DATA[8];

  Flash_ptrA = (char *)0x10F8;              // Initialize Flash segment A ptr
  for (i = 0; i < 8; i++)
  {
    CAL_DATA[i] = *Flash_ptrA++;            // Save DCO constants
  }

  Flash_ptrA = (char *)0x10C0;              // Initialize Flash segment A ptr
  Flash_ptrD = (char *)0x1000;              // Initialize Flash segment D ptr
  FCTL3 = FWKEY + LOCKA;                    // Clear LOCK & LOCKA bits
  FCTL1 = FWKEY + ERASE + EEI;              // Set Erase bit, allow interrupts
  *Flash_ptrA = 0;                          // Dummy write to erase Flash seg A
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i = 0; i < 56; i++)
  {
    *Flash_ptrA++ = *Flash_ptrD++;          // copy value segment D to seg A
  }

  for (i = 0; i < 8; i++)
  {
    *Flash_ptrA++ = CAL_DATA[i];            // re-flash DCO calibration data
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCKA + LOCK;             // Set LOCK & LOCKA bit
}

void copy_D2B(void)
{
  char *Flash_ptrB;                         // Segment B pointer
  char *Flash_ptrD;                         // Segment D pointer
  unsigned int i;

  Flash_ptrB = (char *)0x1080;              // Initialize Flash segment B ptr
  Flash_ptrD = (char *)0x1000;              // Initialize Flash segment D ptr
  FCTL3 = FWKEY;                            // Clear LOCK bit
  FCTL1 = FWKEY + ERASE + EEI;              // Set Erase bit, allow interrupts
  *Flash_ptrB = 0;                          // Dummy write to erase Flash seg B
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i = 0; i < 64; i++)
  {
    *Flash_ptrB++ = *Flash_ptrD++;          // copy value segment D to seg B
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

void copy_D2C(void)
{
  char *Flash_ptrC;                         // Segment C pointer
  char *Flash_ptrD;                         // Segment D pointer
  unsigned int i;

  Flash_ptrC = (char *)0x1040;              // Initialize Flash segment C ptr
  Flash_ptrD = (char *)0x1000;              // Initialize Flash segment D ptr
  FCTL3 = FWKEY;                            // Clear LOCK bit
  FCTL1 = FWKEY + ERASE + EEI;              // Set Erase bit, allow interrupts
  *Flash_ptrC = 0;                          // Dummy write to erase Flash seg C
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i = 0; i < 64; i++)
  {
    *Flash_ptrC++ = *Flash_ptrD++;          // copy value segment D to seg C
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}

//****************************************************************************
//  MSP-FET430P120 Demo - Flash In-System Programming, Copy SegA to SegB
//
//  Description: This program first erases flash seg A, then it increments all
//  values in seg A, then it erases seg B, then  copies seg A to seg B.
//  Assumed MCLK 550kHz - 900kHz.
//  //* Set Breakpoint on NOP in the Mainloop to avoid Stressing Flash *//
//
//               MSP430F123(2)
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//
//  M. Mitchell
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x12x2.h>

char  value;                                // 8-bit value to write to segment A

// Function prototypes
void  write_SegA (char value);
void  copy_A2B (void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  FCTL2 = FWKEY + FSSEL0 + FN0;             // MCLK/2 for Flash Timing Generator
  value = 0;                                // initialize value

  while(1)                                  // Repeat forever
  {
    write_SegA(value++);                    // Write segment A, increment value
    copy_A2B();                             // Copy segment A to B
    _NOP();                                 // SET BREAKPOINT HERE
  }
}

void write_SegA (char value)
{
  char *Flash_ptr;                          // Flash pointer
  unsigned int i;

  Flash_ptr = (char *) 0x1080;              // Initialize Flash pointer
  FCTL1 = FWKEY + ERASE;                    // Set Erase bit
  FCTL3 = FWKEY;                            // Clear Lock bit
  *Flash_ptr = 0;                           // Dummy write to erase Flash segment

  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i=0; i<128; i++)
  {
    *Flash_ptr++ = value;                   // Write value to flash
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}


void copy_A2B (void)
{
  char *Flash_ptrA;                         // Segment A pointer
  char *Flash_ptrB;                         // Segment B pointer
  unsigned int i;

  Flash_ptrA = (char *) 0x1080;             // Initialize Flash segment A pointer
  Flash_ptrB = (char *) 0x1000;             // Initialize Flash segment B pointer
  FCTL1 = FWKEY + ERASE;                    // Set Erase bit
  FCTL3 = FWKEY;                            // Clear Lock bit
  *Flash_ptrB = 0;                          // Dummy write to erase Flash segment B
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i=0; i<128; i++)
  {
    *Flash_ptrB++ = *Flash_ptrA++;           // copy value segment A to segment B
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}
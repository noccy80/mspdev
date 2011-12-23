//******************************************************************************
//  MSP430F530x Demo - Single-Byte Flash In-System Programming, Copy SegC to SegD
//
//  Description: This program first erases flash seg C, then it increments all
//  values in seg C, then it erases seg D, then copies seg C to seg D. Starting
//  addresses of segments defined in this code: Seg C-0x1880, Seg D-0x1800.
//  ACLK = REFO = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
//  //* Set Breakpoint on NOP in the Mainloop to avoid Stressing Flash *//
//
//                MSP430F530x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

char value;                                 // 8-bit value to write to seg C

// Function prototypes
void write_SegC(char value);
void copy_C2D(void);

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  value = 0;                                // initialize value

  while(1)
  {
    write_SegC(value++);                    // Write segment C, increment value
    copy_C2D();                             // Copy segment C to D
    __no_operation();                       // Loop forever, SET BREAKPOINT HERE
  }
}

//------------------------------------------------------------------------------
// Input = value, holds value to write to Seg C
//------------------------------------------------------------------------------
void write_SegC(char value)
{
  unsigned int i;
  char * Flash_ptr;                         // Initialize Flash pointer
  Flash_ptr = (char *) 0x1880;
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY+ERASE;                      // Set Erase bit
  *Flash_ptr = 0;                           // Dummy write to erase Flash seg
  FCTL1 = FWKEY+WRT;                        // Set WRT bit for write operation

  for (i = 0; i < 128; i++)
  {
    *Flash_ptr++ = value;                   // Write value to flash
  }
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY+LOCK;                       // Set LOCK bit
}

//------------------------------------------------------------------------------
// Copy Seg C to Seg D
//------------------------------------------------------------------------------
void copy_C2D(void)
{
  unsigned int i;
  char *Flash_ptrC;
  char *Flash_ptrD;

  Flash_ptrC = (char *) 0x1880;             // Initialize Flash segment C ptr
  Flash_ptrD = (char *) 0x1800;             // Initialize Flash segment D ptr

  __disable_interrupt();                    // 5xx Workaround: Disable global
                                            // interrupt while erasing. Re-Enable
                                            // GIE if needed
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY+ERASE;                      // Set Erase bit
  *Flash_ptrD = 0;                          // Dummy write to erase Flash seg D
  FCTL1 = FWKEY+WRT;                        // Set WRT bit for write operation

  for (i = 0; i < 128; i++)
  {
    *Flash_ptrD++ = *Flash_ptrC++;          // copy value segment C to seg D
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY+LOCK;                       // Set LOCK bit
}

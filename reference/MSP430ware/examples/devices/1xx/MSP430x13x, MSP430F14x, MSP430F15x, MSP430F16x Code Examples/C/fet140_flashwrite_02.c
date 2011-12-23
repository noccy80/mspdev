//****************************************************************************
//  MSP430F14x Demo - Flash In-System Programming, BlockWrite
//
//  Description: This program first copies the FlashWrite routine to RAM, then
//  erases flash seg A, then it increments all values in seg A using the 64
//  byte block write mode.
//
//  Assumed default MCLK = DCO ~800 kHz.
//  Minimum RAM requirement = 512 bytes 
//
//  ** Set Breakpoint on NOP in the Mainloop to avoid Stressing Flash **
//
//               MSP430F149
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//
//  H. Grewal / L. Westlund
//  Texas Instruments Inc.
//  Jun 2006
//  Built with IAR Embedded Workbench Version: 3.30A
//******************************************************************************

#include <msp430x16x.h>

// Global variables
char value = 0;                             // 8-bit value to write to segment A
char* Flash_ptr;                            // Flash pointer
char* RAM_ptr;                              // RAM pointer
char* END_ptr;                              // End of FlashWrite routine

// Function prototypes
void FlashWrite();
void CopyRoutine();
void End_of_FlashWrite();

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  _DINT();                                  // Diable Interrupts
  CopyRoutine();                            // Copy FlashWrite routine to RAM
  _EINT();                                  // Enable Interrupts

  while(1)                                  // Repeat forever
  {
    Flash_ptr = (char *) 0x1000;            // Initialize Flash pointer
    FCTL2 = FWKEY + FSSEL1 + FN0;           // MCLK/2 for Flash Timing Generator
    FCTL1 = FWKEY + ERASE;                  // Set Erase bit
    FCTL3 = FWKEY;                          // Clear Lock bit

    *Flash_ptr = 0;                         // Dummy write to erase Flash segment
    while(!(FCTL3 & WAIT));                 // WAIT until Flash is ready
    asm("CALL #300h");                      // Execute FlashWrite from RAM
                                            // Inline Assembly
    value++;                                // Increment value
    _NOP();                                 // SET BREAKPOINT HERE
  }
}

void CopyRoutine()
{
  Flash_ptr = (char*)FlashWrite;            // Set pointer to FlashWrite routine
  RAM_ptr = (char*)0x0300;                  // Set pointer to RAM
  END_ptr = (char*)End_of_FlashWrite;       // Set pointer to End_of_FlashWrite

  while(END_ptr != Flash_ptr)               // Check for end of FlashWrite
  {
    *RAM_ptr = *Flash_ptr;                  // Copy word to RAM
    Flash_ptr++;                            // Increment Flash pointer
    RAM_ptr++;                              // Increment RAM pointer
  }
}

void FlashWrite()
{
  volatile int i;                           // Use as write counter
  Flash_ptr = (char*)0x1000;                // Initialize Flash pointer
  while(FCTL3 & BUSY);                      // Check Flash BUSY bit
  FCTL1 = FWKEY + BLKWRT + WRT;             // Enable block-write operation
  for(i = 0; i < 64; i++)
  {
    *Flash_ptr = value;                     // Write value to flash
    Flash_ptr++;                            // Double-increment Flash pointer
    while(!(FCTL3 & WAIT));                 // WAIT until Flash is ready
  }
  FCTL1 = FWKEY;                            // Clear BLKWRT & WRT bits
  while(FCTL3 & BUSY);                      // Check Flash BUSY bit
  FCTL3 = FWKEY + LOCK;                     // Reset LOCK bit
  return;                                   // Exits routine
}

void End_of_FlashWrite(){}                  // Marks end of FlashWrite

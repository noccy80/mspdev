//******************************************************************************
//  MSP430x21x1 Demo - Flash In-System Programming w/ EEI, Copy SegC to SegD
//
//  Description: This program first erases flash seg D, then it increments all
//  values in seg D, then it erases segs A,B,C and copies D to those locations
//  The EEI bit is set for the Flash Erase Cycles. This does allow the Timer_A
//  Interrupts to be handled also during the Segment erase time.
//  MCLK = 1Mhz Calibrated Value
//  //* Set Breakpoint on NOP in the Mainloop to avoid Stressing Flash *//
//
//               MSP430F21x1
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//
//  Z. Albus / L. Westlund
//  Texas Instruments Inc.
//  December 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.40A
//******************************************************************************

#include <msp430x21x1.h>

char  value;                                // 8-bit value to write to segment D

// Function prototypes
void write_SegD (char value);
void copy_D2A (void);
void copy_D2B (void);
void copy_D2C (void);

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO to 1MHz
  DCOCTL = CALDCO_1MHZ;

  P1DIR |= 0x01;                            // P1.0 output
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 1000;
  TACTL = TASSEL_1 + MC_1;                  // ACLK, upmode

  WDTCTL = WDT_ADLY_1000;                   // WDT 1s, ACLK, interval timer
  IE1 |= WDTIE;                             // Enable WDT interrupt

  _EINT();                                  // enable interrupts

  FCTL2 = FWKEY + FSSEL0 + FN1;             // MCLK/3 for Flash Timing Generator
  value = 0;                                // initialize value

  while(1)                                  // Repeat forever
  {
    LPM3;
    write_SegD(value++);                    // Write segment D, increment value
    copy_D2A();                             // Copy segment D to A
    copy_D2B();                             // Copy segment D to B
    copy_D2C();                             // Copy segment D to C
  }
}

void write_SegD (char value)
{
  char *Flash_ptr;                          // Flash pointer
  unsigned int i;

  Flash_ptr = (char *) 0x1000;              // Initialize Flash pointer
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

// Warning: When this function is called, it MUST complete or
// DCO calibration constants will be lost
void copy_D2A (void)
{
  char *Flash_ptrA;                         // Segment A pointer
  char *Flash_ptrD;                         // Segment D pointer
  unsigned int i;
  char CAL_DATA[10];

  Flash_ptrA = (char *) 0x10F6;             // Initialize Flash segment A pointer
  for (i=0; i<10; i++)
  {
      CAL_DATA[i] = *Flash_ptrA++;          // Save DCO constants
  }

  Flash_ptrA = (char *) 0x10C0;             // Initialize Flash segment A pointer
  Flash_ptrD = (char *) 0x1000;             // Initialize Flash segment D pointer
  FCTL1 = FWKEY + ERASE + EEI;              // Set Erase bit, allow interrupts
  FCTL3 = FWKEY + LOCKA;                    // Clear LOCK & LOCKA bits
  *Flash_ptrA = 0;                          // Dummy write to erase Flash segment A
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i=0; i<54; i++)
  {
    *Flash_ptrA++ = *Flash_ptrD++;          // copy value segment D to segment A
  }

  for (i=0; i<10; i++)
  {
    *Flash_ptrA++ = CAL_DATA[i];            // re-flash DCO calibration data
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCKA + LOCK;             // Set LOCK & LOCKA bit
}

void copy_D2B (void)
{
  char *Flash_ptrB;                         // Segment B pointer
  char *Flash_ptrD;                         // Segment D pointer
  unsigned int i;

  Flash_ptrB = (char *) 0x1080;             // Initialize Flash segment B pointer
  Flash_ptrD = (char *) 0x1000;             // Initialize Flash segment D pointer
  FCTL1 = FWKEY + ERASE + EEI;              // Set Erase bit, allow interrupts
  FCTL3 = FWKEY;                            // Clear LOCK bit
  *Flash_ptrB = 0;                          // Dummy write to erase Flash segment B
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i=0; i<64; i++)
  {
    *Flash_ptrB++ = *Flash_ptrD++;          // copy value segment D to segment B
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

void copy_D2C (void)
{
  char *Flash_ptrC;                         // Segment C pointer
  char *Flash_ptrD;                         // Segment D pointer
  unsigned int i;

  Flash_ptrC = (char *) 0x1040;             // Initialize Flash segment C pointer
  Flash_ptrD = (char *) 0x1000;             // Initialize Flash segment D pointer
  FCTL1 = FWKEY + ERASE + EEI;              // Set Erase bit, allow interrupts
  FCTL3 = FWKEY;                            // Clear LOCK bit
  *Flash_ptrC = 0;                          // Dummy write to erase Flash segment C
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i=0; i<64; i++)
  {
    *Flash_ptrC++ = *Flash_ptrD++;          // copy value segment D to segment C
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

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  LPM3_EXIT;
}

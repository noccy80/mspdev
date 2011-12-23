//******************************************************************************
//  MSP430F22x4 Demo - DCO Calibration Constants Programmer
//
//  NOTE: THIS CODE REPLACES THE TI FACTORY-PROGRAMMED DCO CALIBRATION
//  CONSTANTS LOCATED IN INFOA WITH NEW VALUES. USE ONLY IF THE ORIGINAL
//  CONSTANTS ACCIDENTALLY GOT CORRUPTED OR ERASED.
//
//  Description: This code re-programs the F2xx DCO calibration constants.
//  A software FLL mechanism is used to set the DCO based on an external
//  32kHz reference clock. After each calibration, the values from the
//  clock system are read out and stored in a temporary variable. The final
//  frequency the DCO is set to is 1MHz, and this frequency is also used
//  during Flash programming of the constants. The program end is indicated
//  by the blinking LED.
//  ACLK = LFXT1/8 = 32768/8, MCLK = SMCLK = target DCO
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//
//
//           MSP430F22x4
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|--> LED
//        |           P2.1|--> SMLCK = target DCO
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

#define DELTA_1MHZ    244                   // 244 x 4096Hz = 999.4Hz
#define DELTA_8MHZ    1953                  // 1953 x 4096Hz = 7.99MHz
#define DELTA_12MHZ   2930                  // 2930 x 4096Hz = 12.00MHz
#define DELTA_16MHZ   3906                  // 3906 x 4096Hz = 15.99MHz

unsigned char CAL_DATA[8];                  // Temp. storage for constants
volatile unsigned int i;
int j;
char *Flash_ptrA;                           // Segment A pointer
void Set_DCO(unsigned int Delta);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  for (i = 0; i < 0xfffe; i++);             // Delay for XTAL stabilization
  P1OUT = 0x00;                             // Clear P1 output latches
  P1DIR = 0x01;                             // P1.0 output
  P2SEL |= 0x02;                            // P2.1 SMCLK output
  P2DIR |= 0x02;                            // P2.1 output

  j = 0;                                    // Reset pointer

  Set_DCO(DELTA_16MHZ);                     // Set DCO and obtain constants
  CAL_DATA[j++] = DCOCTL;
  CAL_DATA[j++] = BCSCTL1;

  Set_DCO(DELTA_12MHZ);                     // Set DCO and obtain constants
  CAL_DATA[j++] = DCOCTL;
  CAL_DATA[j++] = BCSCTL1;

  Set_DCO(DELTA_8MHZ);                      // Set DCO and obtain constants
  CAL_DATA[j++] = DCOCTL;
  CAL_DATA[j++] = BCSCTL1;

  Set_DCO(DELTA_1MHZ);                      // Set DCO and obtain constants
  CAL_DATA[j++] = DCOCTL;
  CAL_DATA[j++] = BCSCTL1;

  Flash_ptrA = (char *)0x10C0;              // Point to beginning of seg A
  FCTL2 = FWKEY + FSSEL0 + FN1;             // MCLK/3 for Flash Timing Generator
  FCTL1 = FWKEY + ERASE;                    // Set Erase bit
  FCTL3 = FWKEY + LOCKA;                    // Clear LOCK & LOCKA bits
  *Flash_ptrA = 0x00;                       // Dummy write to erase Flash seg A
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation
  Flash_ptrA = (char *)0x10F8;              // Point to beginning of cal consts
  for (j = 0; j < 8; j++)
    *Flash_ptrA++ = CAL_DATA[j];            // re-flash DCO calibration data
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCKA + LOCK;             // Set LOCK & LOCKA bit

  while (1)
  {
    P1OUT ^= 0x01;                          // Toggle LED
    for (i = 0; i < 0x4000; i++);           // SW Delay
  }
}

void Set_DCO(unsigned int Delta)            // Set DCO to selected frequency
{
  unsigned int Compare, Oldcapture = 0;

  BCSCTL1 |= DIVA_3;                        // ACLK = LFXT1CLK/8
  TACCTL2 = CM_1 + CCIS_1 + CAP;            // CAP, ACLK
  TACTL = TASSEL_2 + MC_2 + TACLR;          // SMCLK, cont-mode, clear

  while (1)
  {
    while (!(CCIFG & TACCTL2));             // Wait until capture occured
    TACCTL2 &= ~CCIFG;                      // Capture occured, clear flag
    Compare = TACCR2;                       // Get current captured SMCLK
    Compare = Compare - Oldcapture;         // SMCLK difference
    Oldcapture = TACCR2;                    // Save current captured SMCLK

    if (Delta == Compare)
      break;                                // If equal, leave "while(1)"
    else if (Delta < Compare)
    {
      DCOCTL--;                             // DCO is too fast, slow it down
      if (DCOCTL == 0xFF)                   // Did DCO roll under?
        if (BCSCTL1 & 0x0f)
          BCSCTL1--;                        // Select lower RSEL
    }
    else
    {
      DCOCTL++;                             // DCO is too slow, speed it up
      if (DCOCTL == 0x00)                   // Did DCO roll over?
        if ((BCSCTL1 & 0x0f) != 0x0f)
          BCSCTL1++;                        // Sel higher RSEL
    }
  }
  TACCTL2 = 0;                              // Stop TACCR2
  TACTL = 0;                                // Stop Timer_A
  BCSCTL1 &= ~DIVA_3;                       // ACLK = LFXT1CLK
}

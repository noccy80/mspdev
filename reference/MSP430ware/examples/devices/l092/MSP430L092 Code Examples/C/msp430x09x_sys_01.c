//********************************************************************************
//  Description: Toggle P1.0 using system NMI ISR. Software Toggles P1.0 in VMA
//  interrupt by writing to vacant memory address 0x2400. 
//  Proper use of the SYSSNIV interrupt vector generator is demonstrated
/****************************VMA**************************************************/
/*                                                                               */
/*                                                                               */
/*                                                                               */
/*                               +----L092---+                                   */
/*                               |*1      14 |                                   */
/*                               | 2      13 |                                   */
/*                               | 3      12 |                                   */
/*                               | 4      11 |                                   */
/*                               | 5      10 |                                   */
/*     P1.0 -Toggle Output  <-   | 6       9 |                                   */
/*                               | 7       8 |                                   */
/*                               +-----------+                                   */
/*                                                                               */
/*  D.Dang/D.Archbold/D.Szmulewicz                                               */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/

#include "msp430x09x.h"  
int *vma_ptr;
void main(void)
{ 
  	WDTCTL = WDTPW + WDTHOLD;                   // Stop WDT
    P1DIR = BIT0;                               // Set P1.0 as output
    vma_ptr = (int *)0x2400;                    // Initialize ponter to Vacant memory
    SFRIE1 = VMAIE;                             // Enable VMA interrupt
  
    while(1) 
  { 
  	    *vma_ptr = 0x56;                        // Write to Vacant memory
        __bis_SR_register(LPM0_bits);           // Enter LPM0
  }	    
}

// SYSSNIV Interrupt Vector handler
#pragma vector=SYSNMI_VECTOR;  
__interrupt void SNI_ISR (void)
{
  switch (__even_in_range(SYSSNIV, 10))         // Efficient switch-implementation
  { 
  	case  2: break;                             // Vector 2: SVMIFG
  	case  4: P1OUT ^= BIT0;                     // Vector 4: VMAIFG 
    __bic_SR_register_on_exit(LPM0_bits);       // Exit Active
  	         break;   
  	case  6: break;                             // Vector 6: JMBINIFG
  	case  8: break;                             // Vector 8: JMBOUTIFG
  	case 10: break;                             // Vector 10: Reserved
  }	
}         



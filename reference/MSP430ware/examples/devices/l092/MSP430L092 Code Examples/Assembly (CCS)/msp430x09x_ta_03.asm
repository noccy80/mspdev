;  Description: Toggle P1.0 using software and Timer_A0 overflow ISR. Timer0_A  
;  In this example an ISR triggers when TA0 overflows. Inside the TA overflow
;  ISR P1.0 is toggled.                                                                   
;  Proper use of the TA0IV interrupt vector generator is demonstrated.        
;***************************Timer_A0*********************************************/
;                                                                              
;                                                                               
;                                                                               
;                               +----L092---+                                   
;                               |*1      14 |                                   
;                               | 2      13 |                                   
;                               | 3      12 |                                 
;                               | 4      11 |                                   
;                               | 5      10 |                                
;                               | 6       9 |                                 
;     P1.1 SMCLK~ 1Mhz/32  <-   | 7       8 |                                  
;                               +-----------+                               
;                                                                               
;  D.Dang;D.Archbold;D.Szmulewicz
;  Texas Instruments Inc.
;  Built with CCS version 4.2.0
;******************************************************************************

 .cdecls C,LIST,"msp430x09x.h"
;-------------------------------------------------------------------------------
            .global main
            .text                           ; Assemble to memory
;-------------------------------------------------------------------------------
main        mov.w   #0x23FC,SP              ; Initialize stack pointer to RAM
            mov.w   #WDTPW + WDTHOLD,&WDTCTL ; Stop WDT  
 
            bis.b   #BIT0+BIT1,&P1DIR       ; P1.0 Output direction
            bis.b   #BIT1,&P1SEL0           ;              
            bis.b   #BIT1,&P1SEL1           ;    
    
;***********************
; Setup CCS            
; SMCLK = HFCLK       
;***********************
           mov.w    #CCSKEY,&CCSCTL0        ; Unlock CCS

check      mov.w    #0,&CCSCTL7             ; Clear HF & LF OSC fault flags
           mov.w    #0,&SFRIFG1             ; Clear OFIFG
           bit.w    #OFIFG,&SFRIFG1         ; Oscillator Flag(s)?
           jnz      check
  
           mov.w    #DIVS_5,&CCSCTL5        ; Set the Dividers for SMCLK to 32
           bis.b    #SELS_0,&CCSCTL4        ; Select HFCLK/DCO as the source for SMCLK 
           bis.b    #0xFF,&CCSCTL0_H        ;  Lock CCS
   
; Lock by writing to upper byte 
          
          mov.w    #TASSEL_2 + MC_2 + TAIE,&TA0CTL ; SMCLK, contmode, TA interrupt enable
  
          bis.w    #LPM0+GIE,SR             ; LPM0, enable interrupts
          nop                               ; Required only for debugger

;-------------------------------------------------------------------------------
TAX_ISR;    Common ISR for overflow
;-------------------------------------------------------------------------------
          add.w     &TA0IV,PC                ; Add Timer_A offset vector
          reti
          reti                              ; TA0CCR1 not used
          reti                              ; TA0CCR2 not used
          reti                              ; Reserve
          reti                              ; Reserve
          reti                              ; Reserve
          reti                              ; Reserve
          xor.b     #BIT0,&P1OUT            ; overflow -> Toggle P1.0
          reti                              ; Return from overflow ISR

;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".int06"        		; Timer_AX Vector
            .short	TAX_ISR                 ;
            .end

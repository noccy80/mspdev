;********************************************************************************
;  Description: Toggle P1.0 using system NMI ISR. Software Toggles P1.0 in VMA
;  interrupt by writing to vacant memory address 0x2400. 
;  Proper use of the SYSSNIV interrupt vector generator is demonstrated
;***************************VMA************************************************* 
;                                                                                
;                                                                                
;                                                                                
;                               +----L092---+                                    
;                               |*1      14 |                                    
;                               | 2      13 |                                    
;                               | 3      12 |                                    
;                               | 4      11 |                                    
;                               | 5      10 |                                    
;     P1.0 -Toggle Output  <-   | 6       9 |                                    
;                               | 7       8 |                                    
;                               +-----------+                                    
;                                                                                
;  D.Dang/D.Archbold/D.Szmulewicz
;  Texas Instruments Inc.
;  Built with CCS version 4.2.0
;******************************************************************************
 .cdecls C,LIST,"msp430x09x.h"
;-------------------------------------------------------------------------------
vma_ptr     .equ    0x2400                  ; Pointer to Vacant memory
;-------------------------------------------------------------------------------
            .global main
            .text                           ; Assemble to memory
;-------------------------------------------------------------------------------
main        mov.w   #WDTPW + WDTHOLD,&WDTCTL ; Stop WDT       
            bis.w   #BIT0,&P1DIR            ; Set P1.0 to output direction
    
            mov.w   #VMAIE,&SFRIE1          ; Enable VMA interrupt
  
while_loop  mov.w   #0x22,&vma_ptr          ; Write to Vacant memory
            bis.w   #LPM0,SR                ; LPM0, enable interrupts
  	        jmp     while_loop
;-------------------------------------------------------------------------------
SNI_ISR;   SYSSNIV Interrupt Vector handler
;-------------------------------------------------------------------------------
          add.w     &SYSSNIV,PC             ; Add offset vector
          reti
          reti                              ; Vector 2: SVMIFG
          xor.b     #BIT0,&P1OUT            ; Vector 4: VMAIFG
          bic.w     #LPM0,0(SP)             ; Modify SP so that it enters active mode after reti  
          reti                              ; Return from ISR
          reti                              ; Vector 6: JMBINIFG
          reti                              ; Vector 8: JMBOUTIFG
          reti                              ; Vector 10: Reserved

;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".int14"        		; SNI Vector
            .short	SNI_ISR                 
            .end

 



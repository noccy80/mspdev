;***************************WDT Toggle Port Pin ******************************** 
;Toggle P1.0 using software timed by WDT ISR                                      
;                                                                                
;                                                                                
;                               +----L092---+                                    
;                               |*1      14 |                                    
;                               | 2      13 |                                    
;                               | 3      12 |                                    
;                               | 4      11 |                                    
;                               | 5      10 |                                    
;       P1.0 -Toggle Output  <- | 6       9 |                                    
;                               | 7       8 |                                    
;                               +-----------+                                    
;                                                                                
;  D.Dang/D.Archbold                                                             
;  Texas Instruments Inc.                                                        
;  D.Dang;D.Archbold;D.Szmulewicz
;  Texas Instruments Inc.
;  Built with CCS version 4.2.0
;******************************************************************************

 .cdecls C,LIST,"msp430x09x.h"
;-------------------------------------------------------------------------------
            .global main
            .text                           ; Assemble to memory
;-------------------------------------------------------------------------------
main
            mov.w   #0xF7FF,SP                ; Initialize stack pointer
            mov.w   #WDTPW+WDTHOLD,&WDTCTL ; Stop WDT  
            bis.b   #BIT0,&P1DIR            ; Set P1.0 to output direction
            bis.b   #BIT0,&P1OUT            ; Output high on P1.0
    

	
	;********************** 
	; Setup CCS             
	; ACLK = VLO            
	; MCLK = HFCLK/8        
	;********************** 
	        mov.w   #CCSKEY,&CCSCTL0        ; Unlock CCS
	        mov.w   #SELA_1,&CCSCTL4        ; Select LFCLK/VLO as the ACLK source         
            bic.w   #DIVA_5,&CCSCTL5        ; Divide fACLK by 4
	        bis.b   #0xFF,&CCSCTL0_H        ; Lock CCS
; Lock by writing to upper byte  
	
	        mov.w   #WDT_ADLY_16,&WDTCTL    ; WDT SMCLK Delay Interval specify  
            bis.b   #WDTIE,&SFRIE1          ; Enable WDT interrupt              
    

            bis.w   #LPM0+GIE,SR            ; LPM0, enable interrupts
            nop                             ; Required only for debugger
;-------------------------------------------------------------------------------
WDT_ISR;    Watchdog Timer interrupt service routine
;-------------------------------------------------------------------------------
            xor.b   #BIT0,&P1OUT            ; P1.0 = toggle
            reti                            ; Return from ISR
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
         
            .sect   ".int10"                 ; WDT_vector
            .short  WDT_ISR                   ;WDT Vector
            .end

 
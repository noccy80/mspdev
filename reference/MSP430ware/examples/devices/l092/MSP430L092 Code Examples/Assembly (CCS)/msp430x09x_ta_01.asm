;  Description: Toggle P1.0 using software and Timer0_A0 ISR. Toggles every      
;  1000 SMCLK cycles. SMCLK provides clock source for TA0CLK.                    
;  During the Timer0_A0 ISR, P1.0 is toggled and 1000 clock cycles are added to                     
;  TA0CCR0. Timer0_A0 ISR is triggered every 1000 cycles. CPU is normally off     
;  and used only during TA ISR.                                                  
;                                                                                
;***************************Timer_A0*********************************************
;                                                                             
; Requirements: Download to EEPROM                                            
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
;  D.Dang/D.Archbold/D.Szmulewicz
;  Texas Instruments Inc.
;  Built with CCS version 4.2.0
;******************************************************************************

 .cdecls C,LIST,"msp430x09x.h"
;-------------------------------------------------------------------------------
            .global main
            .text                           ; Assemble to memory
;-------------------------------------------------------------------------------
main
            mov.w   #WDTPW + WDTHOLD,&WDTCTL ; Stop WDT  

;***********************
; Setup Ports           
;***********************
  
  	        bis.b   #BIT0,&P1OUT            ; P1.0 output
  	        bis.b   #BIT0,&P1DIR            ;               
            bis.b   #BIT1,&P1DIR  	        ;
            bis.b   #BIT1,&P1SEL0           ;    
          	bis.b   #BIT1,&P1SEL1           ;
    
;***********************
; Setup CCS            
; SMCLK = LFCLK        
;***********************
    	    mov.w   #CCSKEY,&CCSCTL0        ; Unlock CCS
    	    mov.w   #0,&CCSCTL5             ; Set the Dividers for SMCLK to 1
    	    mov.w   #SELM_1 + SELS_1 + SELA_1,&CCSCTL4 ; Select LFCLK/VLO as the source for ACLK, MCLK, and SMCLK   
    	    bis.b   #0xFF,&CCSCTL0_H        ; Lock CCS
; Lock by writing to upper byte 
  
         	mov.w   #CCIE,&TA0CCTL0         ; TA0CCR0 interrupt enabled
  	        mov.w   #1000,&TA0CCR0 			; Set value for TA0CCR0
 	        mov.w   #TASSEL_2 + MC_2 + TACLR,&TA0CTL ; SMCLK, cont mode
            bis.w   #LPM0+GIE,SR            ; LPM0, enable interrupts
            nop                             ; Required only for debugger
;-------------------------------------------------------------------------------
TA0_ISR                                     ; Toggle P1.0 Output
;-------------------------------------------------------------------------------
            xor.b   #BIT0,&P1OUT            ; P1.0 = toggle
            reti   
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".int07"                ; TIMER0_A0_VECTOR 
            .short  TA0_ISR                 ; TA0 Vector
            .end



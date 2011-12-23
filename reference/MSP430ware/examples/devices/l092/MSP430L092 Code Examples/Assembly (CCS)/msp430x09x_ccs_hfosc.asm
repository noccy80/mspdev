; Description: This program demonstrates how to configure ACLK, MCLK, and SMCLK  
; to use the HF clock source.                                                    
;***************************Timer_A0******************************************** 
;  Requirements:Oscilloscope                                                     
;                                                                                
;                                                                                
;                               +----L092---+                                    
;                               |*1      14 |                                    
;                               | 2      13 |                                    
;                               | 3      12 |  -> P1.4 MCLK ~1MHz                
;                               | 4      11 |                                    
;                               | 5      10 |                                    
;     P1.0 ACLK ~1MHz   <-      | 6       9 |                                    
;     P1.1 SMCLK ~1MHz  <-      | 7       8 |                                    
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
main        mov.w   #WDTPW + WDTHOLD,&WDTCTL ; Stop WDT  

   ; Setup Port 1 to output ACLK, SMCLK, and MCLK
   ; P1.0 = ACLK -> P1DIR.0 = 1; P1SEL0.0 = 1; P1SEL1.0 = 1;
   ; P1.1 = SMCLK-> P1DIR.1 = 1; P1SEL0.1 = 1; P1SEL1.1 = 1;
   ; P1.4 = MCLK -> P1DIR.4 = 1; P1SEL0.4 = 1; P1SEL1.4 = 1;
    
            bis.b   #BIT0 + BIT1 + BIT4,&P1DIR;
            bis.b   #BIT0 + BIT1 + BIT4,&P1SEL0;
            bis.b   #BIT0 + BIT1 + BIT4,&P1SEL1                
	
	;********************** 
	; Setup CCS             
	; ACLK = HFCLK/DCO      
    ; MCLK = HFCLK/DCO      
    ; SMCLK = HFCLK/DCO     
	;********************** 
            mov.w    #CCSKEY,&CCSCTL0       ; Unlock CCS

check       mov.w    #0,&CCSCTL7            ; Clear HF & LF OSC fault flags
            mov.w    #0,&SFRIFG1            ; Clear OFIFG
            bit.w    #OFIFG,&SFRIFG1        ; Oscillator Flag(s)?
            jnz      check    
            
            mov.w    #SELA_0 + SELM_0 +SELS_0,& CCSCTL4 ; Select HFCLK/DCO as the source for ACLK, MCLK, and SMCLK   
            mov.w    #DIVA_0 + DIVM_0 + DIVS_0,&CCSCTL5 ; Set the Dividers for ACLK, MCLK, and SMCLK to 1
            bis.b    #0xFF,&CCSCTL0_H       ;  Lock CCS   
   
	
        ; Lock by writing to upper byte  
	
loop        jmp     loop
  


 
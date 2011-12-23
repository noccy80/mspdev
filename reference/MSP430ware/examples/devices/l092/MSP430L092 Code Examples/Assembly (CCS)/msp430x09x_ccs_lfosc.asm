; Description: This program demonstrates how to configure ACLK, MCLK, and SMCLK  
; to use the LF clock source.                                                    
;***************************Timer_A0******************************************** 
;  Requirements: Oscilloscope to measure clock frequencies                       
;                                                                                
;                                                                                
;                               +----L092---+                                    
;                               |*1      14 |                                    
;                               | 2      13 |                                    
;                               | 3      12 |  -> P1.4 MCLK~ 17.9kHz             
;                               | 4      11 |                                    
;                               | 5      10 |                                    
;     P1.0 ACLK~ 17.9kHz   <-   | 6       9 |                                    
;     P1.1 SMCLK~ 17.9kHz  <-   | 7       8 |                                    
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
	; ACLK = LFCLK/1        
      ; MCLK = LFCLK/1        
      ; SMCLK = LFCLK/1       
	;********************** 
            mov.w   #CCSKEY,&CCSCTL0                       ; Unlock CCS  
  
            bis.b   #SELA_1 + SELM_1 + SELS_1,&CCSCTL4     ; Select LFCLK as the source for ACLK, MCLK, and SMCLK  
            mov.w   #DIVA_0 + DIVM_0 + DIVS_0,&CCSCTL5     ; Set the Dividers for ACLK, MCLK, and SMCLK to 1
            bis.b   #0xFF,&CCSCTL0_H 

	; Lock by writing to upper byte  
	
loop        jmp     loop  
   




 
;******************************************************************************
;  Description: This program generates two PWM outputs on P1.5,6 using
;  Timer0_A3 configured for up/down mode. The value in TA0CCR0, 128, defines the
;  PWM period/2 and the values in TA0CCR1 and TA0CCR2 the PWM duty cycles. Using
;  32kHz ACLK as TA0CLK. 
;***************************Timer_A0******************************************** 
;                                                                                
;                                                                                
;                                                                                
;              +----L092---+                                                     
;              |*1      14 |     -> P1.6 TA0.1 output                            
;              | 2      13 |     -> P1.5 TA0.2 output                            
;              | 3      12 |                                                     
;              | 4      11 |                                                     
;              | 5      10 |                                                     
;              | 6       9 |                                                     
;              | 7       8 |                                                     
;              +-----------+                                                     
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

 ; P1.1 = SMCLK -> P1DIR.1 = 1; P1SEL0.1 = 1; P1SEL1.1 = 1;
 ; P1.5 = TA0.2 -> P1DIR.5 = 1; P1SEL0.5 = 1; P1SEL1.5 = 1; 500Hz
 ; P1.6 = TA0.1 -> P1DIR.6 = 1; P1SEL0.6 = 1; P1SEL1.6 = 0; 50Hz
  
  	        bis.b   #BIT1 + BIT5 + BIT6,&P1SEL0 ;
            bis.b   #BIT1 + BIT5,&P1SEL1 ;
            bis.b   #BIT0 + BIT1 + BIT5 + BIT6,&P1DIR ;
  
;************************* 
; Setup CCS                
; ACLK = HFCLK/32          
; SMCLK = HFCLK/1  ~1MHz   
;************************* 
    	    mov.w   #CCSKEY,&CCSCTL0        ; Unlock CCS

check       mov.w   #0,&CCSCTL7             ; Clear HF & LF OSC fault flags
            mov.w   #0,&SFRIFG1             ; Clear OFIFG
            bit.w   #OFIFG,&SFRIFG1         ; Oscillator Flag(s)?
            jnz     check  
            
            mov.w   #SELA_0+SELS_0+SELM_0,& CCSCTL4 ; Select HFCLK/DCO as the source for SMCLK   
            mov.w   #DIVA_5+DIVS_0+DIVM_0,&CCSCTL5 ; Set the Dividers for SMCLK to 1
    	
    	    bis.b   #0xFF,&CCSCTL0_H        ; Lock CCS
   
; Lock by writing to upper byte 
  
  
  	        mov.w   #128,&TA0CCR0           ; PWM Period/2
  	        mov.w   #OUTMOD_6,&TA0CCTL1     ; TA0CCR1 toggle/set
            mov.w   #32,&TA0CCR1            ; TA0CCR1 PWM duty cycle
  	        mov.w   #OUTMOD_6,&TA0CCTL2     ; TA0CCR2 toggle/set
  	        mov.w   #96,&TA0CCR2            ; TA0CCR2 PWM duty cycle
            mov.w   #TASSEL_1 + MC_3,&TA0CTL ; ACLK, up-down mode

            bis.w   #LPM3,SR                ; LPM3
            nop                             ; Required only for debugger
        
            .end
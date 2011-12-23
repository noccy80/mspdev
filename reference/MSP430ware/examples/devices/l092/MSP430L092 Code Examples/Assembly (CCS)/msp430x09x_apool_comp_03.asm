; Comparator in Compensated Mode - An input signal on A0 is compared with 
; internal voltage reference.  The Results of the Comparator will be present on P1.3
; 
;                                     MSP430 L092
;                                   -----------------
;                               /|\|              XIN|-
;                                | |                 |
;                                --|RST          XOUT|-
;                                  |             P1.4|<--Comparator Input A0 
;                                  |             P1.3|-->Comparator Output
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
main        mov.w   #WDTPW + WDTHOLD,&WDTCTL ; Stop WDT  
             bis.w     #0x3000,&SYSCNF          ; debug issue
  
  ;************************ 
  ; Setup CCS               
  ; MCLK = SMCLK = HFCLK/1  
  ;************************ 

  
            mov.w    #CCSKEY,&CCSCTL0       ; Unlock CCS

check       mov.w    #0,&CCSCTL7            ; Clear HF & LF OSC fault flags
            mov.w    #0,&SFRIFG1            ; Clear OFIFG
            bit.w    #OFIFG,&SFRIFG1        ; Oscillator Flag(s)?
            jnz      check             
            
            mov.w   #DIVM_0 + DIVS_0,&CCSCTL5 ; Set the Dividers for  MCLK, and SMCLK to 1
            bis.w   #SELM_0 + SELS_0,&CCSCTL4 ; Select HFCLK as the source for MCLK, and SMCLK                 
            bis.b   #0xFF,&CCSCTL0_H        ;  Lock CCS 
   
	
 
 ;************************ 
  ; Setup Port 1            
  ; Output P1.3             
  ;************************ 
                   
            bis.b   #BIT3,&P1DIR
            bis.b   #BIT3,&P1SEL0
            bis.b   #BIT3,&P1SEL1
    
  ;************************ 
  ; Configure APOOL         
  ;************************ 
  
            mov.w   #0,&APIFG               ; Clear all APIFG 
            mov.w   #CLKSEL_2 + APREFON,&APCNF ; Select SMCLK for APOOL Master Clock and Enable APOOL reference
            mov.w   #0,&APIFG               ; Clear all APIFG 

            mov.w   #APPSEL_0 + APNSEL_7,&APCTL ; Select Channels A0 and Voltage Reference
            mov.w   #AZCMP,&APOMR   
            bis.w   #CMPON,&APCNF               ;If Vref > A0, P1.3 = 1, else P1.3 = 0
            nop
loop       jmp      loop  



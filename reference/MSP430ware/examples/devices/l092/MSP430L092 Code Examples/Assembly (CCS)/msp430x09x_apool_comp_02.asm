;******************************************************************************
; Comparator in Non Compensated Mode - An input signal on A0 is compared with 
; an input signal on A2.  The signal present on A2 uses the input divider of 
; the module. The Results of the Comparator will be present on P1.3
;
;                                     MSP430 L092
;                                   -----------------
;                               /|\|              XIN|-
;                                | |                 |
;                                --|RST          XOUT|-
;                                  |             P1.4|<--Comparator Input A0 
;           Comparator Input A2--> | P1.0        P1.3|-->Comparator Output
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
            bis.w      #SELM_0 + SELS_0,&CCSCTL4 ; Select HFCLK as the source for MCLK, and SMCLK                 
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
            mov.w   #CLKSEL_2,&APCNF         
            mov.w   #0,&APIFG  

            mov.w   #APPSEL_0 + APNSEL_2,&APCTL ; A0=P vs A2=N 
            bis.w   #A2DIV_2,&APVDIV        ; A2 divide by 8
            mov.w   #CTEN,&APOMR   
            bis.w   #CMPON,&APCNF               ;If A2/8 < A0, P1.3 = 1, else P1.3 = 0
            nop
 
loop        jmp      loop  

            .end


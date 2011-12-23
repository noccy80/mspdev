;******************************************************************************
;  MSP430L092 Demo - Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
;
;  Description: This program operates MSP430 normally in LPM3, pulsing P1.0
;  WDT ISR used to wake-up system. P1.0 I/O configured
;  as low output to eliminate floating inputs. Current consumption does
;  increase when P1.0 is set. Demo for measuring LPM3 current.
;  ACLK = LFXT1/4 = 32768/4, MCLK = SMCLK = default DCO ~1.2MHz
;  ;* External watch crystal on XIN XOUT is required for ACLK *;
;
;           MSP430F21x2
;         ---------------
;     /|\|            XIN|-
;      | |               | 32kHz
;      --|RST        XOUT|-
;        |               |
;        |           P1.0|-->Output
;
;  D.Dang/D.Archbold/D.Szmulewicz
;  Texas Instruments Inc.
;  Built with CCS version 4.2.0
;******************************************************************************

 .cdecls C,LIST,"msp430x09x.h"
;-------------------------------------------------------------------------------
            .data                           ; RAM variables
;------------------------------------------------------------------------------
            .bss    i,2
;-------------------------------------------------------------------------------
            .global main
            .text                           ; Assemble to memory
;-------------------------------------------------------------------------------
main        mov.w   #WDTPW + WDTHOLD,&WDTCTL ; Stop WDT         

            bis.w   #BIT0,&P1DIR
            mov.w   #CCSKEY,&CCSCTL0        ; Unlock CCS
	        bis.w   #SELA_1,&CCSCTL4        ; Select LFCLK/VLO as the ACLK source          
            bic.w   #DIVA_2,&CCSCTL5        ; Divide fACLK by 4
            bis.b   #0xFF,&CCSCTL0_H        ; Lock CCS
                                            ; Lock by writing to upper byte  
	
            mov.w   #WDT_ADLY_16,&WDTCTL    ; WDT SMCLK Delay Interval specify                  
            bis.w   #WDTIE,&SFRIE1          ; Enable WDT interrupt

repeat      bis.w   #LPM3+GIE,SR            ; LPM3, enable interrupts
            xor.b   #BIT0,&P1OUT            ; P1.0 = toggle
            mov.w   #4,&i                   ; Use as a counter for delay
delay       dec     &i
            jne     delay       
            jmp     repeat

;-------------------------------------------------------------------------------
WDT_ISR;    Watchdog Timer interrupt service routine
;-------------------------------------------------------------------------------
            bic.w   #LPM3,0(SP)             ; Modify SP so that it enters active mode after reti
            reti                            ; Return from ISR
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
         
            .sect   ".int10"                 ; WDT_vector
            .short  WDT_ISR                   ;WDT Vector
            .end

;******************************************************************************
;  MSP430F20x3 Demo - SD16A Sequence of conversions
;  The SD16A takes a sample of a single sequence of channels: A0, A1, then A2. 
;  Sampling begins with ch A0.  The 4th conversion result of each channel is 
;  stored in memory. 
;
;
;                MSP430F20x3
;             ------------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;    Vin+ -->|A0+ P1.0         |
;            |A01- = VSS       |
;            |                 |
;    Vin+ -->|A1+ P1.2         |
;            |A1- = VSS        |
;            |                 |
;    Vin+ -->|A2+ P1.4         |
;            |A2- = VSS        |
;            |                 |
;            |            VREF |---+
;            |                 |   |
;            |                 |  -+- 100nF
;            |                 |  -+-
;            |                 |   |
;            |            AVss |---+
;            |                 |
;
;
;  R. B. Elliott  / H. Grewal
;  Texas Instruments
;  April 2007
;  Built with Code Composer Essentials V2.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x20x3.h"

;-------------------------------------------------------------------------------
            .text   0F800h                ; Program Reset
;-------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer

StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            mov.b   #DIVS_3, &BCSCTL2       ; SMCLK/8

SetupSD16   mov.w   #SD16REFON+SD16SSEL_1,&SD16CTL  ; 1.2V ref, SMCLK
            mov.b   #SD16INCH_0+SD16INTDLY_0,&SD16INCTL0 ; Set channel A0+/-
            mov.w   #SD16UNI+SD16IE+SD16SNGL,&SD16CCTL0    ; 256OSR, unipolar,
                                            ; enable interrupt, 
                                            ; single conversion
                                            
            mov.b   #SD16AE0,&SD16AE        ; P1.0 A0+, A0- = VSS

            mov.w  #03600h, R4              ; Delay for 1.2V ref startup
Delay       dec.w  R4;
            jne    Delay; 
           
            mov.w  #0h, R5                  ; R5 = ch_count
           
                                            ;				
Mainloop    bis.w   #SD16SC,&SD16CCTL0      ; Start conversion
            bis.w   #CPUOFF+GIE,SR          ; CPU off, enable interrupts
            nop                             ; Required only for debugger
            jmp     Mainloop                ; jump back to mainloop
            
                                            
;-------------------------------------------------------------------------------
SD16_ISR; 
;-------------------------------------------------------------------------------
              
            cmp.w #01h, R5;
            jlo   Case0                     ; current channel is A0
            jeq   Case1                     ; current channel is A1
            jmp   Case2                     ; current channel is A2

Case0       mov.w &SD16MEM0, R7             ; R7 = A0 conversion results
            inc.w R5                        ; ch_counter++
            
            mov.b #SD16INCH_1,&SD16INCTL0   ; Enable channel A1+/-
            mov.b #SD16AE2, &SD16AE         ; Enable external input on A1+
            jmp   Done                      ; break
   
   
Case1       mov.w &SD16MEM0, R8             ; R8 = A1 conversion results
            inc.w R5                        ; ch_counter++

            mov.b #SD16INCH_2,&SD16INCTL0   ; Enable channel A2+/-
            mov.b #SD16AE4, &SD16AE         ; Enable external input on A2+
            jmp   Done                      ; break
   

Case2       mov.w &SD16MEM0, R9             ; R9 = A2 conversion results
            mov.w #0h, R5                   ; Reset channel count (end of seq)
            mov.b #SD16AE0, &SD16AE         ; Reset external input to A0+/-
            mov.b #SD16INCH_0,&SD16INCTL0   ; Reset channel observed

Done        bic.w #LPM0,0(SP)               ; Exit LPM0
            reti                            ;		
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int07"                ; SD16 Vector
            .short  SD16_ISR                ;
            .end

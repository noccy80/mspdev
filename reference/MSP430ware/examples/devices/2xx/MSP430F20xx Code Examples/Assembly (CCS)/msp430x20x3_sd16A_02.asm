;*******************************************************************************
;   MSP430F20F3 Demo - SD16, Using the Integrated Temperature Sensor
;
;   Description: Use SD16 and it's integrated temperature sensor to detect
;   temperature delta. The temperature sensor output voltage is sampled
;   ~ every 240ms and compared with the last value and if more than ~0.5C
;   delta, P1.0 is set, else reset.
;   SD16 Internal VRef, Bipolar offset binary output format used.
;   Watchdog used as interval time and ISR used to start next SD16 conversion.
;   ACLK = n/a, MCLK = default DCO, SMCLK = SD16CLK = default DCO/8
;
;		 MSP430F20xx
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |A6+              |
;            |A6-          P1.0|-->LED
;
;   P.Thanigai
;   Texas Instruments Inc.
;   May 2007
;   Built with Code Composer Essentials Version: 2.0
;*******************************************************************************
ADCDeltaOn  .equ      31                     ;  ~ 0.5 Deg C delta for LED on
;   CPU Registers Used
LastADCVal  .equ      R4
 .cdecls C,LIST,  "msp430x20x3.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
            bis.b   #DIVS_3,&BCSCTL2        ; SMCLK/8
SetupWDT    mov.w   #WDT_MDLY_32,&WDTCTL    ; WDT Timer interval
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
SetupSD16   mov.w   #SD16REFON+SD16SSEL_1,&SD16CTL  ; 1.2V ref, SMCLK
            mov.b   #SD16INCH_6,&SD16INCTL0       ; A6+/-
            mov.w   #SD16SNGL+SD16IE,&SD16CCTL0    ; Single conv, interrupt
                                            ;				
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
SD16_ISR;
;-------------------------------------------------------------------------------
            add.w   #ADCDeltaOn,LastADCVal  ;
            bic.b   #01h,&P1OUT             ; LED off
            cmp.w   LastADCVal,&SD16MEM0    ; Clears IFG
            jlo     SD16_ISR_1              ;
            bis.b   #01h,&P1OUT             ; LED on
SD16_ISR_1  mov.w   &SD16MEM0,LastADCVal    ; Store value
            reti                            ;		
                                            ;
;-------------------------------------------------------------------------------
WDT_ISR;
;-------------------------------------------------------------------------------
            bis.w   #SD16SC,&SD16CCTL0      ; Start conversion
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int10"                ; Watchdog Vector
            .short  WDT_ISR                 ;
            .sect   ".int05"                ; SD16 Vector
            .short  SD16_ISR                ;            
            .end
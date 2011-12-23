; Description: The following code example starts and stops the A-Pool with Timer_A0. 
; The starting and stopping ADC ramps can be observed on the AOUT pin. The ADC ramp 
; does not stop at a specific voltage level, because no SBSTP or CBSTP bits are set.
;***************************A_POOL ADC Conversion ****************************** 
;                                                                                
;                                                                                
;              +----L092---+                                                     
;              |*1      14 |                                                     
;              | 2      13 |                                                     
;              | 3      12 |<- Channel A0-Provide Analog Input                   
;              | 4      11 |                                                     
;              | 5      10 |                                                     
;              | 6       9 |                                                     
;              | 7       8 |-> AOUT                                              
;              +-----------+                                                     
;                                                                                
;  D.Dang/ D.Archbold/ D.Szmulewicz                                              
;  Texas Instruments Inc.                                                        
;  Built with IAR Version 4.2.0                                                  
;******************************************************************************* 

 .cdecls C,LIST,"msp430x09x.h"
;-------------------------------------------------------------------------------
            .data                           ; RAM variables
;------------------------------------------------------------------------------
            .bss    Result,1
;-------------------------------------------------------------------------------
            .global main
            .text                           ; Assemble to memory
;-------------------------------------------------------------------------------
main        mov.w   #WDTPW + WDTHOLD,&WDTCTL ; Stop WDT                
   mov.w #600,&TA0CCR0                                    ; Set start value to 600
   mov.w #300,&TA0CCR1                                     ; Set stop value to 300
   mov.w #OUTMOD_3,&TA0CCTL0                       ; Set CCR0 outmode to Set/Reset
   mov.w #OUTMOD_3,&TA0CCTL1                                 ; Set CCR0 outmode to Set/Reset
   mov.w #TASSEL_2+MC_1+TACLR,&TA0CTL                      ; Set SMCLK to timer clock source +
                                                      ; Set timer to up mode +
                                                      ; Clear timer count register
; Begin Configuration of the A-POOL registers
   mov.w #CMPON+DBON+CONVON+APREFON+TA0EN,&APCNF            ; Enable comparator on +
                                                      ; Enable DAC buffer +
                                                      ; Enable conversion +
                                                      ; Enable reference +
                                                      ; Enable TimerA0 start
   mov.w #APPSEL_5+APPSEL_0+OSEL+ODEN+TBSTP,&APCTL          ; Set DAC buffer output to PSEL +
                                                      ; Select output buffer +
                                                      ; Enable output driver +
                                                      ; Enable timer based stop  
loop       jmp     loop


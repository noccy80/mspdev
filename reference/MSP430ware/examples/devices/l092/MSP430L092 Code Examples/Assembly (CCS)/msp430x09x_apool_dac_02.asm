;   Description: Output several Analog Signals using the APOOL DAC. A triangle   
;   waveform is created on the ouput of the DAC.  A timer interrupt is used to   
;   change the value of the DAC.                                                 
;                                                                                
;***************************A_POOL DAC ***************************************** 
;                                                                                
;                                                                                
;              +----L092---+                                                     
;              |*1      14 |                                                     
;              | 2      13 |                                                     
;              | 3      12 |                                                     
;              | 4      11 |                                                     
;              | 5      10 |                                                     
;              | 6       9 |                                                     
;              | 7       8 |  -> AOUT- Analog Output Provided                    
;              +-----------+                                                     
;                                                                                
;  D.Dang/D.Archbold/D.Szmulewicz
;  Texas Instruments Inc.
;  Built with CCS version 4.2.0
;******************************************************************************

 .cdecls C,LIST,"msp430x09x.h"
;-------------------------------------------------------------------------------
            .data                           ; RAM variables
;------------------------------------------------------------------------------
            .bss    Output,1
;-------------------------------------------------------------------------------
            .global main
            .text                           ; Assemble to memory
;-------------------------------------------------------------------------------
main        mov.w   #WDTPW + WDTHOLD,&WDTCTL ; Stop WDT                        
            mov.w   #0x00, &Output          ; Initialize Output to 0x00
; Setup of TimerA0 Capture Compare Register 0    
            mov.w   #CCIE,&TA0CCTL0         ; TA0CCRO Interupt Enable 
            mov.w   #1,&TA0CCR0 
   
;Setup of the A-POOL module for DAC output
            mov.w   #DBON+CONVON+APREFON,&APCNF ; Configure A-POOL elements
            bis.w   #ODEN+OSEL,&APCTL       ; A-POOL Comparator/Saturation Based Stop Enable and Running 
    
; Setup of TimerA0 Control Register   
            mov.w   #TASSEL_2 + MC_1 + TACLR,&TA0CTL ; SMCLK, Up Mode
            bis.w   #LPM0+GIE,SR            ; Enter LPM0 w/ interrupts enabled
            nop                             ; Needed for debugger 

; Timer0_A0 interrupt service routine
;-------------------------------------------------------------------------------
TA0_ISR                                     
;-------------------------------------------------------------------------------
            cmp     #0xFF,&APINT             ; Check for Max Value of Analog Output 256mV
            jl      increase_val            ; Branch to Increase the Value of the Output by 1mv
            mov.b   #0,&Output              ; Re-initialize the output value
            mov.b   #0,&APINT                ; When max value has been reached, restart with output of 1mv
            jmp     return
increase_val:
            mov.b   &Output,&APINT
            inc     &Output 
return      reti                            ; Return from ISR  

;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int07"                ; TIMER0_A0_VECTOR
            .short  TA0_ISR                   
            .end

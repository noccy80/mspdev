;  Description: Output several Analog Signals using the APOOL DAC. A triangle   
;  waveform is created on the ouput of the DAC.  A timer interrupt is used to   
;  change the value of the DAC.                                                 
;                                                                               
;***************************A_POOL DAC ***************************************** 
;                                                                               
;                                                                               
;             +----L092---+                                                     
;             |*1      14 |                                                     
;             | 2      13 |                                                     
;             | 3      12 |                                                     
;             | 4      11 |                                                     
;             | 5      10 |                                                     
;             | 6       9 |                                                     
;             | 7       8 |  -> AOUT- Analog Output Provided                    
;             +-----------+                                                     
;                                                                               
;  D.Dang/D.Archbold/D.Szmulewicz
;  Texas Instruments Inc.
;  Built with CCS version 4.2.0
;******************************************************************************

 .cdecls C,LIST,"msp430x09x.h"
;-------------------------------------------------------------------------------
            .data                           ; RAM variables
;------------------------------------------------------------------------------
            .bss     Output,2
;-------------------------------------------------------------------------------
            .global main        
            .text                           ; Assemble to memory
;-------------------------------------------------------------------------------
main        mov.w   #0x23FC,SP              ; Initialize stack pointer to RAM
            mov.w   #WDTPW + WDTHOLD,&WDTCTL ; Stop WDT 
            mov.w   #0x80, &Output          ; Initialize Output to 0x80
; Setup of TimerA0 Capture Compare Register 0    
            mov.w   #CCIE,&TA0CCTL0         ; TA0CCRO Interupt Enable 
            mov.w   #1,&TA0CCR0 
   
;Setup of the A-POOL module for DAC output
            mov.w   #DBON+CONVON+APREFON,&APCNF ; Configure A-POOL elements
            bis.b   #ODEN+OSEL,&APCTL       ; A-POOL Comparator/Saturation Based Stop Enable and Running 
    
; Setup of TimerA0 Control Register   
            mov.w   #TASSEL_2 + MC_1 + TACLR,&TA0CTL ; SMCLK, Up Mode
            
            bis.w   #LPM0+GIE,SR            ; Enter LPM0 w/ interrupts enabled
            nop                             ; Needed for debugger

; Timer0_A0 interrupt service routine
;-------------------------------------------------------------------------------
TA0_ISR                                     
;-------------------------------------------------------------------------------
            cmp.b   #0xFF,&APFRACT_H        ; Check for Value of Analog Output 128mV 
            jz      Output_129mV            ; Branch to Set the Output Value to 129mV
            cmp.b   #0x7F,&APFRACT_H        ; Check for Max Value of Analog Output 256mV
            jz      Output_1mV              ; Branch to Set the Output Value to 1mV
            cmp     #0xFF,&APFRACT_H        ; Check for Max Value of Analog Output 256mV
            jmp     Increase_Output         ; Branch to Increase the Value of the Output by 1mv
            
Output_129mV
            mov.w   #0,&Output              ; Set the Output Value to 129mV
            mov.b   &Output,&APFRACT_H
            jmp     return
Output_1mV 
            mov.w   #0x80,&Output           ; Set the Output Value to 1mV
            mov.b   &Output,&APFRACT_H
            jmp     return
Increase_Output 
            mov.b   &Output,&APFRACT_H
            inc     &Output                  ; Increase the Value of the Output by 1mv             
return      reti                            ; Return from ISR

;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int07"                ; TIMER0_A0_VECTOR
            .short  TA0_ISR                   
            .end
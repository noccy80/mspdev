; Description: A single sample is made on A0 with reference to AVcc.           
;  Software sets ADC10SC to start sample and conversion - ADC10SC
;  automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
;  and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
;  conversion complete, ADC10_ISR will force exit from LPM0 in Mainloop on
;  reti. If VCC<0.9V, P1.0 set indicating low-battery condition.
;***************************A_POOL ADC Conversion ****************************** 
;                                                                                
;                                                                                
;              +----L092---+                                                     
;              |*1      14 |                                                     
;              | 2      13 |                                                     
;              | 3      12 |                 
;              | 4      11 |                                                     
;              | 5      10 |                                                     
;     P1.0<-   | 6       9 |                                                     
;              | 7       8 |                                                     
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
            .bss    Result,2
;-------------------------------------------------------------------------------
            .global main
            .text                           ; Assemble to memory
;-------------------------------------------------------------------------------
main        mov.w   #WDTPW + WDTHOLD,&WDTCTL ; Stop WDT                
            bis.b   #BIT0,&P1DIR            ; Set P1.0 to output direction
; Begin Configuration of the A-POOL registers
            mov.w   #0,&APCTL;              ; Clear APCTL register
            mov.w   #EOCIE,&APIE;           ; Enable Interrupt for End of Conversion    
            mov.w   #CMPON+DBON+CONVON+APREFON+CLKSEL_MCLK,&APCNF ; Configure A-POOL elements, Select MCLK as  A-POOL Clock Source
            
    
    
  
loop     mov.w   #0x00,&APINT;           ; Clear ADC-DAC-REG
           mov.w   #0,&APIFG               ; Clear Interrupt Flag
            mov.w   #OSEL+CBSTP+SBSTP+RUNSTOP+APPSEL_5+APNSEL_6,&APCTL ; Set Channels and Start Conversion
            bis.w   #LPM0+GIE,SR            ; Enter LPM0 w/ interrupts enabled
            mov.w   &APINT,&Result
; Low-Battery voltage = 0.9V/8 = 113 mV(since APNSEL_6 was chosen). Full scale of ADC = 256mV (0xFF)
; Then 113mV ~ 0x70
            cmp     #70,&Result;
            jl      Set_P1
            bic.b   #BIT0,&P1OUT            ; Clear P1.0
            jmp     loop
Set_P1
            bis.b   #BIT0,&P1OUT            ; Set0 P1.0
            jmp     loop

;-------------------------------------------------------------------------------
A_POOL_ISR       ;A_POOL Interrupt Service Routine                               
;-------------------------------------------------------------------------------
            bic.w   #LPM0,0(SP)             ; Modify SP so that it enters active mode after reti
            mov.w   #0,&APIFG               ; Clear Interrupt Flag
            reti                            ; Return from ISR
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".int09"                ; A_POOL_vector
            .short  A_POOL_ISR              ;A_POOL Vector
            .end


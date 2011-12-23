;   Description: A-Pool ADC conversions with Offset Compensation. A single       
;   ramp conversion using the ADC-DAC-REG with the DAC as ramp generator.  The   
;   counter is cleared by software; channels are set and conversion is triggered 
;   by software.  The comparator stops the counter when the ramp voltage crosses 
;   the selected input voltage.  The Result is stored in APINT.                  
;***************************A_POOL ADC Conversion ****************************** 
;                                                                                
;                                                                                
;              +----L092---+                                                     
;              |*1      14 |                                                     
;              | 2      13 |                                                     
;              | 3      12 |<- Channel A0-Provide Analog Input (0-256mV)         
;              | 4      11 |                                                     
;              | 5      10 |                                                     
;              | 6       9 |                                                     
;              | 7       8 |                                                     
;              +-----------+                                                     
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
            mov.w   #0,&Result              ; Initialize Result variable  

; Begin Configuration of the A-POOL registers
            mov.w   #0,&APCTL;              ; Clear APCTL register
            mov.w   #EOCIE,&APIE;            ; Enable Interrupt for End of Conversion    
            mov.w   #CMPON+DBON+CONVON+APREFON+CLKSEL_MCLK,&APCNF ; Configure A-POOL elements, Select MCLK as A-POOL Clock Source
            mov.w   #0x00,&APINT            ; Clear ADC-DAC-REG
            mov.w   #OSEL+CBSTP+RUNSTOP+APPSEL_5+APNSEL_0,&APCTL ; Set Channels and Start Conversion
            bis.b   #LPM0+GIE,SR            ; Enter LPM0 w/ interrupts enabled
     
            mov.w   &APINT,&Result
            mov.w   #EOCIE,&APIE            ; Enable Interrupt for End of Conversion  
            bis.w   #RUNSTOP + OSWP,&APCTL  ; Cross Channels and Start Conversion 
            bis.w   #LPM0+GIE,SR            ; Enter LPM0 w/ interrupts enabled
    
            add.w   &APINT,&Result          ; Add register value to Result variable
            rrc.w   &Result  
            nop                             ; Place Breakpoint Here   

;-------------------------------------------------------------------------------
A_POOL_ISR       ;A_POOL Interrupt Service Routine                               
;-------------------------------------------------------------------------------
            mov.w   #0,&APIFG               ; Clear Interrupt Flag
            bic.w   #LPM0,0(SP)             ; Modify SP so that it enters active mode after reti
            reti                            ; Return from ISR
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".int09"                ; A_POOL_vector
            .short  A_POOL_ISR              ;A_POOL Vector
            .end


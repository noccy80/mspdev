;   Description: Multiple ADC Channels 
;***************************A_POOL ADC Conversion ****************************** 
;                                                                                
;                                                                                
;                          +----L092---+                                         
;                          |*1      14 |                                         
;                          | 2      13 |                                         
;                          | 3      12 |<- Channel A0(0-256mV)                   
;                          | 4      11 |                                         
;                          | 5      10 |                                         
; Channel A2 (0-256mV)->   | 6       9 |                                         
; Channel A1 (0-256mV)->   | 7       8 |                                         
;                          +-----------+                                         
;  D.Dang/D.Archbold/D.Szmulewicz
;  Texas Instruments Inc.
;  Built with CCS version 4.2.0
;******************************************************************************

 .cdecls C,LIST,"msp430x09x.h"
;-------------------------------------------------------------------------------
            .global main
            .data                           ; RAM variables
;------------------------------------------------------------------------------
            .bss    ChannelA0,2
            .bss    ChannelA1,2
            .bss    ChannelA2,2
;-------------------------------------------------------------------------------
            .global main
            .text                           ; Assemble to memory
;-------------------------------------------------------------------------------
main        mov.w   #WDTPW + WDTHOLD,&WDTCTL ; Stop WDT       
 
 ; Begin Configuration of the A-POOL registers  
            mov.w   #0,&APCTL               ; Clear APCTL register
            mov.w   #CMPON+DBON+CONVON+EOCBU+APREFON+CLKSEL_MCLK,&APCNF ; Configure A-POOL elements, Select MCLK as A-POOL Clock Source
            mov.w   #0x00,&APINT            ; Clear ADC-DAC-REG
    
    
loop     mov.w #EOCIE,&APIE           ; Enable Interrupt for end of conversion
           mov.w   #0x00,&APINT            ; Clear ADC-DAC-REG
           mov.w   #OSEL+CBSTP+RUNSTOP+APNSEL_0+APPSEL_5,&APCTL ; Set Channels and Start Conversion
            bis.w   #LPM0+GIE,SR            ; Enter LPM0 w/ interrupts enabled
            mov.w   &APINT,&ChannelA0       ; Get Result for A0
          
           mov.w #EOCIE,&APIE           ; Enable Interrupt for end of conversion
           mov.w   #0x00,&APINT            ; Clear ADC-DAC-REG
            mov.w   #OSEL+CBSTP+RUNSTOP+APNSEL_1+APPSEL_5,&APCTL ; Set Channels and Start Conversion
            bis.w   #LPM0+GIE,SR            ; Enter LPM0 w/ interrupts enabled
            mov.w   &APINT,&ChannelA1       ; Get Result for A1
  
           mov.w #EOCIE,&APIE           ; Enable Interrupt for end of conversion
           mov.w   #0x00,&APINT            ; Clear ADC-DAC-REG 
           mov.w   #OSEL+CBSTP+RUNSTOP+APNSEL_2+APPSEL_5,&APCTL ; Set Channels and Start Conversion
            bis.w   #LPM0+GIE,SR            ; Enter LPM0 w/ interrupts enabled
            mov.w   &APINT,&ChannelA2       ; Get Result for A2
            nop
            jmp     loop
 
   
;-------------------------------------------------------------------------------
A_POOL_ISR       ;A_POOL Interrupt Service Routine                               
;-------------------------------------------------------------------------------
            mov.w   #0,&APIFG 
            bic.w   #LPM0,0(SP)             ; Modify SP so that it enters active mode after reti
            
            reti                            ; Return from ISR
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".int09"                ; A_POOL_vector
            .short  A_POOL_ISR              ;A_POOL Vector
            .end



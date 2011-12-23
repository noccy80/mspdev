;   Description:  ADC Temperature Sample                                         
;***************************A_POOL ADC Conversion ****************************** 
;                                                                                
;                                                                                
;              +----L092---+                                                     
;              |*1      14 |                                                     
;              | 2      13 |                                                     
;              | 3      12 |                                                     
;              | 4      11 |                                                     
;              | 5      10 |                                                     
;              | 6       9 |                                                     
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
            .bss    DegC,4
            .bss    DegF,4
;-------------------------------------------------------------------------------
            .global main
            .text                           ; Assemble to memory
;-------------------------------------------------------------------------------
main        mov.w   #WDTPW + WDTHOLD,&WDTCTL ; Stop WDT                


  
  ; Begin Configuration of the A-POOL registers
   
            mov.w   #0,&APCTL               ; Clear APCTL register
            bis.b   #EOCIE,&APIE            ; Enable Interrupt for End of Conversion   
            mov.w   #REFTSEL,&APTRIM 
            mov.w   #TMPSEN,&APVDIV         ; Enable Temperature Sensor 
            mov.w   #CMPON+DBON+CONVON+APREFON+CLKSEL_MCLK,&APCNF ; Configure A-POOL elements, Select MCLK as A-POOL Clock Source


    
            mov.w   #OSEL+ODEN+OSWP+APPSEL_5+APNSEL_4,&APCTL ; Set Channels and Start Conversion  
            mov.w   #0,&APINT               ; Clear ADC-DAC-REG
    
            bis.w   #CBSTP+SBSTP+RUNSTOP,&APCTL;
            bis.w   #LPM0+GIE,SR            ; Enter LPM0 w/ interrupts enabled
    
            mov.w   &APINT,&Result 
            mov.w   &Result, R12         
            mov.w   #169,R12
            sub.w   #165,R12                ; Subtract 165
            rla     R12                     ; Multiply by 2
            mov.w   R12,&DegC               ; Simple example with roundings. For more accurate result please refer to C code example
          
            nop                             ; SET BREAKPOINT HERE


    
    
  
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


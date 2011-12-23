;******************************************************************************* 
;  MSP430L092 Demo - Reset on Invalid Address fetch, Toggle P1.0                 
;                                                                                
;  Description: Toggle P1.0 by xor'ing P1.0 inside of a software loop that       
;  ends with TAR loaded with 3FFFh - op-code for "jmp $" This simulates a code   
;  error. The MSP430L029 will force a reset because it will not allow a fetch    
;  from within the address range of the peripheral memory, as is seen by         
;  return to the mainloop and P1.0 toggle.                                       
;                                                                                
;                                                                                
;                MSP430L092                                                      
;             -----------------                                                     
;         /|\|              XIN|-                                                
;          | |                 |                                                 
;          --|RST          XOUT|-                                                
;            |                 |                                                 
;            |             P1.0|-->Out                                           
;                                                                                
;  D.Dang/D.Archbold/D.Szmulewicz
;  Texas Instruments Inc.
;  Built with CCS version 4.2.0
;******************************************************************************
 .cdecls C,LIST,"msp430x09x.h"
 
count       .equ    R4 
;-------------------------------------------------------------------------------
            .global main
            .text                           ; Assemble to memory
;-------------------------------------------------------------------------------
main        mov.w   #WDTPW + WDTHOLD,&WDTCTL ; Stop WDT       
            bis.w   #BIT0,&P1DIR            ; Set P1.0 to output direction
            bis.w   #0x3FFF,TA0R;           ; Opcode for "jmp $"

while_loop  xor.b   #BIT0,&P1DIR            ; Toggle P1.0 (LED)
            mov.w   #50000,count            ; Load delay counter
delay_loop  dec.w   count                   ; Decrement delay counter    
            jne     delay_loop              
            mov.w   #0x0350,PC              ; attempt to execute an instruction
                                            ; from address 0x0170 (invalid fetch)
            jmp     while_loop



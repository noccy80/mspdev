;******************************************************************************
;  MSP430G2x21/G2x31 Demo - I2C Slave Receiver, single byte
;
;  Description: I2C Slave communicates with I2C Master using
;  the USI. Master data should increment from 0x00 with each transmitted byte
;  which is verified by the slave.
;  LED off for address or data Ack; LED on for address or data NAck.d by the slave.
;  ACLK = n/a, MCLK = SMCLK = Calibrated 1MHz
;
;  ***THIS IS THE SLAVE CODE***
;
;                  Slave                      Master
;                                      (msp430g2x21_usi_07.asm)
;             MSP430G2x21/G2x31          MSP430G2x21/G2x31
;             -----------------          -----------------
;         /|\|              XIN|-    /|\|              XIN|-
;          | |                 |      | |                 |
;          --|RST          XOUT|-     --|RST          XOUT|-
;            |                 |        |                 |
;      LED <-|P1.0             |        |                 |
;            |                 |        |             P1.0|-> LED
;            |         SDA/P1.7|<-------|P1.7/SDA         |
;            |         SCL/P1.6|<-------|P1.6/SCL         |
;
;  Note: internal pull-ups are used in this example for SDA & SCL
;
;  D. Dang
;  Texas Instruments Inc.
;  October 2010
;  Built with Code Composer Essentials Version: 4.2.0
;******************************************************************************

I2CState   .equ     R4
MST_data   .equ     R5
slav_add   .equ     R6

 .cdecls C,LIST,  "msp430g2221.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
CheckCal    cmp.b   #0FFh,&CALBC1_1MHZ      ; Calibration constants erased?
            jeq     Trap
            cmp.b   #0FFh,&CALDCO_1MHZ
            jne     Load  
Trap        jmp     $                       ; Trap CPU!!
Load        mov.b   &CALBC1_1MHZ,&BCSCTL1   ; Set DCO to 1MHz
            mov.b   &CALDCO_1MHZ,&DCOCTL
SetupP1     mov.b   #0xC0,&P1OUT            ; P1.6 &P1.7 pullups      
            bis.b   #0xC0,&P1REN            ; P1.6 &P1.7 pullups 
            mov.b   #0xFF,&P1DIR            ; unused pins output direction
SetupP2     clr.b   &P2OUT                  ;
            mov.b   #0xFF,&P2DIR            
SetupUSI    mov.b   #USIPE6+USIPE7+USISWRST,&USICTL0; Port, I2C slave
            mov.b   #USIIE+USII2C+USISTTIE,&USICTL1 ;Enable I2C mode,interrupts
            mov.b   #USICKPL,&USICKCTL      ; Setup clock polarity
            bis.b   #USIIFGCC,&USICNT      
            bic.b   #USISWRST,&USICTL0
            bic.b   #USIIFG,&USICTL1
            clr.w   I2CState
            clr.w   MST_data
            mov.b   #0x90,slav_add                                                   
Mainloop         
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            jmp     Mainloop                                                               
;-------------------------------------------------------------------------------
USI_ISR  ;
;-------------------------------------------------------------------------------
            bit.b   #USISTTIFG,&USICTL1     ; Start entry?
            jnc     Check_State
            bis.b   #0x01,&P1OUT            ; turn on LED, sequence start
            mov.w   #2,I2CState             ; First I2C state, Rx address
Check_State add.w   I2CState,PC             ; I2C State Machine
            jmp     STATE0                  
            jmp     STATE2
            jmp     STATE4
            jmp     STATE6
            jmp     STATE8
            jmp     STATE10
     
STATE0      nop                             ; Idle, should not get here
            bic.b   #USIIFG,&USICTL1
            reti 
STATE2                                      ; Rx address 
            mov.b   &USICNT,R8              ; Bit counter = 8, Rx address
            and.b   #0xE0,R8
            add.b   #0x8,R8
            mov.b   R8,&USICNT
            bic.b   #USISTTIFG,&USICTL1     ; Clear Start flag
            mov.w   #4,I2CState             ; Go to next state, chk address
            bic.b   #USIIFG,&USICTL1
            reti           
STATE4                                      ; Process address and send (N)Ack 
            bit.b   #0X01,&USISRL           ; If read
            jnc     Chk_Add
            inc.b   slav_add                ; Save R/W bit
Chk_Add     
            bis.b   #USIOE,&USICTL0         ; SDA = output
            cmp.b   slav_add,&USISRL        ; address match?
            jnz     Add_NACK
            clr.b   &USISRL
            bic.b   #0x01,&P1OUT            ; LED off
            mov.w   #8,I2CState             ; Go to next state: Rx data
            bis.b   #0x01,&USICNT           ; Bit counter = 1, send Ack bit
            bic.b   #USIIFG,&USICTL1
            reti                  
Add_NACK
            mov.b   #0xFF,&USISRL           ; Send NACK
            bis.b   #0x1,&P1OUT             ; LED on:error
            mov.w   #6,I2CState             ; go to next state, prep next start
            bis.b   #0x01,&USICNT           ; Bit counter = 1, Send Nack
            bic.b   #USIIFG,&USICTL1 
            reti                 
STATE6                                      ; Prep for Re-start condition
            bic.b   #USIOE,&USICTL0         ; SDA = input
            mov.b   #0x90,slav_add          ; Reset Slave address
            clr.w   I2CState                ; Reset state machine
            bic.b   #USIIFG,&USICTL1
            reti
STATE8                                      ; Receive data byte
            bic.b   #USIOE,&USICTL0         ; SDA =input
            bis.b   #0x8,&USICNT            ; Bit counter = 8, Rx data
            mov.w   #10,I2CState            ; Go to next state,test data,(N)Ack
            bic.b   #USIIFG,&USICTL1 
            reti         
STATE10                                     ; Check Data and Tx (N)Ack
            bis.b   #USIOE,&USICTL0         ; SDA = output
            cmp.b   MST_data,&USISRL        ; If data valid ...
            jne     Data_NACK
            clr.b   &USISRL                 ; Send Ack
            inc.b   MST_data                ; Increment master data
            bic.b   #0x1,&P1OUT             ; LED off
            jmp     STATE10_Exit                 
Data_NACK                                               
            mov.b   #0xFF,&USISRL           ; Send Nack
            bis.b   #0x1,&P1OUT             ; LED on : error
STATE10_Exit            
            bis.b   #0x1,&USICNT            ; Bit counter = 1, Send Nack
            mov.w   #6,I2CState             ; next state, prep for next start
            bic.b   #USIIFG,&USICTL1 
            reti         
        
;-------------------------------------------------------------------------------
;           Interrupt Vectors 
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int04"                ; USI Vector
            .short  USI_ISR                 ;
            .end

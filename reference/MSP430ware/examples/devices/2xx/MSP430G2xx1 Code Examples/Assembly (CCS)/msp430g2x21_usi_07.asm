;******************************************************************************
;  MSP430G2x21/G2x31 Demo - I2C Master Transmitter, single byte
;
;  Description: I2C Master communicates with I2C Slave using
;  the USI. Master data is sent and increments from 0x00 with each transmitted
;  byte which is verified by the slave.
;  LED off for address or data Ack; LED on for address or data NAck.
;  ACLK = n/a, MCLK = SMCLK = Calibrated 1MHz
;
;  ***THIS IS THE MASTER CODE***
;
;                  Slave                      Master
;          (msp430g2x21_usi_08.asm)
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
SetupP1     mov.b   #0xC0,&P1OUT            ; P1.6 & P1.7 as pullups
            bis.b   #0xC0,&P1REN            ; P1.6 & P1.7 as pullups
            mov.b   #0xFF,&P1DIR            ; unused pins as output
SetupP2     mov.b   #0x00,&P2OUT                  
            mov.b   #0xFF,&P2DIR            
SetupUSI    mov.b   #USIPE6+USIPE7+USIMST+USISWRST,&USICTL0; Port, I2C master
            mov.b   #USIIE+USII2C,&USICTL1  ; Enable I2C
            mov.b   #USIDIV_3+USISSEL_2+USICKPL,&USICKCTL    ;  SMCLK/8
            bis.b   #USIIFGCC,&USICNT       ; Disable automatic clear control
            bic.b   #USISWRST,&USICTL0      ; Enable USI
            bic.b   #USIIFG,&USICTL1        ; Clear pending flag
            clr.w   I2CState
            clr.b   MST_data
            mov.b   #0x90,slav_add                                             
Mainloop    bis.b   #USIIFG,&USICTL1        
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            call    #Delay
            jmp     Mainloop                         
;------------------------------------------------------------------------------
USI_ISR  ;
;------------------------------------------------------------------------------
            add.w   I2CState,PC             ; I2C State Machine
            jmp     STATE0
            jmp     STATE2
            jmp     STATE4
            jmp     STATE6
            jmp     STATE8
            jmp     STATE10
            
STATE0      
            bis.b   #0x01,&P1OUT            ; LED on: sequence start
            clr.b   &USISRL                 ; Generate start condition
            bis.b   #USIGE+USIOE,&USICTL0   ; 
            bic.b   #USIGE,&USICTL0         ;
            mov.b   slav_add,&USISRL        ; Transmit address, R/W =0
            mov.b   &USICNT,R8              ; Bit counter = 8, Tx address
            and.b   #0xE0,R8
            add.b   #0x08,R8
            mov.b   R8,&USICNT
            mov.w   #2,I2CState             ; Go to next state: Rx address(N)ACK
            bic.b   #USIIFG,&USICTL1
            reti
STATE2                                      ; Rx address             
            bic.b   #USIOE,&USICTL0         ; SDA = input
            bis.b   #0x01,&USICNT           ; Bit counter = 1, rx (N)ACK 
            mov.w   #4,I2CState             ; Go to next state, chk (N)ACK
            bic.b   #USIIFG,&USICTL1
            reti       
STATE4                                      ; Process address (N)Ack, data Tx
            bis.b   #USIOE,&USICTL0         ; SDA = output
            bit.b   #0x1,&USISRL            ; if NACK received
            jnc     Data_Tx                 ; ACK 
            clr.b   &USISRL
            bis.b   #0x01,&USICNT           ; bit counter = 1, SCL high,SDA low
            mov.w   #10,I2CState            ; goto next state, generate stop
            bis.b   #0x01,&P1OUT            ; Turn on LED : error
            bic.b   #USIIFG,&USICTL1
            reti
Data_Tx     
            mov.b   MST_data,&USISRL
            bis.b   #0x8,&USICNT            ; Bit counter = 8, Rx data
            mov.w   #6,I2CState             ; next state: Test data, (N)ACK
            bic.b   #0x1,&P1OUT             ; LED off
            bic.b   #USIIFG,&USICTL1 
            reti                      
STATE6                                      ; Receive Data Ack/Nack bit
            bic.b   #USIOE,&USICTL0         ; SDA = input
            bis.b   #0x01,&USICNT           ; Bit counter = 1, receive (N)Ack bit     
            mov.w   #8,I2CState             ; Go to next state: check (N)Ack
            bic.b   #USIIFG,&USICTL1 
            reti
STATE8                                      ; Process data (N)Ack bit
            bis.b   #USIOE,&USICTL0
            bit.b   #0x01,&USISRL           ; if NACK received
            jz      Data_Ack
            bis.b   #0x1,&P1OUT             ; LED on:error ; nack
            jmp     STATE8_Exit
Data_Ack
            inc.b   MST_data                ; Increment Master data
            bic.b   #0x1,&P1OUT             ; LED off
STATE8_Exit            
            clr.b   &USISRL       
            bis.b   #0x1,&USICNT            ; Bit counter = 1, SCL high,SDA low
            mov.w   #10,I2CState            ; Go to next state : generate stop
            bic.b   #USIIFG,&USICTL1 
            reti          
STATE10           
            mov.b   #0xFF,&USISRL           ; USISRL=1 to release SDA
            bis.b   #USIGE,&USICTL0         ; Transparent latch enabled
            bic.b   #USIGE+USIOE,&USICTL0   ; Latch/SDA output disabled
            clr.w   I2CState                ; Reset state machine for next Tx
            bic.w   #LPM0,0(SP)             ; Exit active for next transfer
            bic.b   #USIIFG,&USICTL1 
            reti          
;-------------------------------------------------------------------------------
Delay                                       ; Delay betn. communication cycles
;-------------------------------------------------------------------------------
            mov.w   #0xFFFF,R7
DL1         dec.w   R7
            jnz     DL1
            ret                              
;-------------------------------------------------------------------------------
;           Interrupt Vectors 
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int04"                ; USI Vector
            .short  USI_ISR                 ;
            .end
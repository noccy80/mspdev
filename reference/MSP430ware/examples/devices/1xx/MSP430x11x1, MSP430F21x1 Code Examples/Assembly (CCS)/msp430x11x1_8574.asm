;*******************************************************************************
;   MSP430x11x1 Demo - Software I2C Master Interface to PCF8574, Read/Write
;
;   Description: Software I2C communication with a PCF8574 in read and write
;   mode is demonstrated. PCF8574 port P is configured with P0-P3 input, P4-P7
;   output. Read P0-P3 input data is written back to Port P4-P7. Ack error
;   checking not implemented. I2C timing assumed with MCLK ~800kHz.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~800k
;
;                                 MSP430F1121
;                              -----------------
;                  /|\ /|\ /|\|              XIN|-
;                  10k 10k  | |                 |
;       PCF8574     |   |   --|RST          XOUT|-
;       ---------   |   |     |                 |
;  --->|P0    SDA|<-|---+---->|P2.0         P1.0|---> LED
;  --->|P1       |  |         |                 |
;  --->|P2       |  |         |                 |
;  --->|P3    SCL|<-+---------|P2.1             |
;  <---|P4       |            |                 |
;  <---|P5       |            |                 |
;  <---|P6       |            |                 |
;  <---|P7       |            |                 |
;   +--|A0,A1,A2 |            |                 |
;   |  |         |            |                 |
;  \|/
;
;            CPU registers used
RXTXI2C  .equ     R7
ADDRI2C  .equ     R8
DATAI2C  .equ     R9
BITI2C   .equ     R10
;
;            Definitions for I2C bus
SDA         .equ    001h                    ; P2.0 controls SDA line (pull-up)
SCL         .equ    002h                    ; P2.1 controls SCL line (pull-up)
Code        .equ    040h                    ; Device Code with A0=A1=A2=0
;
;
;   M. Buccini / Z. Albus
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x11x1.h"
;-------------------------------------------------------------------------------
            .text
;-------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            mov.b   #Code,ADDRI2C           ;
                                            ;
Mainloop    call    #Read_I2C               ; DATAI2C = P-port data
            rlc.b   DATAI2C                 ;
            rlc.b   DATAI2C                 ;
            rlc.b   DATAI2C                 ;
            rlc.b   DATAI2C                 ; P7-P4 = P3-P0
            bis.b   #00Fh,DATAI2C           ; P1-3 mask as inputs
            call    #Write_I2C              ; Write data to ouput register
                                            ;
Delay       push.w  #0                      ; Delay to TOS
Delay_1     dec.w   0(SP)                   ;
            jnz     Delay_1                 ;
            incd.w  SP                      ; Clean-up stack
            jmp     Mainloop                ;
                                            ;
;;/////////I2C Subroutines start//////////////////////////////////////////////
;-------------------------------------------------------------------------------
Read_I2C;   enter ADDRI2C=00 - FF I2C device address to read
;                 RXTXI2C=x
;                 DATAI2C=x
;           exit  ADDRI2C=00 - FF I2C device address to read
;                 RXTXI2C=x
;                 DATAI2C=00 - FF I2C device data
;-------------------------------------------------------------------------------
            mov.b   ADDRI2C,RXTXI2C         ; Control
            bis.b   #01h,RXTXI2C            ; "read"
            call    #I2C_Start              ; Send Start, control+1 and Ack
            call    #I2C_RX                 ; Send Read
            call    #I2C_RX_NACK            ; Send NACK
            call    #I2C_Stop               ; Send Stop
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
Write_I2C;  enter ADDRI2C=00 - FF I2C device address to write to
;                 RXTXI2C=x
;                 DATAI2C=00 - FF I2C device data to write
;           exit  ADDRI2C=00 - FF I2C device address to write to
;                 RXTXI2C=x
;                 DATAI2C=00 - FF I2C device data to write
;-------------------------------------------------------------------------------
            mov.b   ADDRI2C,RXTXI2C         ; Control
            call    #I2C_Start              ; Send Start, control and Ack
            mov.b   DATAI2C,RXTXI2C         ; Data
            call    #I2C_TX                 ; Send Data and Ack
            call    #I2C_Stop               ; Send Stop
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
I2C_Start;  enter SDA=x, SCL=x
;           exit  SDA=0, SCL=0
;-------------------------------------------------------------------------------
            bic.b   #SCL+SDA,&P2DIR         ; SCL=1,SDA=1
            bic.b   #SCL+SDA,&P2OUT         ;
            bis.b   #SDA,&P2DIR             ; SDA=0
            bis.b   #SCL,&P2DIR             ; SCL=0
;-------------------------------------------------------------------------------
I2C_TX;     enter SDA=x, SCL=0
;           exit  SDA=1, SCL=0
;-------------------------------------------------------------------------------
            mov     #8,BITI2C               ;
I2C_TX_Bit  rla.b   RXTXI2C                 ; data bit -> carry
            jc      I2C_TX1                 ;
I2C_TX0     bis.b   #SDA,&P2DIR             ; SDA=0
            jmp     I2C_TXx                 ;
I2C_TX1     bic.b   #SDA,&P2DIR             ; SDA=1
I2C_TXx     bic.b   #SCL,&P2DIR             ; SCL=1
            nop                             ; delay to meet I2C spec
            nop                             ;
            bis.b   #SCL,&P2DIR             ; SCL=0
            dec     BITI2C                  ;
            jnz     I2C_TX_Bit              ; continue until 8 bits are sent
            bic.b   #SDA,&P2DIR             ; SDA=1
                                            ;
I2C_TX_Ack  bic.b   #SCL,&P2DIR             ; SCL=1
;            bit.b  #SDA,&P2IN               ; Slave_Ack --> carry
;            jnc    I2C_Error                ; No carry = Ack error
            nop                             ; delay to meet I2C spec
            nop                             ;
            bis.b   #SCL,&P2DIR             ; SCL=0
            ret                             ; Return from subroutine
                                            ;
;-------------------------------------------------------------------------------
I2C_RX  ;   enter SDA=1, SCL=0
;           exit  SDA=x, SCL=0
;-------------------------------------------------------------------------------
            mov.b   #8,BITI2C               ; 8 bits to read
I2C_RX_Bit  bic.b   #SCL,&P2DIR             ; SCL=1
            bit.b   #SDA,&P2IN              ; SDA bit -> carry
            rlc.b   DATAI2C                 ; store data bit
            bis.b   #SCL,&P2DIR             ; SCL=0
            dec     BITI2C                  ; all bits read?
            jnz     I2C_RX_Bit              ; continue until 8 bits are read
            ret                             ; Return from subroutine
                                            ;
I2C_RX_ACK  bis.b   #SDA,&P2DIR             ; SDA=0, Master Ack
I2C_RX_NACK bic.b   #SCL,&P2DIR             ; SCL=1
            nop                             ; delay to meet I2C spec
            nop                             ;
            bis.b   #SCL,&P2DIR             ; SCL=0
            bic.b   #SDA,&P2DIR             ; SDA=1
            ret                             ; Return from subroutine
                                            ;
;-------------------------------------------------------------------------------
I2C_Stop;   enter SDA=1, SCL=0
;           exit  SDA=1, SCL=1
;-------------------------------------------------------------------------------
            bis.b   #SDA,&P2DIR             ; SDA = 0
            bic.b   #SCL,&P2DIR             ; SCL = 1
            bic.b   #SDA,&P2DIR             ; SDA = 1
I2C_End     ret                             ;
;;/////////I2C Subroutines end////////////////////////////////////////////////
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end

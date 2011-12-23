;******************************************************************************
;   MSP-FET430P140 Demo - I2C, Master Writes Multiple Bytes to MSP430 Slave
;
;   Description: This demo connects two MSP430's via the I2C bus. The master
;   writes 3 bytes to the slave. This is the master code. The slave code is
;   called fet140_i2c_07.asm. The TX data is incremented each time it is
;   sent.
;   ACLK = n/a, MCLK = SMCLK = I2CCLOCK = DCO ~800kHz;
;   ;* MSP430F169 Device Required *//
;
;                                 /|\  /|\
;                  MSP430F169     10k  10k     MSP430F169
;                    slave         |    |        master
;              -----------------|  |    |  -----------------
;             |             P3.1|<-|---+->|P3.1             |
;             |                 |  |      |             P1.0|-->LED
;             |                 |  |      |                 |
;             |             P3.3|<-+----->|P3.3             |
;             |                 |         |                 |
;
;
;   H. Grewal / L. Westlund
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x16x.h"
;------------------------------------------------------------------------------
            .text                  ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            bis.b   #0Ah,&P3SEL             ; Select I2C pins
            bis.b   #01h,&P1DIR             ; P1.0 output
            bic.b   #01h,&P1OUT             ; Clear P1.0

I2C_init    bis.b   #I2C+SYNC,&U0CTL        ; Recommended init procedure
            bic.b   #I2CEN,&U0CTL           ; Recommended init procedure
            bis.b   #I2CSSEL1+I2CTRX,&I2CTCTL ; SMCLK
            mov.b   #03h,&I2CNDAT           ; Read one byte
            mov     #0048h,&I2CSA           ; Slave Address is 048h
            bis.b   #TXRDYIE,&I2CIE         ; Enable RXRDYIE
            bis.b   #I2CEN,&U0CTL           ; Enable I2C
            clr     R5                      ; Use R5 to hold TX data

Mainloop    bis.b   #MST,&U0CTL             ; Master mode
            bis.b   #I2CSTT+I2CSTP,&I2CTCTL ; Initiate transfer
Byte1       bit.b   #TXRDYIFG,&I2CIFG
            jz      Byte1                   ; Repeat
            mov.b   R5,&I2CDRB              ; Load I2CDRB
            inc.b   R5
Byte2       bit.b   #TXRDYIFG,&I2CIFG
            jz      Byte2                   ; Repeat
            mov.b   R5,&I2CDRB              ; Load I2CDRB
            inc.b   R5
Byte3       bit.b   #TXRDYIFG,&I2CIFG
            jz      Byte3                   ; Repeat
            mov.b   R5,&I2CDRB              ; Load I2CDRB
            jmp     $

;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET vector
            .short  RESET                   ;
            .end
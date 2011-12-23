;******************************************************************************
;   MSP-FET430P140 Demo - I2C, Master Reads from MSP430 Slave
;
;   Description: This demo connects two MSP430's via the I2C bus. The master
;   reads from the slave. This is the master code. The slave code is called
;   fet140_i2c_05.asm. The data from the slave transmitter begins
;   at 0 and increments with each transfer. The received data is in R5 and is
;   checked for validity. If the received data is incorrect, the CPU is trapped
;   and the P1.0 LED will stay on. The RXRDYIFG interrupt is used to know when
;   new data has been received.
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
;   M. Mitchell / L. Westlund
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
            bis.b   #I2CSSEL1,&I2CTCTL      ; SMCLK
            mov.b   #01h,&I2CNDAT           ; Read one byte
            mov     #0048h,&I2CSA           ; Slave Address is 048h
            bis.b   #RXRDYIE,&I2CIE         ; Enable RXRDYIE
            bis.b   #I2CEN,&U0CTL           ; Enable I2C

            clr     R6                      ; Use R6 to check incoming data

Mainloop    bis.b   #MST,&U0CTL             ; Master mode
            bis.b   #I2CSTT+I2CSTP,&I2CTCTL ; Initiate transfer
            bis.b   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            bis.b   #01h,&P1OUT             ; .set P1.0
            cmp     R5,R6                   ; Test received data
            jne     Trap                    ; Trap CPU if wrong
            bic.b   #01h,&P1OUT             ; Clear P1.0
            inc.b   R6                      ; Increment correct RX value
            jmp     Mainloop                ; Repeat

Trap        jmp     $                       ; Trap CPU

;------------------------------------------------------------------------------
I2C_ISR;    Common ISR for I2C Module
;------------------------------------------------------------------------------
            add     &I2CIV,PC               ; Add I2C offset vector
            reti                            ; No interrupt
            reti                            ; Arbitration Lost
            reti                            ; No Acknowledge
            reti                            ; Own Address
            reti                            ; Register Access Ready
            jmp     RXRDY_ISR               ; Receive Ready
            reti                            ; Transmit Ready
            reti                            ; General Call
            reti                            ; Start Condition

RXRDY_ISR   mov.b   &I2CDRB,R5              ; RX data in R5
            bic     #LPM0,0(SP)             ; Clear LPM0
            reti

;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET vector
            .short  RESET                   ;
            .sect   ".int08"                ; I2C interruplt vector
            .short  I2C_ISR                 ;
            .end
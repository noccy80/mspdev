;******************************************************************************
;  MSP430F54xA Demo - USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
;
;  Description: This demo connects two MSP430's via the I2C bus. The slave
;  transmits to the master. This is the MASTER CODE. It continuously
;  receives an array of data and demonstrates how to implement an I2C
;  master receiver receiving multiple bytes using the USCI_B0 TX interrupt.
;  ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.045MHz
;
;                                /|\  /|\
;                MSP430F5438A    10k  10k     MSP430F5438A
;                   slave         |    |         master
;             -----------------   |    |   -----------------
;           -|XIN  P3.1/UCB0SDA|<-|----+->|P3.1/UCB0SDA  XIN|-
;            |                 |  |       |                 |
;           -|XOUT             |  |       |             XOUT|-
;            |     P3.2/UCB0SCL|<-+------>|P3.2/UCB0SCL     |
;            |                 |          |                 |
;
;   D. Dang
;   Texas Instruments Inc.
;   December 2009
;   Built with CCS Version: 4.0.2 
;******************************************************************************

    .cdecls C,LIST,"msp430x54xA.h"


PRxData    .equ    R5 
RXByteCtr    .equ    R6 

;-------------------------------------------------------------------------------
            .global _main 
;-------------------------------------------------------------------------------
            .bss    RxBuffer,128 
;-------------------------------------------------------------------------------
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT

            bis.b   #0x06,&P3SEL            ; Assign I2C pins to USCI_B0
            bis.b   #UCSWRST,&UCB0CTL1      ; **Put state machine in reset**
            mov.b   #UCMST + UCMODE_3 + UCSYNC,&UCB0CTL0
                                            ; I2C Master, synchronous mode
            mov.b   #UCSSEL_2 + UCSWRST,& UCB0CTL1
                                            ; Use SMCLK, keep SW reset
            mov.b   #12,&UCB0BR0            ; fSCL = SMCLK/12 = ~100kHz
            mov.b   #0,&UCB0BR1             ;
            mov.w   #0x48,&UCB0I2CSA        ; Slave Address is 048h
            bic.b   #UCSWRST,&UCB0CTL1      ; **Initialize USCI state machine**
            bis.b   #UCRXIE,&UCB0IE         ; Enable RX interrupt

Mainloop
            mov.w   #RxBuffer,PRxData       ; Start of RX buffer
            mov.w   #5,RXByteCtr            ; Load RX byte counter
Mainloop_1  bit.b   #UCTXSTP,&UCB0CTL1      ; Ensure stop condition got sent
            jc      Mainloop_1
            bis.b   #UCTXSTT,&UCB0CTL1      ; I2C start condition

            bis.b   #LPM0 + GIE,SR          ; Enter LPM0, enable interrupts
                                            ; Remain in LPM0 until all data
                                            ; is RX'd
            nop                             ; Set breakpoint >>here<< and
            jmp     Mainloop                ; Repeat
                                            ;
;-------------------------------------------------------------------------------
; The USCI_B0 data ISR is used to move received data from the I2C slave
; to the MSP430 memory. It is structured such that it can be used to receive
; any 2+ number of bytes by pre-loading RXByteCtr with the byte count.
;-------------------------------------------------------------------------------
USCI_B0_ISR;        USCI_B0 Interrupt Handler ISR
;-------------------------------------------------------------------------------
            add.w   &UCB0IV,PC              ; Add offset to PC
            reti                            ; Vector 0: No interrupt
            reti                            ; Vector 2: ALIFG
            reti                            ; Vector 4: NACKIFG
            reti                            ; Vector 6: STTIFG
            reti                            ; Vector 8: STPIFG
            jmp     RXIFG_ISR               ; Vector 10: RXIFG
            reti                            ; Vector 12: TXIFG

RXIFG_ISR
            dec.w   RXByteCtr               ; Decrement RX byte counter
            jz      USCIAB0TX_ISR_2         ; Jump if all bytes were RX'd
            mov.b   &UCB0RXBUF,0(PRxData)   ; Get RX data
            inc.w   PRxData                 ; Increment address pointer
            cmp.w   #1,RXByteCtr            ; Only one byte left?
            jeq     USCIAB0TX_ISR_1         ; Jump if yes
            reti

USCIAB0TX_ISR_1
            bis.b   #UCTXSTP,&UCB0CTL1      ; Generate I2C stop condition
            reti

USCIAB0TX_ISR_2
            mov.b   &UCB0RXBUF,0(PRxData)   ; Move final RX data to address PRxData
            bic.w   #LPM0,0(SP)             ; Exit active from ISR
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int56"              ; USCI_BO Interrupt Vector
            .short  USCI_B0_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
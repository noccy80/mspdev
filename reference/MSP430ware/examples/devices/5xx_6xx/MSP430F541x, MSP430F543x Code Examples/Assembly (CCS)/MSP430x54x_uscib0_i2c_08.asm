;*******************************************************************************
;  MSP430F54x Demo - USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
;
;  Description: This demo connects two MSP430's via the I2C bus. The master
;  transmits to the slave. This is the MASTER CODE. It cntinuously
;  transmits an array of data and demonstrates how to implement an I2C
;  master transmitter sending multiple bytes using the USCI_B0 TX interrupt.
;  ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.045MHz
;
;                                /|\  /|\
;                MSP430F5438     10k  10k      MSP430F5438
;                   slave         |    |         master
;             -----------------   |    |   -----------------
;           -|XIN  P3.1/UCB0SDA|<-|----+->|P3.1/UCB0SDA  XIN|-
;            |                 |  |       |                 |
;           -|XOUT             |  |       |             XOUT|-
;            |     P3.2/UCB0SCL|<-+------>|P3.2/UCB0SCL     |
;            |                 |          |                 |
;
;   M. Morales
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials v3.x
;*******************************************************************************

    .cdecls C,LIST,"msp430x54x.h"

PTxData    .equ    R5 
TXByteCtr    .equ    R6 
TXBytes    .equ    5 

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT

            bis.b   #0x06,&P3SEL            ; Assign I2C pins to USCI_B0
            bis.b   #UCSWRST,&UCB0CTL1      ; **Put state machine in reset**
            mov.b   #UCMST + UCMODE_3 + UCSYNC,&UCB0CTL0; I2C Master, synchronous mode
            mov.b   #UCSSEL_2 + UCSWRST,&UCB0CTL1; Use SMCLK, keep SW reset
            mov.b   #12,&UCB0BR0            ; fSCL = SMCLK/12 = ~100kHz
            mov.b   #0,&UCB0BR1             ;
            mov.w   #0x48,&UCB0I2CSA        ; Slave Address is 048h
            bic.b   #UCSWRST,&UCB0CTL1      ; **Initialize USCI state machine**
            bis.b   #UCTXIE,&UCB0IE         ; Enable TX interrupt

Mainloop    mov.w   #50,R15                 ; Delay required between transaction
Mainloop_1  dec.w   R15
            jnz     Mainloop_1
            mov.w   #TxData,PTxData         ; TX array start address
                                            ; Place breakpoint here to see each
                                            ; transmit operation.
            mov.b   #TXBytes,TXByteCtr      ; Load TX byte counter
            bis.b   #UCTR+UCTXSTT,&UCB0CTL1 ; I2C TX, start condition
            bis.b   #LPM0 + GIE,SR          ; Enter LPM0, enable interrupts
            nop                             ; Remain in LPM0 until all data
                                            ; is TX'd
Mainloop_2  bit.b   #UCTXSTP,&UCB0CTL1      ; Loop until I2C STP got sent
            jc      Mainloop_2
            jmp     Mainloop                ; Repeat
                                            ;
;-------------------------------------------------------------------------------
; The USCIAB0TX_ISR is structured such that it can be used to transmit any
; number of bytes by pre-loading TXByteCtr with the byte count. Also, PTxData
; points to the next byte to transmit.
;-------------------------------------------------------------------------------
USCI_B0_ISR;        USCI_B0 Interrupt Handler ISR
;-------------------------------------------------------------------------------
            add.w   &UCB0IV,PC              ; Add offset to PC
            reti                            ; Vector 0: No interrupt
            reti                            ; Vector 2: ALIFG
            reti                            ; Vector 4: NACKIFG
            reti                            ; Vector 6: STTIFG
            reti                            ; Vector 8: STPIFG
            reti                            ; Vector 10: RXIFG
            jmp     TXIFG_ISR               ; Vector 12: TXIFG
                                            ;
TXIFG_ISR                                   ; TXIFG Interrupt Handler
            tst.w   TXByteCtr               ; Check TX byte counter
            jz      USCIAB0TX_ISR_1         ; Jump if all bytes were TX'd

            mov.b   @PTxData+,&UCB0TXBUF    ; Load TX buffer
            dec.w   TXByteCtr               ; Decrement TX byte counter
            reti

USCIAB0TX_ISR_1
            bis.b   #UCTXSTP,&UCB0CTL1      ; I2C stop condition
            bic.b   #UCTXIFG,&UCB0IFG       ; Clear USCI_B0 TX int flag
            bic.b   #LPM0,0(SP)             ; Exit LPM0
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
TxData;     Table of data to transmit
;-------------------------------------------------------------------------------
            .byte   011h
            .byte   022h
            .byte   033h
            .byte   044h
            .byte   055h
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int56"              ; USCI_BO Interrupt Vector
            .short  USCI_B0_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end

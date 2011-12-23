;*******************************************************************************
;  MSP430F54x Demo - USCI_B0 I2C Slave TX single bytes to MSP430 Master
;
;  Description: This demo connects two MSP430's via the I2C bus. The master
;  reads from the slave. This is the SLAVE code. The TX data begins at 0
;  and is incremented each time it is sent. An incoming start condition
;  is used as a trigger to increment the outgoing data. The master checks the
;  data it receives for validity. If it is incorrect, it stops communicating
;  and the P1.0 LED will stay on. The USCI_B0 TX interrupt is used to know
;  when to TX.
;  ACLK = n/a, MCLK = SMCLK = default DCO = ~1.045MHz
;
;                                /|\  /|\
;               MSP430F5438      10k  10k     MSP430F5438
;                   slave         |    |        master
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

TXData    .equ    R5 

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT
                                            ;
            bis.b   #0x06,&P3SEL            ; Assign I2C pins to USCI_B0
            bis.b   #UCSWRST,&UCB0CTL1      ; **Put state machine in reset**
            mov.b   #UCMODE_3 + UCSYNC,&UCB0CTL0 ; I2C Slave, synchronous mode
            mov.w   #0x48,&UCB0I2COA        ; Own Address is 048h
            bic.b   #UCSWRST,&UCB0CTL1      ; **Initialize USCI state machine**
            bis.b   #UCTXIE + UCSTTIE + UCSTPIE,&UCB0IE ; Enable TX, Start &
                                            ; Stop Interrupts
            clr.b   TXData                  ; Used to hold TX data

            bis.b   #LPM0 + GIE,SR          ; Enter LPM0 w/ interrupts enabled
            nop                             ; For debugger
                                            ;
;-------------------------------------------------------------------------------
USCI_B0_ISR;        USCI_B0 Interrupt Handler ISR
;-------------------------------------------------------------------------------
            add.w   &UCB0IV,PC              ; Add offset to PC
            reti                            ; Vector 0: No interrupt
            reti                            ; Vector 2: ALIFG
            reti                            ; Vector 4: NACKIFG
            jmp     STTIFG_ISR              ; Vector 6: STTIFG
            jmp     STPIFG_ISR              ; Vector 8: STPIFG
            reti                            ; Vector 10: RXIFG
            jmp     TXIFG_ISR               ; Vector 12: TXIFG
                                            ;
STTIFG_ISR                                  ; STT Interrupt Handler
            bic.b   #UCSTTIFG,&UCB0IFG      ; Clear start condition int flag
            reti                            ;
STPIFG_ISR                                  ; STP Interrupt Handler
            inc.b   TXData;                 ; Increment TXData
            bic.b   #UCSTPIFG,&UCB0IFG      ; Clear stop condition int flag
            reti
TXIFG_ISR                                   ; TXIFG Interrupt Handler
            mov.b   TXData,&UCB0TXBUF       ; TX data
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
;*******************************************************************************
;   MSP430x24x Demo - USCI_B1 I2C Master TX single bytes to MSP430 Slave
;
;   Description: This demo connects two MSP430's via the I2C bus. The master
;   transmits to the slave. This is the master code. It continuously
;   transmits 00h, 01h, ..., 0ffh and demonstrates how to implement an I2C
;   master transmitter sending a single byte using the USCI_B1 TX interrupt.
;   ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.045MHz
;
;                                 /|\  /|\
;                MSP430F249       10k  10k     MSP430F249
;                    slave         |    |        master
;              -----------------   |    |  -----------------
;            -|XIN  P5.1/UCB1SDA|<-|---+->|P5.1/UCB1SDA  XIN|-
;             |                 |  |      |                 | 32kHz
;            -|XOUT             |  |      |             XOUT|-
;             |     P5.2/UCB1SCL|<-+----->|P5.2/UCB1SCL     |
;             |                 |         |             P1.0|--> LED
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x24x.h"
;-------------------------------------------------------------------------------
			.text							;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0500h,SP         		; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP5     bis.b   #06h,&P5SEL             ; Assign I2C pins to USCI_B1
SetupUCB1   bis.b   #UCSWRST,&UCB1CTL1      ; Enable SW reset
            mov.b   #UCMST+UCMODE_3+UCSYNC,&UCB1CTL0
                                            ; I2C Master, synchronous mode
            mov.b   #UCSSEL_2+UCSWRST,&UCB1CTL1
                                            ; Use SMCLK, keep SW reset
            mov.b   #12,&UCB1BR0            ; fSCL = SMCLK/12 = ~100kHz
            mov.b   #00,&UCB1BR1
            mov.w   #048h,&UCB1I2CSA        ; Slave Address is 048h
            bic.b   #UCSWRST,&UCB1CTL1      ; Clear SW reset, resume operation
            bis.b   #UCB1TXIE,&UC1IE        ; Enable TX interrupt

            clr.b   R5                      ; Load TX data into R5

Main        mov.w   #1,R6                   ; Load TX byte counter
Main_1      bit.b   #UCTXSTP,&UCB1CTL1      ; Ensure stop condition got sent
            jc      Main_1
            bis.b   #UCTR+UCTXSTT,&UCB1CTL1 ; I2C TX, start condition
            bis.b   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
                                            ; Remain in LPM0 until all data
                                            ; is TX'd
            inc.b   R5                      ; Increment data byte
            jmp     Main                    ; Repeat
;-------------------------------------------------------------------------------
; The USCIAB1TX_ISR is structured such that it can be used to transmit any
; number of bytes by pre-loading R6 with the byte count.
;-------------------------------------------------------------------------------
USCIAB1TX_ISR;      USCI_B1 Data ISR
;-------------------------------------------------------------------------------
            tst.w   R6                      ; Check TX byte counter
            jz      USCIAB1TX_ISR_1         ; Jump if all bytes were TX'd
            mov.b   R5,&UCB1TXBUF           ; Load TX buffer
            dec.w   R6                      ; Decrement TX byte counter
            reti

USCIAB1TX_ISR_1
            bis.b   #UCTXSTP,&UCB1CTL1      ; I2C stop condition
            bic.b   #UCB1TXIFG,&UC1IFG      ; Clear USCI_B1 TX int flag
            bic.w   #LPM0,0(SP)             ; Clear LPM0
            reti
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int17"        ; USCI_B1 Rx Vector
            .short  USCIAB1TX_ISR            ;
            .sect  	".reset"           		; POR, ext. Reset, Watchdog
            .short  RESET
            .end
            
;*******************************************************************************
;   MSP430x41x2 Demo - USCI_B0 I2C Master TX single bytes to MSP430 Slave
;
;   Description: This demo connects two MSP430's via the I2C bus. The master
;   transmits to the slave. This is the master code. It continuously
;   transmits 00h, 01h, ..., 0ffh and demonstrates how to implement an I2C
;   master transmitter sending a single byte using the USCI_B0 TX interrupt.
;   ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.045MHz
;
;                                 /|\  /|\
;                MSP430F41x2      10k  10k     MSP430F41x2
;                    slave         |    |        master
;              -----------------   |    |  -----------------
;            -|XIN  P6.2/UCB0SDA|<-|---+->|P6.2/UCB0SDA  XIN|-
;             |                 |  |      |                 | 32kHz
;            -|XOUT             |  |      |             XOUT|-
;             |     P6.1/UCB0SCL|<-+----->|P6.1/UCB0SCL     |
;             |                 |         |                 |
;
;  P. Thanigai
;  Texas Instruments Inc.
;  January 2009
;  Built with CCE Version: 3.1 
;******************************************************************************
 .cdecls C,LIST, "msp430x41x2.h" 
 
            .global _main
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
_main
RESET       mov.w   #0400h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP6     bis.b   #06h,&P6SEL             ; Assign I2C pins to USCI_B0
SetupUCB0   bis.b   #UCSWRST,&UCB0CTL1      ; Enable SW reset
            mov.b   #UCMST+UCMODE_3+UCSYNC,&UCB0CTL0
                                            ; I2C Master, synchronous mode
            mov.b   #UCSSEL_2+UCSWRST,&UCB0CTL1
                                            ; Use SMCLK, keep SW reset
            mov.b   #12,&UCB0BR0            ; fSCL = SMCLK/12 = ~100kHz
            mov.b   #00,&UCB0BR1
            mov.w   #048h,&UCB0I2CSA        ; Slave Address is 048h
            bic.b   #UCSWRST,&UCB0CTL1      ; Clear SW reset, resume operation
            bis.b   #UCB0TXIE,&IE2          ; Enable TX interrupt

            clr.b   R5                      ; Load TX data into R5

Main        mov.w   #1,R6                   ; Load TX byte counter
Main_1      bit.b   #UCTXSTP,&UCB0CTL1      ; Ensure stop condition got sent
            jc      Main_1
            bis.b   #UCTR+UCTXSTT,&UCB0CTL1 ; I2C TX, start condition
            bis.b   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
                                            ; Remain in LPM0 until all data
                                            ; is TX'd
            inc.b   R5                      ; Increment data byte
            jmp     Main                    ; Repeat
;-------------------------------------------------------------------------------
; The USCIAB0TX_ISR is structured such that it can be used to transmit any
; number of bytes by pre-loading R6 with the byte count.
;-------------------------------------------------------------------------------
USCIAB0TX_ISR;      USCI_B0 Data ISR
;-------------------------------------------------------------------------------
            tst.w   R6                      ; Check TX byte counter
            jz      USCIAB0TX_ISR_1         ; Jump if all bytes were TX'd
            mov.b   R5,&UCB0TXBUF           ; Load TX buffer
            dec.w   R6                      ; Decrement TX byte counter
            reti

USCIAB0TX_ISR_1
            bis.b   #UCTXSTP,&UCB0CTL1      ; I2C stop condition
            bic.b   #UCB0TXIFG,&IFG2        ; Clear USCI_B0 TX int flag
            bic.w   #LPM0,0(SP)             ; Clear LPM0
            reti
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int08"        		; USCI_B0 I2C Data Int Vector
            .short  USCIAB0TX_ISR
            .sect  	".reset"            	; POR, ext. Reset, Watchdog
            .short 	RESET
            .end


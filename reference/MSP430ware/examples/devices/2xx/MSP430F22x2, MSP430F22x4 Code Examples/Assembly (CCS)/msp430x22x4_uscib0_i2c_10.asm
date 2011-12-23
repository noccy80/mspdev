;*******************************************************************************
;   MSP430F22x4 Demo - USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
;
;   Description: This demo connects two MSP430's via the I2C bus. The slave
;   transmits to the master. This is the master code. It continuously
;   receives an array of data and demonstrates how to implement an I2C
;   master receiver receiving multiple bytes using the USCI_B0 TX interrupt.
;   ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.2MHz
;
;                                 /|\  /|\
;                MSP430F22x4      10k  10k     MSP430F22x4
;                    slave         |    |        master
;              -----------------   |    |  -----------------
;            -|XIN  P3.1/UCB0SDA|<-|---+->|P3.1/UCB0SDA  XIN|-
;             |                 |  |      |                 |
;            -|XOUT             |  |      |             XOUT|-
;             |     P3.2/UCB0SCL|<-+----->|P3.2/UCB0SCL     |
;             |                 |         |                 |
;
;  P.Thanigai
;  Texas Instruments Inc.
;  August 2007
;  Built with Code Composer Essentials Version: 2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x22x4.h"
;------------------------------------------------------------------------------             
RxData      .usect ".bss",128              ; Received data buffer-128 bytes
;------------------------------------------------------------------------------                              
;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------

RESET       mov.w   #300h,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP3     bis.b   #06h,&P3SEL             ; Assign I2C pins to USCI_B0
SetupUCB0   bis.b   #UCSWRST,&UCB0CTL1      ; Enable SW reset
            mov.b   #UCMST+UCMODE_3+UCSYNC,&UCB0CTL0
                                            ; I2C Master, synchronous mode
            mov.b   #UCSSEL_2+UCSWRST,&UCB0CTL1
                                            ; Use SMCLK, keep SW reset
            mov.b   #12,&UCB0BR0            ; fSCL = SMCLK/12 = ~100kHz
            mov.b   #00,&UCB0BR1
            mov.w   #048h,&UCB0I2CSA        ; Slave Address is 048h
            bic.b   #UCSWRST,&UCB0CTL1      ; Clear SW reset, resume operation
            bis.b   #UCB0RXIE,&IE2          ; Enable RX interrupt

Main        mov.w   #RxData,R5              ; Start of RX buffer
            mov.w   #5,R6                   ; Load RX byte counter
Main_1      bit.b   #UCTXSTP,&UCB0CTL1      ; Ensure stop condition got sent
            jc      Main_1
            bis.b   #UCTXSTT,&UCB0CTL1      ; I2C start condition
            bis.b   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
                                            ; Remain in LPM0 until all data
                                            ; is RX'd
            nop                             ; Set breakpoint >>here<< and
                                            ; read out the RxData buffer
            jmp     Main                    ; Repeat
;-------------------------------------------------------------------------------
; The USCI_B0 data ISR is used to move received data from the I2C slave
; to the MSP430 memory. It is structured such that it can be used to receive
; any 2+ number of bytes by pre-loading R6 with the byte count.
;-------------------------------------------------------------------------------
USCIAB0TX_ISR;      USCI_B0 Data ISR
;-------------------------------------------------------------------------------
            dec.w   R6                      ; Decrement RX byte counter
            jz      USCIAB0TX_ISR_2         ; Jump if all bytes were RX'd
            mov.b   &UCB0RXBUF,0(R5)        ; Move RX data to address R5
            inc.w   R5                      ; Increment address pointer
            cmp.w   #1,R6                   ; Only one byte left?
            jeq     USCIAB0TX_ISR_1         ; Jump if yes
            reti

USCIAB0TX_ISR_1
            bis.b   #UCTXSTP,&UCB0CTL1      ; Generate I2C stop condition
            reti

USCIAB0TX_ISR_2
            mov.b   &UCB0RXBUF,0(R5)        ; Move final RX data to address R5
            bic.w   #CPUOFF,0(SP)           ; Exit LPM0
            reti
            
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int06"                ; USCI Vector
            .short  USCIAB0TX_ISR           ;        
            .end


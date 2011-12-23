;*******************************************************************************
;   MSP430x47xx Demo - USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
;
;   Description: This demo connects two MSP430's via the I2C bus. The slave
;   transmits to the master. This is the slave code. The interrupt driven
;   data transmission is demonstrated using the USCI_B0 TX interrupt.
;
;                                 /|\  /|\
;                MSP430x47xx      10k  10k   MSP430x47xx
;                    slave         |    |        master
;              -----------------   |    |  -----------------
;            -|XIN  P3.1/UCB0SDA|<-|---+->|P3.1/UCB0SDA  XIN|-
;       32kHz |                 |  |      |                 | 32kHz
;            -|XOUT             |  |      |             XOUT|-
;             |     P3.2/UCB0SCL|<-+----->|P3.2/UCB0SCL     |
;             |                 |         |                 |
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x47x4.h"
;-------------------------------------------------------------------------------
			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP3     bis.b   #BIT1+BIT2,&P3SEL             ; Assign I2C pins to USCI_B0
SetupUCB0   bis.b   #UCSWRST,&UCB0CTL1      ; Enable SW reset
            mov.b   #UCMODE_3+UCSYNC,&UCB0CTL0
                                            ; I2C Slave, synchronous mode
            mov.w   #048h,&UCB0I2COA        ; Own Address is 048h
            bic.b   #UCSWRST,&UCB0CTL1      ; Clear SW reset, resume operation
            bis.b   #UCSTPIE+UCSTTIE,&UCB0I2CIE
                                            ; Enable STT and STP interrupt
            bis.b   #UCB0TXIE,&IE2          ; Enable TX interrupt

Main        mov.w   #TxData,R5              ; Start of TX buffer
            clr.w   R6                      ; Clear TX byte count
            bis.b   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
                                            ; Remain in LPM0 until master
                                            ; finishes RX
            nop                             ; Set breakpoint >>here<< and
                                            ; read out the R6 counter
            jmp     Main                    ; Repeat
;-------------------------------------------------------------------------------
; The USCI_B0 data ISR is used to move data from MSP430 memory to the
; I2C master. R5 points to the next byte to be transmitted, and R6 keeps
; track of the number of bytes transmitted.
;-------------------------------------------------------------------------------
USCIAB0TX_ISR;      USCI_B0 Data ISR
;-------------------------------------------------------------------------------
            mov.b   @R5+,&UCB0TXBUF         ; Transmit data at address R5
            inc.w   R6                      ; Increment TX byte counter
            reti
;-------------------------------------------------------------------------------
; The USCI_B0 state ISR is used to wake up the CPU from LPM0 in order to do
; processing in the main program after data has been transmitted. LPM0 is
; only exit in case of a (re-)start or stop condition when actual data
; was transmitted.
;-------------------------------------------------------------------------------
USCIAB0RX_ISR;      USCI_B0 State ISR
;-------------------------------------------------------------------------------
            bic.b   #UCSTPIFG+UCSTTIFG,&UCB0STAT
                                            ; Clear interrupt flags
            tst.w   R6                      ; Check TX byte counter
            jz      USCIAB0RX_ISR_1         ; Jump if nothing was transmitted
            bic.w   #LPM0,0(SP)             ; Clear LPM0

USCIAB0RX_ISR_1
            reti
;-------------------------------------------------------------------------------
TxData;     Table of data to transmit
;-------------------------------------------------------------------------------
            .byte      011h                    ; Table of data to transmit
            .byte      022h
            .byte      033h
            .byte      044h
            .byte      055h
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int08"        ; USCI_B0 I2C Data Int Vector
            .short  USCIAB0TX_ISR
            .sect   ".int09"        ; USCI_B0 I2C Sate Int Vector
            .short  USCIAB0RX_ISR
            .sect   ".reset"            ; POR, ext. Reset, Watchdog
            .short  RESET
            .end


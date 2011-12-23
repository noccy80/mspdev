;*******************************************************************************
;   MSP430F22x4 Demo - USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
;
;   Description: This demo connects two MSP430's via the I2C bus. The slave
;   transmits to the master. This is the slave code. The interrupt driven
;   data transmission is demonstrated using the USCI_B0 TX interrupt.
;   ACLK = n/a, MCLK = SMCLK = default DCO = ~1.2MHz
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
            .text                  			; Program reset
;------------------------------------------------------------------------------

RESET       mov.w   #300h,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP3     bis.b   #06h,&P3SEL             ; Assign I2C pins to USCI_B0
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
;------------------------------------------------------------------------------
TxData      .byte  011h,022h,033h,044h,055h ; Table of data to transmit
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int06"                ; USCI Vector
            .short  USCIAB0TX_ISR           ; 
            .sect   ".int07"                ; USCI Vector
            .short  USCIAB0RX_ISR           ;        
            .end


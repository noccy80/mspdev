;*******************************************************************************
;   MSP430F22x4 Demo - USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
;
;   Description: This demo connects two MSP430's via the I2C bus. The master
;   transmits to the slave. This is the slave code. The interrupt driven
;   data receiption is demonstrated using the USCIB0 RX interrupt.
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
RxData      .usect  ".bss",128              ; Received data buffer-128 bytes
;------------------------------------------------------------------------------                             
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
            bis.b   #UCB0RXIE,&IE2          ; Enable RX interrupt

Main        mov.w   #RxData,R5              ; Start of RX buffer
            clr.w   R6                      ; Clear RX byte count
            bis.b   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
                                            ; Remain in LPM0 until master
                                            ; finishes TX
            nop                             ; Set breakpoint >>here<< and
                                            ; read out the RxData buffer
            jmp     Main                    ; Repeat
;-------------------------------------------------------------------------------
; The USCI_B0 data ISR is used to move received data from the I2C master
; to the MSP430 memory.
;-------------------------------------------------------------------------------
USCIAB0TX_ISR;      USCI_B0 Data ISR
;-------------------------------------------------------------------------------
            mov.b   &UCB0RXBUF,0(R5)        ; Move RX data to address R5
            inc.w   R5                      ; Increment address pointer
            inc.w   R6                      ; Increment RX byte count
            reti
;-------------------------------------------------------------------------------
; The USCI_B0 state ISR is used to wake up the CPU from LPM0 in order to
; process the received data in the main program. LPM0 is only exit in case
; of a (re-)start or stop condition when actual data was received.
;-------------------------------------------------------------------------------
USCIAB0RX_ISR;      USCI_B0 State ISR
;-------------------------------------------------------------------------------
            bic.b   #UCSTPIFG+UCSTTIFG,&UCB0STAT
                                            ; Clear interrupt flags
            tst.w   R6                      ; Check RX byte counter
            jz      USCIAB0RX_ISR_1         ; Jump if nothing was received
            bic.w   #LPM0,0(SP)             ; Clear LPM0

USCIAB0RX_ISR_1
            reti         
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



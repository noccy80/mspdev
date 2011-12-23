;*******************************************************************************
;   MSP430x41x2 Demo - USCI_B0 I2C Slave RX single bytes from MSP430 Master
;
;   Description: This demo connects two MSP430's via the I2C bus. The master
;   transmits to the slave. This is the slave code. The interrupt driven
;   data receiption is demonstrated using the USCI_B0 RX interrupt.
;   ACLK = n/a, MCLK = SMCLK = default DCO = ~1.045MHz
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
            mov.b   #UCMODE_3+UCSYNC,&UCB0CTL0
                                            ; I2C Slave, synchronous mode
            mov.w   #048h,&UCB0I2COA        ; Own Address is 048h
            bic.b   #UCSWRST,&UCB0CTL1      ; Clear SW reset, resume operation
            bis.b   #UCB0RXIE,&IE2          ; Enable RX interrupt

Main        bis.b   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            nop                             ; Set breakp. >>here<< and read R5
            jmp     Main                    ; Repeat
;-------------------------------------------------------------------------------
USCIAB0TX_ISR;      USCI_B0 Data ISR
;-------------------------------------------------------------------------------
            mov.b   &UCB0RXBUF,R5           ; RX data in R5
            bic.w   #LPM0,0(SP)             ; Clear LPM0
            reti
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".int08"		        ; USCI_B0 I2C Data Int Vector
            .short  USCIAB0TX_ISR
            .sect	".reset"            ; POR, ext. Reset, Watchdog
            .short  RESET
            .end


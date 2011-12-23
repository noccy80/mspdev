;*******************************************************************************
;   MSP430x24x Demo - USCI_B1 I2C Slave RX single bytes from MSP430 Master
;
;   Description: This demo connects two MSP430's via the I2C bus. The master
;   transmits to the slave. This is the slave code. The interrupt driven
;   data receiption is demonstrated using the USCI_B1 RX interrupt.
;   ACLK = n/a, MCLK = SMCLK = default DCO = ~1.045MHz
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
SetupP3     bis.b   #06h,&P5SEL             ; Assign I2C pins to USCI_B1
SetupUCB1   bis.b   #UCSWRST,&UCB1CTL1      ; Enable SW reset
            mov.b   #UCMODE_3+UCSYNC,&UCB1CTL0
                                            ; I2C Slave, synchronous mode
            mov.w   #048h,&UCB1I2COA        ; Own Address is 048h
            bic.b   #UCSWRST,&UCB1CTL1      ; Clear SW reset, resume operation
            bis.b   #UCB1RXIE,&UC1IE         ; Enable RX interrupt

Main        bis.b   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            nop                             ; Set breakp. >>here<< and read R5
            jmp     Main                    ; Repeat
;-------------------------------------------------------------------------------
USCIAB1TX_ISR;      USCI_B1 Data ISR
;-------------------------------------------------------------------------------
            mov.b   &UCB1RXBUF,R5           ; RX data in R5
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
            
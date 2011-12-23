;*******************************************************************************
;   MSP430x47xx Demo - USCI_B0 I2C Master Interface to PCF8574, Read/Write
;
;   Description: I2C communication with a PCF8574 in read and write mode is
;   demonstrated. PCF8574 port P is configured with P0-P3 input, P4-P7. Read
;   P0-P3 input data is written back to Port P4-P7. This example uses the
;   RX ISR and generates an I2C restart condition while switching from
;   master receiver to master transmitter.
;   ACLK = 32kHz, MCLK = SMCLK = TACLK = BRCLK = 1MHz
;
;                               MSP430x47xx
;                              -----------------
;                  /|\ /|\ /|\|              XIN|-
;                  10k 10k  | |                 | 32kHz
;       PCF8574     |   |   --|RST          XOUT|-
;       ---------   |   |     |                 |
;  --->|P0    SDA|<-|---+---->|P3.1/UCB0SDA     |
;  --->|P1       |  |         |                 |
;  --->|P2       |  |         |                 |
;  --->|P3    SCL|<-+---------|P3.2/UCB0SCL     |
;  <---|P4       |            |                 |
;  <---|P5       |            |                 |
;  <---|P6       |            |                 |
;  <---|P7       |            |                 |
;   +--|A0,A1,A2 |            |                 |
;   |  |         |            |                 |
;  \|/
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
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop Watchdog Timer
SetupP3     bis.b   #BIT1+BIT2,&P3SEL       ; Assign P3.1 and P3.2 to I2C 
SetupP5     bis.b   #BIT1, &P5DIR
SetupUCB0   bis.b   #UCSWRST,&UCB0CTL1      ; Enable SW reset
            mov.b   #UCMST+UCMODE_3+UCSYNC,&UCB0CTL0
                                            ; I2C Master, synchronous mode
            mov.b   #UCSSEL_2+UCSWRST,&UCB0CTL1
                                            ; Use SMCLK, keep SW reset
            mov.b   #11,&UCB0BR0            ; fSCL = SMCLK/11 = 95.3kHz
            mov.b   #00,&UCB0BR1
            mov.w   #020h,&UCB0I2CSA        ; Set slave address
            bic.b   #UCSWRST,&UCB0CTL1      ; Clear SW reset, resume operation
            bis.b   #UCB0RXIE,&IE2          ; Enable RX interrupt
SetupTA     mov.w   #CCIE,&TACCTL0          ; TACCR0 interrupt enabled
            mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, contmode

Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            bic.b   #UCTR,&UCB0CTL1         ; I2C RX
            bis.b   #UCTXSTT,&UCB0CTL1      ; I2C start condition
Mainloop_1  bit.b   #UCTXSTT,&UCB0CTL1      ; Loop until I2C STT is sent
            jc      Mainloop_1
            bis.b   #UCTR+UCTXSTT,&UCB0CTL1 ; I2C TX, start condition
            bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
Mainloop_2
            bit.b   #UCTXSTT,&UCB0CTL1      ; Loop until I2C STT is sent
            jc      Mainloop_2
            bis.b   #UCTXSTP,&UCB0CTL1      ; I2C stop condition after 1st TX
            jmp     Mainloop                ; Repeat
;-------------------------------------------------------------------------------
TA0_ISR;
;-------------------------------------------------------------------------------
            xor.b   #BIT1, &P5OUT
            bic.w   #LPM0,0(SP)           ; Exit LPM0
            reti
;-------------------------------------------------------------------------------
USCIAB0TX_ISR;      USCI_B0 Data ISR
;-------------------------------------------------------------------------------
            mov.b   &UCB0RXBUF,R4           ; Move RX data
            rlc.b   R4                      ; Rotate left 4 bits
            rlc.b   R4
            rlc.b   R4
            rlc.b   R4
            bis.b   #0fh,R4                 ; Isolate lower nibble
            mov.b   R4,&UCB0TXBUF           ; Move TX data
            bic.w   #LPM0,0(SP)           ; Exit LPM0
            reti
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int06"          ; Timer_A0 Vector
            .short  TA0_ISR
            .sect   ".int08"        ; USCI_B0 I2C Data Int Vector
            .short  USCIAB0TX_ISR
            .sect   ".reset"            ; POR, ext. Reset, Watchdog
            .short  RESET
            .end

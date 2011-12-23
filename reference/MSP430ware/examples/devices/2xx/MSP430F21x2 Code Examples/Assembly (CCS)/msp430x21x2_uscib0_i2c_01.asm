;*******************************************************************************
;   MSP430F21x2 Demo - USCI_B0 I2C Master to TMP100, Set P5.1 if Temp > 28C
;
;   Description: I2C interface to TMP100 temperature sensor in 9-bit mode.
;   Timer_A CCR0 interrupt is used to wake up and read the two bytes of
;   the TMP100 temperature register every 62ms. If the temperature is greater
;   than 28C, P1.0 is set, else reset. CPU is operated in LPM0. I2C speed
;   is ~100kHz.
;   ACLK = n/a, MCLK = SMCLK = TACLK = BRCLK = default DCO = ~1.2MHz
;
;          /|\           /|\ /|\
;           |   TMP100   10k 10k     MSP430F21x2
;           |   -------   |   |   -------------------
;           +--|Vcc SDA|<-|---+->|P3.1/UCB0SDA    XIN|-
;           |  |       |  |      |                   |
;           +--|A1,A0  |  |      |               XOUT|-
;              |       |  |      |                   |
;           +--|Vss SCL|<-+------|P3.2/UCB0SCL   P1.0|---> LED
;          \|/  -------          |                   |
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"
 ;-------------------------------------------------------------------------------
 			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP         		; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #01h,&P1DIR             ; P1.0 output
SetupP3     bis.b   #06h,&P3SEL             ; Assign I2C pins to USCI_B0
SetupUCB0   bis.b   #UCSWRST,&UCB0CTL1      ; Enable SW reset
            mov.b   #UCMST+UCMODE_3+UCSYNC,&UCB0CTL0
                                            ; I2C Master, synchronous mode
            mov.b   #UCSSEL_2+UCSWRST,&UCB0CTL1
                                            ; Use SMCLK, keep SW reset
            mov.b   #12,&UCB0BR0            ; fSCL = SMCLK/12 = ~100kHz
            mov.b   #00,&UCB0BR1
            mov.w   #04Eh,&UCB0I2CSA        ; Set slave address
            bic.b   #UCSWRST,&UCB0CTL1      ; Clear SW reset, resume operation
            bis.b   #UCB0RXIE,&IE2          ; Enable RX interrupt
SetupTA     mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, contmode

Mainloop    mov.w   #2,R6                   ; Load RX byte counter
            bis.b   #UCTXSTT,&UCB0CTL1      ; I2C start condition
            bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, enable interrupts
                                            ; Remain in LPM0 until all data
                                            ; is RX'd

            cmp.w   #01D00h,R4              ; >28C?
            jlo     Low_Temp
            bis.b   #01h,&P1OUT             ; P1.0 = 1
            jmp     Wait_Next
Low_Temp    bic.b   #01h,&P1OUT             ; P1.0 = 0
Wait_Next   dint
            bis.w   #CCIE,&TACCTL0          ; TACCR0 interrupt enabled
            bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
                                            ; Remain in LPM0 until TACCR0
                                            ; interrupt occurs
            bic.w   #CCIE,&TACCTL0          ; TACCR0 interrupt disabled
            jmp     Mainloop
;-------------------------------------------------------------------------------
TA0_ISR
;-------------------------------------------------------------------------------
            bic.w   #CPUOFF,0(SP)           ; Exit LPM0
            reti
;-------------------------------------------------------------------------------
; The USCIAB0TX_ISR is structured such that it can be used to receive any
; 2+ number of bytes by pre-loading R6 with the byte count.
;-------------------------------------------------------------------------------
USCIAB0TX_ISR;      USCI_B0 Data ISR
;-------------------------------------------------------------------------------
            dec.w   R6                      ; Decrement RX byte counter
            jz      USCIAB0TX_ISR_2         ; Jump if all bytes were RX'd
            mov.b   &UCB0RXBUF,R4           ; Get received byte
            swpb    R4                      ; Move into MSB
            cmp.w   #1,R6                   ; Only one byte left?
            jeq     USCIAB0TX_ISR_1         ; Jump if yes
            reti

USCIAB0TX_ISR_1
            bis.b   #UCTXSTP,&UCB0CTL1      ; Generate I2C stop condition
            reti

USCIAB0TX_ISR_2
            mov.b   &UCB0RXBUF,R5           ; Get final received byte
            bis.w   R5,R4                   ; Combine MSB and LSB
            bic.w   #CPUOFF,0(SP)           ; Exit LPM0
            reti
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".int09"		        ; Timer_A0 Vector
            .short	TA0_ISR
            .sect	".int06"				;USCIAB0TX_VECTOR
            .short	USCIAB0TX_ISR
            .sect	".reset"				; MSP430 RESET Vector
            .short	RESET 
            .end


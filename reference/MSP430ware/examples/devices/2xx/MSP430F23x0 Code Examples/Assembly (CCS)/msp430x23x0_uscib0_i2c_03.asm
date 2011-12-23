;*******************************************************************************
;   MSP430F23x0 Demo - USCI_B0 I2C Master Interface to DAC8571, Write
;
;   Description: Using UCB0TXIE, a continuous sine wave is output to the
;   external DAC using a 16-point look-up table. Only one start condition
;   is executed. Data is handled by the ISR and the CPU is normally in LPM0.
;   ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.2MHz
;
;                MSP430F23x0                       DAC8571
;            ------------------                   ------------
;          -|XIN   P3.1/UCB0SDA|<--------------->|SDA         |
;           |      P3.2/UCB0SCL|---------------->|SCL  I2C    |
;          -|XOUT              |                 |    SLAVE   |
;           |     I2C MASTER   |              GND|A0          |
;
;
;   DAC8571 I2C address = 0x4C (A0 = GND)
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x23x0.h"
;-------------------------------------------------------------------------------
			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #450h,SP         ; Initialize stackpointer
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop Watchdog Timer
SetupP3     bis.b   #06h,&P3SEL             ; Assign I2C pins to USCI_B0
SetupUCB0   bis.b   #UCSWRST,&UCB0CTL1      ; Enable SW reset
            mov.b   #UCMST+UCMODE_3+UCSYNC,&UCB0CTL0
                                            ; I2C Master, synchronous mode
            mov.b   #UCSSEL_2+UCSWRST,&UCB0CTL1
                                            ; Use SMCLK, keep SW reset
            mov.b   #12,&UCB0BR0            ; fSCL = SMCLK/12 = ~100kHz
            mov.b   #00,&UCB0BR1
            mov.w   #04ch,&UCB0I2CSA        ; Set slave address
            bic.b   #UCSWRST,&UCB0CTL1      ; Clear SW reset, resume operation
            bis.b   #UCB0TXIE,&IE2          ; Enable TX ready interrupt

Main        clr.w   R12                     ; Clear byte counter
            bis.b   #UCTR+UCTXSTT,&UCB0CTL1 ; I2C TX, start condition
            mov.b   #010h,&UCB0TXBUF        ; Write DAC control byte
            bis.w   #CPUOFF+GIE,SR          ; Enter LPM0 w/ interrupts
            nop                             ; Required for debug
;-------------------------------------------------------------------------------
USCIAB0TX_ISR;
;-------------------------------------------------------------------------------
            mov.b   Sine_Tab(R12),&UCB0TXBUF; Transmit data byte
            inc.w   R12                     ;
            and.w   #01Fh,R12               ; Do not exceed table
            reti                            ; Return ISR
;-------------------------------------------------------------------------------
;           16 Point 16-bit Sine Table
;-------------------------------------------------------------------------------
Sine_Tab    .byte      0FFh                    ; MSB Word 0
            .byte      0FFh                    ; LSB
            .byte      0F6h                    ; MSB Word 1
            .byte      040h                    ; LSB
            .byte      0DAh                    ; MSB Word 2
            .byte      081h                    ; LSB
            .byte      0B0h                    ; MSB Word 3
            .byte      0FAh                    ; LSB
            .byte      07Fh                    ; MSB Word 4
            .byte      0FFh                    ; LSB
            .byte      04Fh                    ; MSB Word 5
            .byte      003h                    ; LSB
            .byte      025h                    ; MSB Word 6
            .byte      07Ch                    ; LSB
            .byte      009h                    ; MSB Word 7
            .byte      0BDh                    ; LSB
            .byte      000h                    ; MSB Word 8
            .byte      000h                    ; LSB
            .byte      009h                    ; MSB Word 9
            .byte      0BDh                    ; LSB
            .byte      025h                    ; MSB Word 10
            .byte      07Ch                    ; LSB
            .byte      04Fh                    ; MSB Word 11
            .byte      003h                    ; LSB
            .byte      07Fh                    ; MSB Word 12
            .byte      0FEh                    ; LSB
            .byte      0B0h                    ; MSB Word 13
            .byte      0FAh                    ; LSB
            .byte      0DAh                    ; MSB Word 14
            .byte      081h                    ; LSB
            .byte      0F6h                    ; MSB Word 15
            .byte      040h                    ; LSB
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".int06"			; 
            .short	USCIAB0TX_ISR			; USCI0 transmit
            .sect   ".reset"      		; POR, ext. Reset, Watchdog
            .short  RESET
            .end
            
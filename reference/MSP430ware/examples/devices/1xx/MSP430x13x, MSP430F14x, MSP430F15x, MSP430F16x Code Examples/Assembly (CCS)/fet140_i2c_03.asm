;******************************************************************************
;   MSP-FET430P140 Demo - I2C, Master Interface to DAC8571, Repeat Mode
;   Master = '169, Slave = DAC8571
;
;   Description: Using the I2C interrupt TXRDY, a continuous
;   sine wave is output to the external DAC using a 16-point look-up table.
;   Only one start condition is executed. Data is handled in bytes by the I2C
;   module and the CPU is normally in LPM0.
;   ACLK = n/a, MCLK = SMCLK = I2CCLOCK = DCO ~ 750kHz
;
;                    MSP430x169                         DAC8571
;                  ---------------                   ------------
;                 |            SDA|<--------------->|SDA         |
;                 |     I2C    SCL|---------------->|SCL  I2C    |
;                 |   MASTER      |                 |    SLAVE   |
;                 |               |              GND|A0          |
;
;
;   DAC8571 I2C address = 0x4C (A0 = GND)
;
;   Z. Albus / L. Westlund
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x16x.h"
;------------------------------------------------------------------------------
            .text                  ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop Watchdog Timer
SetupP3     bis.b   #0Ah,&P3SEL             ; Assign I2C pins to module
SetupI2C    bis.b   #I2C+SYNC,&U0CTL        ; Switch USART0 to I2C mode
            bic.b   #I2CEN,&U0CTL           ; Disable I2C
            mov.b   #I2CRM+I2CSSEL1,&I2CTCTL; S/W controls data flow, SMCLK
            mov.w   #04Ch,&I2CSA            ; Slave address
            mov.b   #TXRDYIE,&I2CIE         ; Enable I2C interrupts
            bis.b   #I2CEN,&U0CTL           ; Enable I2C
                                            ;
Main        clr     R12                     ; Clear byte counter
            bis.b   #MST,&U0CTL             ; Master
            bis.b   #I2CTRX+I2CSTT,&I2CTCTL ; Write, ST
            mov.b   #010h,&I2CDRB           ; Write DAC control byte
            bis.w   #LPM0 + GIE,SR          ; Enter LPM0 w/ interrupt
End_Main    nop                             ; Required for debug
                                            ;
;------------------------------------------------------------------------------
I2C_ISR;    Common ISR for I2C Module
;------------------------------------------------------------------------------
            add.w   &I2CIV,PC               ; Add I2C offset vector
            reti                            ; No interrupt
            reti                            ; Arbitration Lost - n/a
            reti                            ; No Acknowledgement - n/a
            reti                            ; Own Address - n/a
            reti                            ; Register Access Ready
            reti                            ; Receive Data Ready - n/a
            jmp     TXRDY_ISR               ; Transmit Data Ready
            reti                            ; General Call - GCIFG
            reti                            ; Start Condition RX'd - n/a
                                            ;
TXRDY_ISR   mov.b   Sine_Tab(R12),&I2CDRB   ; Transmit data byte
            inc.b   R12                     ;
            and.b   #01Fh,R12               ; Do not exceed table
EXIT        reti                            ; Return ISR
                                            ;
;-----------------------------------------------------------------------------
;           16 Point 16-bit Sine Table
            .text
;-----------------------------------------------------------------------------
Sine_Tab    .byte   0FFh                    ; MSB Word 0
            .byte   0FFh                    ; LSB
            .byte   0F6h                    ; MSB Word 1
            .byte   040h                    ; LSB
            .byte   0DAh                    ; MSB Word 2
            .byte   081h                    ; LSB
            .byte   0B0h                    ; MSB Word 3
            .byte   0FAh                    ; LSB
            .byte   07Fh                    ; MSB Word 4
            .byte   0FFh                    ; LSB
            .byte   04Fh                    ; MSB Word 5
            .byte   003h                    ; LSB
            .byte   025h                    ; MSB Word 6
            .byte   07Ch                    ; LSB
            .byte   009h                    ; MSB Word 7
            .byte   0BDh                    ; LSB
            .byte   000h                    ; MSB Word 8
            .byte   000h                    ; LSB
            .byte   009h                    ; MSB Word 9
            .byte   0BDh                    ; LSB
            .byte   025h                    ; MSB Word 10
            .byte   07Ch                    ; LSB
            .byte   04Fh                    ; MSB Word 11
            .byte   003h                    ; LSB
            .byte   07Fh                    ; MSB Word 12
            .byte   0FEh                    ; LSB
            .byte   0B0h                    ; MSB Word 13
            .byte   0FAh                    ; LSB
            .byte   0DAh                    ; MSB Word 14
            .byte   081h                    ; LSB
            .byte   0F6h                    ; MSB Word 15
            .byte   040h                    ; LSB
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
             .sect   ".reset"               ; POR, ext. Reset, Watchdog, Flash
             .short  RESET                  ;
             .sect   ".int08"               ; I2C Interrupt Vector
             .short  I2C_ISR                ;
             .end
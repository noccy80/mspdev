;*******************************************************************************
;   MSP430xG461x Demo -  DMA0, Rpt'd Block, I2C Master Intf. to DAC8571, DCO
;   Master = MSP430F4619, Slave = DAC8571
;
;   Description: Using the DMA0, 16-bit sine data is transmitted to the
;   external DAC. The DAC8571 is configured and sent continuous data without
;   a stop or repeated start condition. Data is handled in bytes by the I2C
;   module and the CPU is normally in LPM0.
;   ACLK = 32kHz, MCLK = SMCLK = TACLK = BRCLK = 1MHz
;
;                MSP430xG461x                       DAC8571
;            ------------------                   ------------
;          -|XIN   P3.1/UCB0SDA|<--------------->|SDA         |
;     32kHz |      P3.2/UCB0SCL|---------------->|SCL  I2C    |
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
 .cdecls C,LIST, "msp430xG46x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-----------------------------------------------------------------------------
RESET       mov.w   #850,SP         		; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop Watchdog Timer
SetupP3     bis.b   #06h,&P3SEL             ; Assign I2C pins to USCI_B0
SetupUCB0   bis.b   #UCSWRST,&UCB0CTL1      ; Enable SW reset
            mov.b   #UCMST+UCMODE_3+UCSYNC,&UCB0CTL0
                                            ; I2C Master, synchronous mode
            mov.b   #UCSSEL_2+UCSWRST,&UCB0CTL1
                                            ; Use SMCLK, keep SW reset
            mov.b   #11,&UCB0BR0            ; fSCL = SMCLK/11 = 95.3kHz
            mov.b   #00,&UCB0BR1
            mov.w   #04ch,&UCB0I2CSA        ; Set slave address
            bic.b   #UCSWRST,&UCB0CTL1      ; Clear SW reset, resume operation
SetupDMA    mov.w   #DMA0TSEL_13,&DMACTL0   ; USCI_B0 Transmit Ready Trigger
            movx.a  #Sine_Tab,&DMA0SA       ; Source block address
            movx.a  #UCB0TXBUF,&DMA0DA      ; Destination single address
            mov.w   #020h,&DMA0SZ           ; Block size
            mov.w   #DMADT_4+DMASRCINCR_3+DMADSTBYTE+DMASRCBYTE,&DMA0CTL
                                            ; Rpt, inc src, byte-byte

Main        bis.b   #UCTR+UCTXSTT,&UCB0CTL1 ; Transmitter, Send Start Condition
            bis.w   #DMAEN,&DMA0CTL         ; Enable DMA for consecutive Xfers
            mov.b   #010h,&UCB0TXBUF        ; Write DAC control
            bis.w   #LPM0+GIE,SR            ; Enter LPM0
            nop                             ; Required for debug
;-------------------------------------------------------------------------------
Sine_Tab;   16 Point 16-bit Sine Table
;-------------------------------------------------------------------------------
            .byte      0FFh                    ; MSB Word 0
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
            .sect	".reset"            ; POR, ext. Reset, Watchdog
            .short   RESET
            .end

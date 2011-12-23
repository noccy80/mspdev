;******************************************************************************
;   MSP430xG46x Demo - USART1, SPI 3-Wire Slave Data Echo
;
;   Description: SPI slave talks to SPI master using 3-wire mode. Data received
;   from master is echoed back.  USART1 RX ISR is used to handle communication,
;   CPU normally in LPM4.  Prior to initial data exchange, master pulses
;   slaves RST for complete reset.
;   ACLK = 32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz
;
;   Use with SPI Master Incremented Data code example.  If the slave is in
;   debug mode, the reset signal from the master will conflict with slave's
;   JTAG; to work around,control the master device.

;                MSP430FG461x
;             -----------------
;         /|\|              XIN|-
;          | |                 |   32kHz xtal
;          | |             XOUT|-
; Master---+-|RST              |
;            |             P4.3|<- Data In (SIMO1)
;            |                 |
;            |             P4.4|-> Data Out (SOMI1)
;            |                 |
;            |             P4.5|<- Serial Clock In (UCLK1)
;
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"

MST_Data	.equ   R6
SLV_Data	.equ   R7

;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
waitForMstr bit.b   #020h,&P4IN             ; If clock sig from mstr stays low,
            jz      waitForMstr             ; it is not yet in SPI mode
SetupP4     bis.b   #038h,&P4SEL            ; P4.5,4,3 SPI option select
SetupSPI    mov.b   #CHAR+SYNC+SWRST,&U1CTL ; 8-bit, SPI, Slave
            bis.b   #CKPL+STC,&U1TCTL       ; Polarity, UCLK, 3-wire
            bis.b   #USPIE1,&ME2            ; Module enable
            bic.b   #SWRST,&U1CTL           ; SPI enable
            bis.b   #URXIE1,&IE2            ; Receive interrupt enable

Mainloop    bis.b   #LPM4+GIE,SR            ; Enter LPM4, enable interrupts
            nop                             ; Required for debugger only
                                            ;
;------------------------------------------------------------------------------
USART1RX_ISR;       Test for valid RX and TX character
;------------------------------------------------------------------------------
TX1         bit.b   #UTXIFG1,&IFG2
            jz      TX1
            mov.b   &U1RXBUF,&U1TXBUF
            reti

;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect    ".int19"
            .short   USART1RX_ISR
            .sect	".reset"            	
            .short   RESET
            .end
            
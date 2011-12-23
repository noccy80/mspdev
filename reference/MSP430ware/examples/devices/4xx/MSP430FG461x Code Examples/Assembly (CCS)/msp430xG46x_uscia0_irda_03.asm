;*******************************************************************************
;   MSP430xG461x Demo - USCI_A0 IrDA Physical Layer Comm, 4MHz SMCLK
;
;   Description: This example receives bytes through the USCI module
;   configured for IrDA mode, and sends them out using the USART1 module
;   to a PC running a terminal software. Likewise, data received from the PC
;   through the USART1 is transmitted via IrDA.
;
;   MCLK = SMCLK = DCO = 4MHz, ACLK = 32kHz
;   //* An external 32kHz XTAL on XIN XOUT is required for ACLK *//
;
;                                     MSP430xG461x
;                                -----------------------
;                               |                       |
;                            /|\|                    XIN|-
;                             | |                       | 32kHz
;                             --|RST                XOUT|-
;                               |                       |
;     GP2W0116YPS   /|\         |                       |
;       -------      |          |                       |
;      |    Vcc|-----+  IrDA    |                       |
;      #    LED|-----+ 9600 8N1 |                       |
;      #    TxD|<---------------|P2.4/UCA0TXD           |
;      #    RxD|--------------->|P2.5/UCA0RXD      UTXD1|--> 115,200 8N1
;      #     SD|-----+          |                  URXD1|<-- Terminal SW
;      |    GND|-----+          |                       |
;       -------      |           -----------------------
;                   ---
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP2     bis.b   #030h,&P2SEL            ; Use P2.4/P2.5 for USCI_A0
SetupP4     bis.b   #03h,&P4SEL             ; P4.0,1 = USART1 TXD/RXD
SetupOSC    mov.b   #121,&SCFQCTL           ; Set FLL to 3.998MHz
            mov.b   #FLLD0+FN_2,&SCFI0      ; Adjust range select
SetupUCA0   bis.b   #UCSWRST,&UCA0CTL1      ; Set USCI_A0 SW Reset
            mov.b   #UCSSEL_2+UCSWRST,&UCA0CTL1
                                            ; Use SMCLK, keep SW reset
            mov.b   #26,&UCA0BR0            ; 4Mhz/26=153.8kHz
            mov.b   #0,&UCA0BR1
            mov.b   #UCBRF_1+UCOS16,&UCA0MCTL
                                            ; Set 1st stage modulator to 1
                                            ; 16-times oversampling mode
            mov.b   #UCIRTXPL2+UCIRTXPL0+UCIRTXCLK+UCIREN,&UCA0IRTCTL
                                            ; Pulse length = 6 half clock cyc
                                            ; Enable BITCLK16, IrDA enc/dec
            mov.b   #UCIRRXPL,&UCA0IRRCTL   ; Light = low pulse
            bic.b   #UCSWRST,&UCA0CTL1      ; Resume USCI_A0 operation
            bis.b   #UCA0RXIE,&IE2          ; Enable USCI_A0 RX int
SetupUSART1 bis.b   #SWRST,&U1CTL           ; Set USART1 SW Reset
            bis.b   #UTXE1+URXE1,&ME2       ; Enable USART1 TXD/RXD
            mov.b   #CHAR+SWRST,&U1CTL      ; 8-bit characters, keep SW reset
            mov.b   #SSEL1,&U1TCTL          ; BRCLK = SMCLK
            mov.b   #022h,&U1BR0            ; 4MHz/115,200=34.72
            mov.b   #000h,&U1BR1            ;
            mov.b   #0ddh,&U1MCTL           ; Modulation
            bic.b   #SWRST,&U1CTL           ; Release USART1 state machine
            bis.b   #URXIE1,&IE2            ; Enable UART1 RX int

Mainloop    bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, interrupts enabled
            nop
;-------------------------------------------------------------------------------
USART1RX_ISR;
;           Read RX'd byte from UART1 and transmit using USCI_A0 IrDA
;-------------------------------------------------------------------------------
            bit.b   #UCA0TXIFG,&IFG2        ; Ensure TX buffer is ready
            jnc     USART1RX_ISR
            mov.b   &U1RXBUF,&UCA0TXBUF     ; Move RX'd character to USCI_A
            reti
;-------------------------------------------------------------------------------
USCIRX_ISR; Read RX'd IrDA byte from USCI_A0 and transmit to UART1
;-------------------------------------------------------------------------------
            bit.b   #UTXIFG1,&IFG2          ; Ensure TX buffer is ready
            jnc     USCIRX_ISR
            mov.b   &UCA0RXBUF,&U1TXBUF     ; Move RX'd character to UART1
            reti                            ; Return from ISR
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int19"         ; USART 1 Receive
            .short  USART1RX_ISR
            .sect  	".int25"        ; USCI A0/B0 Receive
            .short  USCIRX_ISR
            .sect   ".reset"            ; POR, ext. Reset
            .short  RESET
            .end

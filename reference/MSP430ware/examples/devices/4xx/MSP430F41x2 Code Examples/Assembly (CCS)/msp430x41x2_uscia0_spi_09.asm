;*******************************************************************************
;   MSP430x41x2 Demo - USCI_A0, SPI 3-Wire Master Incremented Data
;
;   Description: SPI master talks to SPI slave using 3-wire mode. Incrementing
;   data is sent by the master starting at 0x01. Received data is expected to
;   be same as the previous transmission.  USCI RX ISR is used to handle
;   communication with the CPU, normally in LPM0. If high, P5.1 indicates
;   valid data reception.
;   ACLK = n/a, MCLK = SMCLK = DCO ~1.045MHz, BRCLK = SMCLK/2
;
;   Use with SPI Slave Data Echo code example.
;
;                  MSP430F41x2
;                 -----------------
;             /|\|              XIN|-
;              | |                 |
;              --|RST          XOUT|-
;                |                 |
;                |             P6.6|-> Data Out (UCA0SIMO)
;                |                 |
;          LED <-|P5.1         P6.5|<- Data In (UCA0SOMI)
;                |                 |
;  Slave reset <-|P1.1         P6.3|-> Serial Clock Out (UCA0CLK)
;
;  P. Thanigai
;  Texas Instruments Inc.
;  January 2009
;  Built with CCE Version: 3.1
;******************************************************************************
 .cdecls C,LIST, "msp430x41x2.h" 
            .global _main  
;-------------------------------------------------------------------------------
MST_Data	.equ   R6
SLV_Data	.equ   R7
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0400h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps

OFIFGcheck  bic.b   #OFIFG,&IFG1            ; Clear OFIFG
            mov.w   #047FFh,R15             ; Wait for OFIFG to set again if
OFIFGwait   dec.w   R15                     ; not stable yet
            jnz     OFIFGwait
            bit.b   #OFIFG,&IFG1            ; Has it set again?
            jnz     OFIFGcheck              ; If so, wait some more

            mov.w   #2100,R15               ; Now with stable ACLK, wait for
DCO_delay   dec.w   R15                     ; DCO to stabilize.
            jnz     DCO_delay               ;

SetupP1     clr.b   &P1OUT                  ; 
            bis.b   #02h,&P1DIR             ; P1 setup for LED and slave reset
            mov.b   #02h,&P1OUT             ; Set slave reset
SetupP5     mov.b   #02h,&P5OUT             ; P5 setup for LED
            bis.b   #02h,&P5DIR             ;            
SetupP6     bis.b   #BIT3+BIT5+BIT6,&P6SEL

SetupSPI    bis.b   #UCCKPL+UCMSB+UCMST+UCSYNC,&UCA0CTL0;3-pin, 8-bit SPI master
            bis.b   #UCSSEL_2,&UCA0CTL1     ; SMCLK
            bis.b   #02h,&UCA0BR0           ; /2
            clr.b   &UCA0BR1                ;
            clr.b   &UCA0MCTL               ; No modulation
            bic.b   #UCSWRST,&UCA0CTL1      ; **Initialize USCI state machine**
            bis.b   #UCA0RXIE,&IE2          ; Enable USCI_A0 RX interrupt

            bic.b   #02h,&P1OUT             ; Now with SPI signals initialized,
            bis.b   #02h,&P1OUT             ; reset slave
            mov.w   #50,R15                 ; Wait for slave to initialize
waitForSlv  dec.w   R15                     ;
            jnz     waitForSlv              ;
                                            ;
            mov.b   #001h,MST_Data          ; Initialize data values
            mov.b   #000h,SLV_Data          ;
                                            ;
Mainloop    mov.b   MST_Data,&UCA0TXBUF     ; Transmit first character
            bis.b   #LPM0+GIE,SR            ; CPU off, enable interrupts
            nop                             ; Required for debugger only
                                            ;
;-------------------------------------------------------------------------------
USCIA0RX_ISR;       Test for valid RX and TX character
;-------------------------------------------------------------------------------
TX1         bit.b   #UCA0TXIFG,&IFG2        ; USCI_A0 TX buffer ready?
            jz      TX1                     ; Jump is TX buffer not ready
                                            ;
            cmp.b   SLV_Data,&UCA0RXBUF     ; Test for correct character RX'd
            jeq     Pass                    ;
Fail        bic.b   #02h,&P5OUT             ; If incorrect, clear LED
            jmp     TX2                     ;
Pass        bis.b   #02h,&P5OUT             ; If correct, light LED
TX2         inc.b   MST_Data                ; Increment master value
            inc.b   SLV_Data                ; Increment expected slave value
            mov.b   MST_Data,&UCA0TXBUF     ; Send next value
                                            ;
            mov.w   #30,R15                 ; Add time between transmissions to
cycleDelay  dec.w   R15                     ; make sure slave can keep up
            jnz     cycleDelay              ;
            reti                            ; Exit ISR
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".int09"        ; USCI_A0 Rx Vector
            .short  USCIA0RX_ISR            ;
            .sect	".reset"            ; RESET Vector
            .short  RESET                   ;
            .end

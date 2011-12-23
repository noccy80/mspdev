;*******************************************************************************
;   MSP430x41x2 Demo - USCI_A0, SPI 3-Wire Slave Data Echo
;
;   Description: SPI slave talks to SPI master using 3-wire mode. Data received
;   from master is echoed back.  USCI RX ISR is used to handle communication,
;   CPU normally in LPM4.  Prior to initial data exchange, master pulses
;   slaves RST for complete reset.
;   ACLK = n/a, MCLK = SMCLK = DCO ~1.045MHz
;
;   Use with SPI Master Incremented Data code example.  
;
;              MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          | |             XOUT|-
; Master---+-|RST              |
;            |             P6.5|<- Data Out (UCA0SOMI)
;            |                 |
;            |             P6.6|-> Data In (UCA0SIMO)
;            |                 |
;            |             P6.3|<- Serial Clock In (UCA0CLK)
;
;  P. Thanigai
;  Texas Instruments Inc.
;  January 2009
;  Built with CCE Version: 3.1
;******************************************************************************
 .cdecls C,LIST, "msp430x41x2.h" 
            .global _main  
;-------------------------------------------------------------------------------
MST_Data	.equ    R6
SLV_Data	.equ	R7
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0400h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer        
OFIFGcheck  bic.b   #OFIFG,&IFG1            ; Clear OFIFG
            mov.w   #047FFh,R15             ; Wait for OFIFG to set again if
OFIFGwait   dec.w   R15                     ; not stable yet
            jnz     OFIFGwait
            bit.b   #OFIFG,&IFG1            ; Has it set again?
            jnz     OFIFGcheck              ; If so, wait some more

            mov.w   #2100,R15               ; Now with stable ACLK, wait for
DCO_delay   dec.w   R15                     ; DCO to stabilize
            jnz     DCO_delay

waitForMstr bit.b   #0x08,&P6IN             ; If clock sig from mstr stays low,
            jz      waitForMstr             ; it is not yet in SPI mode
SetupP6     bis.b   #BIT3+BIT5+BIT6,&P6SEL
SetupSPI    mov.b   #UCSWRST,&UCA0CTL1      ; **Put state machine in reset**
            bis.b   #UCCKPL+UCMSB+UCSYNC,&UCA0CTL0;3-pin, 8-bit SPI master
            bic.b   #UCSWRST,&UCA0CTL1      ; **Initialize USCI state machine**
            bis.b   #UCA0RXIE,&IE2          ; Enable USCI_A0 RX interrupt
                                            ;
Mainloop    bis.b   #LPM4+GIE,SR            ; Enter LPM4, enable interrupts
            nop                             ; Required for debugger only
                                            ;
;-------------------------------------------------------------------------------
USCIA0RX_ISR;       Test for valid RX and TX character
;-------------------------------------------------------------------------------
TX1         bit.b   #UCA0TXIFG,&IFG2        ; USCI_A0 TX buffer ready?
            jz      TX1                     ;
            mov.b   &UCA0RXBUF,&UCA0TXBUF   ;
            reti
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".int09"		        ; USCI_A0 Rx Vector
            .short  USCIA0RX_ISR            ;
            .sect	".reset"	            ; RESET Vector
            .short  RESET                   ;
            .end

;*******************************************************************************
;   MSP430x24x Demo - USCI_A1, SPI 3-Wire Slave Data Echo
;
;   Description: SPI slave talks to SPI master using 3-wire mode. Data received
;   from master is echoed back.  USCI RX ISR is used to handle communication,
;   CPU normally in LPM4.  Prior to initial data exchange, master pulses
;   slaves RST for complete reset.
;   ACLK = n/a, MCLK = SMCLK = DCO ~1.045MHz
;
;   Use with SPI Master Incremented Data code example.  If the slave is in
;   debug mode, the reset signal from the master will conflict with slave's
;   JTAG; to work around,  control the
;	the Master device with CCE.  If breakpoints are inserted in Master slave
;	must stop also.
;                MSP430F249
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          | |             XOUT|-
; Master---+-|RST              |
;            |             P3.7|<- Data Out (UCA1SOMI)
;            |                 |
;            |             P3.6|-> Data In (UCA1SIMO)
;            |                 |
;            |             P5.0|<- Serial Clock In (UCA1CLK)
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x24x.h"

MST_Data	.equ   R6
SLV_Data	.equ   R7
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0500h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
CheckCal    cmp.b   #0FFh,&CALBC1_1MHZ      ; Calibration constants erased?
            jeq     Trap
            cmp.b   #0FFh,&CALDCO_1MHZ
            jne     Load  
Trap        jmp     $                       ; Trap CPU!!
Load        mov.b   &CALBC1_1MHZ,&BCSCTL1   ; Set DCO to 1MHz
            mov.b   &CALDCO_1MHZ,&DCOCTL    ;                                 
waitForMstr bit.b   #01h,&P5IN              ; If clock sig from mstr stays low,
            jz      waitForMstr             ; it is not yet in SPI mode
                                            ;
SetupP3     bis.b   #0C0h,&P3SEL            ; P3.6,7 USCI_A1 option select
SetuP5      bis.b   #01h,&P5SEL             ; P5.0 USCI_A1 option select
SetupSPI    mov.b   #UCSWRST,&UCA1CTL1      ; **Put state machine in reset**
            bis.b   #UCCKPL+UCMSB+UCSYNC,&UCA1CTL0;3-pin, 8-bit SPI master
            bic.b   #UCSWRST,&UCA1CTL1      ; **Initialize USCI state machine**
            bis.b   #UCA1RXIE,&UC1IE        ; Enable USCI_A1 RX interrupt
                                            ;
Mainloop    bis.b   #LPM4+GIE,SR            ; Enter LPM4, enable interrupts
            nop                             ; Required for debugger only
                                            ;
;-------------------------------------------------------------------------------
USCIA1RX_ISR;       Test for valid RX and TX character
;-------------------------------------------------------------------------------
TX1         bit.b   #UCA1TXIFG,&UC1IFG      ; USCI_A1 TX buffer ready?
            jz      TX1                     ;
            mov.b   &UCA1RXBUF,&UCA1TXBUF   ;
            reti
;-------------------------------------------------------------------------------
 ;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int17"        		; USCI_A1 Rx Vector
            .short   USCIA1RX_ISR            ;
            .sect   ".reset"            	; RESET Vector
            .short   RESET                  ;
            .end
            
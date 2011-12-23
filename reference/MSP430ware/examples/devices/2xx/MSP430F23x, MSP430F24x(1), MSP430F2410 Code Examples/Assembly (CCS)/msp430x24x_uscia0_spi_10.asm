;*******************************************************************************
;   MSP430x24x Demo - USCI_A0, SPI 3-Wire Slave Data Echo
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
;
;                MSP430F249
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          | |             XOUT|-
; Master---+-|RST              |
;            |             P3.5|<- Data Out (UCA0SOMI)
;            |                 |
;            |             P3.4|-> Data In (UCA0SIMO)
;            |                 |
;            |             P3.0|<- Serial Clock In (UCA0CLK)
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x24x.h"

MST_Data  .equ	R6
SLV_Data  .equ	R7
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
waitForMstr bit.b   #01h,&P3IN              ; If clock sig from mstr stays low,
            jz      waitForMstr             ; it is not yet in SPI mode
                                            ;
SetupP3     bis.b   #031h,&P3SEL            ; P3.0,4,5 USCI_A0 option select
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
            .sect   ".int23"        ; USCI_A0 Rx Vector
            .short  USCIA0RX_ISR            ;
            .sect	".reset"            ; POR, ext. Reset
            .short  RESET      
            .end
            
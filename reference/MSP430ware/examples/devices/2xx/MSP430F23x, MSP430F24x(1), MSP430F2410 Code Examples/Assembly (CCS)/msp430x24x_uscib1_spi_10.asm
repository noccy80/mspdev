;*******************************************************************************
;   msp430x24x Demo - USCI_B1, SPI 3-Wire Slave Data Echo
;
;   Description: SPI slave talks to SPI master using 3-wire mode. Data received
;   from master is echoed back.  USCI RX ISR is used to handle communication,
;   CPU normally in LPM4.  Prior to initial data exchange, master pulses
;   slaves RST for complete reset.
;   ACLK = n/a, MCLK = SMCLK = DCO ~ 1048kHz
;
;   Use with SPI Master Incremented Data code example.  If the slave is in
;   debug mode, the reset signal from the master will conflict with slave's
;   JTAG; to work around, control the
;	the Master device with CCE.  If breakpoints are inserted in Master slave
;	must stop also.
;
;                    MSP430F249
;                 -----------------
;             /|\|              XIN|-
;              | |                 |  
;     Master---|-|RST          XOUT|-
;                |                 |
;                |             P5.1|-> Data Out (UCB1SIMO)
;                |                 |
;                |             P5.2|<- Data In (UCB1SOMI)
;                |                 |
;                |             P5.3|-> Serial Clock Out (UCB1CLK)
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x24x.h"

MST_Data	.equ  R6
SLV_Data	.equ  R7
;-------------------------------------------------------------------------------
			.text							;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0500h,SP         		; Initialize stackpointers
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
CheckCal    cmp.b   #0FFh,&CALBC1_1MHZ      ; Calibration constants erased?
            jeq     Trap
            cmp.b   #0FFh,&CALDCO_1MHZ
            jne     Load  
Trap        jmp     $                       ; Trap CPU!!
Load        mov.b   &CALBC1_1MHZ,&BCSCTL1   ; Set DCO to 1MHz
            mov.b   &CALDCO_1MHZ,&DCOCTL    ;                                            ;
waitForMstr bit.b   #BIT3,&P5IN             ; If clock sig from mstr stays low,
            jz      waitForMstr             ; it is not yet in SPI mode
                                            ;
SetupP3     bis.b   #00Eh,&P5SEL            ; P5.3,2,1 option select
SetupSPI    mov.b   #UCSWRST,&UCB1CTL1      ; **Put state machine in reset**
            bis.b   #UCCKPL+UCMSB+UCSYNC,&UCB1CTL0;3-pin, 8-bit SPI master
            bic.b   #UCSWRST,&UCB1CTL1      ; **Initialize USCI state machine**
            bis.b   #UCB1RXIE,&UC1IE        ; Enable USCI_B1 RX interrupt
                                            ;
Mainloop    bis.b   #LPM3+GIE,SR            ; Enter LPM3, enable interrupts
            nop                             ; Required for debugger only
                                            ;
;-------------------------------------------------------------------------------
USCIB1RX_ISR;       Test for valid RX and TX character
;-------------------------------------------------------------------------------
TX1         bit.b   #UCB1TXIFG,&UC1IFG      ; USCI_B1 TX buffer ready?
            jz      TX1                     ;
            mov.b   &UCB1RXBUF,&UCB1TXBUF   ;
            reti
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int17"        ; USCI_B1 Rx Vector
            .short  USCIB1RX_ISR            ;
            .sect  	".reset"           		; POR, ext. Reset, Watchdog
            .short  RESET
            .end
 
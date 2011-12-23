;*******************************************************************************
;   MSP430F22x4 Demo - USCI_A0, SPI 3-Wire Slave Data Echo
;
;   Description: SPI slave talks to SPI master using 3-wire mode. Data received
;   from master is echoed back.  USCI RX ISR is used to handle communication,
;   CPU normally in LPM4.  Prior to initial data exchange, master pulses
;   slaves RST for complete reset.
;   ACLK = n/a, MCLK = SMCLK = DCO ~1.2MHz
;
;   Use with SPI Master Incremented Data code example.  If the slave is in
;   debug mode, the reset signal from the master will conflict with slave's
;   JTAG; to work around, use IAR's "Release JTAG on Go" on slave device.  If
;   breakpoints are set in slave RX ISR, master must stopped also to avoid
;   overrunning slave RXBUF.
;
;                MSP430F22x4
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
;  P.Thanigai
;  Texas Instruments Inc.
;  August 2007
;  Built with Code Composer Essentials Version: 2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x22x4.h"
  
MST_Data  .set     R6
SLV_Data  .set     R7

;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer                                            ;
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
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int07"                ; USCI Vector
            .short  USCIA0RX_ISR            ;        
            .end


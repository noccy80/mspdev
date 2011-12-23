;*******************************************************************************
;   MSP430F22x4 Demo - USCI_A0, SPI 3-Wire Master Incremented Data
;
;   Description: SPI master talks to SPI slave using 3-wire mode. Incrementing
;   data is sent by the master starting at 0x01. Received data is expected to
;   be same as the previous transmission.  USCI RX ISR is used to handle
;   communication with the CPU, normally in LPM0. If high, P1.0 indicates
;   valid data reception.
;   ACLK = n/a, MCLK = SMCLK = DCO ~1.2MHz, BRCLK = SMCLK/2
;
;   Use with SPI Slave Data Echo code example. If slave is in debug mode, P3.6
;   slave reset signal conflicts with slave's JTAG; to work around, use IAR's
;   "Release JTAG on Go" on slave device.  If breakpoints are set in
;   slave RX ISR, master must stopped also to avoid overrunning slave
;   RXBUF.
;
;                    MSP430F22x4 
;                 -----------------
;             /|\|              XIN|-
;              | |                 |
;              --|RST          XOUT|-
;                |                 |
;                |             P3.4|-> Data Out (UCA0SIMO)
;                |                 |
;          LED <-|P1.0         P3.5|<- Data In (UCA0SOMI)
;                |                 |
;  Slave reset <-|P3.6         P3.0|-> Serial Clock Out (UCA0CLK)
;
;
;  P.Thanigai
;  Texas Instruments Inc.
;  August 2007
;  Built with Code Composer Essentials Version: 2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x22x4.h"
 
MST_Data   .set     R6   
SLV_Data   .set     R7                             
;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP1     clr.b   &P1OUT                  ; P1 setup for LED
            bis.b   #01h,&P1DIR             ;
SetupP3     mov.b   #40h,&P3OUT             ; Set slave reset
            bis.b   #40h,&P3DIR             ;
            bis.b   #31h,&P3SEL             ; P3.0,4,5 USCI_A0 option select
SetupSPI    bis.b   #UCCKPL+UCMSB+UCMST+UCSYNC,&UCA0CTL0;3-pin, 8-bit SPI master
            bis.b   #UCSSEL_2,&UCA0CTL1     ; SMCLK
            bis.b   #02h,&UCA0BR0           ; /2
            clr.b   &UCA0BR1                ;
            clr.b   &UCA0MCTL               ; No modulation
            bic.b   #UCSWRST,&UCA0CTL1      ; **Initialize USCI state machine**
            bis.b   #UCA0RXIE,&IE2          ; Enable USCI_A0 RX interrupt

            bic.b   #040h,&P3OUT            ; Now with SPI signals initialized,
            bis.b   #040h,&P3OUT            ; reset slave
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
USCIAB0RX_ISR;       Test for valid RX and TX character
;-------------------------------------------------------------------------------
TX1         bit.b   #UCA0TXIFG,&IFG2        ; USCI_A0 TX buffer ready?
            jz      TX1                     ; Jump is TX buffer not ready
                                            ;
            cmp.b   SLV_Data,&UCA0RXBUF     ; Test for correct character RX'd
            jeq     Pass                    ;
Fail        bic.b   #01h,&P1OUT             ; If incorrect, clear LED
            jmp     TX2                     ;
Pass        bis.b   #01h,&P1OUT             ; If correct, light LED
TX2         inc.b   MST_Data                ; Increment master value
            inc.b   SLV_Data                ; Increment expected slave value
            mov.b   MST_Data,&UCA0TXBUF     ; Send next value
                                            ;
            mov.w   #30,R15                 ; Add time between transmissions to
cycleDelay  dec.w   R15                     ; make sure slave can keep up
            jnz     cycleDelay              ;
            reti                            ; Exit ISR
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int07"                ; USCI Vector
            .short  USCIAB0RX_ISR           ;        
            .end

;*******************************************************************************
;   MSP430x24x Demo - USCI_B1, SPI 3-Wire Master Incremented Data
;
;   Description: SPI master talks to SPI slave using 3-wire mode. Incrementing
;   data is sent by the master starting at 0x01. Received data is expected to
;   be same as the previous transmission.  USCI RX ISR is used to handle
;   communication with the CPU, normally in LPM0. If high, P1.0 indicates
;   valid data reception.  Because all execution after LPM0 is in ISRs,
;   initialization waits for DCO to stabilize against ACLK.
;   ACLK = n/a, MCLK = SMCLK = DCO ~ 1048kHz.  BRCLK = SMCLK/2
;
;   Use with SPI Slave Data Echo code example.  If slave is in debug mode, P1.1
;   slave reset signal conflicts with slave's JTAG; to work around, control the
;	the Master device with CCE.  If breakpoints are inserted in Master slave
;	must stop also.
;
;                    MSP430F249
;                 -----------------
;             /|\|              XIN|-
;              | |                 |  
;              --|RST          XOUT|-
;                |                 |
;                |             P5.1|-> Data Out (UCB1SIMO)
;                |                 |
;          LED <-|P1.0         P5.2|<- Data In (UCB1SOMI)
;                |                 |
;  Slave reset <-|P3.5         P5.3|-> Serial Clock Out (UCB1CLK)
;
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
            mov.b   &CALDCO_1MHZ,&DCOCTL    ;
SetupP1     clr.b   &P1OUT                  ; 
            bis.b   #001h,&P1DIR            ; P1.0 setup for LED 
SetupP3     mov.b   #020h,&P3OUT            ; Set slave reset - P3.5
            bis.b   #020h,&P3DIR
SetupP5     bis.b   #00Eh,&P5SEL            ; P5.1,2,3 USCI_B1 option select      
            
SetupSPI    bis.b   #UCCKPL+UCMSB+UCMST+UCSYNC,&UCB1CTL0;3-pin, 8-bit SPI master
            bis.b   #UCSSEL_2,&UCB1CTL1     ; SMCLK
            bis.b   #02h,&UCB1BR0           ; /2
            clr.b   &UCB1BR1                ;
            bic.b   #UCSWRST,&UCB1CTL1      ; **Initialize USCI state machine**
            bis.b   #UCB1RXIE,&UC1IE        ; Enable USCI_B1 RX interrupt

            bic.b   #02h,&P3OUT             ; Now with SPI signals initialized,
            bis.b   #02h,&P3OUT             ; reset slave
            mov.w   #50,R15                 ; Wait for slave to initialize
waitForSlv  dec.w   R15                     ;
            jnz     waitForSlv              ;
                                            ;
            mov.b   #001h,MST_Data          ; Initialize data values
            mov.b   #000h,SLV_Data          ;
                                            ;
Mainloop    mov.b   MST_Data,&UCB1TXBUF     ; Transmit first character
            bis.b   #LPM0+GIE,SR            ; CPU off, enable interrupts
            nop                             ; Required for debugger only
                                            ;
;-------------------------------------------------------------------------------
USCIB1RX_ISR;       Test for valid RX and TX character
;-------------------------------------------------------------------------------
TX1         bit.b   #UCB1TXIFG,&UC1IFG      ; USCI_B1 TX buffer ready?
            jz      TX1                     ; Jump is TX buffer not ready
                                            ;
            cmp.b   SLV_Data,&UCB1RXBUF     ; Test for correct character RX'd
            jeq     Pass                    ;
Fail        bic.b   #01h,&P1OUT             ; If incorrect, clear LED
            jmp     TX2                     ;
Pass        bis.b   #01h,&P1OUT             ; If correct, light LED
TX2         inc.b   MST_Data                ; Increment master value
            inc.b   SLV_Data                ; Increment expected slave value
            mov.b   MST_Data,&UCB1TXBUF     ; Send next value
                                            ;
            mov.w   #30,R15                 ; Add time between transmissions to
cycleDelay  dec.w   R15                     ; make sure slave can keep up
            jnz     cycleDelay              ;
            reti                            ; Exit ISR
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int17"        ; USCI_B1 Rx Vector
            .short  USCIB1RX_ISR            ;
            .sect  	".reset"           		; POR, ext. Reset, Watchdog
            .short  RESET
            .end
 
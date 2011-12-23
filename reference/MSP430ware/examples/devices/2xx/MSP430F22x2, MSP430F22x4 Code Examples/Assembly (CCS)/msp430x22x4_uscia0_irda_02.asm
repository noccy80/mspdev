;*******************************************************************************
;   MSP430F22x4 Demo - USCI_A0 IrDA Monitor, 8MHz SMCLK
;
;   Description: This example receives bytes through the USCI module
;   configured for IrDA mode, and sends them out as ASCII strings using the
;   Timer_A UART to a PC running a terminal software. The code can be used
;   to monitor and log an IrDA communication.
;
;   ACLK = n/a, MCLK = SMCLK = BRCLK = CALxxx_8MHZ = 8MHz
;
;                                      MSP430F22x4
;                                -----------------------
;                               |                       |
;                            /|\|                    XIN|-
;                             | |                       |
;                             --|RST                XOUT|-
;                               |                       |
;     GP2W0116YPS   /|\         |                       |
;       -------      |          |                       |
;      |    Vcc|-----+  IrDA    |               P2.4/TA2|--> 115,200 8N1
;      #    LED|-----+ 9600 8N1 |                       |    Terminal SW
;      #    TxD|<---------------|P3.4/UCA0TXD           |
;      #    RxD|--------------->|P3.5/UCA0RXD           |
;      #     SD|-----+          |                       |
;      |    GND|-----+          |                       |
;       -------      |           -----------------------
;                   ---
;
;  P.Thanigai
;  Texas Instruments Inc.
;  August 2007
;  Built with Code Composer Essentials Version: 2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x22x4.h"
;-------------------------------------------------------------------------------
BITTIME     .set     69                     ; UART bit time = 8MHz / 115,200

TXData      .usect  ".bss",2                ; Data to transmit
TxBitCnt    .usect  ".bss",1                ; Keeps track of # bits TX'd
;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBCS    mov.b   &CALDCO_8MHZ,&DCOCTL    ; Load 8MHz constants
            mov.b   &CALBC1_8MHZ,&BCSCTL1   ;
SetupP2     bis.b   #010h,&P2SEL            ; Use P2.4 for Timer_A
            bis.b   #010h,&P2DIR            ; P2.4 output
SetupP3     bis.b   #030h,&P3SEL            ; Use P3.4/P3.5 for USCI_A0
SetupUSCI0  bis.b   #UCSWRST,&UCA0CTL1      ; Set SW Reset
            mov.b   #UCSSEL_2+UCSWRST,&UCA0CTL1
                                            ; Use SMCLK, keep SW reset
            mov.b   #52,&UCA0BR0            ; 8MHz/52=153.8KHz
            mov.b   #0,&UCA0BR1             ;
            mov.b   #UCBRF_1+UCOS16,&UCA0MCTL
                                            ; Set 1st stage modulator to 1
                                            ; 16-times oversampling mode
            mov.b   #UCIRTXPL2+UCIRTXPL0+UCIRTXCLK+UCIREN,&UCA0IRTCTL
                                            ; Pulse length = 6 half clock cyc
                                            ; Enable BITCLK16, IrDA enc/dec
            mov.b   #UCIRRXPL,&UCA0IRRCTL   ; Light = low pulse
            bic.b   #UCSWRST,&UCA0CTL1      ; Resume operation
SetupTA     mov.w   #OUT,&TACCTL2           ; TXD Idle as Mark
            mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, continuous mode
                                            ;
Mainloop    dint                            ;
            bis.b   #UCA0RXIE,&IE2          ; Enable RX int
            bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, interrupts enabled
            mov.b   R5,R6                   ; Save received character
            clrc                            ;
            rrc.b   R5                      ; R5 >>= 4
            rra.b   R5                      ;
            rra.b   R5                      ;
            rra.b   R5                      ;
Rdy4TX1     bit.w   #CCIE,&TACCTL2          ; Loop while TX is pending
            jc      Rdy4TX1                 ;
            mov.b   Nibble2ASCII(R5),R15    ;
            call    #TX_Byte                ; TX upper nibble
                                            ;
Rdy4TX2     bit.w   #CCIE,&TACCTL2          ; Loop while TX is pending
            jc      Rdy4TX2                 ;
            and.b   #0fh,R6                 ;
            mov.b   Nibble2ASCII(R6),R15    ; TX lower nibble
            call    #TX_Byte                ;
                                            ;
Rdy4TX3     bit.w   #CCIE,&TACCTL2          ; Loop while TX is pending
            jc      Rdy4TX3                 ;
            mov.b   #' ',R15                ; TX space character
            call    #TX_Byte                ;
            jmp     Mainloop                ; Again
;-------------------------------------------------------------------------------
TX_Byte;    TX the byte stored in R15 using Timer_A UART
;-------------------------------------------------------------------------------
            mov.b   #10,&TxBitCnt           ; Load Bit counter, 8 data + ST/SP
            mov.w   &TAR,&TACCR2            ; Current state of TA counter
            add.w   #BITTIME,&TACCR2        ; Some time till first bit
            bis.w   #0100h,R15              ; Add mark stop bit
            rla.w   R15                     ; Add space start bit
            mov.w   R15,&TXData             ; Load global variable
            mov.w   #OUTMOD0+CCIE,&TACCTL2  ; TXD = mark = idle
            ret                             ;
;-------------------------------------------------------------------------------
USCIRX_ISR; Read RXed character, return from LPM0
;-------------------------------------------------------------------------------
            mov.b   &UCA0RXBUF,R5           ; Get RXed character
            bic.b   #UCA0RXIE,&IE2          ; Disable RX int
            bic.w   #CPUOFF,0(SP)           ; Return active after receiption
            reti                            ; Return from ISR
;-------------------------------------------------------------------------------
TAX_ISR;    Common ISR for TACCR1-2 and overflow
;-------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add Timer_A offset vector
            reti                            ; No interrupt
            reti                            ; TACCR1 - not used
            jmp     TACCR2_ISR              ; TACCR2
            reti                            ; Reserved
            reti                            ; Reserved
            reti                            ; Overflow - not used
;-------------------------------------------------------------------------------
TACCR2_ISR; Timer_A UART TX
;-------------------------------------------------------------------------------
            add.w   #BITTIME,&TACCR2        ; Add Offset to TACCR2
            tst.b   &TxBitCnt               ; All bits TXed?
            jnz     TX_Cont                 ; Jump if not
            bic.w   #CCIE,&TACCTL2          ; All bits TXed, disable interrupt
            reti                            ;
TX_Cont     bit.w   #01h,&TXData            ;
            jz      TX_Zero                 ;
            bic.w   #OUTMOD2,&TACCTL2       ; TX Mark
            jmp     TX_Cont2                ;
TX_Zero     bis.w   #OUTMOD2,&TACCTL2       ; TX Space
TX_Cont2    rra.w   &TXData                 ;
            dec.b   &TxBitCnt               ;
            reti                            ;
;-------------------------------------------------------------------------------
;Table for nibble-to-ASCII conversion
;-------------------------------------------------------------------------------
Nibble2ASCII .byte '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'           
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int07"                ; USCI Vector
            .short  USCIRX_ISR              ; 
            .sect   ".int08"                ; Timer_AX Vector
            .short  TAX_ISR                 ;        
            .end

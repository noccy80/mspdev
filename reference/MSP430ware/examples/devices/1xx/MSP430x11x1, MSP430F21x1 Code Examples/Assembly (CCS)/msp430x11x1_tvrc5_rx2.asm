;*******************************************************************************
;   MSP430x11x1 Demo - Decode RC5 IR Remote Control, No XTAL, Rosc
;
;   Description: Decode 12-bit RC5 format IR packet using Timer_A. CCR0 is
;   used to decode IR packet, capture mode to detect mid-bit edge and compare
;   mode to latch data bit. CCR2 is used for decoder over-run detection.
;   P1.0 is set if channel+ is RXed, reset if not. Normal mode LPM4.
;   IR data are received MSB first. 2 Start, C and 11-bits of data.
;   S1-S2-C-A4-A3-A2-A1-A0-C5-C4-C3-C2-C1-C0
;   Using a 100k resistor on ROSC, with default DCO setting, set DCOCLK ~2MHz.
;   ACLK = n/a, MCLK = SMCLK ~2MHz DCOCLK
;   ;* Use of external resistor reduces temperature sensitivity of DCOCLK *//
;
;                  MSP430F1121
;               -----------------
;     /|\   /|\|              XIN|-
;      |     | |                 |
;     100k   --|RST          XOUT|-
;      |       |                 |
;      +-------|P2.5/ROSC        |
;              |                 |
; IR Receiver->|P2.2/CCR0    P1.0|--> LED
;              |                 |
;
;   IR Receiver = Sharp GP1UD28YK
;
;   Bit pattern as seen at MSP430
;
;    1.78ms
;    +---  +---  +---     ----  ---+     +---
;       |  |  |  |  |     |  |  |  |     |  |
;       ---+  ---+  +--+---  +--+  +-----+  +--
;    ^Start^Start^  1  ^ 0   ^  0  ^
;
;   CPU registers used
IRData  .equ     R6
IRBit   .equ     R7
;
Bit_50      .equ    1780                    ; 890 us @ 2MHz SMCLK
Bit_75      .equ    2696                    ; 1348 us @ 2MHz SMCLK
Ch_up       .equ    32                      ;
;Ch_dwn      .equ    33                      ;
;
;   M. Buccini / Z. Albus
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x11x1.h"
;-------------------------------------------------------------------------------
            .text                           ; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0300h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop Watchdog Timer
SetupBC     bis.b   #DCOR,&BCSCTL2          ; Rosc
            bis.w   #OSCOFF,SR              ; XTAL not used
Setup_TA    mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, ContMode
SetupP1     bis.b   #01h,&P1DIR             ; P1.0 = output
            bic.b   #01h,&P1OUT             ; P1.0 = 0, LED off
SetupP2     bis.b   #04h,&P2SEL             ; P2.2 = CCR0
                                            ;
Mainloop    call    #IR_Ready               ; Ready IR decoder
            bis.w   #LPM4+GIE,SR            ; Enter LPM3 w/ interrupts
            call    #LED_Disp               ; Test for Channel +
            jmp     Mainloop                ;
                                            ;
;-------------------------------------------------------------------------------
IR_Ready;   Subroutine to prepare to receive 12-bit RC5 into IRData
          ; !! Sync capture not possible as DCO=TACLK=SMCLK can be off !!
;-------------------------------------------------------------------------------
            clr.w   IRData                  ;
            mov.w   #14,IRBit               ; 12 data + 1 start + completion
SetupC0     mov.w   #CM_2+CCIS_1+CAP+CCIE,&CCTL0; CAP CCI0B, falling, int
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
TA0_ISR;
;-------------------------------------------------------------------------------
            bit.w   #CAP,&CCTL0             ;
            jc      RX_edge                 ; Jump -> Edge captured
                                            ;
RX_Bit      dec.w   IRBit                   ;
            jz      RX_Comp                 ; Test of .end of packet
RX_Cont     bit.w   #SCCI,&CCTL0            ; Carry = Data bit in SCCI
            rlc.w   IRData                  ; Carry -> IRData
            mov.w   #CM_3+CCIS_1+SCS+CAP+CCIE,&CCTL0; CAP CCI1B,both edges, int
            push.w  &CCR0                   ; Max time till next edge
            add.w   #Bit_50,0(SP)           ;
            pop.w   &CCR2                   ;
            mov.w   #CCIE,&CCTL2            ; Enable timeout interrupt
            reti                            ;
                                            ;
RX_Comp     clr.w   &CCTL0                  ; Disable CCR0
            and.w   #0FFFh,IRData           ; Isolate 12-bit packet
            bic.w   #CPUOFF,0(SP)           ; Decode = Active in Mainloop
            reti                            ;
                                            ;
RX_edge     clr.w   &CCTL2                  ; Disable CCR2 timeout
            mov.w   #CCIS_1+CCIE,&CCTL0     ; Compare mode w/ int.
            add.w   #Bit_75,&CCR0           ; Time to middle of data bit
            bic.w   #SCG1+SCG0,0(SP)        ; !!! DCO needs to remain on !!!
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
TAX_ISR;    Common ISR - CCR1-4 and overflow
;-------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add Timer_A offset vector
            reti                            ; CCR0 - no source
            reti                            ; CCR1
            jmp     TA2_ISR                 ; CCR2
;            reti                            ; CCR3
;            reti                            ; CCR4
;TA_over     reti                            ; Return from overflow ISR		
                                            ;
TA2_ISR     clr.w   &CCTL2                  ; Disable CCR2 timeout
            call    #IR_Ready               ; ERROR - restart RX sequence
            reti                            ; Return from interrupt
                                            ;
;-------------------------------------------------------------------------------
LED_Disp;   LED0 (P1.0) set if IRData = Channel+ code (32)
;-------------------------------------------------------------------------------
            and.w   #03Fh,IRData            ; Isolate 6-bit comand code
LED_off     bic.b   #01h,&P1OUT             ; LED0 off
LED0_tst    cmp.w   #Ch_up,IRData           ; Test for Channel+ (32)
            jne     LED_exit                ;
            bis.b   #01h,&P1OUT             ; LED0 on
LED_exit    ret                             ; Return from subroutine
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int09"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .sect   ".int08"                ; Timer_AX Vector
            .short  TAX_ISR                 ;
            .end

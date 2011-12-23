;*******************************************************************************
;   MSP430x11x1 Demo - Timer_A, Ultra-Low Pwr 1200Hz Detect, ACLK +/- 5%
;
;   Description: Using Timer_A capture capability. At 250ms intervals,
;   CCR0 is enabled on P2.2 to detect presence or absence of 1200Hz. If
;   1200Hz is present, P1.0 is set, if not, reset. WDT is used for 250ms
;   wake-up to hunt for tone. System runs normally in LPM3.
;   ;* External watch crystal installed on XIN XOUT is required for ACLK *//	
;
;        32768Hz = ACLK
;        1200Hz  = 27.3 ACLK clocks
;        1260Hz  = 26 ACLK clocks
;        1730Hz  = 28 ACLK clock
;
;                MSP430F1121
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;    Signal->|P2.2/CCR0    P1.0|-->LED
;            |                 |			
;
;
;           CPU registers used
Period  .equ     R15
OldCap  .equ     R14
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
RESET       mov.w   #300h,SP		        ; Initialize stackpointer
SetupWDT    mov.w   #WDT_ADLY_250,&WDTCTL   ; WDT 250ms Interval Timer
            bis.b   #WDTIE,&IE1             ; Enable WDT Interrupt
SetupP1     mov.b   #0FFh,&P1DIR            ; All P1.x Outputs
            clr.b   &P1OUT                  ; All P1.x Reset
SetupP2     mov.b   #0FBh,&P2DIR            ; P2.2 Input / All P2.x Output
            bis.b   #004h,&P2SEL            ; P2.2 CCR0 input
            clr.b   &P2OUT                  ; All P2.x Reset
                                            ;
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3 W/ interrupts
            call    #Get_CCR0               ; Capture CCR0 on P2.2
            cmp.w   #29,Period              ;
            jhs     OFF                     ;
            cmp.w   #26,Period              ;
            jlo     OFF                     ;
                                            ;
ON          bis.b   #001h,&P1OUT            ; P1.0 = 1
            jmp     Mainloop                ;
OFF         bic.b   #001h,&P1OUT            ; P1.0 = 0
            jmp     Mainloop                ;
                                            ;
;-------------------------------------------------------------------------------
Get_CCR0; Subroutine to get CCR0 Capture
;-------------------------------------------------------------------------------
            clr     Period                  ;
            clr     OldCap                  ;
            mov     #TASSEL0+TACLR,&TACTL   ; ACLK, TAR cleared
SetupC0     mov     #CCIS0+CM0+CAP+CCIE+SCS,&CCTL0; CCI0B, CAP, interrupt
            bis     #MC1,&TACTL             ; Start timer in continuous mode
Test_1      cmp     #112,&TAR               ; Timeout
            jlo     Test_1                  ; jump if 112 > &TAR - timeout
            clr     &TACTL                  ; Stop Timer_A
            clr     &CCTL0                  ; Stop CCTL0
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
TA0_ISR;    Timer_A C0 ISR
;-------------------------------------------------------------------------------
            push.w  &CCR0                   ; Captured TAR, rising edge
            mov.w   @SP,Period              ;
            sub.w   OldCap,Period           ; New - old = period
            pop.w   OldCap                  ; For next calculation
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
WDT_ISR;    Exit LPM3 on reti
;-------------------------------------------------------------------------------
            bic.w    #LPM3,0(SP)            ; Clear LPM3 from TOS
            reti                            ;		
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int10"                ; WDT Vector
            .short  WDT_ISR                 ;
            .sect   ".int09"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end

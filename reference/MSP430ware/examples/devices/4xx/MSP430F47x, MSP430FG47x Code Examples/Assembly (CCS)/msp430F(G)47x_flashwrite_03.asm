;*******************************************************************************
;   MSP430F(G)47x Demo - Flash In-System Programming w/ EEI, Copy SegC to SegD
;
;   Description: This program first erases flash seg C, then it increments all
;   values in seg C, then it erases seg D, then copies seg C to seg D.
;   The EEI bit is set for the Flash Erase Cycles. This does allow the Timer_A
;   Interrupts to be handled also during the Segment erase time.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* Set Breakpoint in the Mainloop to avoid Stressing Flash *//
;
;               MSP430F(G)47x
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;
;   P.Thanigai
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials Version: 3.0
;******************************************************************************
 .cdecls C,LIST, "msp430xG47x.h" 
;-------------------------------------------------------------------------------
value	    .equ   R4
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFTG    mov.w   #FWKEY+FSSEL0+FN1,&FCTL2; Flash Timing generator = MCLK/3
SetupP4     bis.b   #040h,&P4DIR            ; P4.6 output
SetupC0     mov.w   #CCIE,&TACCTL0          ; TACCR0 interrupt enabled
            mov.w   #50000,&TACCR0          ;
SetupTA     mov.w   #TASSEL_2+MC_1,&TACTL   ; SMCLK, upmode
            clr.b   value                   ; value = value to write to flash
            eint                            ; interrupts enabled
                                            ;
Mainloop    call    #Write_SegC             ; Copy value to segment C
            inc.b   value                   ;
            call    #CopyC2D                ;
            jmp     Mainloop                ; Use this instruction with care
                                            ; as it could destroy the Flash mem
                                            ; if running for a long time
                                            ;
;-------------------------------------------------------------------------------
Write_SegC ;Input = value, holds value to write to Seg C, R5 used as working reg
;-------------------------------------------------------------------------------
            mov.w   #01040h,R5              ; Flash pointer
Erase_SegC  mov.w   #FWKEY,&FCTL3           ; Lock = 0
            mov.w   #FWKEY+ERASE+EEI,&FCTL1 ; Erase bit = 1, allow interrupts
            mov.w   #0,&01040h              ; Dummy write to SegC to erase
Prog_SegC   mov.w   #FWKEY+WRT,&FCTL1       ; Write bit = 1, block interrupts
Prog_L1     mov.b   value,0(R5)             ; Write value to flash
            inc.w   R5                      ;
            cmp.w   #01080h,R5              ;
            jne     Prog_L1                 ;
            mov.w   #FWKEY,&FCTL1           ; Write bit = 0
            mov.w   #FWKEY+LOCK,&FCTL3      ; Lock = 1
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
CopyC2D    ;Copy Seg C to Seg D, R5 used as working reg.
;-------------------------------------------------------------------------------
Erase_SegD  mov.w   #FWKEY,&FCTL3           ; Lock = 0
            mov.w   #FWKEY+ERASE+EEI,&FCTL1 ; Erase bit = 1, allow interrupts
            mov.w   #0,&01000h              ; Dummy write to SegD to erase
            mov.w   #01040h,R5              ; R5 = First byte in Seg C
Prog_SegD   mov.w   #FWKEY+WRT,&FCTL1       ; Write bit = 1, block interrupts
            mov.w   #FWKEY,&FCTL3           ; Lock = 0
Prog_L2     mov.b   @R5+,-65(R5)            ; Copy Seg C to Seg D
            cmp.w   #01080h,R5              ;
            jne     Prog_L2                 ;
            mov.w   #FWKEY,&FCTL1           ; Write bit = 0
            mov.w   #FWKEY+LOCK,&FCTL3      ; Lock = 1
            ret                             ;
;-------------------------------------------------------------------------------
TA0_ISR;    Toggle P4.6
;-------------------------------------------------------------------------------
            xor.b   #040h,&P4OUT            ; Toggle P4.6
            reti                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            	; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int06"	            ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end


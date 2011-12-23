;*******************************************************************************
;   MSP430F22x4 Demo - Flash In-System Programming w/ EEI, Copy SegD to A/B/C
;
;   Description: This program first erases flash seg D, then it increments all
;   values in seg D, then it erases segs A,B,C and copies D to those locations
;   The EEI bit is set for the Flash Erase Cycles. This does allow the Timer_A
;   Interrupts to be handled also during the Segment erase time.
;   ACLK = n/a, MCLK = SMCLK = CALxxx_1MHZ = 1MHz
;   //* Set Breakpoint in the Mainloop to avoid Stressing Flash *//
;
;                MSP430F22x4
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;
;  P.Thanigai
;  Texas Instruments Inc.
;  August 2007
;  Built with Code Composer Essentials Version: 2.0
;*******************************************************************************

 .cdecls C,LIST,  "msp430x22x4.h"
;-------------------------------------------------------------------------------
value       .set    R4
;-------------------------------------------------------------------------------            
DCOCalTemp  .usect ".bss",8                 ; Temp. storage for DCO constants
;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupDCO    mov.b   &CALBC1_1MHZ,&BCSCTL1   ; Set DCO to 1MHz
            mov.b   &CALDCO_1MHZ,&DCOCTL    ;
SetupFTG    mov.w   #FWKEY+FSSEL0+FN1,&FCTL2; Flash Timing generator = MCLK/3
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
SetupC0     mov.w   #CCIE,&TACCTL0          ; TACCR0 interrupt enabled
            mov.w   #50000,&TACCR0          ;
SetupTA     mov.w   #TASSEL_2+MC_1,&TACTL   ; SMCLK, upmode
            clr.b   value                   ; value = value to write to flash
            eint                            ; interrupts enabled
                                            ;
Mainloop    call    #Write_SegD             ; Copy value to segment D
            inc.b   value                   ;
            call    #CopyD2A                ; Copy segment D to A
            call    #CopyD2B                ; Copy segment D to B
            call    #CopyD2C                ; Copy segment D to C
            jmp     Mainloop                ; Use this instruction with care
                                            ; as it could destroy the Flash mem
                                            ; if running for a long time
                                            ;
;-------------------------------------------------------------------------------
Write_SegD; Input = value, holds value to write to Seg D, R5 used as working reg
;-------------------------------------------------------------------------------
            mov.w   #01000h,R5              ; Initialize Flash pointer
Erase_SegD  mov.w   #FWKEY,&FCTL3           ; Lock = 0
            mov.w   #FWKEY+ERASE+EEI,&FCTL1 ; Erase bit = 1, allow interrupts
            mov.w   #0,&01000h              ; Dummy write to SegD to erase
Prog_SegD   mov.w   #FWKEY+WRT,&FCTL1       ; Write bit = 1, block interrupts
            mov.w   #FWKEY,&FCTL3           ; Lock = 0
Prog_L1     mov.b   value,0(R5)             ; Write value to flash
            inc.w   R5                      ;
            cmp.w   #01040h,R5              ;
            jne     Prog_L1                 ;
            mov.w   #FWKEY,&FCTL1           ; Write bit = 0
            mov.w   #FWKEY+LOCK,&FCTL3      ; Lock = 1
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
CopyD2A;   Copy Seg D to Seg A, R5 used as working reg.
;          Warning: When this function is called, it MUST complete or
;          DCO calibration constants will be lost
;-------------------------------------------------------------------------------
SaveConsts  mov.w   #010F8h,R5              ; Pointer to DCO constants (Flash)
            mov.w   @R5+,-(010F8h-DCOCalTemp)-2(R5)
            mov.w   @R5+,-(010F8h-DCOCalTemp)-2(R5)
            mov.w   @R5+,-(010F8h-DCOCalTemp)-2(R5)
            mov.w   @R5+,-(010F8h-DCOCalTemp)-2(R5)
                                            ;
Erase_SegA  mov.w   #FWKEY+LOCKA,&FCTL3     ; Clear LOCK & LOCKA bits
            mov.w   #FWKEY+ERASE+EEI,&FCTL1 ; Erase bit = 1, allow interrupts
            mov.w   #0,&010C0h              ; Dummy write to SegA to erase
            mov.w   #01000h,R5              ; R5 = First byte in Seg D
Prog_SegA   mov.w   #FWKEY+WRT,&FCTL1       ; Write bit = 1, block interrupts
Prog_L2     mov.b   @R5+,191(R5)            ; Copy Seg D to Seg A
            cmp.w   #01038h,R5              ; Only copy 56 byte...
            jne     Prog_L2                 ;
                                            ;
RestConsts  mov.w   #DCOCalTemp,R5          ; Pointer to DCO constants (RAM)
            mov.w   @R5+,010F8h-DCOCalTemp-2(R5)
            mov.w   @R5+,010F8h-DCOCalTemp-2(R5)
            mov.w   @R5+,010F8h-DCOCalTemp-2(R5)
            mov.w   @R5+,010F8h-DCOCalTemp-2(R5)
                                            ;
            mov.w   #FWKEY,&FCTL1           ; Clear WRT bit
            mov.w   #FWKEY+LOCKA+LOCK,&FCTL3; Set LOCK & LOCKA bit
            ret                             ;
;-------------------------------------------------------------------------------
CopyD2B;    Copy Seg D to Seg B, R5 used as working reg.
;-------------------------------------------------------------------------------
Erase_SegB  mov.w   #FWKEY,&FCTL3           ; Lock = 0
            mov.w   #FWKEY+ERASE+EEI,&FCTL1 ; Erase bit = 1, allow interrupts
            mov.w   #0,&01080h              ; Dummy write to SegB to erase
            mov.w   #01000h,R5              ; R5 = First byte in Seg D
Prog_SegB   mov.w   #FWKEY+WRT,&FCTL1       ; Write bit = 1, block interrupts
Prog_L3     mov.b   @R5+,127(R5)            ; Copy Seg D to Seg B
            cmp.w   #01040h,R5              ;
            jne     Prog_L3                 ;
            mov.w   #FWKEY,&FCTL1           ; Clear WRT bit
            mov.w   #FWKEY+LOCK,&FCTL3      ; Lock = 1
            ret                             ;
;-------------------------------------------------------------------------------
CopyD2C;    Copy Seg D to Seg C, R5 used as working reg.
;-------------------------------------------------------------------------------
Erase_SegC  mov.w   #FWKEY,&FCTL3           ; Lock = 0
            mov.w   #FWKEY+ERASE+EEI,&FCTL1 ; Erase bit = 1, allow interrupts
            mov.w   #0,&01040h              ; Dummy write to SegC to erase
            mov.w   #01000h,R5              ; R5 = First byte in Seg D
Prog_SegC   mov.w   #FWKEY+WRT,&FCTL1       ; Write bit = 1, block interrupts
Prog_L4     mov.b   @R5+,63(R5)             ; Copy Seg D to Seg C
            cmp.w   #01040h,R5              ;
            jne     Prog_L4                 ;
            mov.w   #FWKEY,&FCTL1           ; Clear WRT bit
            mov.w   #FWKEY+LOCK,&FCTL3      ; Lock = 1
            ret                             ;
;-------------------------------------------------------------------------------
TA0_ISR;    Toggle P1.0
;-------------------------------------------------------------------------------
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int09"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end

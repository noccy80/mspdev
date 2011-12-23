;*******************************************************************************
;   MSP430x261x Demo - Flash In-System Programming w/ EEI, Copy SegD to B&C
;
;   Description: This program first erases flash seg D, then it increments all
;   values in seg D, then it erases segs B&C and copies D to those locations
;   The EEI bit is set for the Flash Erase Cycles. This does allow the Timer_A
;   Interrupts to be handled also during the Segment erase time.
;   ACLK = n/a, MCLK = SMCLK = CALxxx_1MHZ = 1MHz
;   //* Set Breakpoint in the Mainloop to avoid Stressing Flash *//
;
;                MSP430F241x
;                MSP430F261x
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
value		.equ   R4
;-------------------------------------------------------------------------------
DCOCalTemp  .usect ".bss",8                       ; Temp. storage for DCO constants
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
CheckCal    cmp.b   #0FFh,&CALBC1_1MHZ      ; Calibration constants erased?
            jeq     Trap
            cmp.b   #0FFh,&CALDCO_1MHZ
            jne     Load  
Trap        jmp     $                       ; Trap CPU!!
Load        mov.b   &CALBC1_1MHZ,&BCSCTL1   ; Set DCO to 1MHz
            mov.b   &CALDCO_1MHZ,&DCOCTL    ;             
SetupFTG    mov.w   #FWKEY+FSSEL0+FN1,&FCTL2; Flash Timing generator = MCLK/3
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
SetupC0     mov.w   #CCIE,&TACCTL0          ; TACCR0 interrupt enabled
            mov.w   #50000,&TACCR0          ;
SetupTA     mov.w   #TASSEL_2+MC_1,&TACTL   ; SMCLK, upmode
            clr.b   value                   ; value = value to write to flash
            eint                            ; interrupts enabled
                                            ;
Mainloop    calla   #Write_SegD             ; Copy value to segment D
            inc.b   value                   ;
            calla   #CopyD2B                ; Copy segment D to B
            calla   #CopyD2C                ; Copy segment D to C
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
            reta                            ;
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
            reta                            ;
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
            reta                            ;
;-------------------------------------------------------------------------------
TA0_ISR;    Toggle P1.0
;-------------------------------------------------------------------------------
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; MSP430 RESET Vector
            .short  RESET                 ;
            .sect   ".int25"	          ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end
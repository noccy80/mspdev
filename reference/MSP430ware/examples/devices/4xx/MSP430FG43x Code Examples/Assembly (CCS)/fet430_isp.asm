;*****************************************************************************
;   MSP-FET430P430 Demo - Flash In-System Program Memory
;
;   Description: This program demonstrates in-system programming of FLASH
;   memory. Two variable bytes @ 01080h/01081h in SegmentA are modified.
;   The subroutine Update_SegA will save the variables on the stack,
;   incrementing 01080h and decrementing 01081h. SegmentA is first erased and
;   then re-Flashed with the modified variables on the TOS. Flash timing
;   generator must meet datasheet specifications. This program assumes a
;   watch crystal is used, the FLL is active, and MCLK = 1048576 Hz. A
;   breakpoint can be set on "jmp Mainloop", observing flash memory
;   locations 01080h/01081h in a memory window.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   ;* An external watch crystal between XIN & XOUT is required for ACLK *//	
;   ;* IMPORTANT - set breakpoint to avoid stressing Flash *//
;
;                MSP430FG439
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;
;   M. Buccini / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"
;------------------------------------------------------------------------------
            .text                  ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
                                            ;				          							
Mainloop    call    #Update_SegA            ;
Delay       push.w  #0FFFFh                 ; Delay TOS
D1          dec.w   0(SP)                   ; Decrement delay TOS
            jnz     D1                      ;
            incd.w  SP                      ; Clean up stack
            jmp     Mainloop                ; Set BREAKPOINT HERE
                                            ;
;------------------------------------------------------------------------------
Update_SegA; Increment byte 01080h, decrement byte 01081h in Flash SegA
;------------------------------------------------------------------------------
Timing      mov.w   #FWKEY+FSSEL0+FN1,&FCTL2  ; *Timing generator = MCLK/3
            push.b  &01081h                 ; Save contents of 01081h on TOS
            push.b  &01080h                 ; Save contents of 01080h on TOS
            inc.b   0(SP)                   ; Increment TOS
            dec.b   2(SP)                   ; Decrement TOS
                                            ;
Erase_SegA  mov.w   #FWKEY,&FCTL3           ; Lock = 0
            mov.w   #FWKEY+ERASE,&FCTL1     ; Erase bit = 1
            mov.w   #0,&01080h              ; Dummy write to SegA to erase
                                            ;
Write_SegA  mov.w   #FWKEY+WRT,&FCTL1       ; Write bit = 1
            pop.b   &01080h                 ; Write to Flash 01080h
            pop.b   &01081h                 ; Write to Flash 01081h
            mov.w   #FWKEY+LOCK,&FCTL3      ; Lock = 1
            ret                             ;
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .end

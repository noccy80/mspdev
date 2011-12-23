Readme File for MSP430 Code Examples
------------------------------------
The MSP430 code examples are provided for demonstration purposes only. The 
intent is to show how to use the various peripherals found on the MSP430. To 
avoid redundancy, registers were not configured unless necessary. Default 
values were used. Delay loops were ommitted in many cases. For instance, 
when enabling the ADC12's internal reference, one should allow 17 msec for it
to settle to ensure the first sample is accurate. Always consult applicable
datasheet when developing an application.



Coding Style Guidelines for Assembly Code Examples
--------------------------------------------------
1. No line should exceed 80 characters.
2. Use MACROs provided in the MSP430 header file.
3. Labels start in column 1 and are 10 characters or less.
4. Instructions/DIRECTIVES start in column 13.
5. Instructions are lower case and DIRECTIVES are upper case.
6. Operands start in column 21.
7. Comments start in column 45, first word is capitalized.
8. For multi-line comments, additional lines are NOT capitalized.


Examples:


Column:     13      21                      45
            |       |                       |
Label       in/DIR  short_operand           ; Comment


Column:     13      21                      45
            |       |                       |
Label       in/DIR  this_operand_is_extra_long
                                            ; Comment


Column:     13      21                      45
            |       |                       |
Label       in/DIR  this_operand_is_extra_long
                                            ; First line of comment
                                            ; additional comment line


Use MACROs from MSP430 header file:

StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop Watchdog Timer

Instead of hex values:
 
StopWDT     mov.w   #05A80h,&0120h          ; Stop Watchdog Timer

Use ".w" extension for word instructions:
RESET         mov.w   #300h,SP                ; Initialize stack pointer




Coding Style Guidelines for C Code Examples
--------------------------------------------------
1. No line should exceed 80 characters.
2. Use MACROs provided in the MSP430 header file.
3. Comments start in column 45, first word is capitalized.
4. For multi-line comments, additional lines are NOT capitalized.
5. Use two-space indentation



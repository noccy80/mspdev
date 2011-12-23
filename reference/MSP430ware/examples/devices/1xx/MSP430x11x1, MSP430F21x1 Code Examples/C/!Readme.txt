File Name                            Description
----------------------------------------------------------------------------------------
msp430x11x1_1.c                      Software Toggle P1.0
msp430x11x1_549.c                    Software SPI Interface TLC549, Set P1.0 if > 0.5*Vcc
msp430x11x1_ca_01.c                  Comp_A, Output Reference Voltages on P2.3
msp430x11x1_ca_02.c                  Comp_A, Detect Threshold, Set P1.0 if P2.3 > 0.25*Vcc
msp430x11x1_ca_03.c                  Comp_A, Simple 2.2V Low Battery Detect
msp430x11x1_ca_04.c                  Comp_A, Slope ADC to Detect Temp Lvl, Set P1.0 > 25C
msp430x11x1_clks.c                   Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
msp430x11x1_flashwrite_01.c          Flash In-System Programming, Copy SegA to SegB
msp430x11x1_fll_01.c                 Basic Clock, Implement Auto RSEL SW FLL
msp430x11x1_fll_02.c                 Basic Clock, Implement Cont. SW FLL with Auto RSEL
msp430x11x1_hfxtal.c                 Basic Clock, MCLK Sourced from HF XTAL
msp430x11x1_lpm3.c                   Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
msp430x11x1_nmi.c                    Basic Clock, Configure RST/NMI as NMI
msp430x11x1_P2_int.c                 Software Port Interrupt Service on P2.0 from LPM4
msp430x11x1_P2_poll.c                Software Poll P2.0, Set P1.0 if P2.0 = 1
msp430x11x1_rosc.c                   DCOCLK Biased with External Resistor Rosc
msp430x11x1_ta_01.c                  Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
msp430x11x1_ta_02.c                  Timer_A, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
msp430x11x1_ta_03.c                  Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x11x1_ta_04.c                  Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x11x1_ta_05.c                  Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
msp430x11x1_ta_06.c                  Timer_A, Toggle P1.0, CCR1 Cont. Mode ISR, DCO SMCLK
msp430x11x1_ta_07.c                  Timer_A, Toggle P1.0-3, Cont. Mode ISR, DCO SMCLK
msp430x11x1_ta_08.c                  Timer_A, Toggle P1.0-3, Cont. Mode ISR, 32kHz ACLK
msp430x11x1_ta_09.c                  Timer_A, Toggle P1.0-3, Cont. Mode ISR, HF XTAL ACLK
msp430x11x1_ta_10.c                  Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK
msp430x11x1_ta_11.c                  Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
msp430x11x1_ta_12.c                  Timer_A, Toggle P1.1/TA0, Up Mode, HF XTAL ACLK
msp430x11x1_ta_13.c                  Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
msp430x11x1_ta_14.c                  Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK
msp430x11x1_ta_15.c                  Timer_A, Toggle P1.1/TA0, Up/Down Mode, HF XTAL ACLK
msp430x11x1_ta_16.c                  Timer_A, PWM TA1-2, Up Mode, DCO SMCLK
msp430x11x1_ta_17.c                  Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
msp430x11x1_ta_18.c                  Timer_A, PWM TA1-2, Up Mode, HF XTAL ACLK
msp430x11x1_ta_19.c                  Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
msp430x11x1_ta_20.c                  Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
msp430x11x1_ta_21.c                  Timer_A, PWM TA1-2, Up/Down Mode, HF XTAL ACLK
msp430x11x1_ta_uart115k.c            Timer_A, UART 115200 Echo, HF XTAL ACLK
msp430x11x1_ta_uart19200_01.c        Timer_A, UART 19200 Echo, HF XTAL ACLK
msp430x11x1_ta_uart2400.c            Timer_A, Ultra-Low Pwr UART 2400 Echo, 32kHz ACLK
msp430x11x1_ta_uart9600_01.c         Timer_A, UART 9600 Echo, HF XTAL ACLK
msp430x11x1_ta_uart9600_02.c         Timer_A, Ultra-Low Pwr UART 9600 Echo, 32kHz ACLK
msp430x11x1_ta_uart9600_03.c         Timer_A, UART 9600 Echo, 32kHz ACLK
msp430x11x1_ta_uart9600_04.c         Timer_A, Ultra-Low Pwr UART 9600 Echo, No XTAL, ROSC
msp430x11x1_ta_uart9600_05.c         Timer_A, Ultra-Low Pwr UART 9600 String, 32kHz ACLK
msp430x11x1_wdt_01.c                 WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
msp430x11x1_wdt_02.c                 WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
msp430x11x1_wdt_03.c                 WDT, Toggle P1.0, Interval Overflow ISR, HF XTAL ACLK
msp430x21x1_2.c                      Reset on Invalid Address fetch, Toggle P1.0
msp430x21x1_ca_05.c                  Comp_A, Millivolt Meter
msp430x21x1_ca_06.c                  Comp_A, Slope ADC to measure temperature
msp430x21x1_ca_CASHORT.c             Comp_A, Simple 2.2V Low Battery Detect using CASHORT
msp430x21x1_flashwrite_03.c          Flash In-System Programming, Copy SegC to SegD
msp430x21x1_flashwrite_04.c          Flash In-System Programming w/ EEI, Copy SegC to SegD
msp430x21x1_fll_03.c                 Basic Clock, Implement Auto RSEL SW FLL
msp430x21x1_hfxtal.c                 Basic Clock, MCLK Sourced from HF XTAL
msp430x21x1_HF_ExtACLK.c             Basic Clock, MCLK Sourced from HF Digital source
msp430x21x1_LF_ExtACLK.c             LF Mode Ext Digital Clk source
msp430x21x1_LF_OFIFG_extclk.c        OFIFG ISR for LF Failsafe Operation on Ext Clk
msp430x21x1_LF_OFIFG_XTAL.c          OFIFG ISR for LF Failsafe Operation
msp430x21x1_Pull-up.c                21x1 Pull-up resistors demo
msp430x21x1_ta_uart115k_12MHz.c      Timer_A UART 115k, 12MHz DCO SMCLK
msp430x21x1_ta_uart115k_16MHz.c      Timer_A UART 115k, 16MHz DCO SMCLK
msp430x21x1_ta_uart115k_8MHz.c       Timer_A UART 115k, 8MHz DCO SMCLK
msp430x21x1_ta_uart19200_1MHz.c      Timer_A UART 19200 TX, 1MHz DCO
msp430x21x1_ta_uart9600_1MHz.c       Timer_A UART 9600, 1MHz DCO SMCLK
msp430x21x1_wdt_04.c                 WDT+ Failsafe Clock, DCO SMCLK


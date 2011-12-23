File Name                              Description
----------------------------------------------------------------------------------------
msp430x11x1_1.asm                      Software Toggle P1.0
                                       Software Parallel Interface to HC138
msp430x11x1_164.asm                    Software SPI Interface to HC164 Shift Register
msp430x11x1_165.asm                    Software Interface to HC165 Shift Register
msp430x11x1_1820.asm                   Software 1-Wire Interface DS1820, Set P1.0 if > 30C
                                       Software Interface to CD4511 7-Segment Decoder
msp430x11x1_549.asm                    Software SPI Interface TLC549, Set P1.0 if > 0.5*Vcc
msp430x11x1_5616.asm                   Software SPI Interface to TLV5616 12-Bit DAC
                                       Software SPI Interface to HC595 Shift Register
msp430x11x1_5timers.asm                5 Interrupt Timers & 2 Clock Outputs, 32kHz ACLK
msp430x11x1_7822.asm                   Software Interface to Read ADS7822
msp430x11x1_831.asm                    Software SPI Interface to TLV0831
msp430x11x1_8574.asm                   Software I2C Master Interface to PCF8574, Read/Write
msp430x11x1_ca_01.asm                  Comp_A, Output Reference Voltages on P2.3
msp430x11x1_ca_02.asm                  Comp_A, Detect Threshold, Set P1.0 if P2.3 > 0.25*Vcc
msp430x11x1_ca_03.asm                  Comp_A, Simple 2.2V Low Battery Detect
msp430x11x1_ca_04.asm                  Comp_A, Slope ADC to Detect Temp Lvl, Set P1.0 > 25C
msp430x11x1_ca_05.asm                  Comp_A, Thermometer 59-99 F
msp430x11x1_ca_06.asm                  Comp_A, Thermometer 0-50 C
msp430x11x1_ca_07.asm                  Comp_A, Resistance Meter
msp430x11x1_clks.asm                   Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
msp430x11x1_flashwrite_01.asm          Flash In-System Programming, Copy SegA to SegB
                                       Flash In-System Programming, Copy SegA to SegB, Blk
msp430x11x1_fll_01.asm                 Basic Clock, Implement Auto RSEL SW FLL
msp430x11x1_fll_02.asm                 Basic Clock, Implement Cont. SW FLL with Auto RSEL
msp430x11x1_hfxtal.asm                 Basic Clock, MCLK Sourced from HF XTAL
msp430x11x1_hfxtal_nmi.asm             Basic Clock, MCLK Configured with HF XTAL & Osc Fault
msp430x11x1_lpm3.asm                   Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
msp430x11x1_nmi.asm                    Basic Clock, Configure RST/NMI as NMI
msp430x11x1_P2_int.asm                 Software Port Interrupt on P2.0 from LPM4
msp430x11x1_P2_poll.asm                Software Poll P2.0, Set P1.0 if P2.0 = 1
msp430x11x1_r2r.asm                    Software Output 6-Bit R2R DAC
msp430x11x1_rosc.asm                   DCOCLK Biased with External Resistor Rosc
msp430x11x1_selftest.asm               Use JTAG for Downloadable Test Code
msp430x11x1_ta_01.asm                  Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
msp430x11x1_ta_02.asm                  Timer_A, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
msp430x11x1_ta_03.asm                  Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x11x1_ta_04.asm                  Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x11x1_ta_05.asm                  Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
msp430x11x1_ta_06.asm                  Timer_A, Toggle P1.0, CCR1 Cont. Mode ISR, DCO SMCLK
msp430x11x1_ta_07.asm                  Timer_A, Toggle P1.0-3, Cont. Mode ISR, DCO SMCLK
msp430x11x1_ta_08.asm                  Timer_A, Toggle P1.0-3, Cont. Mode ISR, 32kHz ACLK
msp430x11x1_ta_09.asm                  Timer_A, Toggle P1.0-3, Cont. Mode ISR, HF XTAL ACLK
msp430x11x1_ta_10.asm                  Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK
msp430x11x1_ta_11.asm                  Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
msp430x11x1_ta_12.asm                  Timer_A, Toggle P1.1/TA0, Up Mode, HF XTAL ACLK
msp430x11x1_ta_13.asm                  Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
msp430x11x1_ta_14.asm                  Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK
msp430x11x1_ta_15.asm                  Timer_A, Toggle P1.1/TA0, Up/Down Mode, HF XTAL ACLK
msp430x11x1_ta_16.asm                  Timer_A, PWM TA1-2, Up Mode, DCO SMCLK
msp430x11x1_ta_17.asm                  Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
msp430x11x1_ta_18.asm                  Timer_A, PWM TA1-2 Up Mode, HF XTAL ACLK
msp430x11x1_ta_19.asm                  Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
msp430x11x1_ta_20.asm                  Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
msp430x11x1_ta_21.asm                  Timer_A, PWM TA1-2, Up/Down Mode, HF XTAL ACLK
msp430x11x1_ta_22.asm                  Timer_A, Output 40kHz Square Wave, Up Mode, DCO SMCLK
msp430x11x1_ta_23.asm                  Timer_A, Ultra-Low Pwr 1200Hz Detect, ACLK +/- 5%
msp430x11x1_ta_24.asm                  Timer_A, Ultra-Low Pwr 1800Hz Detect, SMCLK +/- 1%
msp430x11x1_ta_uart115k.asm            Timer_A, UART 115200 Echo, HF XTAL ACLK
msp430x11x1_ta_uart19200_01.asm        Timer_A, UART 19200 Echo, HF XTAL ACLK
msp430x11x1_ta_uart19200_02.asm        Timer_A, Ultra-Low Pwr UART 19200 Echo, 32kHz ACLK
msp430x11x1_ta_uart19200_03.asm        Timer_A, UART 19200 Echo, 32kHz ACLK
msp430x11x1_ta_uart19200_04.asm        Timer_A, Ultra-Low Pwr UART 19200 Echo, No XTAL ROSC
msp430x11x1_ta_uart2400.asm            Timer_A, Ultra-Low Pwr UART 2400 Echo, 32kHz ACLK
msp430x11x1_ta_uart9600_01.asm         Timer_A, UART 9600 Echo, HF XTAL ACLK
msp430x11x1_ta_uart9600_02.asm         Timer_A, Ultra-Low Pwr UART 9600 Echo, 32kHz ACLK
msp430x11x1_ta_uart9600_03.asm         Timer_A, UART 9600 Echo, 32kHz ACLK
msp430x11x1_ta_uart9600_04.asm         Timer_A, Ultra-Low Pwr UART 9600 Echo, No XTAL, ROSC
msp430x11x1_ta_uart9600_05.asm         Timer_A, Ultra-Low Pwr UART 9600 String, 32kHz ACLK
msp430x11x1_ta_uart9600_06.asm         Timer_A, Ultra-Low Pwr UART 9600 Echo, 32kHz ACLK
msp430x11x1_tmp100.asm                 Software I2C Master Interface to TMP100
msp430x11x1_tvrc5_rx.asm               Decode RC5 IR Remote Control, 32kHz ACLK
msp430x11x1_tvrc5_rx2.asm              Decode RC5 IR Remote Control, No XTAL, Rosc
msp430x11x1_tvrc5_tx.asm               Encode RC5 IR Remote Control, 32kHz ACLK
msp430x11x1_tvrc5_tx2.asm              Encode RC5 IR Remote Control, No XTAL, Rosc
msp430x11x1_wdt_01.asm                 WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
msp430x11x1_wdt_02.asm                 WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
msp430x11x1_wdt_03.asm                 WDT, Toggle P1.0, Interval Overflow ISR, HF XTAL ACLK
msp430x21x1_2.asm                      Reset on Invalid Address fetch, Toggle P1.0
msp430x21x1_ca_08.asm                  Comp_A, Millivolt Meter
msp430x21x1_ca_CASHORT.asm             Comp_A, Simple 2.2V Low Battery Detect using CASHORT
msp430x21x1_flashwrite_03.asm          Flash In-System Programming, Copy SegC to SegD
msp430x21x1_fll_03.asm                 Basic Clock, Implement Auto RSEL SW FLL
msp430x21x1_hfxtal.asm                 Basic Clock, MCLK Sourced from HF XTAL
msp430x21x1_HF_ExtACLK.asm             Basic Clock, MCLK Sourced from HF Digital source
msp430x21x1_LF_OFIFG_extclk.asm        OFIFG ISR for LF Failsafe Operation on Ext Clk
msp430x21x1_LF_OFIFG_XTAL.asm          OFIFG ISR for LF Failsafe Operation
msp430x21x1_Pull-up.asm                21x1 Pull-up resistors demo
msp430x21x1_ta_uart115k_12MHz.asm      Timer_A, UART 115200 Echo, 12MHz DCO SMCLK
msp430x21x1_ta_uart115k_16MHz.asm      Timer_A, UART 115200 Echo, 16MHz DCO SMCLK
msp430x21x1_ta_uart115k_8MHz.asm       Timer_A, UART 115200 Echo, 8MHz DCO SMCLK
msp430x21x1_ta_uart9600_1MHz.asm       Timer_A, Ultra-Low Pwr UART 9600 Echo,1MHz DCO SMCLK
msp430x21x1_wdt_04.asm                 WDT+ Failsafe Clock, DCO SMCLK


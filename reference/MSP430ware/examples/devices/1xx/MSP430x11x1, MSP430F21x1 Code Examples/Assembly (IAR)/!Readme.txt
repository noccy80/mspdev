File Name                              Description
----------------------------------------------------------------------------------------
msp430x11x1_1.s43                      Software Toggle P1.0
msp430x11x1_138.s43                    Software Parallel Interface to HC138
msp430x11x1_164.s43                    Software SPI Interface to HC164 Shift Register
msp430x11x1_165.s43                    Software Interface to HC165 Shift Register
msp430x11x1_1820.s43                   Software 1-Wire Interface DS1820, Set P1.0 if > 30C
msp430x11x1_4511.s43                   Software Interface to CD4511 7-Segment Decoder
msp430x11x1_549.s43                    Software SPI Interface TLC549, Set P1.0 if > 0.5*Vcc
msp430x11x1_5616.s43                   Software SPI Interface to TLV5616 12-Bit DAC
msp430x11x1_595.s43                    Software SPI Interface to HC595 Shift Register
msp430x11x1_5timers.s43                5 Interrupt Timers & 2 Clock Outputs, 32kHz ACLK
msp430x11x1_7822.s43                   Software Interface to Read ADS7822
msp430x11x1_831.s43                    Software SPI Interface to TLV0831
msp430x11x1_8574.s43                   Software I2C Master Interface to PCF8574, Read/Write
msp430x11x1_ca_01.s43                  Comp_A, Output Reference Voltages on P2.3
msp430x11x1_ca_02.s43                  Comp_A, Detect Threshold, Set P1.0 if P2.3 > 0.25*Vcc
msp430x11x1_ca_03.s43                  Comp_A, Simple 2.2V Low Battery Detect
msp430x11x1_ca_04.s43                  Comp_A, Slope ADC to Detect Temp Lvl, Set P1.0 > 25C
msp430x11x1_ca_05.s43                  Comp_A, Thermometer 59-99 F
msp430x11x1_ca_06.s43                  Comp_A, Thermometer 0-50 C
msp430x11x1_ca_07.s43                  Comp_A, Resistance Meter
msp430x11x1_clks.s43                   Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
msp430x11x1_flashwrite_01.s43          Flash In-System Programming, Copy SegA to SegB
msp430x11x1_flashwrite_02.s43          Flash In-System Programming, Copy SegA to SegB, Blk
msp430x11x1_fll_01.s43                 Basic Clock, Implement Auto RSEL SW FLL
msp430x11x1_fll_02.s43                 Basic Clock, Implement Cont. SW FLL with Auto RSEL
msp430x11x1_hfxtal.s43                 Basic Clock, MCLK Sourced from HF XTAL
msp430x11x1_hfxtal_nmi.s43             Basic Clock, MCLK Configured with HF XTAL & Osc Fault
msp430x11x1_lpm3.s43                   Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
msp430x11x1_nmi.s43                    Basic Clock, Configure RST/NMI as NMI
msp430x11x1_P2_int.s43                 Software Port Interrupt on P2.0 from LPM4
msp430x11x1_P2_poll.s43                Software Poll P2.0, Set P1.0 if P2.0 = 1
msp430x11x1_r2r.s43                    Software Output 6-Bit R2R DAC
msp430x11x1_rosc.s43                   DCOCLK Biased with External Resistor Rosc
msp430x11x1_selftest.s43               Use JTAG for Downloadable Test Code
msp430x11x1_ta_01.s43                  Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
msp430x11x1_ta_02.s43                  Timer_A, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
msp430x11x1_ta_03.s43                  Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x11x1_ta_04.s43                  Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x11x1_ta_05.s43                  Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
msp430x11x1_ta_06.s43                  Timer_A, Toggle P1.0, CCR1 Cont. Mode ISR, DCO SMCLK
msp430x11x1_ta_07.s43                  Timer_A, Toggle P1.0-3, Cont. Mode ISR, DCO SMCLK
msp430x11x1_ta_08.s43                  Timer_A, Toggle P1.0-3, Cont. Mode ISR, 32kHz ACLK
msp430x11x1_ta_09.s43                  Timer_A, Toggle P1.0-3, Cont. Mode ISR, HF XTAL ACLK
msp430x11x1_ta_10.s43                  Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK
msp430x11x1_ta_11.s43                  Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
msp430x11x1_ta_12.s43                  Timer_A, Toggle P1.1/TA0, Up Mode, HF XTAL ACLK
msp430x11x1_ta_13.s43                  Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
msp430x11x1_ta_14.s43                  Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK
msp430x11x1_ta_15.s43                  Timer_A, Toggle P1.1/TA0, Up/Down Mode, HF XTAL ACLK
msp430x11x1_ta_16.s43                  Timer_A, PWM TA1-2, Up Mode, DCO SMCLK
msp430x11x1_ta_17.s43                  Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
msp430x11x1_ta_18.s43                  Timer_A, PWM TA1-2 Up Mode, HF XTAL ACLK
msp430x11x1_ta_19.s43                  Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
msp430x11x1_ta_20.s43                  Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
msp430x11x1_ta_21.s43                  Timer_A, PWM TA1-2, Up/Down Mode, HF XTAL ACLK
msp430x11x1_ta_22.s43                  Timer_A, Output 40kHz Square Wave, Up Mode, DCO SMCLK
msp430x11x1_ta_23.s43                  Timer_A, Ultra-Low Pwr 1200Hz Detect, ACLK +/- 5%
msp430x11x1_ta_24.s43                  Timer_A, Ultra-Low Pwr 1800Hz Detect, SMCLK +/- 1%
msp430x11x1_ta_uart115k.s43            Timer_A, UART 115200 Echo, HF XTAL ACLK
msp430x11x1_ta_uart19200_01.s43        Timer_A, UART 19200 Echo, HF XTAL ACLK
msp430x11x1_ta_uart19200_02.s43        Timer_A, Ultra-Low Pwr UART 19200 Echo, 32kHz ACLK
msp430x11x1_ta_uart19200_03.s43        Timer_A, UART 19200 Echo, 32kHz ACLK
msp430x11x1_ta_uart19200_04.s43        Timer_A, Ultra-Low Pwr UART 19200 Echo, No XTAL ROSC
msp430x11x1_ta_uart2400.s43            Timer_A, Ultra-Low Pwr UART 2400 Echo, 32kHz ACLK
msp430x11x1_ta_uart9600_01.s43         Timer_A, UART 9600 Echo, HF XTAL ACLK
msp430x11x1_ta_uart9600_02.s43         Timer_A, Ultra-Low Pwr UART 9600 Echo, 32kHz ACLK
msp430x11x1_ta_uart9600_03.s43         Timer_A, UART 9600 Echo, 32kHz ACLK
msp430x11x1_ta_uart9600_04.s43         Timer_A, Ultra-Low Pwr UART 9600 Echo, No XTAL, ROSC
msp430x11x1_ta_uart9600_05.s43         Timer_A, Ultra-Low Pwr UART 9600 String, 32kHz ACLK
msp430x11x1_ta_uart9600_06.s43         Timer_A, Ultra-Low Pwr UART 9600 Echo, 32kHz ACLK
msp430x11x1_tmp100.s43                 Software I2C Master Interface to TMP100
msp430x11x1_tvrc5_rx.s43               Decode RC5 IR Remote Control, 32kHz ACLK
msp430x11x1_tvrc5_rx2.s43              Decode RC5 IR Remote Control, No XTAL, Rosc
msp430x11x1_tvrc5_tx.s43               Encode RC5 IR Remote Control, 32kHz ACLK
msp430x11x1_tvrc5_tx2.s43              Encode RC5 IR Remote Control, No XTAL, Rosc
msp430x11x1_wdt_01.s43                 WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
msp430x11x1_wdt_02.s43                 WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
msp430x11x1_wdt_03.s43                 WDT, Toggle P1.0, Interval Overflow ISR, HF XTAL ACLK
msp430x21x1_2.s43                      Reset on Invalid Address fetch, Toggle P1.0
msp430x21x1_ca_08.s43                  Comp_A, Millivolt Meter
msp430x21x1_ca_CASHORT.s43             Comp_A, Simple 2.2V Low Battery Detect using CASHORT
msp430x21x1_flashwrite_03.s43          Flash In-System Programming, Copy SegC to SegD
msp430x21x1_fll_03.s43                 Basic Clock, Implement Auto RSEL SW FLL
msp430x21x1_hfxtal.s43                 Basic Clock, MCLK Sourced from HF XTAL
msp430x21x1_HF_ExtACLK.s43             Basic Clock, MCLK Sourced from HF Digital source
msp430x21x1_LF_OFIFG_extclk.s43        OFIFG ISR for LF Failsafe Operation on Ext Clk
msp430x21x1_LF_OFIFG_XTAL.s43          OFIFG ISR for LF Failsafe Operation
msp430x21x1_Pull-up.s43                21x1 Pull-up resistors demo
msp430x21x1_ta_uart115k_12MHz.s43      Timer_A, UART 115200 Echo, 12MHz DCO SMCLK
msp430x21x1_ta_uart115k_16MHz.s43      Timer_A, UART 115200 Echo, 16MHz DCO SMCLK
msp430x21x1_ta_uart115k_8MHz.s43       Timer_A, UART 115200 Echo, 8MHz DCO SMCLK
msp430x21x1_ta_uart9600_1MHz.s43       Timer_A, Ultra-Low Pwr UART 9600 Echo,1MHz DCO SMCLK
msp430x21x1_wdt_04.s43                 WDT+ Failsafe Clock, DCO SMCLK


File Name                    Description
----------------------------------------------------------------------------------------
fet440_1.asm                 Software Toggle P5.1
fet440_adc12_01.asm          ADC12, Sample A0, Set P5.1 if A0 > 0.5*AVcc
fet440_adc12_02.asm          ADC12, Using the Internal Reference
fet440_adc12_03.asm          ADC12, Sample A10 Temp, Set P5.1 if temp ++ ~2c
fet440_adc12_04.asm          ADC12, Extend Sampling Period With SHT Bits
fet440_adc12_05.asm          ADC12, Using an External Reference
fet440_adc12_06.asm          ADC12, Repeated Sequence of Conversions
fet440_adc12_07.asm          ADC12, Repeated Single Channel Conversions
fet440_adc12_08.asm          ADC12, Using 10 External Channels of Conversion
fet440_adc12_09.asm          ADC12, Sequence of Conversions (non-repeated)
fet440_adc12_10.asm          ADC12, Sample A10 Temp and Convert to oC and oF
fet440_bt_01.asm             Basic Timer, Toggle P5.1 Inside ISR, DCO SMCLK
fet440_bt_02.asm             Basic Timer, Toggle P5.1 Inside ISR, 32kHz ACLK
fet440_clks_01.asm           FLL+, Output MCLK, SMCLK, ACLK Using 32kHz XTAL
fet440_clks_02.asm           FLL+, Output 32kHz Xtal + HF Xtal + Internal DCO
fet440_fll_01.asm            FLL+, Runs Internal DCO at 2.45MHz
fet440_fll_02.asm            FLL+, Runs Internal DCO at 8MHz
fet440_hfxt2.asm             FLL+, MCLK Configured to Operate from XT2 HF XTAL
fet440_isp.asm               Flash In-System Program Memory
fet440_lcd_01.asm            LCD, Display "6543210" on STK/EVK LCD
fet440_lcd_02.asm            LCD, Display Numbers on a Static LCD
fet440_lcd_03.asm            LCD, Display Numbers on a 4-Mux LCD
fet440_LFxtal_nmi.asm        LFXT1 Oscillator Fault Detection
fet440_lpm3.asm              FLL+, LPM3 Using Basic Timer ISR, 32kHz ACLK
fet440_spi0_016x.asm         USART0, SPI Interface to HC165/164 Shift Registers
fet440_svs_01.asm            SVS, POR @ 2.5V Vcc
fet440_ta_01.asm             Timer_A, Toggle P5.1, CCR0 Cont. Mode ISR, DCO SMCLK
fet440_ta_02.asm             Timer_A, Toggle P5.1, CCR0 Up Mode ISR, DCO SMCLK
fet440_ta_03.asm             Timer_A, Toggle P5.1, Overflow ISR, DCO SMCLK
fet440_ta_04.asm             Timer_A, Toggle P5.1, Overflow ISR, 32kHz ACLK
fet440_ta_05.asm             Timer_A, Toggle P5.1, CCR0 Up Mode ISR, 32kHz ACLK
fet440_ta_16.asm             Timer_A, PWM TA1-2 Up Mode, DCO SMCLK
fet440_ta_17.asm             Timer_A, PWM TA1-2 Up Mode, 32kHz ACLK
fet440_tb_01.asm             Timer_B, Toggle P5.1, CCR0 Cont. Mode ISR, DCO SMCLK
fet440_tb_02.asm             Timer_B, Toggle P5.1, CCR0 Up Mode ISR, DCO SMCLK
fet440_tb_03.asm             Timer_B, Toggle P5.1, Overflow ISR, DCO SMCLK
fet440_tb_04.asm             Timer_B, Toggle P5.1, Overflow ISR, 32kHz ACLK
fet440_tb_05.asm             Timer_B Toggle P5.1, CCR0 Up Mode ISR, 32kHz ACLK
fet440_tb_10.asm             Timer_B, PWM TB1-6 Up Mode, DCO SMCLK
fet440_tb_11.asm             Timer_B, PWM TB1-6 Up Mode, 32kHz ACLK
fet440_uart01_0115k.asm      USART0, 115200 UART Echo ISR, DCO SMCLK
fet440_uart01_02400.asm      USART0, 2400 UART Ultra-low Pwr Echo ISR, 32kHz ACLK
fet440_uart01_09600.asm      USART0, 9600 UART Echo ISR, DCO SMCLK
fet440_uart01_19200.asm      USART0, 19200 UART Echo ISR, DCO SMCLK
fet440_uart02_19200.asm      USART0, 19200 UART Ultra-low Pwr Echo ISR, DCO SMCLK
fet440_uart11_19200.asm      USART1, 19200 UART Echo ISR, DC0 SMCLK
fet440_uart11_38400.asm      USART1, 38400 UART Echo ISR, DCO SMCLK
fet440_wdt_01.asm            WDT, Toggle P5.1, Interval Overflow ISR, DCO SMCLK
fet440_wdt_02.asm            WDT, Toggle P5.1, Interval Overflow ISR, 32kHz ACLK


File Name                    Description
----------------------------------------------------------------------------------------
fet430_1.asm                 Software Toggle P5.1
fet430_adc12_01.asm          ADC12, Sample A0, Set P5.1 if A0 > 0.5*AVcc
fet430_adc12_02.asm          ADC12, Using the Internal Reference
fet430_adc12_03.asm          ADC12, Sample A10 Temp, Set P5.1 if temp ++ ~2c
fet430_adc12_04.asm          ADC12, Extend Sampling Period With SHT Bits
fet430_adc12_05.asm          ADC12, Using an External Reference
fet430_adc12_06.asm          ADC12, Repeated Sequence of Conversions
fet430_adc12_07.asm          ADC12, Repeated Single Channel Conversions
fet430_adc12_08.asm          ADC12, Using 10 External Channels of Conversion
fet430_adc12_09.asm          ADC12, Sequence of Conversions (non-repeated)
fet430_adc12_10.asm          ADC12, Sample A10 Temp and Convert to oC and oF
fet430_adc12_11.asm          ADC12, Using the Internal Reference, Channel A12
fet430_adc12_12.asm          ADC12, Using the Internal Reference, Channel A13
fet430_adc12_13.asm          ADC12, Using the Internal Reference, Channel A14
fet430_adc12_14.asm          ADC12, Using the Internal Reference, Channel A15
fet430_bt_01.asm             Basic Timer, Toggle P5.1 Inside ISR, DCO SMCLK
fet430_bt_02.asm             Basic Timer, Toggle P5.1 Inside ISR, 32kHz ACLK
fet430_clks_01.asm           FLL+, Output MCLK, SMCLK, ACLK Using 32kHz XTAL
fet430_clks_02.asm           FLL+, Output 32kHz Xtal + HF Xtal + Internal DCO
fet430_dac12_01.asm          DAC12_0, Output 1.0V on DAC0
fet430_dac12_02.asm          DAC12_1, Output 2.0V on DAC1
fet430_dac12_03.asm          DAC12_0, Output Voltage Ramp on DAC0
fet430_dac12_04.asm          DAC12_0, Output Voltage Ramp on VeREF+
                             DAC0 Output Voltage Ramp, DAC1 Constant, DAC ISR
fet430_dma_01.asm            DMA0, Repeated Burst to-from RAM, Software Trigger
fet430_dma_02.asm            DMA0, Repeated Block To P5OUT, CCR2IFG Trigger
fet430_dma_03.asm            DMA0, Repeated Block UART0 9600, CCR2IFG, ACLK
fet430_dma_04.asm            DMA0, Block Mode UART1 9600, ACLK
fet430_dma_05.asm            DMA0, Repeated Block to DAC0 Sine Output, CCR2, DCO
fet430_dma_06.asm            DMA0, ADC12 A10 Block Xfer to RAM, Timer_B, SMCLK
fet430_dma_07.asm            DMA0, ADC12 A10 Block Xfer to Flash, Timer_B, SMCLK
fet430_fll_01.asm            FLL+, Runs Internal DCO at 2.45MHz
fet430_fll_02.asm            FLL+, Runs Internal DCO at 8MHz
fet430_hfxt2.asm             FLL+, MCLK Configured to Operate from XT2 HF XTAL
fet430_isp.asm               Flash In-System Program Memory
fet430_lcd_01.asm            LCD, Display "0123456" on SBLCDA4 LCD
fet430_lcd_02.asm            LCD, Display "430" on Varitronix VI-322 LCD
fet430_lpm3.asm              FLL+, LPM3 Using Basic Timer ISR, 32kHz ACLK
fet430_oa_01.asm             OA0, Comparator Mode
fet430_oa_02.asm             OA0, Comparator in General-Purpose Mode
fet430_oa_03.asm             OA0, General-Purpose Mode
fet430_oa_04.asm             OA0, Inverting PGA Mode
fet430_oa_05.asm             OA0, Non-Inverting PGA Mode
fet430_oa_06.asm             OA0, Unity-Gain Buffer Mode
fet430_oa_07.asm             OA1, Comparator Mode
fet430_oa_08.asm             OA1, Comparator in General-Purpose Mode
fet430_oa_09.asm             OA1, Inverting PGA Mode
fet430_oa_10.asm             OA1, Non-Inverting PGA Mode
fet430_oa_11.asm             OA1, Unity-Gain Buffer Mode
fet430_oa_12.asm             3-Amp Differential Amplifier with OA0, OA1, and OA2
fet430_oa_13.asm             3-Amp Differential Amplifier with OA1, OA2, and OA0
fet430_oa_14.asm             3-Amp Differential Amplifier with OA2, OA0, and OA1
fet430_spi0_016x.asm         USART0, SPI Interface to HC165/164 Shift Registers
fet430_svs_01.asm            SVS, POR @ 2.5V Vcc
fet430_ta_01.asm             Timer_A, Toggle P5.1, CCR0 Cont. Mode ISR, DCO SMCLK
fet430_ta_02.asm             Timer_A, Toggle P5.1, CCR0 Up Mode ISR, DCO SMCLK
fet430_ta_03.asm             Timer_A, Toggle P5.1, Overflow ISR, DCO SMCLK
fet430_ta_04.asm             Timer_A, Toggle P5.1, Overflow ISR, 32kHz ACLK
fet430_ta_05.asm             Timer_A, Toggle P5.1, CCR0 Up Mode ISR, 32kHz ACLK
fet430_ta_16.asm             Timer_A, PWM TA1-2 Up Mode, DCO SMCLK
fet430_ta_17.asm             Timer_A, PWM TA1-2 Up Mode, 32kHz ACLK
fet430_tb_01.asm             Timer_B, Toggle P5.1, CCR0 Cont. Mode ISR, DCO SMCLK
fet430_tb_02.asm             Timer_B, Toggle P5.1, CCR0 Up Mode ISR, DCO SMCLK
fet430_tb_03.asm             Timer_B, Toggle P5.1, Overflow ISR, DCO SMCLK
fet430_tb_04.asm             Timer_B, Toggle P5.1, Overflow ISR, 32kHz ACLK
fet430_tb_05.asm             Timer_B, Toggle P5.1, CCR0 Up Mode ISR, 32kHz ACLK
fet430_tb_10.asm             Timer_B, PWM TB1-2 Up Mode, DCO SMCLK
fet430_tb_11.asm             Timer_B, PWM TB1-2 Up Mode, 32kHz ACLK
fet430_uart01_0115k.asm      USART0, 115200 UART Echo ISR, DCO SMCLK
fet430_uart01_02400.asm      USART0, 2400 UART Ultra-low Pwr Echo ISR, 32kHz ACLK
fet430_uart01_09600.asm      USART0, 9600 UART Echo ISR, DCO SMCLK
fet430_uart01_19200.asm      USART0, 19200 UART Echo ISR, DCO SMCLK
fet430_uart02_19200.asm      USART0, 19200 UART Ultra-low Pwr Echo ISR, DCO SMCLK
fet430_wdt_01.asm            WDT, Toggle P5.1, Interval Overflow ISR, DCO SMCLK
fet430_wdt_02.asm            WDT, Toggle P5.1, Interval Overflow ISR, 32kHz ACLK


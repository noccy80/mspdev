File Name                                 Description
----------------------------------------------------------------------------------------
msp430xG46x_1.s43                          Software Toggle P1.0
msp430xG46x_adc12_01.s43                   ADC12, Sample A0, Set P5.1 if A0 > 0.5*AVcc
msp430xG46x_adc12_02.s43                   ADC12, Using the Internal Reference
msp430xG46x_adc12_03.s43                   ADC12, Sample A10 Temp, Set P5.1 if Temp ++ ~2C
msp430xG46x_adc12_04.s43                   ADC12, Extend Sampling Period with SHT Bits
msp430xG46x_adc12_05.s43                   ADC12, Using an External Reference
msp430xG46x_adc12_06.s43                   ADC12, Repeated Sequence of Conversions
msp430xG46x_adc12_07.s43                   ADC12, Repeated Single Channel Conversions
msp430xG46x_adc12_08.s43                   ADC12, Using 10 External Channels for Conversion
msp430xG46x_adc12_09.s43                   ADC12, Sequence of Conversions (non-repeated)
msp430xG46x_adc12_10.s43                   ADC12, Sample A10 Temp and Convert to oC and oF
msp430xG46x_bt_01.s43                      Basic Timer, Toggle P5.1 Inside ISR, 32kHz ACLK
msp430xG46x_clks_02.s43                    FLL+, Output 32kHz Xtal + HF Xtal + Internal DCO
msp430xG46x_compA_01.s43                   Comparator A, Poll input CA0, result in P5.1
msp430xG46x_compA_02.s43                   Comparator A, Poll input CA0, CA exchange, result in P5.1
msp430xG46x_compA_04.s43                   Comparator A, Poll input CA0, result in P5.1
msp430xG46x_compA_05.s43                   Comparator A, Poll input CA0, interrupt triggered
msp430xG46x_dac12_01.s43                   DAC12_0, Output 1.0V on DAC0
msp430xG46x_dac12_02.s43                   DAC12_1, Output 2.0V on DAC1
msp430xG46x_dac12_03.s43                   DAC12_0, Output Voltage Ramp on DAC0
msp430xG46x_dma_01.s43                     DMA0, Repeated Burst to-from RAM, Software Trigger
msp430xG46x_dma_02.s43                     DMA0, Repeated Block to P1OUT, TACCR2 Trigger
msp430xG46x_dma_04.s43                     DMA0, Block Mode UART1 9600, ACLK
msp430xG46x_dma_05.s43                     DMA0, Repeated Blk to DAC0, Sine Output, TACCR1, DCO
msp430xG46x_dma_06.s43                     DMA2, Rpt'd Blk to DAC1, 8-Bit Sine, TBCCR2, DCO
msp430xG46x_dma_07.s43                     DMA0/1, Rpt'd Blk to DAC12_0/1, Sin/Cos, TACCR1, XT2
msp430xG46x_dma_08.s43                     DDMA0, Rpt'd Block, I2C Master Intf. to DAC8571, DCO
msp430xG46x_dma_09.s43                     DMA0, ADC12 A10 Block Xfer to RAM, TBCCR1, DCO
msp430xG46x_fll_01.s43                     FLL+, Runs Internal DCO at 2.45MHz
msp430xG46x_fll_02.s43                     FLL+, Runs Internal DCO at 8MHz
msp430xG46x_hfxt2.s43                      FLL+, MCLK Configured to Operate from XT2 HF XTAL
msp430xG46x_lpm3.s43                       Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
msp430xG46x_MPY_01.s43                     16x16 Unsigned Multiply
msp430xG46x_MPY_02.s43                     8x8 Unsigned Multiply
msp430xG46x_MPY_03.s43                     16x16 Signed Multiply
msp430xG46x_MPY_04.s43                     8x8 Signed Multiply
msp430xG46x_MPY_05.s43                     16x16 Unsigned Multiply Accumulate
msp430xG46x_MPY_06.s43                     8x8 Unsigned Multiply Accumulate
msp430xG46x_MPY_07.s43                     16x16 Signed Multiply Accumulate
msp430xG46x_MPY_08.s43                     8x8 Signed Multiply Accumulate
msp430xG46x_oa_01.s43                      OA0, Comparator Mode
msp430xG46x_oa_02.s43                      OA0, Comparator in General-Purpose Mode
msp430xG46x_oa_03.s43                      OA0, General-Purpose Mode
msp430xG46x_oa_04.s43                      OA0, Inverting PGA Mode
msp430xG46x_oa_05.s43                      OA0, Non-Inverting PGA Mode
msp430xG46x_oa_06.s43                      OA0, Unity-Gain Buffer Mode
msp430xG46x_oa_07.s43                      OA1, Comparator Mode
msp430xG46x_oa_08.s43                      OA1, Comparator in General-Purpose Mode
msp430xG46x_oa_09.s43                      OA1, Inverting PGA Mode
msp430xG46x_oa_10.s43                      OA1, Non-Inverting PGA Mode
msp430xG46x_oa_11.s43                      OA1, Unity-Gain Buffer Mode
msp430xG46x_oa_12.s43                      3-Amp Differential Amplifier with OA0, OA1, and OA2
msp430xG46x_oa_13.s43                      3-Amp Differential Amplifier with OA1, OA2, and OA0
msp430xG46x_oa_14.s43                      3-Amp Differential Amplifier with OA2, OA0, and OA1
msp430xG46x_OF_LFXT1_nmi.s43               LFXT1 Oscillator Fault Detection
msp430xG46x_OF_XT2.s43                     XT2 Oscillator Fault Detection
msp430xG46x_P1_01.s43                      Software Poll P1.4, Set P5.1 if P1.4 = 1
msp430xG46x_P1_02.s43                      Software Port Interrupt on P1.4 from LPM4
msp430xG46x_P1_05.s43                      Write a byte to Port 1
msp430xG46x_P7_05.s43                      Write a byte to Port 7
msp430xG46x_P8_05.s43                      Write a byte to Port 8
msp430xG46x_PA_05.s43                      Write a word to Port A
msp430xG46x_PB_05.s43                      Write a word to Port B
msp430xG46x_rtc_01.s43                     Real Time Clock, Toggle P5.1 Inside ISR, 32kHz ACLK;and send Time via UART
msp430xG46x_rtc_02.s43                     Real Time Clock, Toggle P5.1 Inside ISR, 32kHz ACLK
msp430xG46x_ta_01.s43                      Timer_A, Toggle P5.1, TACCR0 Cont. Mode ISR, DCO SMCLK
msp430xG46x_ta_02.s43                      Timer_A, Toggle P5.1, TACCR0 Up Mode ISR, DCO SMCLK
msp430xG46x_ta_03.s43                      Timer_A, Toggle P5.1, Overflow ISR, DCO SMCLK
msp430xG46x_ta_04.s43                      Timer_A, Toggle P5.1, Overflow ISR, 32kHz ACLK
msp430xG46x_ta_05.s43                      Timer_A, Toggle P5.1, TACCR0 Up Mode ISR, 32kHz ACLK
msp430xG46x_ta_08.s43                      Timer_A, Toggle P1.0,P1.2 & P2.0 Cont. Mode ISR, 32kHz ACLK
msp430xG46x_ta_11.s43                      Timer_A, Toggle P1.0/TA0, Up Mode, 32kHz ACLK
msp430xG46x_ta_13.s43                      Timer_A, Toggle P1.0/TA0, Up/Down Mode, DCO SMCLK
msp430xG46x_ta_17.s43                      Timer_A, PWM TA1-2 Up Mode, 32kHz ACLK
msp430xG46x_ta_19.s43                      Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
msp430xG46x_tb_01.s43                      Timer_B, Toggle P5.1, TBCCR0 Cont. Mode ISR, DCO SMCLK
msp430xG46x_tb_02.s43                      Timer_B, Toggle P5.1, TBCCR0 Up Mode ISR, DCO SMCLK
msp430xG46x_tb_04.s43                      Timer_B, Toggle P5.1, Overflow ISR, 32kHz ACLK
msp430xG46x_tb_05.s43                      Timer_B, Toggle P5.1, TBCCR0 Up Mode ISR, 32kHz ACLK
msp430xG46x_tb_10.s43                      Timer_B, PWM TB1-6, Up Mode, DCO SMCLK
msp430xG46x_usart1_19200.s43               USART1, Ultra-Low Pwr UART 19200 Echo ISR, 32kHz ACLK
msp430xG46x_usart1_spi0_09.s43             USART1, SPI 3-Wire Master Incremented Data
msp430xG46x_usart1_spi0_10.s43             USART1, SPI 3-Wire Slave Data Echo
msp430xG46x_usart1_spi1_01.s43             USART1, SPI Interface to TLC549 8-Bit ADC
msp430xG46x_usart1_uart_115k.s43           USART1, 115200 UART Echo ISR, DCO SMCLK
msp430xG46x_usart1_uart_2400.s43           USART1, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
msp430xG46x_usart1_uart_9600.s43           USART1, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430xG46x_uscia0_duplex_9600.s43         USCI_A0, UART 9600 Full-Duplex Transceiver, 32K ACLK
msp430xG46x_uscia0_irda_01.s43             USCI_A0 IrDA External Loopback Test, 4MHz SMCLK
msp430xG46x_uscia0_irda_02.s43             USCI_A0 IrDA Monitor, 4MHz SMCLK
msp430xG46x_uscia0_irda_03.s43             USCI_A0 IrDA Physical Layer Comm, 4MHz SMCLK
msp430xG46x_uscia0_spi_09.s43              USCI_A0, SPI 3-Wire Master Incremented Data
msp430xG46x_uscia0_spi_10.s43              USCI_A0, SPI 3-Wire Slave Data Echo
msp430xG46x_uscia0_uart_115k.s43           USCI_A0, 115200 UART Echo ISR, DCO SMCLK
msp430xG46x_uscia0_uart_115k_lpm.s43       USCI_A0, 115200 UART Echo ISR, DCO SMCLK, LPM3
msp430xG46x_uscia0_uart_9600.s43           USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430xG46x_uscib0_i2c_02.s43              USCI_B0 I2C Master Interface to PCF8574, Read/Write
msp430xG46x_uscib0_i2c_03.s43              USCI_B0 I2C Master Interface to DAC8571, Write
msp430xG46x_uscib0_i2c_08.s43              USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
msp430xG46x_uscib0_i2c_09.s43              USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
msp430xG46x_uscib0_i2c_10.s43              USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
msp430xG46x_uscib0_i2c_11.s43              USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
msp430xG46x_uscib0_spi_01.s43              USCI_B0, SPI Interface to TLC549 8-Bit ADC


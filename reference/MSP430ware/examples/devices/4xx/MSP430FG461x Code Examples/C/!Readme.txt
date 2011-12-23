File Name                                     Description
----------------------------------------------------------------------------------------
msp430xG46x_1.c                               Software Toggle P1.0
msp430xG46x_adc12_01.c                        ADC12, Sample A0, Set P5.1 if A0 > 0.5*AVcc
msp430xG46x_adc12_02.c                        ADC12, Using the Internal Reference
msp430xG46x_adc12_03.c                        ADC12, Sample A10 Temp, Set P5.1 if Temp ++ ~2C
msp430xG46x_adc12_04.c                        ADC12, Extend Sampling Period with SHT Bits
msp430xG46x_adc12_05.c                        ADC12, Using an External Reference
msp430xG46x_adc12_06.c                        ADC12, Repeated Sequence of Conversions
msp430xG46x_adc12_07.c                        ADC12, Repeated Single Channel Conversions
msp430xG46x_adc12_08.c                        ADC12, Using 10 External Channels for Conversion
msp430xG46x_adc12_09.c                        ADC12, Sequence of Conversions (non-repeated)
msp430xG46x_adc12_10.c                        ADC12, Sample A10 Temp and Convert to oC and oF
msp430xG46x_bt_01.c                           Basic Timer, Toggle P5.1 Inside ISR, 32kHz ACLK
msp430xG46x_clks_02.c                         FLL+, Output 32kHz Xtal + HF Xtal + Internal DCO
msp430xG46x_compA_01.c                        Comparator A, Poll input CA0, result in P5.1
msp430xG46x_compA_02.c                        Comparator A, Poll input CA0, CA exchange, result in P5.1
msp430xG46x_compA_04.c                        Comparator A, Poll input CA0, result in P5.1
msp430xG46x_compA_05.c                        Comparator A, Poll input CA0, interrupt triggered
msp430xG46x_dac12_01.c                        DAC12_0, Output 1.0V on DAC0
msp430xG46x_dac12_02.c                        DAC12_1, Output 2.0V on DAC1
msp430xG46x_dac12_03.c                        DAC12_0, Output Voltage Ramp on DAC0
msp430xG46x_dma_01_CCE.c                      DMA0, Repeated Burst to-from RAM, Software Trigger
msp430xG46x_dma_01_IAR.c                      DMA0, Repeated Burst to-from RAM, Software Trigger
msp430xG46x_dma_02_CCE.c                      DMA0, Repeated Block to P1OUT, TACCR2 Trigger
msp430xG46x_dma_02_IAR.c                      DMA0, Repeated Block to P1OUT, TACCR2 Trigger
msp430xG46x_dma_04_CCE.c                      DMA0, Block Mode UART1 9600, ACLK
msp430xG46x_dma_04_IAR.c                      DMA0, Block Mode UART1 9600, ACLK
msp430xG46x_dma_05_CCE.c                      DMA0, Repeated Blk to DAC0, Sine Output, TACCR1, DCO
msp430xG46x_dma_05_IAR.c                      DMA0, Repeated Blk to DAC0, Sine Output, TACCR1, DCO
msp430xG46x_dma_06_CCE.c                      DMA2, Rpt'd Blk to DAC1, 8-Bit Sine, TBCCR2, DCO
msp430xG46x_dma_06_IAR.c                      DMA2, Rpt'd Blk to DAC1, 8-Bit Sine, TBCCR2, DCO
msp430xG46x_dma_07_CCE.c                      DMA0/1, Rpt'd Blk to DAC12_0/1, Sin/Cos, TACCR1, XT2
msp430xG46x_dma_07_IAR.c                      DMA0/1, Rpt'd Blk to DAC12_0/1, Sin/Cos, TACCR1, XT2
msp430xG46x_dma_08_CCE.c                      DDMA0, Rpt'd Block, I2C Master Intf. to DAC8571, DCO
msp430xG46x_dma_08_IAR.c                      DDMA0, Rpt'd Block, I2C Master Intf. to DAC8571, DCO
msp430xG46x_dma_09_CCE.c                      DMA0, ADC12 A10 Block Xfer to RAM, TBCCR1, DCO
msp430xG46x_dma_09_IAR.c                      DMA0, ADC12 A10 Block Xfer to RAM, TBCCR1, DCO
msp430xG46x_dma_10.c                          DMA0 triggers DMA1, DMA 1 triggers DMA2, DMA2 makes single transfer
msp430xG46x_fll_01.c                          FLL+, Runs Internal DCO at 2.45MHz
msp430xG46x_fll_02.c                          FLL+, Runs Internal DCO at 8MHz
msp430xG46x_hfxt2.c                           FLL+, MCLK Configured to Operate from XT2 HF XTAL
msp430xG46x_lpm3.c                            Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
msp430xG46x_MPY_01.c                          16x16 Unsigned Multiply
msp430xG46x_MPY_02.c                          8x8 Unsigned Multiply
msp430xG46x_MPY_03.c                          16x16 Signed Multiply
msp430xG46x_MPY_04.c                          8x8 Signed Multiply
msp430xG46x_MPY_05.c                          16x16 Unsigned Multiply Accumulate
msp430xG46x_MPY_06.c                          8x8 Unsigned Multiply Accumulate
msp430xG46x_MPY_07.c                          16x16 Signed Multiply Accumulate
msp430xG46x_MPY_08.c                          8x8 Signed Multiply Accumulate
msp430xG46x_oa_01.c                           OA0, Comparator Mode
msp430xG46x_oa_02.c                           OA0, Comparator in General-Purpose Mode
msp430xG46x_oa_03.c                           OA0, General-Purpose Mode
msp430xG46x_oa_04.c                           OA0, Inverting PGA Mode
msp430xG46x_oa_05.c                           OA0, Non-Inverting PGA Mode
msp430xG46x_oa_06.c                           OA0, Unity-Gain Buffer Mode
msp430xG46x_oa_07.c                           OA1, Comparator Mode
msp430xG46x_oa_08.c                           OA1, Comparator in General-Purpose Mode
msp430xG46x_oa_09.c                           OA1, Inverting PGA Mode
msp430xG46x_oa_10.c                           OA1, Non-Inverting PGA Mode
msp430xG46x_oa_11.c                           OA1, Unity-Gain Buffer Mode
msp430xG46x_oa_12.c                           3-Amp Differential Amplifier with OA0, OA1, and OA2
msp430xG46x_oa_13.c                           3-Amp Differential Amplifier with OA1, OA2, and OA0
msp430xG46x_oa_14.c                           3-Amp Differential Amplifier with OA2, OA0, and OA1
msp430xG46x_OF_LFXT1_nmi.c                    LFXT1 Oscillator Fault Detection
msp430xG46x_OF_XT2.c                          XT2 Oscillator Fault Detection
msp430xG46x_P1_01.c                           Software Poll P1.4, Set P5.1 if P1.4 = 1
msp430xG46x_P1_02.c                           Software Port Interrupt on P1.4 from LPM4
msp430xG46x_P1_05.c                           Write a byte to Port 1
msp430xG46x_P7_05.c                           Write a byte to Port 7
msp430xG46x_P8_05.c                           Write a byte to Port 8
msp430xG46x_PA_05.c                           Write a word to Port A
msp430xG46x_PB_05.c                           Write a word to Port B
msp430xG46x_rtc_01.c                          Real Time Clock, Toggle P5.1 Inside ISR, 32kHz ACLK;and send Time via UART
msp430xG46x_rtc_02.c                          Real Time Clock, Toggle P5.1 Inside ISR, 32kHz ACLK
msp430xG46x_ta_01.c                           Timer_A, Toggle P5.1, TACCR0 Cont. Mode ISR, DCO SMCLK
msp430xG46x_ta_02.c                           Timer_A, Toggle P5.1, TACCR0 Up Mode ISR, DCO SMCLK
msp430xG46x_ta_03.c                           Timer_A, Toggle P5.1, Overflow ISR, DCO SMCLK
msp430xG46x_ta_04.c                           Timer_A, Toggle P5.1, Overflow ISR, 32kHz ACLK
msp430xG46x_ta_05.c                           Timer_A, Toggle P5.1, TACCR0 Up Mode ISR, 32kHz ACLK
msp430xG46x_ta_08.c                           Timer_A, Toggle P1.0,P1.2 & P2.0 Cont. Mode ISR, 32kHz ACLK
msp430xG46x_ta_11.c                           Timer_A, Toggle P1.0/TA0, Up Mode, 32kHz ACLK
msp430xG46x_ta_13.c                           Timer_A, Toggle P1.0/TA0, Up/Down Mode, DCO SMCLK
msp430xG46x_ta_17.c                           Timer_A, PWM TA1-2 Up Mode, 32kHz ACLK
msp430xG46x_ta_19.c                           Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
msp430xG46x_tb_01.c                           Timer_B, Toggle P5.1, TBCCR0 Cont. Mode ISR, DCO SMCLK
msp430xG46x_tb_02.c                           Timer_B, Toggle P5.1, TBCCR0 Up Mode ISR, DCO SMCLK
msp430xG46x_tb_04.c                           Timer_B, Toggle P5.1, Overflow ISR, 32kHz ACLK
msp430xG46x_tb_05.c                           Timer_B, Toggle P5.1, TBCCR0 Up Mode ISR, 32kHz ACLK
msp430xG46x_tb_10.c                           Timer_B, PWM TB1-6, Up Mode, DCO SMCLK
msp430xG46x_usart1_19200.c                    USART1, Ultra-Low Pwr UART 19200 Echo ISR, 32kHz ACLK
msp430xG46x_usart1_spi0_09.c                  USART1, SPI 3-Wire Master Incremented Data
msp430xG46x_usart1_spi0_10.c                  USART1, SPI 3-Wire Slave Data Echo
msp430xG46x_usart1_spi1_01.c                  USART1, SPI Interface to TLC549 8-Bit ADC
msp430xG46x_usart1_uart_115k.c                USART1, 115200 UART Echo ISR, DCO SMCLK
msp430xG46x_usart1_uart_2400.c                USART1, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
msp430xG46x_usart1_uart_9600.c                USART1, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430xG46x_uscia0b0_uart_spi_01.c            USCI_A0 UART TX single byte and USCI_B0 SPI Master TX single byte to MSP430 Slave
msp430xG46x_uscia0b0_uart_spi_02.c            USCI_A0 UART RX single byte and USCI_B0 SPI Slave RX single byte from MSP430 Master
msp430xG46x_uscia0_duplex_9600.c              USCI_A0, UART 9600 Full-Duplex Transceiver, 32K ACLK
msp430xG46x_uscia0_irda_01.c                  USCI_A0 IrDA External Loopback Test, 4MHz SMCLK
msp430xG46x_uscia0_irda_02.c                  USCI_A0 IrDA Monitor, 4MHz SMCLK
msp430xG46x_uscia0_irda_03.c                  USCI_A0 IrDA Physical Layer Comm, 4MHz SMCLK
msp430xG46x_uscia0_spi_09.c                   USCI_A0, SPI 3-Wire Master Incremented Data
msp430xG46x_uscia0_spi_10.c                   USCI_A0, SPI 3-Wire Slave Data Echo
msp430xG46x_uscia0_uart_115k.c                USCI_A0, 115200 UART Echo ISR, DCO SMCLK
msp430xG46x_uscia0_uart_115k_lpm.c            USCI_A0, 115200 UART Echo ISR, DCO SMCLK, LPM3
msp430xG46x_uscia0_uart_9600.c                USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430xG46x_uscia0_uart_uscia0b0_i2c_1.c      USCI_A0 UART TX single byte and USCI_B0 I2C Master TX single byte to MSP430 Slave
msp430xG46x_uscia0_uart_uscia0b0_i2c_2.c      USCI_A0 UART RX single byte and USCI_B0 I2C Slave RX single byte from MSP430 Master
msp430xG46x_uscib0_i2c_02.c                   USCI_B0 I2C Master Interface to PCF8574, Read/Write
msp430xG46x_uscib0_i2c_03.c                   USCI_B0 I2C Master Interface to DAC8571, Write
msp430xG46x_uscib0_i2c_08.c                   USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
msp430xG46x_uscib0_i2c_09.c                   USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
msp430xG46x_uscib0_i2c_10.c                   USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
msp430xG46x_uscib0_i2c_11.c                   USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
msp430xG46x_uscib0_spi_01.c                   USCI_B0, SPI Interface to TLC549 8-Bit ADC


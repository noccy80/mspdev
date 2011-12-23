File Name                                    Description
----------------------------------------------------------------------------------------
msp430x24x_1.s43                             Software Toggle P1.0
msp430x24x_1_vlo.s43                         Software Toggle P1.0, MCLK = VLO/8
msp430x24x_adc12_01.s43                      ADC12, Sample A0, Set P1.0 if A0 > 0.5*AVcc
msp430x24x_adc12_02.s43                      ADC12, Using the Internal Reference
msp430x24x_adc12_03.s43                      ADC12, Sample A10 Temp, Set P1.0 if Temp ++ ~2C
msp430x24x_adc12_04.s43                      ADC12, Extend Sampling Period with SHT Bits
msp430x24x_adc12_05.s43                      ADC12, Using an External Reference
msp430x24x_adc12_06.s43                      ADC12, Repeated Sequence of Conversions
msp430x24x_adc12_07.s43                      ADC12, Repeated Single Channel Conversions
msp430x24x_adc12_08.s43                      ADC12, Using 10 External Channels for Conversion
msp430x24x_adc12_09.s43                      ADC12, Sequence of Conversions (non-repeated)
msp430x24x_adc12_10.s43                      ADC12, Sample A10 Temp and Convert to oC and oF
msp430x24x_clks.s43                          Basic Clock, Output Buffered SMCLK, ACLK, and MCLK
msp430x24x_compA_01.s43                      Comparator A, Poll input CA0, result in P1.0
msp430x24x_compA_02.s43                      Comparator A, Poll input CA0, CA exchange, result in P1.0
msp430x24x_compA_04.s43                      Comparator A, Poll input CA0, result in P1.0
msp430x24x_compA_05.s43                      Comparator A, Poll input CA0, interrupt triggered
msp430x24x_dco_flashcal.s43                  DCO Calibration Constants Programmer
msp430x24x_flashwrite_01.s43                 Flash In-System Programming, Copy SegC to SegD
msp430x24x_flashwrite_02.s43                 Flash In-System Programming w/ EEI, Copy SegC to SegD
msp430x24x_flashwrite_03.s43                 Flash In-System Programming w/ EEI, Copy SegD to B&C
msp430x24x_fll_01.s43                        Basic Clock, Implement Auto RSEL SW FLL
msp430x24x_fll_02.s43                        Basic Clock, Implement Cont. SW FLL with Auto RSEL
msp430x24x_hfxt2.s43                         Basic Clock, MCLK Configured to Operate from XT2 HF XTAL
msp430x24x_hfxt2_nmi.s43                     Basic Clock, MCLK Sourced from HF XTAL XT2, NMI
msp430x24x_lpm3.s43                          Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
msp430x24x_lpm3_vlo.s43                      Basic Clock, LPM3 Using WDT ISR, VLO ACLK
msp430x24x_MPY_01.s43                        16x16 Unsigned Multiply
msp430x24x_MPY_02.s43                        8x8 Unsigned Multiply
msp430x24x_MPY_03.s43                        16x16 Signed Multiply
msp430x24x_MPY_04.s43                        8x8 Signed Multiply
msp430x24x_MPY_05.s43                        16x16 Unsigned Multiply Accumulate
msp430x24x_MPY_06.s43                        8x8 Unsigned Multiply Accumulate
msp430x24x_MPY_07.s43                        16x16 Signed Multiply Accumulate
msp430x24x_MPY_08.s43                        8x8 Signed Multiply Accumulate
msp430x24x_nmi.s43                           Configure RST/NMI as NMI
msp430x24x_OF_LFXT1_nmi.s43                  LFXT1 Oscillator Fault Detection
msp430x24x_OF_XT2.s43                        XT2 Oscillator Fault Detection
msp430x24x_P1_01.s43                         Software Poll P1.3, Set P1.0 if P1.3 = 1
msp430x24x_P1_02.s43                         Software Port Interrupt Service on P1.3 from LPM4
msp430x24x_P1_05.s43                         Write a byte to Port 1
msp430x24x_rosc.s43                          DCOCLK Biased with External Resistor Rosc
msp430x24x_svs_01.s43                        SVS, POR @ 2.5V Vcc
msp430x24x_ta_01.s43                         Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
msp430x24x_ta_02.s43                         Timer_A, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
msp430x24x_ta_03.s43                         Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x24x_ta_04.s43                         Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x24x_ta_05.s43                         Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
msp430x24x_ta_11.s43                         Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
msp430x24x_ta_13.s43                         Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
msp430x24x_ta_17.s43                         Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
msp430x24x_ta_19.s43                         Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
msp430x24x_ta_20.s43                         Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
msp430x24x_ta_24.s43                         Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz INCLK
msp430x24x_tb_01.s43                         Timer_B, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
msp430x24x_tb_02.s43                         Timer_B, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
msp430x24x_tb_03.s43                         Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x24x_tb_04.s43                         Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x24x_tb_05.s43                         Timer_B, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
msp430x24x_tb_06.s43                         Timer_B, PWM TB1-6, Up Mode, DCO SMCLK
msp430x24x_tb_07.s43                         Timer_B, PWM TB1-6, Up Mode, 32kHz ACLK
msp430x24x_tb_09.s43                         Timer_B, PWM TB1-2, Up/Down Mode, DCO SMCLK
msp430x24x_tb_10.s43                         Timer_B, PWM TB1-2, Up/Down Mode, 32kHz ACLK
msp430x24x_uscia0_irda_01.s43                USCI_A0 IrDA External Loopback Test, 8MHz SMCLK
msp430x24x_uscia0_irda_02.s43                USCI_A0 IrDA Monitor, 8MHz SMCLK
msp430x24x_uscia0_irda_03.s43                USCI_A0 IrDA Physical Layer Comm, 8MHz SMCLK
msp430x24x_uscia0_spi_01.s43                 USCI_A0, SPI Interface to HC164 Shift Register
msp430x24x_uscia0_spi_02.s43                 USCI_A0, SPI Interface to HC165 Shift Register
msp430x24x_uscia0_spi_03.s43                 USCI_A0, SPI Interface to HC165/164 Shift Registers
msp430x24x_uscia0_spi_09.s43                 USCI_A0, SPI 3-Wire Master Incremented Data
msp430x24x_uscia0_spi_10.s43                 USCI_A0, SPI 3-Wire Slave Data Echo
msp430x24x_uscia0_uart_01_115k.s43           USCI_A0, 115200 UART Echo ISR, DCO SMCLK
msp430x24x_uscia0_uart_01_115k_lpm4.s43      USCI_A0, 115200 UART Echo ISR, DCO SMCLK, LPM4
msp430x24x_uscia0_uart_01_19200.s43          USCI_A0, 19200 UART Echo ISR, DCO SMCLK
msp430x24x_uscia0_uart_01_9600.s43           USCI_A0, 9600 UART Echo ISR, DCO SMCLK
msp430x24x_uscia0_uart_04_9600.s43           USCI_A0, 9600 UART, SMCLK, LPM0, Echo with over-sampling
msp430x24x_uscia0_uart_05_9600.s43           USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430x24x_uscia0_uart_06_9600.s43           USCI_A0, Ultra-Low Pwr UART 9600 String, 32kHz ACLK
msp430x24x_uscia0_uart_07_9600.s43           USCI_A0, Ultra-Low Pwr UART 9600 RX/TX, 32kHz ACLK
msp430x24x_uscia0_uart_08_9600.s43           USCI_A0, UART 9600 Full-Duplex Transceiver, 32kHz ACLK
msp430x24x_uscia1_irda_01.s43                USCI_A1 IrDA External Loopback Test, 8MHz SMCLK
msp430x24x_uscia1_spi_09.s43                 USCI_A1, SPI 3-Wire Master Incremented Data
msp430x24x_uscia1_spi_10.s43                 USCI_A1, SPI 3-Wire Slave Data Echo
msp430x24x_uscia1_uart_05_9600.s43           USCI_A1, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430x24x_uscib0_i2c_01.s43                 USCI_B0 I2C Master to TMP100, Set P1.0 if Temp > 28C
msp430x24x_uscib0_i2c_02.s43                 USCI_B0 I2C Master Interface to PCF8574, Read/Write
msp430x24x_uscib0_i2c_04.s43                 USCI_B0 I2C Master RX single bytes from MSP430 Slave
msp430x24x_uscib0_i2c_05.s43                 USCI_B0 I2C Slave TX single bytes to MSP430 Master
msp430x24x_uscib0_i2c_06.s43                 USCI_B0 I2C Master TX single bytes to MSP430 Slave
msp430x24x_uscib0_i2c_07.s43                 USCI_B0 I2C Slave RX single bytes from MSP430 Master
msp430x24x_uscib0_i2c_08.s43                 USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
msp430x24x_uscib0_i2c_09.s43                 USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
msp430x24x_uscib0_i2c_10.s43                 USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
msp430x24x_uscib0_i2c_11.s43                 USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
msp430x24x_uscib0_spi_01.s43                 USCI_B0, SPI Interface to TLC549 8-Bit ADC
msp430x24x_uscib0_spi_02.s43                 USCI_B0, SPI Interface to TLV1549 10-Bit ADC
msp430x24x_uscib0_spi_09.s43                 USCI_B0, SPI 3-Wire Master Incremented Data
msp430x24x_uscib0_spi_10.s43                 USCI_B0, SPI 3-Wire Slave Data Echo
msp430x24x_uscib1_i2c_06.s43                 USCI_B1 I2C Master TX single bytes to MSP430 Slave
msp430x24x_uscib1_i2c_07.s43                 USCI_B1 I2C Slave RX single bytes from MSP430 Master
msp430x24x_uscib1_spi_09.s43                 USCI_B1, SPI 3-Wire Master Incremented Data
msp430x24x_uscib1_spi_10.s43                 USCI_B1, SPI 3-Wire Slave Data Echo
msp430x24x_wdt_01.s43                        WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
msp430x24x_wdt_02.s43                        WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
msp430x24x_wdt_04.s43                        WDT+ Failsafe Clock, WDT mode, DCO SMCLK
msp430x24x_wdt_05.s43                        Reset on Invalid Address fetch, Toggle P1.0
msp430x24x_wdt_06.s43                        WDT+ Failsafe Clock, 32kHz ACLK


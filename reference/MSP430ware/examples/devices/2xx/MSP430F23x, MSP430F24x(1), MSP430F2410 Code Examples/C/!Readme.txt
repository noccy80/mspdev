File Name                                 Description
----------------------------------------------------------------------------------------
msp430x24x_1.c                            Software Toggle P1.0
msp430x24x_1_vlo.c                        Software Toggle P1.0, MCLK = VLO/8
msp430x24x_adc12_01.c                     ADC12, Sample A0, Set P1.0 if A0 > 0.5*AVcc
msp430x24x_adc12_02.c                     ADC12, Using the Internal Reference
msp430x24x_adc12_03.c                     ADC12, Sample A10 Temp, Set P1.0 if Temp ++ ~2C
msp430x24x_adc12_04.c                     ADC12, Extend Sampling Period with SHT Bits
msp430x24x_adc12_05.c                     ADC12, Using an External Reference
msp430x24x_adc12_06.c                     ADC12, Repeated Sequence of Conversions
msp430x24x_adc12_07.c                     ADC12, Repeated Single Channel Conversions
msp430x24x_adc12_08.c                     ADC12, Using 10 External Channels for Conversion
msp430x24x_adc12_09.c                     ADC12, Sequence of Conversions (non-repeated)
msp430x24x_adc12_10.c                     ADC12, Sample A10 Temp and Convert to oC and oF
msp430x24x_clks.c                         Basic Clock, Output Buffered SMCLK, ACLK, and MCLK
msp430x24x_compA_01.c                     Comparator A, Poll input CA0, result in P1.0
msp430x24x_compA_02.c                     Comparator A, Poll input CA0, CA exchange, result in P1.0
msp430x24x_compA_04.c                     Comparator A, Poll input CA0, result in P1.0
msp430x24x_compA_05.c                     Comparator A, Poll input CA0, interrupt triggered
msp430x24x_dco_flashcal.c                 DCO Calibration Constants Programmer
msp430x24x_flashwrite_01.c                Flash In-System Programming, Copy SegC to SegD
msp430x24x_flashwrite_02.c                Flash In-System Programming w/ EEI, Copy SegC to SegD
msp430x24x_flashwrite_03.c                Flash In-System Programming w/ EEI, Copy SegD to A/B/C
msp430x24x_fll_01.c                       Basic Clock, Implement Auto RSEL SW FLL
msp430x24x_fll_02.c                       Basic Clock, Implement Cont. SW FLL with Auto RSEL
msp430x24x_hfxt2.c                        Basic Clock, MCLK Configured to Operate from XT2 HF XTAL
msp430x24x_hfxt2_nmi.c                    Basic Clock, MCLK Sourced from HF XTAL XT2, NMI
msp430x24x_lpm3.c                         Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
msp430x24x_lpm3_vlo.c                     Basic Clock, LPM3 Using WDT ISR, VLO ACLK
msp430x24x_MPY_01.c                       16x16 Unsigned Multiply
msp430x24x_MPY_02.c                       8x8 Unsigned Multiply
msp430x24x_MPY_03.c                       16x16 Signed Multiply
msp430x24x_MPY_04.c                       8x8 Signed Multiply
msp430x24x_MPY_05.c                       16x16 Unsigned Multiply Accumulate
msp430x24x_MPY_06.c                       8x8 Unsigned Multiply Accumulate
msp430x24x_MPY_07.c                       16x16 Signed Multiply Accumulate
msp430x24x_MPY_08.c                       8x8 Signed Multiply Accumulate
msp430x24x_nmi.c                          Configure RST/NMI as NMI
msp430x24x_OF_LFXT1.c                     LFXT1 Oscillator Fault Detection
msp430x24x_OF_XT2.c                       XT2 Oscillator Fault Detection
msp430x24x_P1_01.c                        Software Poll P1.3, Set P1.0 if P1.3 = 1
msp430x24x_P1_02.c                        Software Port Interrupt Service on P1.3 from LPM4
msp430x24x_P1_05.c                        Write a byte to Port 1
msp430x24x_rosc.c                         DCOCLK Biased with External Resistor Rosc
msp430x24x_svs_01.c                       SVS, POR @ 2.5V Vcc
msp430x24x_ta_01.c                        Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
msp430x24x_ta_02.c                        Timer_A, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
msp430x24x_ta_03.c                        Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x24x_ta_04.c                        Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x24x_ta_05.c                        Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
msp430x24x_ta_11.c                        Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
msp430x24x_ta_13.c                        Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
msp430x24x_ta_17.c                        Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
msp430x24x_ta_19.c                        Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
msp430x24x_ta_20.c                        Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
msp430x24x_ta_24.c                        Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz INCLK
msp430x24x_tb_01.c                        Timer_B, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
msp430x24x_tb_02.c                        Timer_B, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
msp430x24x_tb_03.c                        Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x24x_tb_04.c                        Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x24x_tb_05.c                        Timer_B, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
msp430x24x_tb_06.c                        Timer_B, PWM TB1-6, Up Mode, DCO SMCLK
msp430x24x_tb_07.c                        Timer_B, PWM TB1-6, Up Mode, 32kHz ACLK
msp430x24x_tb_09.c                        Timer_B, PWM TB1-2, Up/Down Mode, DCO SMCLK
msp430x24x_tb_10.c                        Timer_B, PWM TB1-2, Up/Down Mode, 32kHz ACLK
msp430x24x_uscia0_irda_01.c               USCI_A0 IrDA External Loopback Test, 8MHz SMCLK
msp430x24x_uscia0_irda_02.c               USCI_A0 IrDA Monitor, 8MHz SMCLK
msp430x24x_uscia0_irda_03.c               USCI_A0 IrDA Physical Layer Comm, 8MHz SMCLK
msp430x24x_uscia0_spi_01.c                USCI_A0, SPI Interface to HC164 Shift Register
msp430x24x_uscia0_spi_02.c                USCI_A0, SPI Interface to HC165 Shift Register
msp430x24x_uscia0_spi_03.c                USCI_A0, SPI Interface to HC165/164 Shift Registers
msp430x24x_uscia0_spi_09.c                USCI_A0, SPI 3-Wire Master Incremented Data
msp430x24x_uscia0_spi_10.c                USCI_A0, SPI 3-Wire Slave Data Echo
msp430x24x_uscia0_uart_01_115k.c          USCI_A0, 115200 UART Echo ISR, DCO SMCLK
msp430x24x_uscia0_uart_01_115k_lpm.c      USCI_A0, 115200 UART Echo ISR, DCO SMCLK, LPM4
msp430x24x_uscia0_uart_01_19200.c         USCI_A0, 19200 UART Echo ISR, DCO SMCLK
msp430x24x_uscia0_uart_01_9600.c          USCI_A0, 9600 UART Echo ISR, DCO SMCLK
msp430x24x_uscia0_uart_04_9600.c          USCI_A0, 9600 UART, SMCLK, LPM0, Echo with over-sampling
msp430x24x_uscia0_uart_05_9600.c          USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430x24x_uscia0_uart_06_9600.c          USCI_A0, Ultra-Low Pwr UART 9600 String, 32kHz ACLK
msp430x24x_uscia0_uart_07_9600.c          USCI_A0, Ultra-Low Pwr UART 9600 RX/TX, 32kHz ACLK
msp430x24x_uscia0_uart_08_9600.c          USCI_A0, UART 9600 Full-Duplex Transceiver, 32kHz ACLK
msp430x24x_uscia1_irda_01.c               USCI_A1 IrDA External Loopback Test, 8MHz SMCLK
msp430x24x_uscia1_spi_09.c                USCI_A1, SPI 3-Wire Master Incremented Data
msp430x24x_uscia1_spi_10.c                USCI_A1, SPI 3-Wire Slave Data Echo
msp430x24x_uscia1_uart_05_9600.c          USCI_A1, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430x24x_uscib0_i2c_01.c                USCI_B0 I2C Master to TMP100, Set P1.0 if Temp > 28C
msp430x24x_uscib0_i2c_02.c                USCI_B0 I2C Master Interface to PCF8574, Read/Write
msp430x24x_uscib0_i2c_04.c                USCI_B0 I2C Master RX single bytes from MSP430 Slave
msp430x24x_uscib0_i2c_05.c                USCI_B0 I2C Slave TX single bytes to MSP430 Master
msp430x24x_uscib0_i2c_06.c                USCI_B0 I2C Master TX single bytes to MSP430 Slave
msp430x24x_uscib0_i2c_07.c                USCI_B0 I2C Slave RX single bytes from MSP430 Master
msp430x24x_uscib0_i2c_08.c                USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
msp430x24x_uscib0_i2c_09.c                USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
msp430x24x_uscib0_i2c_10.c                USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
msp430x24x_uscib0_i2c_11.c                USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
msp430x24x_uscib0_i2c_15.c                USCI_B0 I2C Slave RX multiple bytes from MSP430 Master & USCI_A1 SPI Slave RX single bytes simultaneously.
msp430x24x_uscib0_spi_01.c                USCI_B0, SPI Interface to TLC549 8-Bit ADC
msp430x24x_uscib0_spi_02.c                USCI_B0, SPI Interface to TLV1549 10-Bit ADC
msp430x24x_uscib0_spi_09.c                USCI_B0, SPI 3-Wire Master Incremented Data
msp430x24x_uscib0_spi_10.c                USCI_B0, SPI 3-Wire Slave Data Echo
msp430x24x_uscib1_i2c_06.c                USCI_B1 I2C Master TX single bytes to MSP430 Slave
msp430x24x_uscib1_i2c_07.c                USCI_B1 I2C Slave RX single bytes from MSP430 Master
msp430x24x_uscib1_spi_09.c                USCI_B1, SPI 3-Wire Master Incremented Data
msp430x24x_uscib1_spi_10.c                USCI_B1, SPI 3-Wire Slave Data Echo
msp430x24x_wdt_01.c                       WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
msp430x24x_wdt_02.c                       WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
msp430x24x_wdt_04.c                       WDT+ Failsafe Clock, WDT mode, DCO SMCLK
msp430x24x_wdt_05.c                       Reset on Invalid Address fetch, Toggle P1.0
msp430x24x_wdt_06.c                       WDT+ Failsafe Clock, 32kHz ACLK


File Name                                    Description
----------------------------------------------------------------------------------------
msp430x23x0_1.asm                            Software Toggle P1.0
msp430x23x0_1_vlo.asm                        Software Toggle P1.0, MCLK = VLO/8
msp430x23x0_ca_01.asm                        Comp_A+, Output Reference Voltages on P2.4
msp430x23x0_ca_02.asm                        Comp_A+, Detect Threshold, Set P1.0 if P2.4 > 0.25*Vcc
msp430x23x0_ca_03.asm                        Comp_A+, Simple 2.2V Low Battery Detect
msp430x23x0_clks.asm                         Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
msp430x23x0_dco_flashcal.asm                 DCO Calibration Constants Programmer
msp430x23x0_flashwrite_01.asm                Flash In-System Programming, Copy SegC to SegD
msp430x23x0_flashwrite_03.asm                Flash In-System Programming w/ EEI, Copy SegC to SegD
msp430x23x0_flashwrite_04.asm                Flash In-System Programming w/ EEI, Copy SegD to A/B/C
msp430x23x0_fll_01.asm                       Basic Clock, Implement Auto RSEL SW FLL
msp430x23x0_fll_02.asm                       Basic Clock, Implement Cont. SW FLL with Auto RSEL
msp430x23x0_hfxtal.asm                       Basic Clock, MCLK Sourced from HF XTAL
msp430x23x0_hfxtal_nmi.asm                   Basic Clock, LFXT1/MCLK Sourced from HF XTAL, NMI
msp430x23x0_lpm3.asm                         Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
msp430x23x0_lpm3_vlo.asm                     Basic Clock, LPM3 Using WDT ISR, VLO ACLK
msp430x23x0_nmi.asm                          Basic Clock, Configure RST/NMI as NMI
msp430x23x0_p1_01.asm                        Software Poll P1.3, Set P1.0 if P1.3 = 1
msp430x23x0_p1_02.asm                        Software Port Interrupt Service on P1.3 from LPM4
msp430x23x0_p1_03.asm                        Poll P1 With Software with Internal Pull-up
msp430x23x0_p1_04.asm                        P1 Interrupt from LPM4 with Internal Pull-up
msp430x23x0_rosc.asm                         DCOCLK Biased with External Resistor Rosc
msp430x23x0_ta_01.asm                        Timer_A, Toggle P1.0, TACCR0 Cont. Mode ISR, DCO SMCLK
msp430x23x0_ta_02.asm                        Timer_A, Toggle P1.0, TACCR0 Up Mode ISR, DCO SMCLK
msp430x23x0_ta_03.asm                        Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x23x0_ta_04.asm                        Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x23x0_ta_05.asm                        Timer_A, Toggle P1.0, TACCR0 Up Mode ISR, 32kHz ACLK
msp430x23x0_ta_06.asm                        Timer_A, Toggle P1.0, TACCR1 Cont. Mode ISR, DCO SMCLK
msp430x23x0_ta_07.asm                        Timer_A, Toggle P1.0-3, Cont. Mode ISR, DCO SMCLK
msp430x23x0_ta_08.asm                        Timer_A, Toggle P1.0-3, Cont. Mode ISR, 32kHz ACLK
msp430x23x0_ta_09.asm                        Timer_A, Toggle P1.0-3, Cont. Mode ISR, HF XTAL ACLK
msp430x23x0_ta_10.asm                        Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK
msp430x23x0_ta_11.asm                        Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
msp430x23x0_ta_12.asm                        Timer_A, Toggle P1.1/TA0, Up Mode, HF XTAL ACLK
msp430x23x0_ta_13.asm                        Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
msp430x23x0_ta_14.asm                        Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK
msp430x23x0_ta_15.asm                        Timer_A, Toggle P1.1/TA0, Up/Down Mode, HF XTAL ACLK
msp430x23x0_ta_16.asm                        Timer_A, PWM TA1-2, Up Mode, DCO SMCLK
msp430x23x0_ta_17.asm                        Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
msp430x23x0_ta_18.asm                        Timer_A, PWM TA1-2, Up Mode, HF XTAL ACLK
msp430x23x0_ta_19.asm                        Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
msp430x23x0_ta_20.asm                        Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
msp430x23x0_ta_21.asm                        Timer_A, PWM TA1-2, Up/Down Mode, HF XTAL ACLK
msp430x23x0_ta_22.asm                        Timer_A, Ultra-Low Pwr Pulse Accumulator
msp430x23x0_tb_01.asm                        Timer_B, Toggle P1.0, TBCCR0 Cont. Mode ISR, DCO SMCLK
msp430x23x0_tb_02.asm                        Timer_B, Toggle P1.0, TBCCR0 Up Mode ISR, DCO SMCLK
msp430x23x0_tb_03.asm                        Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x23x0_tb_04.asm                        Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x23x0_tb_05.asm                        Timer_B, Toggle P1.0, TBCCR0 Up Mode ISR, 32kHz ACLK
msp430x23x0_tb_06.asm                        Timer_B, Toggle P1.0, TBCCR1 Cont. Mode ISR, DCO SMCLK
msp430x23x0_tb_07.asm                        Timer_B, Toggle P4.0-2, Cont. Mode ISR, DCO SMCLK
msp430x23x0_tb_08.asm                        Timer_B, Toggle P4.0-2, Cont. Mode ISR, 32kHz ACLK
msp430x23x0_tb_09.asm                        Timer_B, Toggle P4.0-2, Cont. Mode ISR, HF XTAL ACLK
msp430x23x0_tb_10.asm                        Timer_B, PWM TB1-2, Up Mode, DCO SMCLK
msp430x23x0_tb_11.asm                        Timer_B, PWM TB1-2, Up Mode, 32kHz ACLK
msp430x23x0_tb_12.asm                        Timer_B, PWM TB1-2, Up Mode, HF XTAL ACLK
msp430x23x0_tb_13.asm                        Timer_B, PWM TB1-2, Up/Down Mode, DCO SMCLK
msp430x23x0_tb_14.asm                        Timer_B, PWM TB1-2, Up/Down Mode, 32kHz ACLK
msp430x23x0_tb_15.asm                        Timer_B, PWM TB1-2, Up/Down Mode, HF XTAL ACLK
msp430x23x0_uscia0_irda_01.asm               USCI_A0 IrDA External Loopback Test, 8MHz SMCLK
msp430x23x0_uscia0_irda_02.asm               USCI_A0 IrDA Monitor, 8MHz SMCLK
msp430x23x0_uscia0_irda_03.asm               USCI_A0 IrDA Physical Layer Comm, 8MHz SMCLK
msp430x23x0_uscia0_spi_01.asm                USCI_A0, SPI Interface to HC164 Shift Register
msp430x23x0_uscia0_spi_02.asm                USCI_A0, SPI Interface to HC165 Shift Register
msp430x23x0_uscia0_spi_03.asm                USCI_A0, SPI Interface to HC165/164 Shift Registers
msp430x23x0_uscia0_spi_09.asm                USCI_A0, SPI 3-Wire Master Incremented Data
msp430x23x0_uscia0_spi_10.asm                USCI_A0, SPI 3-Wire Slave Data Echo
msp430x23x0_uscia0_uart_01_115k.asm          USCI_A0, 115200 UART Echo ISR, DCO SMCLK
msp430x23x0_uscia0_uart_01_115k_lpm.asm      USCI_A0, 115200 UART Echo ISR, DCO SMCLK, LPM4
msp430x23x0_uscia0_uart_01_19200.asm         USCI_A0, 19200 UART Echo ISR, DCO SMCLK
msp430x23x0_uscia0_uart_01_19200_2.asm       USCI_A0, UART 19200 Echo ISR, XT2 HF XTAL SMCLK
msp430x23x0_uscia0_uart_01_9600.asm          USCI_A0, 9600 UART Echo ISR, DCO SMCLK
msp430x23x0_uscia0_uart_05_9600.asm          USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430x23x0_uscia0_uart_06_9600.asm          USCI_A0, Ultra-Low Pwr UART 9600 String, 32kHz ACLK
msp430x23x0_uscia0_uart_07_9600.asm          USCI_A0, Ultra-Low Pwr UART 9600 RX/TX, 32kHz ACLK
msp430x23x0_uscia0_uart_08_9600.asm          USCI_A0, UART 9600 Full-Duplex Transceiver, 32kHz ACLK
msp430x23x0_uscib0_i2c_01.asm                USCI_B0 I2C Master to TMP100, Set P5.1 if Temp > 28C
msp430x23x0_uscib0_i2c_02.asm                USCI_B0 I2C Master Interface to PCF8574, Read/Write
msp430x23x0_uscib0_i2c_03.asm                USCI_B0 I2C Master Interface to DAC8571, Write
msp430x23x0_uscib0_i2c_04.asm                USCI_B0 I2C Master RX single bytes from MSP430 Slave
msp430x23x0_uscib0_i2c_05.asm                USCI_B0 I2C Slave TX single bytes to MSP430 Master
msp430x23x0_uscib0_i2c_06.asm                USCI_B0 I2C Master TX single bytes to MSP430 Slave
msp430x23x0_uscib0_i2c_07.asm                USCI_B0 I2C Slave RX single bytes from MSP430 Master
msp430x23x0_uscib0_i2c_08.asm                USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
msp430x23x0_uscib0_i2c_09.asm                USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
msp430x23x0_uscib0_i2c_10.asm                USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
msp430x23x0_uscib0_i2c_11.asm                USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
msp430x23x0_uscib0_spi_01.asm                USCI_B0, SPI Interface to TLC549 8-Bit ADC
msp430x23x0_uscib0_spi_02.asm                USCI_B0, SPI Interface to TLV1549 10-Bit ADC
msp430x23x0_wdt_01.asm                       WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
msp430x23x0_wdt_02.asm                       WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
msp430x23x0_wdt_04.asm                       WDT+ Failsafe Clock, DCO SMCLK
msp430x23x0_wdt_05.asm                       Reset on Invalid Address fetch, Toggle P1.0
msp430x23x0_wdt_06.asm                       WDT+ Failsafe Clock, 32kHz ACLK


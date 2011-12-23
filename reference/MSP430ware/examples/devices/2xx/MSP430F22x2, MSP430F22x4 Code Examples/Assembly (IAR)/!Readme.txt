File Name                                    Description
----------------------------------------------------------------------------------------
msp430x22x4_1.s43                            Software Toggle P1.0
msp430x22x4_1_vlo.s43                        Software Toggle P1.0, MCLK = VLO/8
msp430x22x4_adc10_01.s43                     ADC10, Sample A0, AVcc Ref, Set P1.0 if A0 > 0.5*AVcc
msp430x22x4_adc10_02.s43                     ADC10, Sample A0, 1.5V Ref, Set P1.0 if A0 > 0.2V
msp430x22x4_adc10_03.s43                     ADC10, Sample A10 Temp, Set P1.0 if Temp ++ ~2C
msp430x22x4_adc10_04.s43                     ADC10, Sample A0, Signed, Set P1.0 if A0 > 0.5*AVcc
msp430x22x4_adc10_05.s43                     ADC10, Sample A11, Lo_Batt, Set P1.0 if AVcc < 2.3V
msp430x22x4_adc10_06.s43                     ADC10, Output Internal Vref on P2.4 & ADCCLK on P1.0
msp430x22x4_adc10_07.s43                     ADC10, DTC Sample A0 64x, AVcc, Repeat Single, DCO
msp430x22x4_adc10_08.s43                     ADC10, DTC Sample A0 64x, 1.5V, Repeat Single, DCO
msp430x22x4_adc10_09.s43                     ADC10, DTC Sample A10 64x, 1.5V, Repeat Single, DCO
msp430x22x4_adc10_10.s43                     ADC10, DTC Sample A2-0, AVcc, Single Sequence, DCO
msp430x22x4_adc10_11.s43                     ADC10, Sample A0, 1.5V, TA1 Trig, Set P1.0 if > 0.5V
msp430x22x4_adc10_12.s43                     ADC10, Sample A7, 1.5V, TA1 Trig, Ultra-Low Pwr
msp430x22x4_adc10_13.s43                     ADC10, DTC Sample A1 32x, AVcc, TA0 Trig, DCO
msp430x22x4_adc10_14.s43                     ADC10, DTC Sample A1-0 32x, AVcc, Repeat Seq, DCO
msp430x22x4_adc10_15.s43                     ADC10, DTC Sample A10 32x to Flash, Int Ref, DCO
msp430x22x4_adc10_16.s43                     ADC10, DTC Sample A0 -> TA1, AVcc, DCO
msp430x22x4_adc10_17.s43                     ADC10, DTC Sample A0 -> TA1, AVcc, HF XTAL
msp430x22x4_adc10_18.s43                     ADC10, DTC Sample A1/0 -> TA1/2, 2.5V, HF XTAL
msp430x22x4_adc10_19.s43                     ADC10, DTC Sample A0 64x, AVcc, HF XTAL
msp430x22x4_adc10_20.s43                     ADC10, DTC Sample A0 2-Blk Cont. Mode, AVcc, HF XTAL
msp430x22x4_adc10_temp.s43                   ADC10, Sample A10 Temp and Convert to oC and oF
msp430x22x4_clks.s43                         Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
msp430x22x4_dco_flashcal.s43                 DCO Calibration Constants Programmer
msp430x22x4_flashwrite_01.s43                Flash In-System Programming, Copy SegC to SegD
msp430x22x4_flashwrite_03.s43                Flash In-System Programming w/ EEI, Copy SegC to SegD
msp430x22x4_flashwrite_04.s43                Flash In-System Programming w/ EEI, Copy SegD to A/B/C
msp430x22x4_fll_01.s43                       Basic Clock, Implement Auto RSEL SW FLL
msp430x22x4_fll_02.s43                       Basic Clock, Implement Cont. SW FLL with Auto RSEL
msp430x22x4_hfxtal.s43                       Basic Clock, MCLK Sourced from HF XTAL
msp430x22x4_hfxtal_nmi.s43                   Basic Clock, LFXT1/MCLK Sourced from HF XTAL, NMI
msp430x22x4_lpm3.s43                         Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
msp430x22x4_lpm3_vlo.s43                     Basic Clock, LPM3 Using WDT ISR, VLO ACLK
msp430x22x4_nmi.s43                          Configure RST/NMI as NMI
msp430x22x4_oa_01.s43                        OA0, Comparator Mode
msp430x22x4_oa_02.s43                        OA0, General-Purpose Mode
msp430x22x4_oa_03.s43                        OA0, Inverting PGA Mode
msp430x22x4_oa_04.s43                        OA0, Non-Inverting PGA Mode
msp430x22x4_oa_05.s43                        OA0, Unity-Gain Buffer Mode
msp430x22x4_oa_06.s43                        OA1, Comparator Mode
msp430x22x4_oa_07.s43                        OA1, General-Purpose Mode
msp430x22x4_oa_08.s43                        OA1, Inverting PGA Mode
msp430x22x4_oa_09.s43                        OA1, Non-Inverting PGA Mode
msp430x22x4_oa_10.s43                        OA1, Unity-Gain Buffer Mode
msp430x22x4_p1_01.s43                        Software Poll P1.2, Set P1.0 if P1.2 = 1
msp430x22x4_p1_02.s43                        Software Port Interrupt Service on P1.2 from LPM4
msp430x22x4_p1_03.s43                        Poll P1.2 With Software with Internal Pull-up
msp430x22x4_p1_04.s43                        P1.2 Interrupt from LPM4 with Internal Pull-up
msp430x22x4_rosc.s43                         DCOCLK Biased with External Resistor Rosc
msp430x22x4_ta_01.s43                        Timer_A, Toggle P1.0, TACCR0 Cont. Mode ISR, DCO SMCLK
msp430x22x4_ta_02.s43                        Timer_A, Toggle P1.0, TACCR0 Up Mode ISR, DCO SMCLK
msp430x22x4_ta_03.s43                        Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x22x4_ta_04.s43                        Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x22x4_ta_05.s43                        Timer_A, Toggle P1.0, TACCR0 Up Mode ISR, 32kHz ACLK
msp430x22x4_ta_06.s43                        Timer_A, Toggle P1.0, TACCR1 Cont. Mode ISR, DCO SMCLK
msp430x22x4_ta_07.s43                        Timer_A, Toggle P1.0-3, Cont. Mode ISR, DCO SMCLK
msp430x22x4_ta_08.s43                        Timer_A, Toggle P1.0-3, Cont. Mode ISR, 32kHz ACLK
msp430x22x4_ta_09.s43                        Timer_A, Toggle P1.0-3, Cont. Mode ISR, HF XTAL ACLK
msp430x22x4_ta_10.s43                        Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK
msp430x22x4_ta_11.s43                        Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
msp430x22x4_ta_12.s43                        Timer_A, Toggle P1.1/TA0, Up Mode, HF XTAL ACLK
msp430x22x4_ta_13.s43                        Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
msp430x22x4_ta_14.s43                        Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK
msp430x22x4_ta_15.s43                        Timer_A, Toggle P1.1/TA0, Up/Down Mode, HF XTAL ACLK
msp430x22x4_ta_16.s43                        Timer_A, PWM TA1-2, Up Mode, DCO SMCLK
msp430x22x4_ta_17.s43                        Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
msp430x22x4_ta_18.s43                        Timer_A, PWM TA1-2, Up Mode, HF XTAL ACLK
msp430x22x4_ta_19.s43                        Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
msp430x22x4_ta_20.s43                        Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
msp430x22x4_ta_21.s43                        Timer_A, PWM TA1-2, Up/Down Mode, HF XTAL ACLK
msp430x22x4_ta_22.s43                        Timer_A, Ultra-Low Pwr Pulse Accumulator
msp430x22x4_tb_01.s43                        Timer_B, Toggle P1.0, TBCCR0 Cont. Mode ISR, DCO SMCLK
msp430x22x4_tb_02.s43                        Timer_B, Toggle P1.0, TBCCR0 Up Mode ISR, DCO SMCLK
msp430x22x4_tb_03.s43                        Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x22x4_tb_04.s43                        Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x22x4_tb_05.s43                        Timer_B, Toggle P1.0, TBCCR0 Up Mode ISR, 32kHz ACLK
msp430x22x4_tb_06.s43                        Timer_B, Toggle P1.0, TBCCR1 Cont. Mode ISR, DCO SMCLK
msp430x22x4_tb_07.s43                        Timer_B, Toggle P4.0-2, Cont. Mode ISR, DCO SMCLK
msp430x22x4_tb_08.s43                        Timer_B, Toggle P4.0-2, Cont. Mode ISR, 32kHz ACLK
msp430x22x4_tb_09.s43                        Timer_B, Toggle P4.0-2, Cont. Mode ISR, HF XTAL ACLK
msp430x22x4_tb_10.s43                        Timer_B, PWM TB1-2, Up Mode, DCO SMCLK
msp430x22x4_tb_11.s43                        Timer_B, PWM TB1-2, Up Mode, 32kHz ACLK
msp430x22x4_tb_12.s43                        Timer_B, PWM TB1-2, Up Mode, HF XTAL ACLK
msp430x22x4_tb_13.s43                        Timer_B, PWM TB1-2, Up/Down Mode, DCO SMCLK
msp430x22x4_tb_14.s43                        Timer_B, PWM TB1-2, Up/Down Mode, 32kHz ACLK
msp430x22x4_tb_15.s43                        Timer_B, PWM TB1-2, Up/Down Mode, HF XTAL ACLK
msp430x22x4_uscia0_irda_01.s43               USCI_A0 IrDA External Loopback Test, 8MHz SMCLK
msp430x22x4_uscia0_irda_02.s43               USCI_A0 IrDA Monitor, 8MHz SMCLK
msp430x22x4_uscia0_irda_03.s43               USCI_A0 IrDA Physical Layer Comm, 8MHz SMCLK
msp430x22x4_uscia0_spi_01.s43                USCI_A0, SPI Interface to HC164 Shift Register
msp430x22x4_uscia0_spi_02.s43                USCI_A0, SPI Interface to HC165 Shift Register
msp430x22x4_uscia0_spi_03.s43                USCI_A0, SPI Interface to HC165/164 Shift Registers
msp430x22x4_uscia0_spi_09.s43                USCI_A0, SPI 3-Wire Master Incremented Data
msp430x22x4_uscia0_spi_10.s43                USCI_A0, SPI 3-Wire Slave Data Echo
msp430x22x4_uscia0_uart_01_115k.s43          USCI_A0, 115200 UART Echo ISR, DCO SMCLK
msp430x22x4_uscia0_uart_01_115k_lpm.s43      USCI_A0, 115200 UART Echo ISR, DCO SMCLK, LPM4
msp430x22x4_uscia0_uart_01_19200.s43         USCI_A0, 19200 UART Echo ISR, DCO SMCLK
msp430x22x4_uscia0_uart_01_19200_2.s43       USCI_A0, UART 19200 Echo ISR, HF XTAL SMCLK
msp430x22x4_uscia0_uart_01_9600.s43          USCI_A0, 9600 UART Echo ISR, DCO SMCLK
msp430x22x4_uscia0_uart_05_9600.s43          USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430x22x4_uscia0_uart_06_9600.s43          USCI_A0, Ultra-Low Pwr UART 9600 String, 32kHz ACLK
msp430x22x4_uscia0_uart_07_9600.s43          USCI_A0, Ultra-Low Pwr UART 9600 RX/TX, 32kHz ACLK
msp430x22x4_uscia0_uart_08_9600.s43          USCI_A0, UART 9600 Full-Duplex Transceiver, 32kHz ACLK
msp430x22x4_uscib0_i2c_01.s43                USCI_B0 I2C Master to TMP100, Set P5.1 if Temp > 28C
msp430x22x4_uscib0_i2c_02.s43                USCI_B0 I2C Master Interface to PCF8574, Read/Write
msp430x22x4_uscib0_i2c_03.s43                USCI_B0 I2C Master Interface to DAC8571, Write
msp430x22x4_uscib0_i2c_04.s43                USCI_B0 I2C Master RX single bytes from MSP430 Slave
msp430x22x4_uscib0_i2c_05.s43                USCI_B0 I2C Slave TX single bytes to MSP430 Master
msp430x22x4_uscib0_i2c_06.s43                USCI_B0 I2C Master TX single bytes to MSP430 Slave
msp430x22x4_uscib0_i2c_07.s43                USCI_B0 I2C Slave RX single bytes from MSP430 Master
msp430x22x4_uscib0_i2c_08.s43                USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
msp430x22x4_uscib0_i2c_09.s43                USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
msp430x22x4_uscib0_i2c_10.s43                USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
msp430x22x4_uscib0_i2c_11.s43                USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
msp430x22x4_uscib0_spi_01.s43                USCI_B0, SPI Interface to TLC549 8-Bit ADC
msp430x22x4_uscib0_spi_02.s43                USCI_B0, SPI Interface to TLV1549 10-Bit ADC
msp430x22x4_wdt_01.s43                       WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
msp430x22x4_wdt_02.s43                       WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
msp430x22x4_wdt_04.s43                       WDT+ Failsafe Clock, DCO SMCLK
msp430x22x4_wdt_05.s43                       Reset on Invalid Address fetch, Toggle P1.0
msp430x22x4_wdt_06.s43                       WDT+ Failsafe Clock, 32kHz ACLK


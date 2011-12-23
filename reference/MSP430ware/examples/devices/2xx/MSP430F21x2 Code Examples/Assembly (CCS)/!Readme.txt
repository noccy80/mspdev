File Name                                    Description
----------------------------------------------------------------------------------------
msp430x21x2_1.asm                            Software Toggle P1.0
msp430x21x2_1_vlo.asm                        Software Toggle P1.0, MCLK = VLO/8
msp430x21x2_adc10_01.asm                     ADC10, Sample A0, AVcc Ref, Set P1.0 if A0 > 0.5*AVcc
msp430x21x2_adc10_02.asm                     ADC10, Sample A0, 1.5V Ref, Set P1.0 if A0 > 0.2V
msp430x21x2_adc10_03.asm                     ADC10, Sample A10 Temp, Set P1.0 if Temp ++ ~2C
msp430x21x2_adc10_04.asm                     ADC10, Sample A0, Signed, Set P1.0 if A0 > 0.5*AVcc
msp430x21x2_adc10_05.asm                     ADC10, Sample A11, Lo_Batt, Set P1.0 if AVcc < 2.3V
msp430x21x2_adc10_06.asm                     ADC10, Output Internal Vref on P2.4 & ADCCLK on P1.0
msp430x21x2_adc10_07.asm                     ADC10, DTC Sample A0 64x, AVcc, Repeat Single, DCO
msp430x21x2_adc10_08.asm                     ADC10, DTC Sample A0 64x, 1.5V, Repeat Single, DCO
msp430x21x2_adc10_09.asm                     ADC10, DTC Sample A10 64x, 1.5V, Repeat Single, DCO
msp430x21x2_adc10_10.asm                     ADC10, DTC Sample A2-0, AVcc, Single Sequence, DCO
msp430x21x2_adc10_11.asm                     ADC10, Sample A0, 1.5V, TA1 Trig, Set P1.0 if > 0.5V
msp430x21x2_adc10_12.asm                     ADC10, Sample A7, 1.5V, TA1 Trig, Ultra-Low Pwr
msp430x21x2_adc10_13.asm                     ADC10, DTC Sample A1 32x, AVcc, TA0 Trig, DCO
msp430x21x2_adc10_14.asm                     ADC10, DTC Sample A1-0 32x, AVcc, Repeat Seq, DCO
msp430x21x2_adc10_15.asm                     ADC10, DTC Sample A10 32x to Flash, Int Ref, DCO
msp430x21x2_adc10_16.asm                     ADC10, DTC Sample A0 -> TA1, AVcc, DCO
msp430x21x2_adc10_17.asm                     ADC10, DTC Sample A0 -> TA1, AVcc, HF XTAL
msp430x21x2_adc10_18.asm                     ADC10, DTC Sample A1/0 -> TA1/2, 2.5V, HF XTAL
msp430x21x2_adc10_19.asm                     ADC10, DTC Sample A0 64x, AVcc, HF XTAL
msp430x21x2_adc10_20.asm                     ADC10, DTC Sample A0 2-Blk Cont. Mode, AVcc, HF XTAL
msp430x21x2_adc10_temp.asm                   ADC10, Sample A10 Temp and Convert to oC and oF
msp430x21x2_clks.asm                         Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
msp430x21x2_compA_01.asm                     Comparator A, Poll input CA0, result in P5.1
msp430x21x2_compA_02.asm                     Comparator A, Poll input CA0, CA exchange, result in P5.1
msp430x21x2_compA_04.asm                     Comparator A, Poll input CA0, result in P5.1
msp430x21x2_compA_05.asm                     Comparator A, Poll input CA0, interrupt triggered
msp430x21x2_dco_flashcal.asm                 DCO Calibration Constants Programmer
msp430x21x2_flashwrite_01.asm                Flash In-System Programming, Copy SegC to SegD
msp430x21x2_flashwrite_03.asm                Flash In-System Programming w/ EEI, Copy SegC to SegD
msp430x21x2_flashwrite_04.asm                Flash In-System Programming w/ EEI, Copy SegD to A/B/C
msp430x21x2_fll_01.asm                       Basic Clock, Implement Auto RSEL SW FLL
msp430x21x2_fll_02.asm                       Basic Clock, Implement Cont. SW FLL with Auto RSEL
msp430x21x2_hfxtal.asm                       Basic Clock, MCLK Sourced from HF XTAL
msp430x21x2_hfxtal_nmi.asm                   Basic Clock, LFXT1/MCLK Sourced from HF XTAL, NMI
msp430x21x2_lpm3.asm                         Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
msp430x21x2_lpm3_vlo.asm                     Basic Clock, LPM3 Using WDT ISR, VLO ACLK
msp430x21x2_nmi.asm                          Configure RST/NMI as NMI
msp430x21x2_p1_01.asm                        Software Poll P1.3, Set P1.0 if P1.3 = 1
msp430x21x2_p1_02.asm                        Software Port Interrupt Service on P1.3 from LPM4
msp430x21x2_p1_03.asm                        Poll P1 With Software with Internal Pull-up
msp430x21x2_p1_04.asm                        P1 Interrupt from LPM4 with Internal Pull-up
msp430x21x2_rosc.asm                         DCOCLK Biased with External Resistor Rosc
msp430x21x2_ta0_01.asm                       Timer_A, Toggle P1.0, TACCR0 Cont. Mode ISR, DCO SMCLK
msp430x21x2_ta0_02.asm                       Timer_A, Toggle P1.0, TACCR0 Up Mode ISR, DCO SMCLK
msp430x21x2_ta0_03.asm                       Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x21x2_ta0_04.asm                       Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x21x2_ta0_05.asm                       Timer_A, Toggle P1.0, TACCR0 Up Mode ISR, 32kHz ACLK
msp430x21x2_ta0_06.asm                       Timer_A, Toggle P1.0, TACCR1 Cont. Mode ISR, DCO SMCLK
msp430x21x2_ta0_07.asm                       Timer_A, Toggle P1.0-3, Cont. Mode ISR, DCO SMCLK
msp430x21x2_ta0_08.asm                       Timer_A, Toggle P1.0-3, Cont. Mode ISR, 32kHz ACLK
msp430x21x2_ta0_09.asm                       Timer_A, Toggle P1.0-3, Cont. Mode ISR, HF XTAL ACLK
msp430x21x2_ta0_10.asm                       Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK
msp430x21x2_ta0_11.asm                       Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
msp430x21x2_ta0_12.asm                       Timer_A, Toggle P1.1/TA0, Up Mode, HF XTAL ACLK
msp430x21x2_ta0_13.asm                       Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
msp430x21x2_ta0_14.asm                       Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK
msp430x21x2_ta0_15.asm                       Timer_A, Toggle P1.1/TA0, Up/Down Mode, HF XTAL ACLK
msp430x21x2_ta0_16.asm                       Timer_A, PWM TA1-2, Up Mode, DCO SMCLK
msp430x21x2_ta0_17.asm                       Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
msp430x21x2_ta0_18.asm                       Timer_A, PWM TA1-2, Up Mode, HF XTAL ACLK
msp430x21x2_ta0_19.asm                       Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
msp430x21x2_ta0_20.asm                       Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
msp430x21x2_ta0_21.asm                       Timer_A, PWM TA1-2, Up/Down Mode, HF XTAL ACLK
msp430x21x2_ta0_22.asm                       Timer_A, Ultra-Low Pwr Pulse Accumulator
msp430x21x2_ta1_01.asm                       Timer_A, Toggle P1.0, TACCR0 Cont. Mode ISR, DCO SMCLK
msp430x21x2_ta1_02.asm                       Timer_A, Toggle P1.0, TACCR0 Up Mode ISR, DCO SMCLK
msp430x21x2_ta1_03.asm                       Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
msp430x21x2_ta1_04.asm                       Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp430x21x2_ta1_05.asm                       Timer_A, Toggle P1.0, TACCR0 Up Mode ISR, 32kHz ACLK
msp430x21x2_ta1_06.asm                       Timer_A, Toggle P1.0, TACCR1 Cont. Mode ISR, DCO SMCLK
msp430x21x2_ta1_07.asm                       Timer_A, Toggle P1.0-3, Cont. Mode ISR, DCO SMCLK
msp430x21x2_ta1_08.asm                       Timer_A, Toggle P1.0-3, Cont. Mode ISR, 32kHz ACLK
msp430x21x2_ta1_09.asm                       Timer_A, Toggle P1.0-3, Cont. Mode ISR, HF XTAL ACLK
msp430x21x2_ta1_10.asm                       Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK
msp430x21x2_ta1_11.asm                       Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK
msp430x21x2_ta1_12.asm                       Timer_A, Toggle P1.1/TA0, Up Mode, HF XTAL ACLK
msp430x21x2_ta1_13.asm                       Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
msp430x21x2_ta1_14.asm                       Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK
msp430x21x2_ta1_15.asm                       Timer_A, Toggle P1.1/TA0, Up/Down Mode, HF XTAL ACLK
msp430x21x2_ta1_16.asm                       Timer_A, PWM TA1-2, Up Mode, DCO SMCLK
msp430x21x2_ta1_17.asm                       Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
msp430x21x2_ta1_18.asm                       Timer_A, PWM TA1-2, Up Mode, HF XTAL ACLK
msp430x21x2_ta1_19.asm                       Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
msp430x21x2_ta1_20.asm                       Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
msp430x21x2_ta1_21.asm                       Timer_A, PWM TA1-2, Up/Down Mode, HF XTAL ACLK
msp430x21x2_ta1_22.asm                       Timer_A, Ultra-Low Pwr Pulse Accumulator
msp430x21x2_uscia0_irda_01.asm               USCI_A0 IrDA External Loopback Test, 8MHz SMCLK
msp430x21x2_uscia0_irda_02.asm               USCI_A0 IrDA Monitor, 8MHz SMCLK
msp430x21x2_uscia0_irda_03.asm               USCI_A0 IrDA Physical Layer Comm, 8MHz SMCLK
msp430x21x2_uscia0_spi_01.asm                USCI_A0, SPI Interface to HC164 Shift Register
msp430x21x2_uscia0_spi_02.asm                USCI_A0, SPI Interface to HC165 Shift Register
msp430x21x2_uscia0_spi_03.asm                USCI_A0, SPI Interface to HC165/164 Shift Registers
msp430x21x2_uscia0_spi_09.asm                USCI_A0, SPI 3-Wire Master Incremented Data
msp430x21x2_uscia0_spi_10.asm                USCI_A0, SPI 3-Wire Slave Data Echo
msp430x21x2_uscia0_uart_01_115k.asm          USCI_A0, 115200 UART Echo ISR, DCO SMCLK4
msp430x21x2_uscia0_uart_01_115k_lpm.asm      USCI_A0, 115200 UART Echo ISR, DCO SMCLK, LPM4
msp430x21x2_uscia0_uart_01_19200.asm         USCI_A0, 19200 UART Echo ISR, DCO SMCLK
msp430x21x2_uscia0_uart_01_19200_2.asm       USCI_A0, UART 19200 Echo ISR, HF XTAL SMCLK
msp430x21x2_uscia0_uart_01_9600.asm          USCI_A0, 9600 UART Echo ISR, DCO SMCLK
msp430x21x2_uscia0_uart_05_9600.asm          USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430x21x2_uscia0_uart_06_9600.asm          USCI_A0, Ultra-Low Pwr UART 9600 String, 32kHz ACLK
msp430x21x2_uscia0_uart_07_9600.asm          USCI_A0, Ultra-Low Pwr UART 9600 RX/TX, 32kHz ACLK
msp430x21x2_uscia0_uart_08_9600.asm          USCI_A0, UART 9600 Full-Duplex Transceiver, 32kHz ACLK
msp430x21x2_uscib0_i2c_01.asm                USCI_B0 I2C Master to TMP100, Set P5.1 if Temp > 28C
msp430x21x2_uscib0_i2c_02.asm                USCI_B0 I2C Master Interface to PCF8574, Read/Write
msp430x21x2_uscib0_i2c_03.asm                USCI_B0 I2C Master Interface to DAC8571, Writeve
msp430x21x2_uscib0_i2c_04.asm                USCI_B0 I2C Master RX single bytes from MSP430 Slave
msp430x21x2_uscib0_i2c_05.asm                USCI_B0 I2C Slave TX single bytes to MSP430 Master
msp430x21x2_uscib0_i2c_06.asm                USCI_B0 I2C Master TX single bytes to MSP430 Slave
msp430x21x2_uscib0_i2c_07.asm                USCI_B0 I2C Slave RX single bytes from MSP430 Master
msp430x21x2_uscib0_i2c_08.asm                USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
msp430x21x2_uscib0_i2c_09.asm                USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
msp430x21x2_uscib0_i2c_10.asm                USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
msp430x21x2_uscib0_i2c_11.asm                USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
msp430x21x2_uscib0_spi_01.asm                USCI_B0, SPI Interface to TLC549 8-Bit ADC
msp430x21x2_uscib0_spi_02.asm                USCI_B0, SPI Interface to TLV1549 10-Bit ADC
msp430x21x2_wdt_01.asm                       WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
msp430x21x2_wdt_02.asm                       WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
msp430x21x2_wdt_04.asm                       WDT+ Failsafe Clock, DCO SMCLK
msp430x21x2_wdt_05.asm                       Reset on Invalid Address fetch, Toggle P1.0
msp430x21x2_wdt_06.asm                       WDT+ Failsafe Clock, 32kHz ACLK


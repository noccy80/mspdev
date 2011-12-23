File Name                                   Description
----------------------------------------------------------------------------------------
msp430F(G)47x_1.asm                         Toggle P4.6 in software
msp430F(G)47x_bt_01.asm                     Basic Timer, Toggle P4.6 Inside ISR, DCO SMCLK
msp430F(G)47x_bt_02.asm                     Basic Timer, Toggle P4.6 Inside ISR, 32kHz ACLK
msp430F(G)47x_clks_03.asm                   FLL+, Output 32kHz XTAL + HF XTAL + Internal DCO
msp430F(G)47x_compA_01.asm                  Comparator_A, Poll input CA0, result in P4.6
msp430F(G)47x_compA_02.asm                  Comparator_A, Poll input CA0, CA exchange, result in P4.6
msp430F(G)47x_compA_04.asm                  Comparator_A, Poll input CA0, result in P4.6
msp430F(G)47x_compA_05.asm                  Comparator_A, Poll input CA0, interrupt triggered
msp430F(G)47x_dac12_01.asm                  DAC12_0, Output 1V on DAC0
msp430F(G)47x_dac12_02.asm                  DAC12_0, Output 2V on DAC1
msp430F(G)47x_dac12_03.asm                  DAC12_0, Output Voltage Ramp on DAC0
msp430F(G)47x_dac12_05.asm                  DAC12_0, Output Voltage Ramp on DAC0
msp430F(G)47x_flashwrite_01.asm             Flash In-System Programming, Copy SegC to SegD
msp430F(G)47x_flashwrite_03.asm             Flash In-System Programming w/ EEI, Copy SegC to SegD
msp430F(G)47x_flashwrite_04.asm             Flash In-System Programming w/ EEI, Copy SegD to A/B/C
msp430F(G)47x_fll_01.asm                    FLL+, Runs Internal DCO at 2.5MHz
msp430F(G)47x_fll_02.asm                    FLL+, Runs Internal DCO at 8MHz
msp430F(G)47x_LFxtal_nmi.asm                LFXT1 Oscillator Fault Detection
msp430F(G)47x_lpm3.asm                      FLL+, LPM3 Using Basic Timer ISR, 32kHz ACLK
msp430F(G)47x_oa_02.asm                     OA0,Comparator in General-Purpose Mode
msp430F(G)47x_oa_03.asm                     OA0,General-Purpose Mode
msp430F(G)47x_oa_06.asm                     OA0,Unity-Gain Buffer Mode
msp430F(G)47x_oa_11.asm                     OA1,Unity-Gain Buffer Mode
msp430F(G)47x_sd16a_03.asm                  SD16_A, Continuous Conversion on a Single Channel
msp430F(G)47x_sd16a_04.asm                  SD16_A, Single Conversion on Single Channel Polling IFG
msp430F(G)47x_sd16a_05.asm                  SD16_A, Single Conversion on a Single Channel Using ISR
msp430F(G)47x_sd16a_07.asm                  SD16, Single Conversion on a Single Channel Using ISR
msp430F(G)47x_sd16a_08.asm                  SD16_A, Single Conversion on a Channel using buffered input
msp430F(G)47x_sd16a_09.asm                  SD16_A, Single Conversion on a Single Channel Using ISR
msp430F(G)47x_sd16a_10.asm                  SD16_A, Single Conversion on a Single Channel Using ISR 1024 Extended Oversampling Rate
msp430F(G)47x_sd16a_11.asm                  SD16_A, Single Conversion on a Single Channel Using ISR ACLK input to SD16_A
msp430F(G)47x_sd16a_12.asm                  SD16_A, Single Conversion on a Single Channel Using ISR SMCLK input is divided by 32
msp430F(G)47x_svs_01.asm                    SVS, POR @ 2.5V Vcc
msp430F(G)47x_svs_03.asm                    SVM, Toggle port 4.6 on Vcc < 2.8V
msp430F(G)47x_ta_01.asm                     Timer_A, Toggle P4.6, CCR0 Cont. Mode ISR, DCO SMCLK
msp430F(G)47x_ta_02.asm                     Timer_A, Toggle P4.6, CCR0 Up Mode ISR, DCO SMCLK
msp430F(G)47x_ta_03.asm                     Timer_A, Toggle P4.6, Overflow ISR, DCO SMCLK
msp430F(G)47x_ta_04.asm                     Timer_A, Toggle P4.6, Overflow ISR, 32kHz ACLK
msp430F(G)47x_ta_05.asm                     Timer_A, Toggle P4.6, CCR0 Up Mode ISR, 32kHz ACLK
msp430F(G)47x_ta_16.asm                     Timer_A, Timer_A, PWM TA1-2 Up Mode, DCO SMCLK
msp430F(G)47x_ta_17.asm                     Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
msp430F(G)47x_tb_01.asm                     Timer_B, Toggle P4.6, CCR0 Cont. Mode ISR, DCO SMCLK
msp430F(G)47x_tb_02.asm                     Timer_B, Toggle P4.6, CCR0 Up Mode ISR, DCO SMCLK
msp430F(G)47x_tb_03.asm                     Timer_B, Toggle P4.6, Overflow ISR, DCO SMCLK
msp430F(G)47x_tb_04.asm                     Timer_B, Toggle P4.6, Overflow ISR, 32kHz ACLK
msp430F(G)47x_tb_05.asm                     Timer_B, Toggle P4.6, CCR0 Up Mode ISR, 32kHz ACLK
msp430F(G)47x_tb_10.asm                     Timer_B, PWM TB1 -2 Up Mode, DCO SMCLK
msp430F(G)47x_tb_11.asm                     Timer_B, PWM TB1-2 Up Mode, 32kHz ACLK
msp430F(G)47x_uscia0_duplex_9600.asm        USCI_A0, UART 9600 Full-Duplex Transceiver, 32K ACLK
msp430F(G)47x_uscia0_irda_01.asm            USCI_A0 IrDA External Loopback Test, 4MHz SMCLK
msp430F(G)47x_uscia0_spi_09.asm             USCI_A0, SPI 3-Wire Master Incremented Data
msp430F(G)47x_uscia0_spi_10.asm             USCI_A0, SPI 3-Wire Slave Data Echo
msp430F(G)47x_uscia0_uart_115k.asm          USCI_A0, 115200 UART Echo ISR, DCO SMCLK
msp430F(G)47x_uscia0_uart_115k_lpm.asm      USCI_A0, 115200 UART Echo ISR, DCO SMCLK, LPM3
msp430F(G)47x_uscia0_uart_9600.asm          USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430F(G)47x_uscib0_i2c_02.asm             USCI_B0 I2C Master Interface to PCF8574, Read/Write
msp430F(G)47x_uscib0_i2c_08.asm             USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
msp430F(G)47x_uscib0_i2c_09.asm             USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
msp430F(G)47x_uscib0_i2c_10.asm             USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
msp430F(G)47x_uscib0_i2c_11.asm             USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
msp430F(G)47x_wdt_01.asm                    WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
msp430F(G)47x_wdt_02.asm                    WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK


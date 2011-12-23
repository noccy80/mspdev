File Name                                  Description
----------------------------------------------------------------------------------------
msp430x471x7_1.s43                          Software Toggle P5.1
msp430x471x7_bt_01.s43                      Basic Timer, Toggle P5.1 Inside ISR, 32kHz ACLK
msp430x471x7_bt_02.s43                      Basic Timer, Toggle P5.1 Inside ISR, DCO SMCLK
msp430x471x7_clks_02.s43                    FLL+, Output 32kHz Xtal + HF Xtal + Internal DCO
msp430x471x7_compA_01.s43                   Comparator A, Poll input CA0, result in P5.1
msp430x471x7_compA_02.s43                   Comparator A, Poll input CA0, CA exchange, result in P5.1
msp430x471x7_compA_04.s43                   Comparator A, Poll input CA0, result in P5.1
msp430x471x7_compA_05.s43                   Comparator A, Poll input CA0, interrupt triggered
msp430x471x7_flashwrite_01.s43              Flash In-System Programming, Copy SegC to SegD
msp430x471x7_flashwrite_03.s43              Flash In-System Programming w/ EEI, Copy SegC to SegD
msp430x471x7_flashwrite_04.s43              Flash In-System Programming w/ EEI, Copy SegD to A/B/C
msp430x471x7_fll_01.s43                     FLL+, Runs Internal DCO at 2.45MHz
msp430x471x7_fll_02.s43                     FLL+, Runs Internal DCO at 16MHz
msp430x471x7_hfxt2.s43                      FLL+, MCLK Configured to Operate from XT2 HF XTAL
msp430x471x7_lcda_04.s43                    LCD_A Put "0123456" on SBLCDA4 LCD
msp430x471x7_lcda_05.s43                    LCD_A Put "0123456" on SBLCDA4 LCD with charge pump
msp430x471x7_lpm3.s43                       FLL+, LPM3 Using Basic Timer ISR, 32kHz ACLK
msp430x471x7_MPY_01.s43                     16x16 Unsigned Multiply
msp430x471x7_MPY_03.s43                     16x16 Signed Multiply
msp430x471x7_MPY_09.s43                     32x32 Unsigned Multiply
msp430x471x7_MPY_10.s43                     32x32 Signed Multiply
msp430x471x7_MPY_11.s43                     32x32 Signed Multiply Accumalate
msp430x471x7_MPY_12.s43                     32x32 Unsigned Multiply Accumalate
msp430x471x7_MPY_13.s43                     Saturation mode overflow test
msp430x471x7_MPY_14.s43                     Saturation mode underflow test
msp430x471x7_MPY_15.s43                     Fractional mode, Q15 multiplication
msp430x471x7_OF_LFXT1_nmi.s43               LFXT1 Oscillator Fault Detection
msp430x471x7_OF_XT2.s43                     XT2 Oscillator Fault Detection
msp430x471x7_P1_01.s43                      Software Poll P2.7, Set P5.1 if P2.7 = 1
msp430x471x7_P1_02.s43                      Software Port Interrupt on P2.7 from LPM4
msp430x471x7_P1_05.s43                      Write a byte to Port 1
msp430x471x7_P7_05.s43                      Write a byte to Port 7
msp430x471x7_P8_05.s43                      Write a byte to Port 8
msp430x471x7_PA_05.s43                      Write a Word to Port A (Port7+Port8)
msp430x471x7_PB_05.s43                      Write a Word to Port B (Port9+Port10)
msp430x471x7_rtc_01.s43                     Real Time Clock, Toggle P5.1 Inside ISR, 32kHz ACLK
msp430x471x7_rtc_02.s43                     Real Time Clock, Toggle P5.1 Inside ISR, 32kHz ACLK and send Time via UART
msp430x471x7_sd16_01.s43                    SD16, Continuous Conversion on a Group of 7 Channels
msp430x471x7_sd16_02.s43                    SD16, Single Conversion on a Group of 7 Channels
msp430x471x7_sd16_03.s43                    SD16, Continuous Conversion on a Single Channel
msp430x471x7_sd16_04.s43                    SD16, Single Conversion on Single Channel Polling IFG
msp430x471x7_sd16_05.s43                    SD16, Single Conversion on a Single Channel Using ISR
msp430x471x7_svs_01.s43                     SVS, POR @ 2.5V Vcc
msp430x471x7_svs_03.s43                     SVS, Toggle port 5.1 on Vcc < 2.8V
msp430x471x7_ta_01.s43                      Timer_A, Toggle P5.1, CCR0 Cont. Mode ISR, DCO SMCLK
msp430x471x7_ta_02.s43                      Timer_A, Toggle P5.1, CCR0 Up Mode ISR, DCO SMCLK
msp430x471x7_ta_03.s43                      Timer_A, Toggle P5.1, Overflow ISR, DCO SMCLK
msp430x471x7_ta_04.s43                      Timer_A, Toggle P5.1, Overflow ISR, 32kHz ACLK
msp430x471x7_ta_05.s43                      Timer_A, Toggle P5.1, CCR0 Up Mode ISR, 32kHz ACLK
msp430x471x7_ta_16.s43                      Timer_A, PWM TA1-2 Up Mode, DCO SMCLK
msp430x471x7_ta_17.s43                      Timer_A, PWM TA1-2 Up Mode, 32kHz ACLK
msp430x471x7_tb_01.s43                      Timer_B, Toggle P5.1, CCR0 Cont. Mode ISR, DCO SMCLK
msp430x471x7_tb_02.s43                      Timer_B, Toggle P5.1, CCR0 Up Mode ISR, DCO SMCLK
msp430x471x7_tb_03.s43                      Timer_B, Toggle P5.1, Overflow ISR, DCO SMCLK
msp430x471x7_tb_04.s43                      Timer_B, Toggle P5.1, Overflow ISR, 32kHz ACLK
msp430x471x7_tb_05.s43                      Timer_B, Toggle P5.1, CCR0 Up Mode ISR, 32kHz ACLK
msp430x471x7_tb_10.s43                      Timer_B, PWM TB1-2 Up Mode, DCO SMCLK
msp430x471x7_tb_11.s43                      Timer_B, PWM TB1-2 Up Mode, 32kHz ACLK
msp430x471x7_uscia0_duplex_9600.s43         USCI_A0, UART 9600 Full-Duplex Transceiver, 32K ACLK
msp430x471x7_uscia0_irda_01.s43             USCI_A0 IrDA External Loopback Test, 4MHz SMCLK
msp430x471x7_uscia0_spi_09.s43              USCI_A0, SPI 3-Wire Master Incremented Data
msp430x471x7_uscia0_spi_10.s43              USCI_A0, SPI 3-Wire Slave Data Echo
msp430x471x7_uscia0_uart_115k.s43           USCI_A0, 115200 UART Echo ISR, DCO SMCLK
msp430x471x7_uscia0_uart_115k_lpm.s43       USCI_A0, 115200 UART Echo ISR, DCO SMCLK, LPM3
msp430x471x7_uscia0_uart_9600.s43           USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430x471x7_uscib0_i2c_08.s43              USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
msp430x471x7_uscib0_i2c_09.s43              USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
msp430x471x7_uscib0_i2c_10.s43              USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
msp430x471x7_uscib0_i2c_11.s43              USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
msp430x471x7_uscib0_spi_01.s43              USCI_B0, SPI Interface to TLC549 8-Bit ADC
msp430x471x7_wdt_01.s43                     WDT, Toggle P5.1, Interval Overflow ISR, DCO SMCLK
msp430x471x7_wdt_02.s43                     WDT, Toggle P5.1, Interval Overflow ISR, 32kHz ACLK
msp430x471x7_wdt_04.s43                     WDT+ Failsafe Clock, DCO SMCLK
msp430x471x7_wdt_05.s43                     Reset on Invalid Address fetch, Toggle P5.1
msp430x471x7_wdt_06.s43                     WDT+ Failsafe Clock, 32kHz ACLK


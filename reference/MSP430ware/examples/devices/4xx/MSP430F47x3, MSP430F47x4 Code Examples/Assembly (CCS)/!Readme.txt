File Name                                 Description
----------------------------------------------------------------------------------------
msp430x47x4_sd16_01.asm                   SD16, Continuous Conversion on a Group of 4 Channels
msp430x47x4_sd16_02.asm                   SD16, Single Conversion on a Group of 4 Channels
msp430x47xx_1.asm                         Software Toggle P5.1
msp430x47xx_bt_01.asm                     Basic Timer, Toggle P5.1 Inside ISR, 32kHz ACLK
msp430x47xx_bt_02.asm                     Basic Timer, Toggle P5.1 Inside ISR, DCO SMCLK
msp430x47xx_clks_02.asm                   FLL+, Output 32kHz XTAL + HF XTAL + Internal DCO
msp430x47xx_compA_01.asm                  Comparator_A, Poll input CA0, result in P5.1
msp430x47xx_compA_02.asm                  Comparator_A, Poll input CA0, CA exchange, result in P5.1
msp430x47xx_compA_04.asm                  Comparator_A, Poll input CA0, result in P5.1
msp430x47xx_compA_05.asm                  Comparator_A, Poll input CA0, interrupt triggered
msp430x47xx_flashwrite_01.asm             Flash In-System Programming, Copy SegC to SegD
msp430x47xx_flashwrite_03.asm             Flash In-System Programming w/ EEI, Copy SegC to SegD
msp430x47xx_flashwrite_04.asm             Flash In-System Programming w/ EEI, Copy SegD to A/B/C
msp430x47xx_fll_01.asm                    FLL+, Runs Internal DCO at 2.5MHz
msp430x47xx_fll_02.asm                    FLL+, Runs Internal DCO at 8MHz
msp430x47xx_hfxt2.asm                     FLL+, MCLK Configured to Operate from XT2 HF XTAL
msp430x47xx_lcda_04.asm                   LCD, Display "6543210" on SBLCDA4
msp430x47xx_lcda_05.asm                   LCD, Display "6543210" on SBLCDA4, with charge pump enabled
msp430x47xx_lpm3.asm                      FLL+, LPM3 Using Basic Timer ISR, 32kHz ACLK
msp430x47xx_MPY_01.asm                    16x16 Unsigned Multiply
msp430x47xx_MPY_03.asm                    16x16 Signed Multiply
msp430x47xx_MPY_09.asm                    32x32 Unsigned Multiply
msp430x47xx_MPY_10.asm                    32x32 Signed Multiply
msp430x47xx_MPY_11.asm                    32x32 Signed Multiply Accumalate
msp430x47xx_MPY_12.asm                    32x32 Unsigned Multiply Accumalate
msp430x47xx_MPY_13.asm                    Saturation mode overflow test
msp430x47xx_MPY_14.asm                    Saturation mode underflow test
msp430x47xx_MPY_15.asm                    Fractional mode, Q15 multiplication
msp430x47xx_OF_LFXT1_nmi.asm              LFXT1 Oscillator Fault Detection
msp430x47xx_OF_XT2.asm                    XT2 Oscillator Fault Detection
msp430x47xx_P1_01.asm                     Software Poll P1.4, Set P5.1 if P1.4 = 1
msp430x47xx_P1_02.asm                     Software Port Interrupt on P1.4 from LPM4
msp430x47xx_P1_05.asm                     Write a byte to Port 1
msp430x47xx_P7_05.asm                     Write a byte to Port 7
msp430x47xx_P8_05.asm                     Write a byte to Port 8
msp430x47xx_PA_05.asm                     Write a Word to Port A (Port7+Port8)
msp430x47xx_PB_05.asm                     Write a Word to Port B (Port9+Port10)
msp430x47xx_sd16_01.asm                   SD16, Continuous Conversion on a Group of Channels
msp430x47xx_sd16_02.asm                   SD16, Single Conversion on a Group of Channels
msp430x47xx_sd16_03.asm                   SD16, Continuous Conversion on a Single Channel
msp430x47xx_sd16_04.asm                   SD16, Single Conversion on Single Channel Polling IFG
msp430x47xx_sd16_05.asm                   SD16, Single Conversion on a Single Channel Using ISR
msp430x47xx_svs_01.asm                    SVS, POR @ 2.5V Vcc
msp430x47xx_svs_03.asm                    SVS, Toggle port 5.1 on Vcc < 2.8V
msp430x47xx_ta_01.asm                     Timer_A, Toggle P5.1, CCR0 Cont. Mode ISR, DCO SMCLK
msp430x47xx_ta_02.asm                     Timer_A, Toggle P5.1, CCR0 Up Mode ISR, DCO SMCLK
msp430x47xx_ta_03.asm                     Timer_A, Toggle P5.1, Overflow ISR, DCO SMCLK
msp430x47xx_ta_04.asm                     Timer_A, Toggle P5.1, Overflow ISR, 32kHz ACLK
msp430x47xx_ta_05.asm                     Timer_A, Toggle P5.1, CCR0 Up Mode ISR, 32kHz ACLK
msp430x47xx_ta_16.asm                     Timer_A, Timer_A, PWM TA1-2 Up Mode, DCO SMCLK
msp430x47xx_ta_17.asm                     Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
msp430x47xx_tb_01.asm                     Timer_B, Toggle P5.1, CCR0 Cont. Mode ISR, DCO SMCLK
msp430x47xx_tb_02.asm                     Timer_B, Toggle P5.1, CCR0 Up Mode ISR, DCO SMCLK
msp430x47xx_tb_03.asm                     Timer_B, Toggle P5.1, Overflow ISR, DCO SMCLK
msp430x47xx_tb_04.asm                     Timer_B, Toggle P5.1, Overflow ISR, 32kHz ACLK
msp430x47xx_tb_05.asm                     Timer_B, Toggle P5.1, CCR0 Up Mode ISR, 32kHz ACLK
msp430x47xx_tb_10.asm                     Timer_B, PWM TB1-6, Up Mode, DCO SMCLK
msp430x47xx_tb_11.asm                     Timer_B, PWM TB1-2 Up Mode, 32kHz ACLK
msp430x47xx_uscia0_duplex_9600.asm        USCI_A0, UART 9600 Full-Duplex Transceiver, 32K ACLK
msp430x47xx_uscia0_irda_01.asm            USCI_A0 IrDA External Loopback Test, 4MHz SMCLK
msp430x47xx_uscia0_spi_09.asm             USCI_A0, SPI 3-Wire Master Incremented Data
msp430x47xx_uscia0_spi_10.asm             USCI_A0, SPI 3-Wire Slave Data Echo
msp430x47xx_uscia0_uart_115k.asm          USCI_A0, 115200 UART Echo ISR, DCO SMCLK
msp430x47xx_uscia0_uart_115k_lpm.asm      USCI_A0, 115200 UART Echo ISR, DCO SMCLK, LPM3
msp430x47xx_uscia0_uart_9600.asm          USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430x47xx_uscib0_i2c_02.asm             USCI_B0 I2C Master Interface to PCF8574, Read/Write
msp430x47xx_uscib0_i2c_03.asm             USCI_B0 I2C Master Interface to DAC8571, Write
msp430x47xx_uscib0_i2c_08.asm             USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
msp430x47xx_uscib0_i2c_09.asm             USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
msp430x47xx_uscib0_i2c_10.asm             USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
msp430x47xx_uscib0_i2c_11.asm             USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
msp430x47xx_uscib0_spi_01.asm             USCI_B0, SPI Interface to TLC549 8-Bit ADC
msp430x47xx_wdt_01.asm                    WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
msp430x47xx_wdt_02.asm                    WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
msp430x47xx_wdt_04.asm                    WDT+ Failsafe Clock, DCO SMCLK
msp430x47xx_wdt_05.asm                    Reset on Invalid Address fetch, Toggle P1.0
msp430x47xx_wdt_06.asm                    WDT+ Failsafe Clock, 32kHz ACLK


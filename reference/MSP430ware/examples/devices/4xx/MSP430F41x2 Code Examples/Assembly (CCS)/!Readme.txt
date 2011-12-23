File Name                                 Description
----------------------------------------------------------------------------------------
msp430x41x2_1.asm                         Toggle P5.1 in software
msp430x41x2_1_vlo.asm                     Software Toggle P5.1, MCLK = VLO/8
msp430x41x2_adc10_01.asm                  ADC10, Sample A0, AVcc Ref, Set P1.0 if A0 > 0.5*AVcc
msp430x41x2_adc10_02.asm                  ADC10, Sample A0, 1.5V Ref, Set P1.0 if A0 > 0.2V    
msp430x41x2_adc10_03.asm                  ADC10, Sample A10 Temp, Set P1.0 if Temp ++ ~2C      
msp430x41x2_adc10_04.asm                  ADC10, Sample A0, Signed, Set P1.0 if A0 > 0.5*AVcc  
msp430x41x2_adc10_05.asm                  ADC10, Sample A11, Lo_Batt, Set P1.0 if AVcc < 2.3V  
msp430x41x2_adc10_06.asm                  ADC10, Output Internal Vref on P2.4 & ADCCLK on P1.0 
msp430x41x2_adc10_07.asm                  ADC10, DTC Sample A0 64x, AVcc, Repeat Single, DCO   
msp430x41x2_adc10_08.asm                  ADC10, DTC Sample A0 64x, 1.5V, Repeat Single, DCO   
msp430x41x2_adc10_09.asm                  ADC10, DTC Sample A10 64x, 1.5V, Repeat Single, DCO  
msp430x41x2_adc10_10.asm                  ADC10, DTC Sample A2-0, AVcc, Single Sequence, DCO   
msp430x41x2_adc10_11.asm                  ADC10, Sample A0, 1.5V, TA1 Trig, Set P1.0 if > 0.5V 
msp430x41x2_adc10_12.asm                  ADC10, Sample A7, 1.5V, TA1 Trig, Ultra-Low Pwr      
msp430x41x2_adc10_13.asm                  ADC10, DTC Sample A1 32x, AVcc, TA0 Trig, DCO        
msp430x41x2_adc10_14.asm                  ADC10, DTC Sample A1-0 32x, AVcc, Repeat Seq, DCO    
msp430x41x2_adc10_15.asm                  ADC10, DTC Sample A10 32x to Flash, Int Ref, DCO     
msp430x41x2_adc10_16.asm                  ADC10, DTC Sample A0 -> TA1, AVcc, DCO               
msp430x41x2_adc10_21.asm                  ADC10, Sample A10 Temp and Convert to oC and oF      
msp430x41x2_bt_01.asm                     Basic Timer, Toggle P5.1 Inside ISR, DCO SMCLK
msp430x41x2_bt_02.asm                     Basic Timer, Toggle P5.1 Inside ISR, 32kHz ACLK
msp430x41x2_clks.asm                      FLL+, Output 32kHz XTAL + Internal DCO
msp430x41x2_compA_01.asm                  Comparator A, Poll input CA0, result in P5.1
msp430x41x2_compA_02.asm                  Comparator A, Poll input CA0, CA exchange, result in P5.1 
msp430x41x2_compA_04.asm                  Comparator A, Poll input CA0, result in P5.1 
msp430x41x2_compA_05.asm                  Comparator A, Poll input CA0, interrupt triggered 
msp430x41x2_flashwrite_01.asm             Flash In-System Programming, Copy SegC to SegD
msp430x41x2_fll_01.asm                    FLL+, Runs Internal DCO at 2.5MHz
msp430x41x2_fll_02.asm                    FLL+, Runs Internal DCO at 8MHz
msp430x41x2_LFxtal_nmi.asm                LFXT1 Oscillator Fault Detection
msp430x41x2_lpm3_vlo.asm                  Basic Clock, LPM3 Using WDT ISR, VLO ACLK
msp430x41x2_P1_01.asm                     Software Poll P1.4, Set P5.1 if P1.4 = 1
msp430x41x2_P1_02.asm                     Software Port Interrupt on P1.4 from LPM4
msp430x41x2_svs_01.asm                    SVS, POR @ 2.5V Vcc
msp430x41x2_svs_03.asm                    SVS, Toggle port 5.1 on Vcc < 2.8V
msp430x41x2_ta_01.asm                     Timer_A, Toggle P5.1, CCR0 Cont. Mode ISR, DCO SMCLK
msp430x41x2_ta_02.asm                     Timer_A, Toggle P5.1, CCR0 Up Mode ISR, DCO SMCLK
msp430x41x2_ta_03.asm                     Timer_A, Toggle P5.1, Overflow ISR, DCO SMCLK
msp430x41x2_ta_04.asm                     Timer_A, Toggle P5.1, Overflow ISR, 32kHz ACLK
msp430x41x2_ta_05.asm                     Timer_A, Toggle P5.1, CCR0 Up Mode ISR, 32kHz ACLK
msp430x41x2_ta_16.asm                     Timer_A, Timer_A, PWM TA1-2 Up Mode, DCO SMCLK
msp430x41x2_ta_17.asm                     Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
msp430x41x2_uscia0_irda_01.asm            USCI_A0 IrDA External Loopback Test, 4MHz SMCLK
msp430x41x2_uscia0_spi_09.asm             USCI_A0, SPI 3-Wire Master Incremented Data
msp430x41x2_uscia0_spi_10.asm             USCI_A0, SPI 3-Wire Slave Data Echo
msp430x41x2_uscia0_uart_115k.asm          USCI_A0, 115200 UART Echo ISR, DCO SMCLK                 
msp430x41x2_uscia0_uart_115k_lpm.asm      USCI_A0, 115200 UART Echo ISR, DCO SMCLK, LPM3            
msp430x41x2_uscia0_uart_2400.asm          USCI_A0, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK    
msp430x41x2_uscia0_uart_9600.asm          USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
msp430x41x2_uscia0_uart_9600_02.asm       Ultra-Low Pwr UART 9600 String, 32kHz ACLK             
msp430x41x2_uscib0_i2c_04.asm             Master RX single bytes from MSP430 Slave
msp430x41x2_uscib0_i2c_05.asm             Slave TX single bytes to MSP430 Master  
msp430x41x2_uscib0_i2c_06.asm             Master TX single bytes to MSP430 Slave  
msp430x41x2_uscib0_i2c_07.asm             Slave RX single bytes from MSP430 Master
msp430x41x2_uscib0_i2c_08.asm             USCI_B0 I2C Master TX multiple bytes to MSP430 Slave
msp430x41x2_uscib0_i2c_09.asm             USCI_B0 I2C Slave RX multiple bytes from MSP430 Master
msp430x41x2_uscib0_i2c_10.asm             USCI_B0 I2C Master RX multiple bytes from MSP430 Slave
msp430x41x2_uscib0_i2c_11.asm             USCI_B0 I2C Slave TX multiple bytes to MSP430 Master
msp430x41x2_uscib0_spi_09.asm             USCI_B0, SPI 3-Wire Master Incremented Data
msp430x41x2_uscib0_spi_10.asm             USCI_B0, SPI 3-Wire Slave Data Echo        
msp430x41x2_wdt_01.asm                    WDT, Toggle P5.1, Interval Overflow ISR, DCO SMCLK 
msp430x41x2_wdt_02.asm                    WDT, Toggle P5.1, Interval Overflow ISR, 32kHz ACLK
msp430x41x2_wdt_04.asm                    WDT+ Failsafe Clock, DCO SMCLK
msp430x41x2_wdt_06.asm                    WDT+ Failsafe Clock, 32kHz ACLK


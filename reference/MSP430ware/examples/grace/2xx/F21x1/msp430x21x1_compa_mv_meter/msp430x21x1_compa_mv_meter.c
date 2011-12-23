//*****************************************************************************
//   MSP430x21x1 Demo - Comp_A, Millivolt Meter
//
//   Description: This program demonstrates how to implement an MSP430F21x1/
//   F11x1 millivolt meter using Comparator_A. The measurement result can be
//   read out of variable 'ADCResult' using the watch window.
//
//             MSP430F21x1/11x1
//            -----------------
//       /|\ |              XIN|-
//        |  |                 |
//        ---|RST          XOUT|-
//           |                 |
//    AIN--->|P2.4             |
//           |                 |
//    +-10k--|P2.0             |
//    |      |                 |
//    +----- |P2.3             |
//    |      |                 |
//   ===2.2  |                 |
//    |      |                 |
//    ------ |VSS              |
//*****************************************************************************
/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

/*
 *  ======== main ========
 */

#define VCC_VALUE   (2980)                  // Actual system VCC (mV)
volatile unsigned int ADCResult;            // volatile to prevent opt.

void Init_Sys(void);                        // Function prototypes
unsigned int Meas_ADC(void);
unsigned int Meas_ADC2(void);

void main(int argc, char *argv[])
{
    CSL_init();

    while (1)
    {
      ADCResult = Meas_ADC();                 // Measure ADC
      _NOP();                                 // >>SET BREAKPOINT HERE<<
    }                                         // And read out 'ADCResult'
}

//-----------------------------------------------------------------------------
// Measure A/D Converter, return offset-compensated result
//-----------------------------------------------------------------------------
unsigned int Meas_ADC(void)
{
  unsigned int Result;

  CACTL1 = CAON;                            // Comparator on
  Result = Meas_ADC2();                     // Do 1st ADC conversion
  CACTL1 |= CAEX;                           // Invert comparator terminals
  Result += Meas_ADC2();                    // 2nd ADC, add inverted result
  CACTL1 = 0;                               // Comparator off

  return Result;
}

//-----------------------------------------------------------------------------
// A/D Converter Helper Function
//
// Attn: The loop cycle count has to be equal for both decision paths
//       of the if() statement, otherwise the measurement result will
//       not be accurate. It has been found with IAR V3.30A, that the
//       code below will implement this, even independent of the
//       C compiler optimization settings. Another approach would be
//       implementing the entire function in assembly language.
//-----------------------------------------------------------------------------
unsigned int Meas_ADC2(void)
{
  unsigned int Counter = VCC_VALUE / 2;
  unsigned int Result = 0;

  P2OUT |= 0x01;                            // Set power to capacitor
  while (!(CACTL2 & CAOUT));                // Wait for CAOUT to get set

  do
  {
    if (CACTL2 & CAOUT)                     // Comparator high/low?
    {
      P2OUT &= ~0x01;                       // Remove power if high
    }
    else
    {
      P2OUT |= 0x01;                        // Set power if low
      Result++;                             // Measure the 'ON' time
      _NOP();                               // Timing adjustment
    }
  } while (--Counter);                      // Decrement and loop

  P2OUT &= ~0x01;                           // Remove power from cap

  return Result;
}

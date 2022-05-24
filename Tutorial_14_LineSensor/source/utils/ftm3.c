/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         Common settings of the FTM3
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          15.04.2020
 *
 *--------------------------------------------------------------------
 */

#include "platform.h"
#include "ftm3.h"
#if !SOLUTION

/**
 * Default handler is called if there is no handler for the FTM0 channel or tof interrupt
 */
void Default_Handler_FTM3()
{
  __asm("bkpt"); // Still a hacker? ;-)
}


void FTM3CH0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3CH1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3CH2_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3CH3_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3CH4_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3CH5_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3CH6_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3CH7_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3TOF_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));


#define CHF_CHIE_MASK       (FTM_CnSC_CHF_MASK | FTM_CnSC_CHIE_MASK)
#define TOF_TOIE_MASK       (FTM_SC_TOF_MASK | FTM_SC_TOIE_MASK)

/**
 * Interrupt handler to distribute the different interrupt sources of the FTM:
 * - channel 0..7
 * - timer overflow
 */
void FTM3_IRQHandler(void)
{
  if ((FTM3->CONTROLS[0].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK) FTM3CH0_IRQHandler();
  if ((FTM3->CONTROLS[1].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK) FTM3CH1_IRQHandler();
  if ((FTM3->CONTROLS[2].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK) FTM3CH2_IRQHandler();
  if ((FTM3->CONTROLS[3].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK) FTM3CH3_IRQHandler();
  if ((FTM3->CONTROLS[4].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK) FTM3CH4_IRQHandler();
  if ((FTM3->CONTROLS[5].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK) FTM3CH5_IRQHandler();
  if ((FTM3->CONTROLS[6].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK) FTM3CH6_IRQHandler();
  if ((FTM3->CONTROLS[7].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK) FTM3CH7_IRQHandler();
  if ((FTM3->SC & TOF_TOIE_MASK) == TOF_TOIE_MASK) FTM3TOF_IRQHandler();
}

void ftm3_init(void)
{
  // ftm3 configuration is done with the config tool
  // enabling clockgate needs to be done here
  SIM->SCGC6 |= SIM_SCGC6_FTM3(1);

  // configuration with the tool automatically sets
  // FTM_MODE_FTMEN_MASK, which will undermine the CnV
  // setting, therefore, this needs to be reset
  FTM3->MODE &= ~FTM_MODE_FTMEN_MASK;

  // sets the modulo, can not be done with the config tool
  FTM3->MOD = FTM3_MODULO;
}
#endif

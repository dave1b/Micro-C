/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         Exercise 05.1 - Poling, Interrupts & Timer
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          12.03.20018
 *
 * $Id: mainML.c 71 2018-04-05 09:03:44Z zajost $
 *
 *--------------------------------------------------------------------
 */
#include "platform.h"
#if SOLUTION

#define TICKS_500MS                 (15624)



void main(void)
{
  SIM->SCGC6 |= SIM_SCGC6_FTM3(1);              // set clockgating for FTM3
  FTM3->SC = FTM_SC_CLKS(1) | FTM_SC_PS(4);

  // set TimerChannel
  FTM3->CONTROLS[4].CnSC = FTM_CnSC_MSB(1) | FTM_CnSC_ELSB(1) | FTM_CnSC_ELSA(0);
  FTM3->CONTROLS[5].CnSC = FTM_CnSC_MSB(1) | FTM_CnSC_ELSB(1) | FTM_CnSC_ELSA(0);
  FTM3->CONTROLS[6].CnSC = FTM_CnSC_MSB(1) | FTM_CnSC_ELSB(1) | FTM_CnSC_ELSA(0);

  // Mux LED
  PORTC->PCR[8] = PORT_PCR_MUX(3);
  PORTC->PCR[9] = PORT_PCR_MUX(3);
  PORTC->PCR[10] = PORT_PCR_MUX(3);

  // set TimerChannel Value
  FTM3->CONTROLS[4].CnV = 30000;		// LED grün
  FTM3->CONTROLS[5].CnV = 1;			// LED rot
  FTM3->CONTROLS[6].CnV = 10000;		// LED blau

// Never leave main
  for (;;){}
}
#endif

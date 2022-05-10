/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         Exercise 02 - GPIO C
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          18.02.20018
 *
 *--------------------------------------------------------------------
 */
#include "platform.h"

#if !SOLUTION

/**
 * Application entry point.
 */
int main(void)
{
  uint32_t data;

  PORTC->PCR[8] = PORT_PCR_MUX(1);
  PORTC->PCR[9] = PORT_PCR_MUX(1);
  PORTC->PCR[10] = PORT_PCR_MUX(1);

  PORTB->PCR[1] = PORT_PCR_MUX(1);
  PORTB->PCR[2] = PORT_PCR_MUX(1);
  PORTB->PCR[3] = PORT_PCR_MUX(1);

  GPIOC->PDDR |= ((1<<8) | (1<<9) | (1<<10));        	// PortDataDirectionRegister Port C

  PORTB->PCR[1] |= PORT_PCR_PE(1) | PORT_PCR_PS(1); 	// PortControlRegister PortB, Pin1
  PORTB->PCR[2] |= PORT_PCR_PE(1) | PORT_PCR_PS(1);
  PORTB->PCR[3] |= PORT_PCR_PE(1) | PORT_PCR_PS(1);

  for(;;)
  {
    data = GPIOB->PDIR;
    data <<= 7; 		// schiebt data um 7 Stellen 1->8
                		//data = ~data;
    GPIOC->PDOR = data;
  }
}
#endif

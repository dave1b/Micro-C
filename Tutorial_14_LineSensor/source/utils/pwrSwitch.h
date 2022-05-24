/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         Power-Switch helper functions
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          17.04.2020
 *
 *--------------------------------------------------------------------
 */

#ifndef SOURCES_UTILS_PWRSWITCH_H_
#define SOURCES_UTILS_PWRSWITCH_H_



/**
 * Initializes the Power Switch
 */
#define pwr_switch_init()     (PORTE->PCR[0] = PORT_PCR_MUX(1) | PORT_PCR_PE(1) | PORT_PCR_PS(1))


/**
 * Returns the state of the PowerSwitch
 * 0: Power Switch is in the default position
 * 1: Power Switch is enabled
 */
#define pwr_switch_enabled()  (!(GPIOE->PDIR & (1<<0)))



#endif /* SOURCES_UTILS_PWRSWITCH_H_ */

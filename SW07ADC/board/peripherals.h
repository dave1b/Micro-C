/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "fsl_common.h"
#include "fsl_i2c.h"
#include "fsl_adc16.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals functional group */
/* BOARD_InitPeripherals defines for I2C0 */
/* Definition of peripheral ID */
#define I2C0_PERIPHERAL I2C0
/* Definition of the clock source */
#define I2C0_CLOCK_SOURCE I2C0_CLK_SRC
/* Definition of the clock source frequency */
#define I2C0_CLK_FREQ CLOCK_GetFreq(I2C0_CLOCK_SOURCE)
/* Alias for ADC1 peripheral */
#define ADC1_PERIPHERAL ADC1
/* ADC1 interrupt vector ID (number). */
#define ADC1_IRQN ADC0_IRQn
/* ADC1 interrupt handler identifier. */
#define ADC1_IRQHANDLER 
/* Channel 0 (SE.19) conversion control group. */
#define ADC1_CH0_CONTROL_GROUP 0
/* Channel 1 (SE.0) conversion control group. */
#define ADC1_CH1_CONTROL_GROUP 0
/* Channel 2 (SE.26) conversion control group. */
#define ADC1_CH2_CONTROL_GROUP 0

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern const i2c_master_config_t I2C0_config;
extern adc16_channel_config_t ADC1_channelsConfig[3];
extern const adc16_config_t ADC1_config;
extern const adc16_channel_mux_mode_t ADC1_muxMode;

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/

void BOARD_InitPeripherals(void);

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PERIPHERALS_H_ */
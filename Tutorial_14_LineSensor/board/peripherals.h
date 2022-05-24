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
#include "fsl_adc16.h"
#include "fsl_clock.h"
#include "fsl_ftm.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_i2c.h"
#include "fsl_uart.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals functional group */
/* Alias for ADC1 peripheral */
#define ADC1_PERIPHERAL ADC1
/* ADC1 interrupt vector ID (number). */
#define ADC1_IRQN ADC1_IRQn
/* ADC1 interrupt handler identifier. */
#define ADC1_IRQHANDLER ADC1_IRQHandler
/* Definition of peripheral ID */
#define FTM0_PERIPHERAL FTM0
/* Definition of the clock source frequency */
#define FTM0_CLOCK_SOURCE 250000UL
/* FTM0 interrupt vector ID (number). */
#define FTM0_IRQN FTM0_IRQn
/* FTM0 interrupt vector priority. */
#define FTM0_IRQ_PRIORITY 8
/* FTM0 interrupt handler identifier. */
#define FTM0_IRQHANDLER FTM0_IRQHandler
/* Definition of peripheral ID */
#define FTM3_PERIPHERAL FTM3
/* Definition of the clock source frequency */
#define FTM3_CLOCK_SOURCE CLOCK_GetFreq(kCLOCK_BusClk)
/* FTM3 interrupt vector ID (number). */
#define FTM3_IRQN FTM3_IRQn
/* FTM3 interrupt vector priority. */
#define FTM3_IRQ_PRIORITY 12
/* FTM3 interrupt handler identifier. */
#define FTM3_IRQHANDLER FTM3_IRQHandler
/* Alias for GPIOB peripheral */
#define GPIOB_GPIO GPIOB
/* Alias for PORTB */
#define GPIOB_PORT PORTB
/* GPIOB interrupt vector ID (number). */
#define GPIOB_IRQN PORTB_IRQn
/* GPIOB interrupt handler identifier. */
#define GPIOB_IRQHANDLER PORTB_IRQHandler
/* BOARD_InitPeripherals defines for I2C0 */
/* Definition of peripheral ID */
#define I2C0_PERIPHERAL I2C0
/* Definition of the clock source */
#define I2C0_CLOCK_SOURCE I2C0_CLK_SRC
/* Definition of the clock source frequency */
#define I2C0_CLK_FREQ CLOCK_GetFreq(I2C0_CLOCK_SOURCE)
/* Definition of peripheral ID */
#define UART0_PERIPHERAL UART0
/* Definition of the clock source frequency */
#define UART0_CLOCK_SOURCE CLOCK_GetFreq(UART0_CLK_SRC)
/* UART0 interrupt vector ID (number). */
#define UART0_SERIAL_RX_TX_IRQN UART0_RX_TX_IRQn
/* UART0 interrupt vector priority. */
#define UART0_SERIAL_RX_TX_IRQ_PRIORITY 8
/* UART0 interrupt handler identifier. */
#define UART0_SERIAL_RX_TX_IRQHANDLER UART0_RX_TX_IRQHandler
/* UART0 interrupt vector ID (number). */
#define UART0_SERIAL_ERROR_IRQN UART0_ERR_IRQn
/* UART0 interrupt vector priority. */
#define UART0_SERIAL_ERROR_IRQ_PRIORITY 8
/* UART0 interrupt handler identifier. */
#define UART0_SERIAL_ERROR_IRQHANDLER UART0_ERR_IRQHandler

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern adc16_channel_config_t ADC1_channelsConfig[3];
extern const adc16_config_t ADC1_config;
extern const adc16_channel_mux_mode_t ADC1_muxMode;
extern const adc16_hardware_average_mode_t ADC1_hardwareAverageMode;
extern const ftm_config_t FTM0_config;
extern const ftm_config_t FTM3_config;
extern const i2c_master_config_t I2C0_config;
extern const uart_config_t UART0_config;

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

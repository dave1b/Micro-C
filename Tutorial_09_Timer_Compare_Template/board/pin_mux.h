/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/*! @name PORTA15 (number 45), RED_R_R
  @{ */
#define BOARD_LED_RED_R_R_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_LED_RED_R_R_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_LED_RED_R_R_PIN 15U    /*!<@brief PORTA pin index: 15 */
                                     /* @} */

/*! @name PORTA16 (number 46), RED_R_R_BREAK
  @{ */
#define BOARD_LED_RED_R_R_BREAK_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_LED_RED_R_R_BREAK_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_LED_RED_R_R_BREAK_PIN 16U    /*!<@brief PORTA pin index: 16 */
                                           /* @} */

/*! @name PORTA17 (number 47), RED_R_L
  @{ */
#define BOARD_LED_RED_R_L_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_LED_RED_R_L_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_LED_RED_R_L_PIN 17U    /*!<@brief PORTA pin index: 17 */
                                     /* @} */

/*! @name PORTB20 (number 66), RED_R_L_BREAK
  @{ */
#define BOARD_LED_RED_R_L_BREAK_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_LED_RED_R_L_BREAK_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_LED_RED_R_L_BREAK_PIN 20U    /*!<@brief PORTB pin index: 20 */
                                           /* @} */

/*! @name PORTC8 (number 80), GREEN_F_L
  @{ */
#define BOARD_LED_GREEN_F_L_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_LED_GREEN_F_L_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_LED_GREEN_F_L_PIN 8U     /*!<@brief PORTC pin index: 8 */
                                       /* @} */

/*! @name PORTC9 (number 81), RED_F_L
  @{ */
#define BOARD_LED_RED_F_L_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_LED_RED_F_L_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_LED_RED_F_L_PIN 9U     /*!<@brief PORTC pin index: 9 */
                                     /* @} */

/*! @name PORTC10 (number 82), BLUE_F_L
  @{ */
#define BOARD_LED_BLUE_F_L_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_LED_BLUE_F_L_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_LED_BLUE_F_L_PIN 10U    /*!<@brief PORTC pin index: 10 */
                                      /* @} */

/*! @name PORTC11 (number 83), GREEN_F_R
  @{ */
#define BOARD_LED_GREEN_F_R_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_LED_GREEN_F_R_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_LED_GREEN_F_R_PIN 11U    /*!<@brief PORTC pin index: 11 */
                                       /* @} */

/*! @name PORTD2 (number 95), RED_F_R
  @{ */
#define BOARD_LED_RED_F_R_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_LED_RED_F_R_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_LED_RED_F_R_PIN 2U     /*!<@brief PORTD pin index: 2 */
                                     /* @} */

/*! @name PORTD3 (number 96), BLUE_F_R
  @{ */
#define BOARD_LED_BLUE_F_R_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_LED_BLUE_F_R_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_LED_BLUE_F_R_PIN 3U     /*!<@brief PORTD pin index: 3 */
                                      /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_LED(void);

/*! @name PORTB0 (number 53), RIGHT
  @{ */
#define BOARD_JOYSTICK_RIGHT_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_JOYSTICK_RIGHT_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_JOYSTICK_RIGHT_PIN 0U     /*!<@brief PORTB pin index: 0 */
                                        /* @} */

/*! @name PORTB1 (number 54), DOWN
  @{ */
#define BOARD_JOYSTICK_DOWN_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_JOYSTICK_DOWN_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_JOYSTICK_DOWN_PIN 1U     /*!<@brief PORTB pin index: 1 */
                                       /* @} */

/*! @name PORTB2 (number 55), UP
  @{ */
#define BOARD_JOYSTICK_UP_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_JOYSTICK_UP_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_JOYSTICK_UP_PIN 2U     /*!<@brief PORTB pin index: 2 */
                                     /* @} */

/*! @name PORTB3 (number 56), PUSH
  @{ */
#define BOARD_JOYSTICK_PUSH_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_JOYSTICK_PUSH_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_JOYSTICK_PUSH_PIN 3U     /*!<@brief PORTB pin index: 3 */
                                       /* @} */

/*! @name PORTB9 (number 57), LEFT
  @{ */
#define BOARD_JOYSTICK_LEFT_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_JOYSTICK_LEFT_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_JOYSTICK_LEFT_PIN 9U     /*!<@brief PORTB pin index: 9 */
                                       /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_JOYSTICK(void);

/*! @name PORTB10 (number 58), UART_TX
  @{ */
#define BOARD_BL_UART_TX_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_BL_UART_TX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_BL_UART_TX_PIN 10U    /*!<@brief PORTB pin index: 10 */
                                    /* @} */

/*! @name PORTB11 (number 59), UART_RX
  @{ */
#define BOARD_BL_UART_RX_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_BL_UART_RX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_BL_UART_RX_PIN 11U    /*!<@brief PORTB pin index: 11 */
                                    /* @} */

/*! @name PORTB16 (number 62), MODE
  @{ */
#define BOARD_BL_MODE_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_BL_MODE_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_BL_MODE_PIN 16U    /*!<@brief PORTB pin index: 16 */
                                 /* @} */

/*! @name PORTB17 (number 63), CONNECTED
  @{ */
#define BOARD_BL_CONNECTED_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_BL_CONNECTED_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_BL_CONNECTED_PIN 17U    /*!<@brief PORTB pin index: 17 */
                                      /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_BL(void);

/*! @name ADC1_DP0 (number 20), U_BAT
  @{ */
/* @} */

/*! @name ADC1_DM0 (number 21), I_TOT
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_ADC(void);

#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */

/*! @name PORTA1 (number 35), UART0_RX
  @{ */
#define BOARD_UART_BOARD_UART0_RX_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_UART_BOARD_UART0_RX_PIN 1U     /*!<@brief PORTA pin index: 1 */
                                             /* @} */

/*! @name PORTA2 (number 36), UART0_TX
  @{ */
#define BOARD_UART_BOARD_UART0_TX_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_UART_BOARD_UART0_TX_PIN 2U     /*!<@brief PORTA pin index: 2 */
                                             /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_UART(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

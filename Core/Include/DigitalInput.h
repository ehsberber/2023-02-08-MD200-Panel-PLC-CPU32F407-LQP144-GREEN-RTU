/*
 * DigitalInput.h
 *
 *  Created on: Jan 6, 2022
 *      Author: SBerber
 */

#ifndef APPLICATION_USER_HEADER_DIGITALINPUT_H_
#define APPLICATION_USER_HEADER_DIGITALINPUT_H_


void DigitalInput(void);

#define PLC_ONBOARD_DI_0_PORT		GPIOG
#define PLC_ONBOARD_DI_0_PIN		GPIO_PIN_3

#define PLC_ONBOARD_DI_1_PORT		GPIOG
#define PLC_ONBOARD_DI_1_PIN		GPIO_PIN_2

#define PLC_ONBOARD_DI_2_PORT		GPIOD
#define PLC_ONBOARD_DI_2_PIN		GPIO_PIN_15

#define PLC_ONBOARD_DI_3_PORT		GPIOD
#define PLC_ONBOARD_DI_3_PIN		GPIO_PIN_14

#define PLC_ONBOARD_DI_4_PORT		GPIOD
#define PLC_ONBOARD_DI_4_PIN		GPIO_PIN_10

#define PLC_ONBOARD_DI_5_PORT		GPIOD
#define PLC_ONBOARD_DI_5_PIN		GPIO_PIN_11

#define PLC_ONBOARD_DI_6_PORT		GPIOD
#define PLC_ONBOARD_DI_6_PIN		GPIO_PIN_12

#define PLC_ONBOARD_DI_7_PORT		GPIOD
#define PLC_ONBOARD_DI_7_PIN		GPIO_PIN_13

#define PLC_ONBOARD_DI_8_PORT		GPIOG
#define PLC_ONBOARD_DI_8_PIN		GPIO_PIN_0

#define PLC_ONBOARD_DI_9_PORT		GPIOG
#define PLC_ONBOARD_DI_9_PIN		GPIO_PIN_1

#define PLC_ONBOARD_DI_10_PORT		GPIOE
#define PLC_ONBOARD_DI_10_PIN		GPIO_PIN_10

#define PLC_ONBOARD_DI_11_PORT		GPIOE
#define PLC_ONBOARD_DI_11_PIN		GPIO_PIN_11

#define PLC_ONBOARD_DI_12_PORT		GPIOE
#define PLC_ONBOARD_DI_12_PIN		GPIO_PIN_12

#define PLC_ONBOARD_DI_13_PORT		GPIOE
#define PLC_ONBOARD_DI_13_PIN		GPIO_PIN_13

#define PLC_ONBOARD_DI_14_PORT		GPIOE
#define PLC_ONBOARD_DI_14_PIN		GPIO_PIN_14

#define PLC_ONBOARD_DI_15_PORT		GPIOE
#define PLC_ONBOARD_DI_15_PIN		GPIO_PIN_15


#define   DI_NO_ESB1                                                       0                                                                               //
#define   DI_NO_ESB2                                                       1                                                                               //
#define   DI_NO_ESB3                                                       2                                                                               //
#define   DI_NO_ESB4                                                       3                                                                               //
#define   DI_NO_PUMP1_IGNITION                                             4                                                                               //
#define   DI_NO_START_BUTTON                                               5                                                                               //
#define   DI_NO_THERMIC_RELAY                                              6                                                                               //
#define   DI_NO_PUMP2_IGNITION                                             7                                                                               //



#endif /* APPLICATION_USER_HEADER_DIGITALINPUT_H_ */

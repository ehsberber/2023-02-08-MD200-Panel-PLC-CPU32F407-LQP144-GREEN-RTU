/*
 * Leds.h
 *
 *  Created on: Nov 18, 2022
 *      Author: Sezgin Berber
 */

#ifndef INCLUDE_LEDS_H_
#define INCLUDE_LEDS_H_

	#include "Registers.h"

	#define LED_COUNT												3
	#define LED_STATUS_NONE											0
	#define LED_STATUS_ON											1
	#define LED_STATUS_OFF											2

	#define	LED_RED													0
	#define	LED_GREEN												1
	#define	LED_BLUE												2

	#define	LED_ALL													16

	#define LED_RED_ON			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET)
	#define LED_RED_OFF			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET)

	#define LED_GREEN_ON		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET)
	#define LED_GREEN_OFF		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET)

	#define LED_BLUE_ON			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET)
	#define LED_BLUE_OFF		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET)


	#define LED_RED_STATE		{switch(GPIOE->ODR & GPIO_PIN_1) { case 0:  return 0; break; default: return 1; break;}}
	#define LED_GREEN_STATE		(GPIOB->ODR & GPIO_PIN_9)
	#define LED_BLUE_STATE		(GPIOB->ODR & GPIO_PIN_8)


	//#define LED_STATE(x)  switch(x) { case LED_RED: return(LED_RED_STATE);  break; case LED_GREEN: return(LED_GREEN_STATE);  break; case LED_BLUE: return(LED_BLUE_STATE);  break;  }



	#define LED_ON(x)  { switch(x) { case LED_RED: LED_RED_ON;  break; case LED_GREEN: LED_GREEN_ON;  break; case LED_BLUE: LED_BLUE_ON;  break;  }  }
	#define LED_OFF(x) { switch(x) { case LED_RED: LED_RED_OFF; break; case LED_GREEN: LED_GREEN_OFF; break; case LED_BLUE: LED_BLUE_OFF; break;  }  }

	void Leds(void);
	union unionLeds LedsState(unsigned short LedNo);
	void SystemStateLeds(unsigned char Restart);

#endif /* INCLUDE_LEDS_H_ */

/*
 * TimerProcess.h
 *
 *  Created on: Feb 3, 2022
 *      Author: SBerber
 */

#ifndef APPLICATION_USER_HEADER_TIMERPROCESS
#define APPLICATION_USER_HEADER_TIMERPROCESS

	#include "Registers.h"

	#define TIMER_COUNT						10
	#define TIM_NO_PLC_PROCESS_START		0
	#define TIM_NO_ALERT_RUN				1
	#define TIM_NO_MODEM					2
	#define	TIM_NO_DATA_SEND				3
	#define	TIM_NO_NO_DATA_ACTIVITY			4
	#define TIM_NO_MODBUS_ACTIVE_TIMEOUT	5
	#define  TIM_NO_LED_BLUE				6
	#define  TIM_NO_LED_RED					7
	#define  TIM_NO_LED_GREEN				8

	void TimerProcess(void);
	void TimerInitialize(void);
	void TimerStop(unsigned short TimerNo);
	void TimerStart(unsigned short TimerNo, unsigned int Timeout);
	void TimerRestart(unsigned short TimerNo, unsigned int Timeout);
	void TimerControlProcess(void);


#endif

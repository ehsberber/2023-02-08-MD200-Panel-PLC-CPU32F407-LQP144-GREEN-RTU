/*
 * LedSystemOnline.c
 *
 *  Created on: Nov 18, 2022
 *      Author: Sezgin Berber
 */
#include "MicroPeripheral.h"
#include "Registers.h"
#include "Leds.h"
#include "SystemStates.h"


extern strcPLC Plc;
extern strcREGISTERS Registers;
extern strcSYSTEM System;

unsigned short LedTimerNo(unsigned short LedNo)
{
	unsigned short TimerNo=0;
	switch(LedNo)
		{
			case LED_BLUE:
					 TimerNo = TIM_NO_LED_BLUE;
				 break;

			case LED_GREEN:
				 	 TimerNo = TIM_NO_LED_GREEN;
				 break;

			case LED_RED:
				 	 TimerNo = TIM_NO_LED_RED;
				 break;
		}
	return TimerNo;
}


union unionLeds LedsState(unsigned short LedNo)
{

	union unionLeds LedState;

	LedState.LedsAll = 0;

	switch(LedNo)
		{
			case LED_RED:
					if(GPIOE->ODR & GPIO_PIN_1) {LedState.LED.Red = 1;} 	else	{ LedState.LED.Red = 0; }
				break;

			case LED_GREEN:
					if(GPIOB->ODR & GPIO_PIN_9) {LedState.LED.Green = 1;} 	else	{ LedState.LED.Green = 0; }
				break;

			case LED_BLUE:
					if(GPIOB->ODR & GPIO_PIN_8) {LedState.LED.Blue = 1;} 	else	{ LedState.LED.Blue = 0; }
				break;

			case LED_ALL:
					if(GPIOE->ODR & GPIO_PIN_1) {LedState.LED.Red = 1;} 	else	{ LedState.LED.Red = 0; }
					if(GPIOB->ODR & GPIO_PIN_9) {LedState.LED.Green = 1;} 	else	{ LedState.LED.Green = 0; }
					if(GPIOB->ODR & GPIO_PIN_8) {LedState.LED.Blue = 1;} 	else	{ LedState.LED.Blue = 0; }

				break;
		}

	//LedData = (unsigned int)LedState;
	return LedState;
}



void Leds(void)
{
	unsigned short LedNo;
	unsigned short TimerNo;
	static unsigned short LedStatus[LED_COUNT] = {LED_STATUS_NONE,LED_STATUS_NONE,LED_STATUS_NONE};

	for(LedNo=0;LedNo<LED_COUNT; LedNo++)
		{
			TimerNo = LedTimerNo (LedNo);

			switch(*Plc.Led[LedNo].Status)
				{
					case LED_STATUS_NONE:
							LED_OFF(LedNo);
						break;

					case LED_STATUS_ON:

							if(LedStatus[LedNo] == LED_STATUS_NONE)
								{
									LED_ON(LedNo);
									TimerRestart(TimerNo,  *Plc.Led[LedNo].OnTime );
								}

							if (Registers.Timers.Control[TimerNo]->Timeout)
								{

									if( *Plc.Led[LedNo].OffTime > 0 )
										{
											LED_OFF(LedNo);

											TimerRestart(TimerNo,  *Plc.Led[LedNo].OffTime );

											*Plc.Led[LedNo].Status = LED_STATUS_OFF;
										}
									else
										{
											TimerRestart(TimerNo,  *Plc.Led[LedNo].OnTime );
											LED_ON(LedNo);
										}
								}

						break;

					case LED_STATUS_OFF:

						if(LedStatus[LedNo] == LED_STATUS_NONE)
							{
								LED_OFF(LedNo);
								TimerRestart(TimerNo,  *Plc.Led[LedNo].OffTime );
							}

						if (Registers.Timers.Control[TimerNo]->Timeout)
							{
								if( *Plc.Led[LedNo].OnTime > 0 )
									{
										LED_ON(LedNo);

										TimerRestart(TimerNo,  *Plc.Led[LedNo].OnTime );

										*Plc.Led[LedNo].Status = LED_STATUS_ON;
									}
								else
									{
										TimerRestart(TimerNo,  *Plc.Led[LedNo].OffTime );
										LED_OFF(LedNo);
									}
							}
						break;
				}
			LedStatus[LedNo] = *Plc.Led[LedNo].Status;
		}
}


void SystemStateLeds(unsigned char Restart)
{
	if (!Restart) return;

	switch(*System.State)
		{
			case SYSTEM_STATE_STOP:
					//
					// Led
					//
					*Plc.Led[LED_RED].OnTime 	= 10;
					*Plc.Led[LED_RED].OffTime 	= 10;
					*Plc.Led[LED_RED].Status 	= LED_STATUS_ON;
					//
					// LED GREEN
					//
					*Plc.Led[LED_GREEN].OnTime 	= 00;
					*Plc.Led[LED_GREEN].OffTime = 30;
					*Plc.Led[LED_GREEN].Status 	= LED_STATUS_OFF;
					//
					// LED BLUE
					//
					*Plc.Led[LED_BLUE].OnTime 	= 00;
					*Plc.Led[LED_BLUE].OffTime 	= 30;
					*Plc.Led[LED_BLUE].Status 	= LED_STATUS_OFF;
				break;


			case SYSTEM_STATE_INPROGRESS:
					//
					// LED RED
					//
					*Plc.Led[LED_RED].OnTime 	= 0;
					*Plc.Led[LED_RED].OffTime 	= 10;
					*Plc.Led[LED_RED].Status 	= LED_STATUS_OFF;
					//
					// LED GREEN
					//
					*Plc.Led[LED_GREEN].OnTime 	= 40;
					*Plc.Led[LED_GREEN].OffTime = 10;
					*Plc.Led[LED_GREEN].Status 	= LED_STATUS_OFF;
					//
					// LED BLUE
					//
					*Plc.Led[LED_BLUE].OnTime 	= 00;
					*Plc.Led[LED_BLUE].OffTime 	= 30;
					*Plc.Led[LED_BLUE].Status 	= LED_STATUS_OFF;

				break;


			case SYSTEM_STATE_EMERGENCY_STOP:
					//
					// lED
					//
					*Plc.Led[LED_RED].OnTime 	= 10;
					*Plc.Led[LED_RED].OffTime 	= 10;
					*Plc.Led[LED_RED].Status 	= LED_STATUS_ON;
					//
					// LED GREEN
					//
					*Plc.Led[LED_GREEN].OnTime 	= 00;
					*Plc.Led[LED_GREEN].OffTime = 30;
					*Plc.Led[LED_GREEN].Status 	= LED_STATUS_OFF;
					//
					// LED BLUE
					//
					*Plc.Led[LED_BLUE].OnTime 	= 00;
					*Plc.Led[LED_BLUE].OffTime 	= 30;
					*Plc.Led[LED_BLUE].Status 	= LED_STATUS_OFF;
				break;

		}
}

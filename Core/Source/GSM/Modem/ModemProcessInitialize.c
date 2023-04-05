/*
 * ModemProcessInitialize.c
 *
 *  Created on: Feb 3, 2023
 *      Author: Sezgin Berber
 */
#include "Registers.h"

#include "Peripheral.h"
#include "TimerProcess.h"
#include "Uarts.h"
#include "UartPortProcess.h"
#include "Modem.h"



extern strcUART Uart[UART_COUNT];
extern strcGSM GSM;

void ModemInitializeNext(void)
{
	if(GSM.Modem.Response->ResponseState.Ok)
		{
			switch(*GSM.Modem.CommandNo)
				{
					case cmdAT:
							*GSM.Modem.InitializeState = MODEM_INITIALIZE_STATE_ATE;
						break;

					case cmdATE:
							*GSM.Modem.InitializeState = MODEM_INITIALIZE_STATE_CMGF;
						break;

					case cmdCMGF:
							GSM.Modem.Response->ResponseState.Initialize = INITIALIZE_STATE_OK;
							*GSM.Modem.InitializeState = MODEM_INITIALIZE_STATE_NONE;
						break;

					default:
						*GSM.Modem.InitializeState = MODEM_INITIALIZE_STATE_NONE;
					break;

				}
		}
	else
	{
		if(GSM.Modem.Response->ResponseState.Error)
			{
				switch(*GSM.Modem.CommandNo)
					{
						case cmdAT:
								*GSM.Modem.InitializeState = MODEM_INITIALIZE_STATE_AT;
							break;

						case cmdATE:
								*GSM.Modem.InitializeState = MODEM_INITIALIZE_STATE_ATE;
							break;

						case cmdCMGF:
								GSM.Modem.Response->ResponseState.Initialize = INITIALIZE_STATE_OK;
								*GSM.Modem.InitializeState = MODEM_INITIALIZE_STATE_CMGF;
							break;
						default:
							*GSM.Modem.InitializeState = MODEM_INITIALIZE_STATE_NONE;
						break;

					}
			}
	}
}

void ModemInitialize(void)
{
	switch(*GSM.Modem.InitializeState)
		{
			case MODEM_INITIALIZE_STATE_NONE:


					*GSM.Modem.InitializeState = MODEM_INITIALIZE_STATE_AT;
					*GSM.Modem.CommandCounter = 0;
				break;

			case MODEM_INITIALIZE_STATE_AT:
					*GSM.Modem.CommandNo = cmdAT;
					*GSM.Modem.CommandCounter = 0;

					ModemCommandPrepare();

					uarttxstring(UART_NO_MODEM, GSM.Modem.Command, UART_TX_NO_CR_LF);
					//
					// Set Modem Timer
					//
					TimerRestart(TIM_NO_MODEM, 30 );
					*Uart[UART_NO_MODEM].Offset = 0;

					*GSM.Modem.InitializeState = MODEM_INITIALIZE_STATE_CHECK_RESPONSE;
				break;

			case MODEM_INITIALIZE_STATE_ATE:
					*GSM.Modem.CommandNo = cmdATE;

					*GSM.Modem.CommandCounter = *GSM.Modem.CommandCounter + 1;

					ModemCommandPrepare();

					uarttxstring(UART_NO_MODEM, GSM.Modem.Command, UART_TX_NO_CR_LF);
					//
					// Set Modem Timer
					//
					TimerRestart(TIM_NO_MODEM, 30 );
					*Uart[UART_NO_MODEM].Offset = 0;

					*GSM.Modem.InitializeState = MODEM_INITIALIZE_STATE_CHECK_RESPONSE;
				break;

			case MODEM_INITIALIZE_STATE_CMGF:
					*GSM.Modem.CommandNo = cmdCMGF;

					*GSM.Modem.CommandCounter = *GSM.Modem.CommandCounter + 1;

					ModemCommandPrepare();

					uarttxstring(UART_NO_MODEM, GSM.Modem.Command, UART_TX_NO_CR_LF);
					//
					// Set Modem Timer
					//
					TimerRestart(TIM_NO_MODEM, 30 );
					*Uart[UART_NO_MODEM].Offset = 0;

					*GSM.Modem.InitializeState = MODEM_INITIALIZE_STATE_CHECK_RESPONSE;
				break;

			case MODEM_INITIALIZE_STATE_CHECK_RESPONSE:
					ModemInitializeNext();

				break;
		}
}

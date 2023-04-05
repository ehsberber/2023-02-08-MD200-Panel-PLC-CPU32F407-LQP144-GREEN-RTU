/*
 * Default.c
 *
 *  Created on: Jan 6, 2022
 *      Author: SBerber
 */


#include "Registers.h"
#include "Uarts.h"
#include "Constant.h"
#include "MicroPeripheral.h"
#include "DataPositionHolding.h"
#include "DigitalOutput.h"
#include "DigitalOutputMicroLayer.h"
#include "String.h"
#include "Peripheral.h"
#include "DefaultParameter.h"

extern strcREGISTERS  Registers;
extern strcPLC Plc;
extern strcUART Uart[UART_COUNT];


extern unsigned short *UartDataEnd[UART_COUNT];


//void Default_Peripheral(void)
//{
//	*(unsigned int *)&Registers.Holding[HA_DI_DEBUG_MODE ] = 0x0000;
//
//
//	*Plc.Peripheral.AnalogInput.Scale[AI_CHANNEL_NO_PRESSURE].Bottom 			= 0.0;
//	*Plc.Peripheral.AnalogInput.Scale[AI_CHANNEL_NO_PRESSURE].Top 				= 100.0;
//	*Plc.Peripheral.AnalogInput.Calibration[AI_CHANNEL_NO_PRESSURE].Constant 	= 1.0;
//	*Plc.Peripheral.AnalogInput.Calibration[AI_CHANNEL_NO_PRESSURE].Offset 		= 0.0;
//}

void DefaultProcess(void)
{
	unsigned char Default_PIN_State;
	unsigned short i;

	Default_PIN_State = HAL_GPIO_ReadPin(PLC_DEFAULT_BUTTON_PORT, PLC_DEFAULT_BUTTON_PORT_PIN);

	if (Default_PIN_State == 0)
	{

		HAL_GPIO_WritePin( GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin( GPIOD, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_GPIO_WritePin( PLC_ONBOARD_DO_0_PORT, PLC_ONBOARD_DO_0_PIN, GPIO_PIN_SET);


		 HAL_Delay(2000);

		HAL_GPIO_WritePin( GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin( GPIOD, GPIO_PIN_5, GPIO_PIN_RESET);

		HAL_GPIO_WritePin( PLC_ONBOARD_DO_0_PORT, PLC_ONBOARD_DO_0_PIN, GPIO_PIN_RESET);

		 Default_PIN_State = HAL_GPIO_ReadPin(PLC_DEFAULT_BUTTON_PORT, PLC_DEFAULT_BUTTON_PORT_PIN);

		if (Default_PIN_State == 0)
			{
				//
				// PLC
				//
				*Plc.SlaveAddress = 1;
				*Plc.SerialNo 	  = 202230001;

				//
				// Usart Port Data End
				//
				for(i=0;i<UART_COUNT;i++) *Uart[i].DataEnd = 50;

				SystemRegisterDataDefault();

				CommonRegisterDataDefault();

				PlcRegisterDataDefault();

				UsartRegisterDataDefault();

				AdcRegisterDataDefault();

				AlertRegisterDataDefault();

				CriticalDataRegisterDefault();

				*(unsigned short *)&Registers.Holding[HA_PLC_CONTROL ] |= UPDATE_HOLDING_REG;

			}
	}
}

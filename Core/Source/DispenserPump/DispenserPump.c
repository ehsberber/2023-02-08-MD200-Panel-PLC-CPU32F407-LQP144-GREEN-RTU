/*
 * DispenserPump.c
 *
 *  Created on: Sep 28, 2022
 *      Author: Sezgin Berber
 */
#include "Registers.h"
#include "Peripheral.h"


extern strcPLC Plc;
extern strcSYSTEM System;
extern strcREGISTERS Registers;

void PumpIgnition(void)
{
	//unsigned short SeqDIPumpIgnition;
	//unsigned short StandBy;

	//StandBy = Plc.Peripheral.DigitalInput.StandBy->DIs;

//	SeqDIPumpIgnition = SEQ_DI_PUMP1_IGNITION;

	//if( (System.Indicator->Pump & 0x01) && ((Registers.Input[0] & (0x0001 <<SeqDIPumpIgnition )) != ( StandBy & (0x0001 <<SeqDIPumpIgnition ))) )
	if( (System.Indicator->Pump & 0x01) && (Plc.DInput->DI.Pump1Ignition != Plc.Peripheral.DigitalInput.StandBy->DI.Pump1Ignition) )
		{
			System.Indicator->DispenserPumpIgnition = System.Indicator->DispenserPumpIgnition | 0x01;
		}
	else
		{
			System.Indicator->DispenserPumpIgnition = System.Indicator->DispenserPumpIgnition & ~0x01;
		}

//	SeqDIPumpIgnition = SEQ_DI_PUMP2_IGNITION;

	if( (System.Indicator->Pump & 0x02)  && (Plc.DInput->DI.Pump1Ignition != Plc.Peripheral.DigitalInput.StandBy->DI.Pump2Ignition) )
		{
			System.Indicator->DispenserPumpIgnition = System.Indicator->DispenserPumpIgnition | 0x02;
		}
	else
		{
			System.Indicator->DispenserPumpIgnition = System.Indicator->DispenserPumpIgnition & ~0x02;
		}
}

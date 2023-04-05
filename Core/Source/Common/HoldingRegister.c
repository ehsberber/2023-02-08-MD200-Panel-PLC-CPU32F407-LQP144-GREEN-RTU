/*
 * HoldingRegisterUpdate.c
 *
 *  Created on: Jan 6, 2022
 *      Author: SBerber
 */

#include "DataPositionHolding.h"
#include "Registers.h"
#include "MC25LCxxx.h"


extern strcREGISTERS  Registers;
extern unsigned char *InputParameterList[2];
extern strcPLC Plc;

void UpdateHoldingRegister(void)
{
	unsigned short InProgress= 0;
	//static unsigned short ReadAddress=0;

	if(	 Plc.Control->HRUpdate ||  Plc.Control->HRUpdateInprogress)
		{
			Plc.Control->HRUpdate 			= 0;
			Plc.Control->HRUpdateInprogress = 1;

			*(unsigned short *)&Registers.Holding[HA_PLC_CONTROL ] &= ~(0x0001 << BN_HOLDING_UPDATE_INPROGRESS);

			InProgress = MC25LCxxx_WritePacket(&hspi1, EEPROM_NO_00);
			if(!InProgress)
				{
					Plc.Control->HRUpdateInprogress = 0;
				}
		}
}

//
// Holding Register Write
//
void HoldingRegisterWrite(void)
{
	unsigned char ListNo, InputParameterDataPosition;


	for(ListNo= 0 ; ListNo <2 ; ListNo++)
		MC25LCxxx_WriteList(&hspi1, EEPROM_NO_00, InputParameterList[ListNo], &InputParameterDataPosition);
}

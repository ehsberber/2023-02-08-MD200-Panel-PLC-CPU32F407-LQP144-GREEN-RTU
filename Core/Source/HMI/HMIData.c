/*
 * HMIData.c
 *
 *  Created on: Sep 22, 2022
 *      Author: Sezgin Berber
 */
#include "Registers.h"

extern strcHMI HMI;
extern strcPLC Plc;
extern strcCRITICALS Criticals;
extern strcSYSTEM System;
extern strcALERT Alerts;
extern strcALERTES AlertES;
extern strcDATASENDCENTER DataSendCenter;
extern strcREGISTERS Registers;

void HMIData(void)
{
	//
	// Tank Data
	//

	*HMI.LT[0] 						= *Plc.Peripheral.AnalogInput.Calculated[0];
	*HMI.LT[1] 						= *Plc.Peripheral.AnalogInput.Calculated[1];
	*HMI.PT[0] 						= *Plc.Peripheral.AnalogInput.Calculated[2];
	*HMI.PT[1] 						= *Plc.Peripheral.AnalogInput.Calculated[3];
	*HMI.TankCapacity[0]			= *System.Tanks.Capacity[0];
	*HMI.TankCapacity[1]			= *System.Tanks.Capacity[1];

	*HMI.TankAmountKg[0]			= *System.Tanks.AmoungKg[0];
	*HMI.TankAmountKg[1]			= *System.Tanks.AmoungKg[1];

	*HMI.DigitalInput				= *(unsigned short *)&Registers.Input[0];
	*HMI.DigitalOutput				= *(unsigned short *)&Registers.Coil[0];

}

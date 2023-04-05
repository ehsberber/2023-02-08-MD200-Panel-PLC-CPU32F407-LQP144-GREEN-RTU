/*
 * SystemStates.c
 *
 *  Created on: Sep 7, 2022
 *      Author: Sezgin Berber
 */
#include "SystemStates.h"
#include "Registers.h"
#include "DigitalOutput.h"
#include "Leds.h"

extern strcSYSTEM System;
extern strcPLC Plc;
extern strcREGISTERS  Registers;


void ShutOffRelay(void)
{
	if(System.Control->ShutOffRelayState)
		{
			Registers.Coil[DO_NO_SHUTOFF_BYTE]  = Registers.Coil[DO_NO_SHUTOFF_BYTE] & ~(0x0001 << DO_NO_SHUTOFF);
		}
	else
		{
			Registers.Coil[DO_NO_SHUTOFF_BYTE]  = Registers.Coil[DO_NO_SHUTOFF_BYTE] | (0x0001 << DO_NO_SHUTOFF);
		}
}

void SystemReady(void)
{
	if(Plc.DInput->DI.StartState != Plc.Peripheral.DigitalInput.StandBy->DI.StartState)
		{
			*System.State = SYSTEM_STATE_NOT_READY;
		}
	else
		{
			*System.State = SYSTEM_STATE_INPROGRESS;
		}
}

void SystemStateInProgress(unsigned char Restart)
{


	ShutOffRelay();

	SystemReady();
}

void SystemStateEmergencyStop(unsigned char Restart)
{
	Plc.Status->IDOK = 0;
	if(System.Control->ShutOffRelayState)
		{
			Registers.Coil[DO_NO_SHUTOFF_BYTE]  = Registers.Coil[DO_NO_SHUTOFF_BYTE] | (0x0001 << DO_NO_SHUTOFF);
		}
	else
		{
			Registers.Coil[DO_NO_SHUTOFF_BYTE]  = Registers.Coil[DO_NO_SHUTOFF_BYTE] & ~(0x0001 << DO_NO_SHUTOFF);
		}

	Registers.Coil[DO_NO_FUELING_VALVE1_BYTE]  = Registers.Coil[DO_NO_FUELING_VALVE1_BYTE] & ~(0x0001 << DO_NO_FUELING_VALVE1);
	Registers.Coil[DO_NO_FUELING_VALVE2_BYTE]  = Registers.Coil[DO_NO_FUELING_VALVE2_BYTE] & ~(0x0001 << DO_NO_FUELING_VALVE2);
	Registers.Coil[DO_NO_PUMP1_BYTE]  = Registers.Coil[DO_NO_PUMP1_BYTE] & ~(0x0001 << DO_NO_PUMP1);
	Registers.Coil[DO_NO_PUMP2_BYTE]  = Registers.Coil[DO_NO_PUMP2_BYTE] & ~(0x0001 << DO_NO_PUMP2);

}

void SystemIndicator(void)
{
	if ( Registers.Coil[DO_NO_ALERT_BYTE] & (0x0001 << DO_NO_ALERT ))
		{
			System.Indicator->Alert = 1;
		}
	else
		{
			System.Indicator->Alert = 0;
		}

	if ( Registers.Coil[DO_NO_FUELING_VALVE1_BYTE] & (0x0001 << DO_NO_FUELING_VALVE1 ))
		{
			System.Indicator->FillingValve = System.Indicator->FillingValve | 0x01;
		}
	else
		{
			System.Indicator->FillingValve = System.Indicator->FillingValve & ~0x01;
		}


	if ( Registers.Coil[DO_NO_FUELING_VALVE2_BYTE] & (0x0001 << DO_NO_FUELING_VALVE2 ))
		{
			System.Indicator->FillingValve = System.Indicator->FillingValve | 0x02;
		}
	else
		{
			System.Indicator->FillingValve = System.Indicator->FillingValve & ~0x02;
		}


	if ( Registers.Coil[DO_NO_PUMP1_BYTE] & (0x0001 << DO_NO_PUMP1 ))
		{
			System.Indicator->Pump = System.Indicator->Pump | 0x02;
		}
	else
		{
			System.Indicator->Pump = System.Indicator->Pump & ~0x02;
		}

	if ( Registers.Coil[DO_NO_PUMP2_BYTE] & (0x0001 << DO_NO_PUMP2 ))
		{
			System.Indicator->Pump = System.Indicator->Pump | 0x01;
		}
	else
		{
			System.Indicator->Pump = System.Indicator->Pump & ~0x01;
		}

	if ( Registers.Coil[DO_NO_MODEM_BYTE] & (0x0001 << DO_NO_MODEM ))
		{
			System.Indicator->ModemPower = 1;
		}
	else
		{
			System.Indicator->ModemPower = 0;
		}

	if ( Registers.Coil[DO_NO_SHUTOFF_BYTE] & (0x0001 << DO_NO_SHUTOFF ))
		{
			System.Indicator->Shutoff = 1;
		}
	else
		{
			System.Indicator->Shutoff = 0;
		}

	if ( Registers.Coil[DO_NO_PUMP_PER_RUN_BYTE] & (0x0001 << DO_NO_PUMP_PER_RUN ))
		{
			System.Indicator->PumpPeriodicallyRun = 1;
		}
	else
		{
			System.Indicator->PumpPeriodicallyRun = 0;
		}


	if ( ( Registers.Coil[DO_NO_SHUTOFF_BYTE] & (0x0001 << DO_NO_SHUTOFF )) ==  System.Control->ShutOffRelayState )
		{
			System.Indicator->ShutoffState = 1;
		}
	else
		{
			System.Indicator->ShutoffState = 0;
		}

}

void SystemStateProcess(void)
{
	static signed short SystemState = -1;
	unsigned short SystemStateChange=0;

	SystemIndicator();

	Leds();

	if(*System.State != SystemState  )
		{
			SystemStateChange = 1;
			SystemState = *System.State;
		}


	switch(*System.State)
		{
			case SYSTEM_STATE_NONE:
					if(Plc.Status->ProcessStart)
						{
							*System.State = SYSTEM_STATE_INPROGRESS;
						}
				break;

			case SYSTEM_STATE_STOP:
				break;

			case SYSTEM_STATE_NOT_READY:
			case SYSTEM_STATE_INPROGRESS:
					SystemStateInProgress(SystemStateChange);
				break;

			case SYSTEM_STATE_EMERGENCY_STOP:
					SystemStateEmergencyStop(SystemStateChange);
				break;
		}

}

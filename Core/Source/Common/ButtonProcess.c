/*
 * ButtonProcess.c
 *
 *  Created on: Sep 16, 2022
 *      Author: Sezgin Berber
 */

#include "Registers.h"
#include "Peripheral.h"
#include "DigitalOutput.h"
#include "DefaultParameter.h"
#include "Kalman.h"

extern strcREGISTERS Registers;
extern strcALERT Alerts;
extern strcSYSTEM System;
extern strcPLC Plc;
extern strcDATASENDCENTER DataSendCenter;

void SetRegisterDataDefault(void)
{
	if(System.Button0->Button.HRDefault)
		{
			SystemRegisterDataDefault();

			CommonRegisterDataDefault();

			PlcRegisterDataDefault();

			UsartRegisterDataDefault();

			AdcRegisterDataDefault();

			AlertRegisterDataDefault();

			CriticalDataRegisterDefault();

			System.Button0->Button.HRDefault = 0;

		}

	if(System.Button0->Button.HRUpdate)
		{
			Plc.Control->HRUpdate = 1;

			System.Button0->Button.HRUpdate = 0;
		}

}

void HMIButtonSetting(void)
{
//	static  union unionButtonSetting HMIButtonSetting;
//	unsigned short Channel,Counter;

	if(System.Button2->Button.KalmanDefault )
		{
			 *Plc.Peripheral.AnalogInput.KalmanPar.Len 		= 20;
			 *Plc.Peripheral.AnalogInput.KalmanPar.fP 		= 10;
			 *Plc.Peripheral.AnalogInput.KalmanPar.fQ 		= 0.0001;
			 *Plc.Peripheral.AnalogInput.KalmanPar.fR 		= 0.05;
			 *Plc.Peripheral.AnalogInput.KalmanPar.fKGain	= 0;

			 System.Button2->Button.KalmanDefault = 0;
		}

	if(System.Button2->Button.KalmanReInit)
		{
			InitKalmanParameter();
			System.Button2->Button.KalmanReInit = 0;
		}
}

void HMIButtonProcess(void)
{
	unsigned short Counter ;

	HMIButtonSetting();

	SetRegisterDataDefault();
	//
	// Acknowledge Button
	//
	if (System.Button0->Button.Acknowledge)
		{

			System.Button0->Button.Acknowledge = 0;
		}

	if(System.Button0->Button.TestAlertRunClose)
		{
			System.Warning->TestAlert = 0;
			System.Warning->EndOfFilling = 0;
			System.Warning->EndOfFillingWarning = 0;

			System.Button0->Button.TestAlertRunClose = 0;
		}

	if(System.Button0->Button.OverFillingConfirmation)
		{
			if(System.Warning->OverFillingLevel == 1 )
				{
					System.Warning->OverFillingLevel = 0;
				}
			System.Button0->Button.OverFillingConfirmation = 0;
		}

	if(System.Button0->Button.OverFillingClear)
		{
			System.Warning->OverFillingLevel = 0;

			System.Button0->Button.OverFillingClear = 0;
		}



	if (System.Button0->Button.DataSend)
		{
			if(*DataSendCenter.DataSendPeriod)
				{
					TimerRestart(TIM_NO_DATA_SEND, *DataSendCenter.DataSendPeriod);
				}
			*DataSendCenter.ToBeSendPacket = *DataSendCenter.DefaultPacket;

			System.Button0->Button.DataSend = 0;
		}

	if (System.Button0->Button.CopyChannelMv)
		{
		 for (Counter = 1; Counter<AI_CHANNEL_COUNT; Counter++)
		 	 {
				 *Plc.Peripheral.AnalogInput.ChannelBottomValuemV[Counter]		= *Plc.Peripheral.AnalogInput.ChannelBottomValuemV[0];
				 *Plc.Peripheral.AnalogInput.ChannelTopValuemV[Counter]			= *Plc.Peripheral.AnalogInput.ChannelTopValuemV[0];
		 	 }

		 	 Plc.Control->HRUpdate = 1;

		 	System.Button0->Button.CopyChannelMv = 0;
		}


	if(System.Button1->Button.DOAlert)
		{
			if ( Registers.Coil[DO_NO_ALERT_BYTE] & (0x0001 << DO_NO_ALERT ))
					{
						Registers.Coil[DO_NO_ALERT_BYTE] = Registers.Coil[DO_NO_ALERT_BYTE] & ~(0x0001 << DO_NO_ALERT );
					}
				else
					{
						Registers.Coil[DO_NO_ALERT_BYTE] = Registers.Coil[DO_NO_ALERT_BYTE] |  (0x0001 << DO_NO_ALERT );
					}
			System.Button1->Button.DOAlert = 0;
		}

	if(System.Button1->Button.DOFuelingValve01)
		{
			if ( Registers.Coil[DO_NO_FUELING_VALVE1_BYTE] & (0x0001 << DO_NO_FUELING_VALVE1 ))
					{
						Registers.Coil[DO_NO_FUELING_VALVE1_BYTE] = Registers.Coil[DO_NO_FUELING_VALVE1_BYTE] & ~(0x0001 << DO_NO_FUELING_VALVE1 );
					}
				else
					{
						Registers.Coil[DO_NO_FUELING_VALVE1_BYTE] = Registers.Coil[DO_NO_FUELING_VALVE1_BYTE] |  (0x0001 << DO_NO_FUELING_VALVE1 );
					}
			System.Button1->Button.DOFuelingValve01 = 0;
		}

	if(System.Button1->Button.DOFuelingValve02)
		{
			if ( Registers.Coil[DO_NO_FUELING_VALVE2_BYTE] & (0x0001 << DO_NO_FUELING_VALVE2 ))
					{
						Registers.Coil[DO_NO_FUELING_VALVE2_BYTE] = Registers.Coil[DO_NO_FUELING_VALVE2_BYTE] & ~(0x0001 << DO_NO_FUELING_VALVE2 );
					}
				else
					{
						Registers.Coil[DO_NO_FUELING_VALVE2_BYTE] = Registers.Coil[DO_NO_FUELING_VALVE2_BYTE] |  (0x0001 << DO_NO_FUELING_VALVE2 );
					}
			System.Button1->Button.DOFuelingValve02 = 0;
		}

	if(System.Button1->Button.DOPump01)
		{
			if ( Registers.Coil[DO_NO_PUMP1_BYTE] & (0x0001 << DO_NO_PUMP1))
					{
						Registers.Coil[DO_NO_PUMP1_BYTE] = Registers.Coil[DO_NO_PUMP1_BYTE] & ~(0x0001 << DO_NO_PUMP1 );
					}
				else
					{
						Registers.Coil[DO_NO_PUMP1_BYTE] = Registers.Coil[DO_NO_PUMP1_BYTE] |  (0x0001 << DO_NO_PUMP1 );
					}
			System.Button1->Button.DOPump01 = 0;
		}

	if(System.Button1->Button.DOPump02)
		{
			if ( Registers.Coil[DO_NO_PUMP2_BYTE] & (0x0001 << DO_NO_PUMP2 ))
					{
						Registers.Coil[DO_NO_PUMP2_BYTE] = Registers.Coil[DO_NO_PUMP2_BYTE] & ~(0x0001 << DO_NO_PUMP2 );
					}
				else
					{
						Registers.Coil[DO_NO_PUMP2_BYTE] = Registers.Coil[DO_NO_PUMP2_BYTE] |  (0x0001 << DO_NO_PUMP2 );
					}
			System.Button1->Button.DOPump02 = 0;
		}

	if(System.Button1->Button.DOModemPower)
		{
			if ( Registers.Coil[DO_NO_MODEM_BYTE] & (0x0001 << DO_NO_MODEM ))
					{
						Registers.Coil[DO_NO_MODEM_BYTE] = Registers.Coil[DO_NO_MODEM_BYTE] & ~(0x0001 << DO_NO_MODEM );
					}
				else
					{
						Registers.Coil[DO_NO_MODEM_BYTE] = Registers.Coil[DO_NO_MODEM_BYTE] |  (0x0001 << DO_NO_MODEM );
					}
			System.Button1->Button.DOModemPower = 0;
		}

	if(System.Button1->Button.DOShutOff)
		{
			if ( Registers.Coil[DO_NO_SHUTOFF_BYTE] & (0x0001 << DO_NO_SHUTOFF ))
					{
						Registers.Coil[DO_NO_SHUTOFF_BYTE] = Registers.Coil[DO_NO_SHUTOFF_BYTE] & ~(0x0001 << DO_NO_SHUTOFF );
					}
				else
					{
						Registers.Coil[DO_NO_SHUTOFF_BYTE] = Registers.Coil[DO_NO_SHUTOFF_BYTE] |  (0x0001 << DO_NO_SHUTOFF );
					}
			System.Button1->Button.DOShutOff = 0;
		}

	if(System.Button1->Button.DOPumpPeriodicallyrun)
		{
			if ( Registers.Coil[DO_NO_PUMP_PER_RUN_BYTE] & (0x0001 << DO_NO_PUMP_PER_RUN ))
					{
						Registers.Coil[DO_NO_PUMP_PER_RUN_BYTE] = Registers.Coil[DO_NO_PUMP_PER_RUN_BYTE] & ~(0x0001 << DO_NO_PUMP_PER_RUN );
					}
				else
					{
						Registers.Coil[DO_NO_PUMP_PER_RUN_BYTE] = Registers.Coil[DO_NO_PUMP_PER_RUN_BYTE] |  (0x0001 << DO_NO_PUMP_PER_RUN );
					}
			System.Button1->Button.DOPumpPeriodicallyrun = 0;
		}

	if(System.Button1->Button.DO8)
		{
			if ( Registers.Coil[0] & (0x0001 << 8 ))
					{
						Registers.Coil[0] = Registers.Coil[0] & ~(0x0001 << 8 );
					}
				else
					{
						Registers.Coil[0] = Registers.Coil[0] |  (0x0001 << 8 );
					}
			System.Button1->Button.DO8 = 0;
		}

	if(System.Button1->Button.DO9)
		{
			if ( Registers.Coil[0] & (0x0001 << 9 ))
					{
						Registers.Coil[0] = Registers.Coil[0] & ~(0x0001 << 9 );
					}
				else
					{
						Registers.Coil[0] = Registers.Coil[0] |  (0x0001 << 9 );
					}
			System.Button1->Button.DO9 = 0;
		}


	if(System.Button1->Button.DO10)
		{
			if ( Registers.Coil[0] & (0x0001 << 10 ))
					{
						Registers.Coil[0] = Registers.Coil[0] & ~(0x0001 << 10 );
					}
				else
					{
						Registers.Coil[0] = Registers.Coil[0] |  (0x0001 << 10 );
					}
			System.Button1->Button.DO10 = 0;
		}

	if(System.Button1->Button.DO11)
		{
			if ( Registers.Coil[0] & (0x0001 << 11 ))
					{
						Registers.Coil[0] = Registers.Coil[0] & ~(0x0001 << 11 );
					}
				else
					{
						Registers.Coil[0] = Registers.Coil[0] |  (0x0001 << 11 );
					}
			System.Button1->Button.DO11 = 0;
		}

	if(System.Button1->Button.DO12)
		{
			if ( Registers.Coil[0] & (0x0001 << 12 ))
					{
						Registers.Coil[0] = Registers.Coil[0] & ~(0x0001 << 12 );
					}
				else
					{
						Registers.Coil[0] = Registers.Coil[0] |  (0x0001 << 12 );
					}
			System.Button1->Button.DO12 = 0;
		}

	if(System.Button1->Button.DO13)
		{
			if ( Registers.Coil[0] & (0x0001 << 13 ))
					{
						Registers.Coil[0] = Registers.Coil[0] & ~(0x0001 << 13 );
					}
				else
					{
						Registers.Coil[0] = Registers.Coil[0] |  (0x0001 << 13 );
					}
			System.Button1->Button.DO13 = 0;
		}

	if(System.Button1->Button.DO14)
		{
			if ( Registers.Coil[0] & (0x0001 << 14 ))
					{
						Registers.Coil[0] = Registers.Coil[0] & ~(0x0001 << 14 );
					}
				else
					{
						Registers.Coil[0] = Registers.Coil[0] |  (0x0001 << 14 );
					}
			System.Button1->Button.DO14 = 0;
		}

	if(System.Button1->Button.DO15)
		{
			if ( Registers.Coil[0] & (0x0001 << 15 ))
					{
						Registers.Coil[0] = Registers.Coil[0] & ~(0x0001 << 15 );
					}
				else
					{
						Registers.Coil[0] = Registers.Coil[0] |  (0x0001 << 15 );
					}
			System.Button1->Button.DO15 = 0;
		}

}

void ButtonProcess(void)
{
	HMIButtonProcess();


}


/*
 * DefaultParameter.c
 *
 *  Created on: Sep 14, 2022
 *      Author: Sezgin Berber
 */


/*
 * DataRegisterAssignment.c
 *
 *  Created on: 7 Oca 2022
 *      Author: SBerber
 */

#include "DataPositionHolding.h"
#include "DataPositionStatus.h"
#include "Rtc.h"
#include "Registers.h"
#include "PlcDefinition.h"
#include "Uarts.h"
#include "DataType.h"
#include "Coils.h"
#include "AnalogInput.h"

extern strcPLC Plc;
extern strcSYSTEM System;
extern strcREGISTERS  Registers;
extern strcRTC RtcData;
extern strcRTCCounter RtcCounter;
extern strcDATASENDCENTER DataSendCenter;
extern strcMASTERCODE MasterCode;

extern unsigned char  HoldingRegister_Data[32768] ;

extern unsigned char  StatusRegister_Data[65536] ;

extern unsigned int InputRegister_Data[4];

extern unsigned int  CoilRegister_Data[COIL_INT_COUNT];

extern unsigned char *InputParameterList[2];

extern strcUART Uart[UART_COUNT];

extern strcAnalogInput AnalogInput;

extern strcALERTES AlertES;
extern strcALERT   Alerts;
extern strcCRITICALS Criticals;

void AlertRegisterDataDefault(void)
{
	unsigned char Counter;
	//								//
	//		** 		ALERT	**		//
	//								//
	//
	// Alert Master
	//
	*AlertES.Master.AlertEnable					= 0x8113;
			*AlertES.Master.ESEnable			= 0x8013;
			*AlertES.Master.AlertState 			= 0x0000;
			*AlertES.Master.ESState 			= 0x0000;
			*AlertES.Master.AlertAutoClear 		= 0x8113;
			*AlertES.Master.ESAutoClear 		= 0x8113;

			//AlertES.AutoClear.ES					= (unsigned short *) &Registers.Status[SA_ES_MASTER_AUTO_CLEAR];
			//
			// Alert LT Master
			//
			*AlertES.Master.LT.AlertEnable 	= 0x0001;
			*AlertES.Master.LT.ESEnable 	= 0x0001;
			*AlertES.Master.LT.AlertState	= 0x0000;
			*AlertES.Master.LT.ESState		= 0x0000;
			//
			// Alert GD Master
			//
			*AlertES.Master.GD.AlertEnable 	= 0x000F;
			*AlertES.Master.GD.ESEnable 	= 0x000F;
			*AlertES.Master.GD.AlertState	= 0x0000;
			*AlertES.Master.GD.ESState		= 0x0000;

			//
			// Alert ES Master
			//
			*AlertES.Master.SYSTEM.AlertEnable 	= 0x0007;
			*AlertES.Master.SYSTEM.ESEnable 	= 0x0001;
			*AlertES.Master.SYSTEM.AlertState	= 0x0000;
			*AlertES.Master.SYSTEM.ESState		= 0x0000;


			//								//
			//		** 		ALERT TYPE **	//
			//								//

			*Alerts.TypeNo.LT.VeryHigh				= 0;
			*Alerts.TypeNo.LT.High					= 1;
			*Alerts.TypeNo.LT.EndOfFilling			= 2;
			*Alerts.TypeNo.LT.WarningLow			= 3;
			*Alerts.TypeNo.LT.Low					= 4;
			*Alerts.TypeNo.LT.VeryLow				= 5;

			*Alerts.TypeNo.GD.VeryHigh				= 6;
			*Alerts.TypeNo.GD.High					= 7;

			*Alerts.TypeNo.ESB						= 8;

			*Alerts.TypeNo.SYSTEM.IllegalFueling	= 10;
			*Alerts.TypeNo.SYSTEM.AlertTest			= 9;

			*Alerts.Clear.LT						= 1.0;
			*Alerts.Clear.GD						= 10.0;
			*Alerts.Clear.WarningTimeout  			= 10;


			*Alerts.RunState.WaitToRun				= 300;

			*Alerts.TypeNo.SYSTEM.OverFilling		= 11;

			*Alerts.TypeNo.Thermic					= 13;
			*Alerts.TypeNo.Contactor				= 14;
			*Alerts.TypeNo.Deviation				= 12;
	// LT
	//
	for(Counter = 0; Counter < LT_COUNT; Counter++ )
		{
			*AlertES.LT[Counter].AlertEnable	= 0x0003;
			*AlertES.LT[Counter].ESEnable		= 0x0001;
			*AlertES.LT[Counter].State 			= 0x0000;
		}
	//
	// GD
	//
	for(Counter = 0; Counter < GD_COUNT; Counter++ )
		{
			*AlertES.GD[Counter].AlertEnable 	= 0x0003;
			*AlertES.GD[Counter].ESEnable 		= 0x0001;
			*AlertES.GD[Counter].State 			= 0x0000;
		}
	//
	// ESB
	//

	*AlertES.Master.ESB.AlertEnable 	= 0x000F;
	*AlertES.Master.ESB.ESEnable 		= 0x000F;
	*AlertES.Master.ESB.AlertState		= 0x0000;
	*AlertES.Master.ESB.ESState			= 0x0000;


	Alerts.RunTypes[0].Control->Enable         = 1;
					Alerts.RunTypes[0].Control->Continuously   = 0;
					*Alerts.RunTypes[0].AlertOnTime            = 30;
					*Alerts.RunTypes[0].AlertOffTime           = 20;
					*Alerts.RunTypes[0].AlertCount             = 7;

					Alerts.RunTypes[1].Control->Enable         = 1;
					Alerts.RunTypes[1].Control->Continuously   = 0;
					*Alerts.RunTypes[1].AlertOnTime            = 30;
					*Alerts.RunTypes[1].AlertOffTime           = 20;
					*Alerts.RunTypes[1].AlertCount             = 7;

					Alerts.RunTypes[2].Control->Enable         = 1;
					Alerts.RunTypes[2].Control->Continuously   = 0;
					*Alerts.RunTypes[2].AlertOnTime            = 30;
					*Alerts.RunTypes[2].AlertOffTime           = 20;
					*Alerts.RunTypes[2].AlertCount             = 5;

					Alerts.RunTypes[3].Control->Enable         = 1;
					Alerts.RunTypes[3].Control->Continuously   = 0;
					*Alerts.RunTypes[3].AlertOnTime            = 30;
					*Alerts.RunTypes[3].AlertOffTime           = 20;
					*Alerts.RunTypes[3].AlertCount             = 9;

					Alerts.RunTypes[4].Control->Enable         = 1;
					Alerts.RunTypes[4].Control->Continuously   = 0;
					*Alerts.RunTypes[4].AlertOnTime            = 40;
					*Alerts.RunTypes[4].AlertOffTime           = 20;
					*Alerts.RunTypes[4].AlertCount             = 5;

					Alerts.RunTypes[5].Control->Enable         = 1;
					Alerts.RunTypes[5].Control->Continuously   = 0;
					*Alerts.RunTypes[5].AlertOnTime            = 50;
					*Alerts.RunTypes[5].AlertOffTime           = 10;
					*Alerts.RunTypes[5].AlertCount             = 18;

					Alerts.RunTypes[6].Control->Enable         = 1;
					Alerts.RunTypes[6].Control->Continuously   = 0;
					*Alerts.RunTypes[6].AlertOnTime            = 40;
					*Alerts.RunTypes[6].AlertOffTime           = 20;
					*Alerts.RunTypes[6].AlertCount             = 11;

					Alerts.RunTypes[7].Control->Enable         = 1;
					Alerts.RunTypes[7].Control->Continuously   = 0;
					*Alerts.RunTypes[7].AlertOnTime            = 30;
					*Alerts.RunTypes[7].AlertOffTime           = 20;
					*Alerts.RunTypes[7].AlertCount             = 9;

					Alerts.RunTypes[8].Control->Enable         = 1;
					Alerts.RunTypes[8].Control->Continuously   = 0;
					*Alerts.RunTypes[8].AlertOnTime            = 40;
					*Alerts.RunTypes[8].AlertOffTime           = 10;
					*Alerts.RunTypes[8].AlertCount             = 11;

					Alerts.RunTypes[9].Control->Enable         = 1;
					Alerts.RunTypes[9].Control->Continuously   = 0;
					*Alerts.RunTypes[9].AlertOnTime            = 30;
					*Alerts.RunTypes[9].AlertOffTime           = 30;
					*Alerts.RunTypes[9].AlertCount             = 7;

					Alerts.RunTypes[10].Control->Enable        = 1;
					Alerts.RunTypes[10].Control->Continuously  = 0;
					*Alerts.RunTypes[10].AlertOnTime           = 30;
					*Alerts.RunTypes[10].AlertOffTime          = 20;
					*Alerts.RunTypes[10].AlertCount            = 9;

					Alerts.RunTypes[11].Control->Enable        = 1;
					Alerts.RunTypes[11].Control->Continuously  = 0;
					*Alerts.RunTypes[11].AlertOnTime           = 40;
					*Alerts.RunTypes[11].AlertOffTime          = 20;
					*Alerts.RunTypes[11].AlertCount            = 11;

					Alerts.RunTypes[12].Control->Enable        = 1;
					Alerts.RunTypes[12].Control->Continuously  = 0;
					*Alerts.RunTypes[12].AlertOnTime           = 30;
					*Alerts.RunTypes[12].AlertOffTime          = 10;
					*Alerts.RunTypes[12].AlertCount            = 7;

					Alerts.RunTypes[13].Control->Enable        = 1;
					Alerts.RunTypes[13].Control->Continuously  = 0;
					*Alerts.RunTypes[13].AlertOnTime           = 10;
					*Alerts.RunTypes[13].AlertOffTime          = 10;
					*Alerts.RunTypes[13].AlertCount            = 5;

					Alerts.RunTypes[14].Control->Enable        = 1;
					Alerts.RunTypes[14].Control->Continuously  = 0;
					*Alerts.RunTypes[14].AlertOnTime           = 10;
					*Alerts.RunTypes[14].AlertOffTime          = 10;
					*Alerts.RunTypes[14].AlertCount            = 5;

					Alerts.RunTypes[15].Control->Enable        = 0;
					Alerts.RunTypes[15].Control->Continuously  = 0;
					*Alerts.RunTypes[15].AlertOnTime           = 40;
					*Alerts.RunTypes[15].AlertOffTime          = 10;
					*Alerts.RunTypes[15].AlertCount            = 14;


	 Alerts.RunState.Control->Acknowledge 		= 0;
	 Alerts.RunState.Control->Active 			= 0;
	 Alerts.RunState.Control->Continuously 		= 0;
	 Alerts.RunState.Control->OnOffState        = 0;

	 *Alerts.RunState.AlertNo 					= 0;
	 *Alerts.RunState.AlertCounter				= 0;

}

void CriticalDataRegisterDefault(void)
{

	unsigned char Counter;
	for(Counter = 0; Counter < LT_COUNT; Counter++ )
		{
		    *Criticals.LT[Counter].CriticalLevel.VeryHigh 		= 87.0;
			*Criticals.LT[Counter].CriticalLevel.High			= 85.0;
			*Criticals.LT[Counter].CriticalLevel.EndOfFilling 	= 80.0;
			*Criticals.LT[Counter].CriticalLevel.WarningLow 	= 10.0;
			*Criticals.LT[Counter].CriticalLevel.Low 			=  8.0;
			*Criticals.LT[Counter].CriticalLevel.VeryLow 		=  5.0;
		}

	for(Counter = 0; Counter < GD_COUNT; Counter++ )
		{
			*Criticals.GD[Counter].CriticalLevel.VeryHigh 		= 40.0;
			*Criticals.GD[Counter].CriticalLevel.High 	 		= 20.0;
		}

	*Criticals.GDActiveSensor.SeqNo 					= 0;
	*Criticals.GDActiveSensor.SeqValue 	 				= 0;

	*Criticals.ESBActive.SeqNo							= 0;
}

void AdcRegisterDataDefault(void)
{
	 unsigned short Channel,SequenceNo;

	 *DataSendCenter.DataSendPeriod 					= 3000;
	 *DataSendCenter.DefaultPacket  					= 0x010F;
	 *DataSendCenter.DataChannelValueMultiplier		 	= 1;
	 *DataSendCenter.DataAnalogInputValueMultiplier	 	= 1;

	 Plc.Status->IDOK 	= 0;
	 Plc.Status->IDRead = 0;
	 Plc.Status->ProcessStart = 0;

	 *Plc.RunTime = 200;

	 *Plc.Peripheral.AnalogInput.ChannelType 		= 0xFFFF;

	 *Plc.Peripheral.AnalogInput.KalmanFilterEnable = 0x00FF;
	 *Plc.Peripheral.AnalogInput.AvarageEnable 		= 0x00FF;

	 for (Channel=0; Channel<AI_CHANNEL_COUNT; Channel++)
	 	 {
			 *Plc.Peripheral.AnalogInput.AnalogValue[Channel]			= 0;
			 *Plc.Peripheral.AnalogInput.AnalogValueFiltered[Channel]	= 0;
			 *Plc.Peripheral.AnalogInput.ChannelState[Channel]			= 0;
			 *Plc.Peripheral.AnalogInput.Calculated[Channel]			= 0.0;
			 *Plc.Peripheral.AnalogInput.Scale[Channel].Bottom			= 0.0;
			 *Plc.Peripheral.AnalogInput.Scale[Channel].Top				= 100.0;
			 *Plc.Peripheral.AnalogInput.Calibration[Channel].Constant	= 1.0;
			 *Plc.Peripheral.AnalogInput.Calibration[Channel].Offset	= 0.0;
			 *Plc.Peripheral.AnalogInput.Allocation[Channel]			= Channel;


			 *Plc.Peripheral.AnalogInput.ChannelBottomValuemV[Channel]		= 664.0;
			 *Plc.Peripheral.AnalogInput.ChannelTopValuemV[Channel]			= 2620.0;
	 	 }


	 //
	 // MicroControler Adc 3300000/4096
	 //
	 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_ON_CPU_NO_00]	= 3300000/4096;
	 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_ON_CPU_NO_01]	= 3300000/4096;
	 //
	 // On Board I2C
	 // // 0.5*Vref/ 2^24 = 0.5 * 3.3V / 2^24 = 0.09834766 microVolt
	 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_ONBAORD_IC_NO_00]	= 0.09834766;
	 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_ONBAORD_IC_NO_00]	= 0.09834766;



	 if (*Plc.Peripheral.AnalogInput.ModuleType[0] == AI_MODULE_TYPE_LTC241x)
		 {
		 	 //
		 	 // Vref(uV) / 2^23 = 3300000uV / 2 ^23 = 0.3933907
		 	 //
			 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_MODULE_NO_00]	= 0.3933907;
		 }
	 else
		 {
		 	 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_MODULE_NO_00]	= 1000.0;
		 }

	 if (*Plc.Peripheral.AnalogInput.ModuleType[1] == AI_MODULE_TYPE_LTC241x)
		 {
		 	 //
		 	 // Vref(uV) / 2^23 = 3300000uV / 2 ^23 = 0.3933907
		 	 //
			 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_MODULE_NO_01]	= 0.3933907;
		 }
	 else
		 {
			 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_MODULE_NO_01]	= 1000.0;
		 }



	 for (SequenceNo=0; SequenceNo<CHANNEL_VALUE_SEQ_COUNT; SequenceNo++)
		 {
			 *Plc.Peripheral.AnalogInput.AnalogValue[SequenceNo] 	= 0.0;
		 }

	*Plc.Peripheral.AnalogInput.ModuleChannelPos[0] = 0;
	*Plc.Peripheral.AnalogInput.ModuleChannelPos[1] = 0;
	*Plc.Peripheral.AnalogInput.ModuleChannelPos[2] = 0;
	*Plc.Peripheral.AnalogInput.ModuleChannelPos[3] = 4;

}

void PlcRegisterDataDefault(void)
{
	Plc.Constant.PI_Const				= 3.14;

	Plc.Control->HRUpdate				= 0;
	Plc.Control->HRUpdateInprogress		= 0;

	*Plc.SerialNo 						= 202236001;
	*Plc.SlaveAddress 					= 1;

	*Plc.Peripheral.AnalogInput.EnabledModule = 0x0003;

	*Plc.Peripheral.DigitalOutput.Master[0]	  		= 0;
	*Plc.Peripheral.DigitalOutput.Master[1]	  		= 0;
	*Plc.Peripheral.DigitalOutput.Master[2]	  		= 0;
	*Plc.Peripheral.DigitalOutput.Master[3]	  		= 0;

	*Plc.Peripheral.DigitalInput.EnabledModule	  	= 0x0000;

	Plc.Peripheral.DigitalInput.DebugMode->DIs		= 0x0000;
	Plc.Peripheral.DigitalInput.Debug->DIs			= 0x0000;
	Plc.Peripheral.DigitalInput.StandBy->DIs		= 0x0000;
	Plc.Peripheral.DigitalInput.State->DIs			= 0x0000;

	Plc.Warning->WarningTimeout						= 0;
	Plc.Warning->LTMasterWarning					= 0;
	Plc.Warning->OneWire							= 0;
	Plc.Warning->LTMasterWarning					= 0;
	Plc.Warning->ProbeTimeout						= 0;
}

void CommonRegisterDataDefault(void)
{
	System.Button0->Buttons = 0;


	*System.State 							= 0;
	*System.Substate 						= 0;
	System.Control->AlertRunOnUpDown	 	= 0;
	System.Control->IllegalFueling	 		= 1;
	System.Control->ShutOffRelayState	 	= 0;
	System.Control->FuelingWithID	 		= 1;

}

void SystemRegisterDataDefault(void)
 {
	unsigned char i;

	for (i=0;i< TIMER_COUNT;i++ )
		{
 			*Registers.Timers.Counter[i] = 0;
 			*Registers.Timers.TimeOut[i] = 0;

		}
 }

void UsartRegisterDataDefault(void)
 {
  	//
 	// UART OFFSET DEFAULT
 	//

 	*Uart[0].BufferSize = UART_0_BUFFER_SIZE;
 	*Uart[1].BufferSize = UART_1_BUFFER_SIZE;
 	*Uart[2].BufferSize = UART_2_BUFFER_SIZE;
 	*Uart[3].BufferSize = UART_3_BUFFER_SIZE;
 	*Uart[4].BufferSize = UART_4_BUFFER_SIZE;
 	*Uart[5].BufferSize = UART_5_BUFFER_SIZE;
 	*Uart[6].BufferSize = UART_6_BUFFER_SIZE;

 }



///*
// * DefaultParameter.c
// *
// *  Created on: Sep 14, 2022
// *      Author: Sezgin Berber
// */
//
//
///*
// * DataRegisterAssignment.c
// *
// *  Created on: 7 Oca 2022
// *      Author: SBerber
// */
//
//#include "DataPositionHolding.h"
//#include "DataPositionStatus.h"
//#include "Rtc.h"
//#include "Registers.h"
//#include "PlcDefinition.h"
//#include "Uarts.h"
//#include "OneWireProcess.h"
//#include "DataType.h"
//#include "OneWire.h"
//#include "Coils.h"
//#include "AnalogInput.h"
//
//extern strcPLC Plc;
//extern strcSYSTEM System;
//extern strcONEWIRE OneWire[ONEWIRE_LINES_COUNT];
//extern strcREGISTERS  Registers;
//extern strcRTC RtcData;
//extern strcRTCCounter RtcCounter;
//extern strcONEWIRETEMPERATURE strcOneWireTemperature;
//
//extern unsigned char  HoldingRegister_Data[32768] ;
//
//extern unsigned char  StatusRegister_Data[65536] ;
//
//extern unsigned int InputRegister_Data[4];
//
//extern unsigned int  CoilRegister_Data[COIL_INT_COUNT];
//
//extern unsigned char *InputParameterList[2];
//
//extern strcUART Uart[UART_COUNT];
//
//extern strcAnalogInput AnalogInput;
//
//extern strcALERTES AlertES;
//extern strcALERT   Alerts;
//extern strcCRITICALS Criticals;
//
//void AlertRegisterDataDefault(void)
//{
//	unsigned char Counter;
//	//								//
//	//		** 		ALERT	**		//
//	//								//
//	//
//	// Alert Master
//	//
//	*AlertES.Master.AlertEnable			= 0x0000;
//	*AlertES.Master.ESEnable			= 0x0000;
//	*AlertES.Master.AlertState 			= 0x0000;
//	*AlertES.Master.ESState 			= 0x0000;
//	*AlertES.Master.AlertAutoClear 		= 0x0000;
//	*AlertES.Master.ESAutoClear 		= 0x0000;
//
//	//AlertES.AutoClear.ES					= (unsigned short *) &Registers.Status[SA_ES_MASTER_AUTO_CLEAR];
//	//
//	// Alert LT Master
//	//
//	*AlertES.Master.LT.AlertEnable 	= 0x00E7;
//	*AlertES.Master.LT.ESEnable 	= 0x0000;
//	*AlertES.Master.LT.AlertState	= 0x0000;
//	*AlertES.Master.LT.ESState		= 0x0000;
//	//
//	// Alert GD Master
//	//
//	*AlertES.Master.GD.AlertEnable 	= 0x0007;
//	*AlertES.Master.GD.ESEnable 	= 0x0007;
//	*AlertES.Master.GD.AlertState	= 0x0000;
//	*AlertES.Master.GD.ESState		= 0x0000;
//
//	//
//	// Alert ES Master
//	//
//	*AlertES.Master.SYSTEM.AlertEnable 	= 0x0007;
//	*AlertES.Master.SYSTEM.ESEnable 	= 0x0000;
//	*AlertES.Master.SYSTEM.AlertState	= 0x0000;
//	*AlertES.Master.SYSTEM.ESState		= 0x0000;
//
//
//	//								//
//	//		** 		ALERT TYPE **	//
//	//								//
//
//	*Alerts.TypeNo.LT.VeryHigh				= 7;
//	*Alerts.TypeNo.LT.High					= 0;
//	*Alerts.TypeNo.LT.EndOfFilling			= 0;
//	*Alerts.TypeNo.LT.WarningLow			= 1;
//	*Alerts.TypeNo.LT.Low					= 1;
//	*Alerts.TypeNo.LT.VeryLow				= 6;
//
//	*Alerts.TypeNo.GD.VeryHigh				= 7;
//	*Alerts.TypeNo.GD.High					= 0;
//
//	*Alerts.TypeNo.ESB						= 7;
//
//	*Alerts.TypeNo.SYSTEM.IllegalFueling	= 7;
//	*Alerts.TypeNo.SYSTEM.AlertTest			= 1;
//
//	*Alerts.Clear.LT						= 1.0;
//	*Alerts.Clear.GD						= 1.0;
//	*Alerts.Clear.WarningTimeout  			= 1200;
//
//	//
//	// LT
//	//
//	for(Counter = 0; Counter < LT_COUNT; Counter++ )
//		{
//			*AlertES.LT[Counter].AlertEnable	= 0x00E7;
//			*AlertES.LT[Counter].ESEnable		= 0x0081;
//			*AlertES.LT[Counter].State 			= 0x0000;
//		}
//	//
//	// GD
//	//
//	for(Counter = 0; Counter < GD_COUNT; Counter++ )
//		{
//			*AlertES.GD[Counter].AlertEnable 	= 0x00C0;
//			*AlertES.GD[Counter].ESEnable 		= 0x0080;
//			*AlertES.GD[Counter].State 			= 0x0000;
//		}
//	//
//	// ESB
//	//
//
//	*AlertES.Master.ESB.AlertEnable 	= 0x000F;
//	*AlertES.Master.ESB.ESEnable 		= 0x000F;
//	*AlertES.Master.ESB.AlertState		= 0x0000;
//	*AlertES.Master.ESB.ESState			= 0x0000;
//
//
//	Alerts.RunTypes[0].Control->Enable 			= 1;
//	Alerts.RunTypes[0].Control->Continuously 	= 0;
//	*Alerts.RunTypes[0].AlertOnTime 			= 40;
//	*Alerts.RunTypes[0].AlertOffTime  			= 10;
//	*Alerts.RunTypes[0].AlertCount 				= 10;
//
//	Alerts.RunTypes[1].Control->Enable 			= 1;
//	Alerts.RunTypes[1].Control->Continuously 	= 0;
//	*Alerts.RunTypes[1].AlertOnTime 			= 30;
//	*Alerts.RunTypes[1].AlertOffTime  			= 10;
//	*Alerts.RunTypes[1].AlertCount 				= 4;
//
//	Alerts.RunTypes[2].Control->Enable 			= 1;
//	Alerts.RunTypes[2].Control->Continuously 	= 0;
//	*Alerts.RunTypes[2].AlertOnTime 			= 45;
//	*Alerts.RunTypes[2].AlertOffTime  			= 8;
//	*Alerts.RunTypes[2].AlertCount 				= 6;
//
//	Alerts.RunTypes[3].Control->Enable 			= 1;
//	Alerts.RunTypes[3].Control->Continuously 	= 0;
//	*Alerts.RunTypes[3].AlertOnTime 			= 50;
//	*Alerts.RunTypes[3].AlertOffTime  			= 20;
//	*Alerts.RunTypes[3].AlertCount 				= 8;
//
//	Alerts.RunTypes[4].Control->Enable 			= 1;
//	Alerts.RunTypes[4].Control->Continuously 	= 0;
//	*Alerts.RunTypes[4].AlertOnTime 			= 40;
//	*Alerts.RunTypes[4].AlertOffTime  			= 20;
//	*Alerts.RunTypes[4].AlertCount 				= 12;
//
//	Alerts.RunTypes[5].Control->Enable 			= 1;
//	Alerts.RunTypes[5].Control->Continuously 	= 0;
//	*Alerts.RunTypes[5].AlertOnTime 			= 20;
//	*Alerts.RunTypes[5].AlertOffTime  			= 10;
//	*Alerts.RunTypes[5].AlertCount 				= 8;
//
//
//	Alerts.RunTypes[6].Control->Enable 			= 1;
//	Alerts.RunTypes[6].Control->Continuously 	= 0;
//	*Alerts.RunTypes[6].AlertOnTime 			= 20;
//	*Alerts.RunTypes[6].AlertOffTime  			= 20;
//	*Alerts.RunTypes[6].AlertCount 				= 10;
//
//	Alerts.RunTypes[7].Control->Enable 			= 1;
//	Alerts.RunTypes[7].Control->Continuously 	= 0;
//	*Alerts.RunTypes[7].AlertOnTime 			= 40;
//	*Alerts.RunTypes[7].AlertOffTime  			= 10;
//	*Alerts.RunTypes[7].AlertCount 				= 14;
//
//	Alerts.RunTypes[8].Control->Enable 			= 1;
//	Alerts.RunTypes[8].Control->Continuously 	= 0;
//	*Alerts.RunTypes[8].AlertOnTime 			= 40;
//	*Alerts.RunTypes[8].AlertOffTime  			= 10;
//	*Alerts.RunTypes[8].AlertCount 				= 14;
//
//	Alerts.RunTypes[9].Control->Enable 			= 1;
//	Alerts.RunTypes[9].Control->Continuously 	= 0;
//	*Alerts.RunTypes[9].AlertOnTime 			= 40;
//	*Alerts.RunTypes[9].AlertOffTime  			= 10;
//	*Alerts.RunTypes[9].AlertCount 				= 14;
//
//	Alerts.RunTypes[10].Control->Enable 		= 1;
//	Alerts.RunTypes[10].Control->Continuously 	= 0;
//	*Alerts.RunTypes[10].AlertOnTime 			= 40;
//	*Alerts.RunTypes[10].AlertOffTime  			= 10;
//	*Alerts.RunTypes[10].AlertCount 			= 14;
//
//
//	 Alerts.RunState.Control->Acknowledge 		= 0;
//	 Alerts.RunState.Control->Active 			= 0;
//	 Alerts.RunState.Control->Continuously 		= 0;
//	 Alerts.RunState.Control->OnOffState        = 0;
//
//	 *Alerts.RunState.AlertNo 					= 0;
//	 *Alerts.RunState.AlertCounter				= 0;
//
//}
//
//void CriticalDataRegisterDefault(void)
//{
//
//	unsigned char Counter;
//	for(Counter = 0; Counter < LT_COUNT; Counter++ )
//		{
//			*Criticals.LT[Counter].CriticalLevel.VeryHigh 		= 85.0;
//			*Criticals.LT[Counter].CriticalLevel.High			= 80.0;
//			*Criticals.LT[Counter].CriticalLevel.EndOfFilling 	= 78.0;
//			*Criticals.LT[Counter].CriticalLevel.WarningLow 	= 10.0;
//			*Criticals.LT[Counter].CriticalLevel.Low 			=  8.0;
//			*Criticals.LT[Counter].CriticalLevel.VeryLow 		=  5.0;
//		}
//
//	for(Counter = 0; Counter < GD_COUNT; Counter++ )
//		{
//			*Criticals.GD[Counter].CriticalLevel.VeryHigh 		= 40.0;
//			*Criticals.GD[Counter].CriticalLevel.High 	 		= 20.0;
//		}
//
//	*Criticals.GDActiveSensor.SeqNo 					= 0;
//	*Criticals.GDActiveSensor.SeqValue 	 				= 0;
//
//	*Criticals.ESBActive.SeqNo							= 0;
//}
//
//void AdcRegisterDataDefault(void)
//{
//	 unsigned short Channel,SequenceNo;
//
//	 Plc.Status->IDOK 	= 0;
//	 Plc.Status->IDRead = 0;
//	 Plc.Status->ProcessStart = 0;
//
//
//	 *Plc.Peripheral.AnalogInput.ChannelType 	= 0xFFFF;
//
//	 *Plc.Peripheral.AnalogInput.KalmanFilterEnable = 0xFFFF;
//	 *Plc.Peripheral.AnalogInput.AvarageEnable 		= 0x0000;
//
//	 for (Channel=0; Channel<AI_CHANNEL_COUNT; Channel++)
//	 	 {
//			 *Plc.Peripheral.AnalogInput.AnalogValue[Channel]			= 0;
//			 *Plc.Peripheral.AnalogInput.AnalogValueFiltered[Channel]	= 0;
//			 *Plc.Peripheral.AnalogInput.ChannelState[Channel]			= 0;
//			 *Plc.Peripheral.AnalogInput.Calculated[Channel]			= 0.0;
//			 *Plc.Peripheral.AnalogInput.Scale[Channel].Bottom			= 0.0;
//			 *Plc.Peripheral.AnalogInput.Scale[Channel].Top				= 100.0;
//			 *Plc.Peripheral.AnalogInput.Calibration[Channel].Constant	= 1.0;
//			 *Plc.Peripheral.AnalogInput.Calibration[Channel].Offset	= 0.0;
//			 *Plc.Peripheral.AnalogInput.Allocation[Channel]			= Channel;
//
//
//			 *Plc.Peripheral.AnalogInput.ChannelBottomValuemV[Channel]		= 664.0;
//			 *Plc.Peripheral.AnalogInput.ChannelTopValuemV[Channel]			= 2620.0;
//	 	 }
//
//
//	 //
//	 // MicroControler Adc 3300000/4096
//	 //
//	 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_ON_CPU_NO_00]	= 3300000/4096;
//	 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_ON_CPU_NO_01]	= 3300000/4096;
//	 //
//	 // On Board I2C
//	 // // 0.5*Vref/ 2^24 = 0.5 * 3.3V / 2^24 = 0.09834766 microVolt
//	 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_ONBAORD_IC_NO_00]	= 98.34766;
//	 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_ONBAORD_IC_NO_00]	= 98.34766;
//
//
//
//	 if (*Plc.Peripheral.AnalogInput.ModuleType[0] == AI_MODULE_TYPE_LTC241x)
//		 {
//		 	 //
//		 	 // Vref(uV) / 2^23 = 3300000uV / 2 ^23 = 0.3933907
//		 	 //
//			 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_MODULE_NO_00]	= 0.3933907;
//		 }
//	 else
//		 {
//		 	 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_MODULE_NO_00]	= 1000.0;
//		 }
//
//	 if (*Plc.Peripheral.AnalogInput.ModuleType[1] == AI_MODULE_TYPE_LTC241x)
//		 {
//		 	 //
//		 	 // Vref(uV) / 2^23 = 3300000uV / 2 ^23 = 0.3933907
//		 	 //
//			 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_MODULE_NO_01]	= 0.3933907;
//		 }
//	 else
//		 {
//			 *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ADC_MODULE_NO_01]	= 1000.0;
//		 }
//
//
//
//	 for (SequenceNo=0; SequenceNo<CHANNEL_VALUE_SEQ_COUNT; SequenceNo++)
//		 {
//			 *Plc.Peripheral.AnalogInput.AnalogValue[SequenceNo] 	= 0.0;
//		 }
//
//	*Plc.Peripheral.AnalogInput.ModuleChannelPos[0] = 0;
//	*Plc.Peripheral.AnalogInput.ModuleChannelPos[1] = 0;
//	*Plc.Peripheral.AnalogInput.ModuleChannelPos[2] = 0;
//	*Plc.Peripheral.AnalogInput.ModuleChannelPos[3] = 4;
//
//}
//
//void PlcRegisterDataDefault(void)
//{
//
//	Plc.Constant.PI_Const				= 3.14;
//
//	Plc.Control->HRUpdate				= 0;
//	Plc.Control->HRUpdateInprogress		= 0;
//
//	*Plc.SerialNo 						= 202236001;
//	*Plc.SlaveAddress 					= 1;
//
//	*Plc.Peripheral.AnalogInput.EnabledModule = 0x000C;
//
//
//	*Plc.Peripheral.DigitalOutput.Master[0]	  		= 0;
//	*Plc.Peripheral.DigitalOutput.Master[1]	  		= 0;
//	*Plc.Peripheral.DigitalOutput.Master[2]	  		= 0;
//	*Plc.Peripheral.DigitalOutput.Master[3]	  		= 0;
//
//
//	*Plc.Peripheral.DigitalInput.EnabledModule	  	= 0x0000;
//	Plc.Peripheral.DigitalInput.DebugMode->DIs		= 0x0000;
//	Plc.Peripheral.DigitalInput.Debug->DIs			= 0x0000;
//	Plc.Peripheral.DigitalInput.StandBy->DIs		= 0x0000;
//	Plc.Peripheral.DigitalInput.State->DIs			= 0x0000;
//
//	Plc.Warning->WarningTimeout						= 0;
//	Plc.Warning->LTMasterWarning					= 0;
//	Plc.Warning->OneWire							= 0;
//	Plc.Warning->LTMasterWarning					= 0;
//	Plc.Warning->ProbeTimeout						= 0;
//}
//
//void OneWireRegisterDataDefault(void)
//{
//	unsigned char LineNo,DeviceRomNo;
//
//	for(LineNo=0; LineNo < ONEWIRE_LINES_COUNT ;LineNo++)
//		{
//
//			*OneWire[LineNo].Status 	= 0;
//			OneWire[LineNo].Control 	= 0x00;
//			OneWire[LineNo].Length 		= 0x00;
//
//			for(DeviceRomNo=0; DeviceRomNo < ONEWIRE_MAX_DEVICE_COUNT_IN_LINE ;DeviceRomNo++)
//				{
//					*OneWire[LineNo].Rom[DeviceRomNo]  =  0;
//				}
//
//			OneWire[LineNo].ReadData[0] =  '\0';
//			OneWire[LineNo].WriteData[0] = '\0';
//		}
//}
//
//void CommonRegisterDataDefault(void)
//{
//	unsigned short Counter;
//	System.Button0->Buttons = 0;
//
//
//	*System.State 		= 0;
//	*System.Substate 	= 0;
//	System.Control->AlertRunOnUpDown	 	= 0;
//	System.Control->IllegalFueling	 		= 1;
//	System.Control->ShutOffRelayState	 	= 0;
//	System.Control->FuelingWithID	 		= 1;
//
//	*System.DispenserCount	 		= 1;
//
//	*System.Tanks.Count				= 1;
//	*System.Tanks.FuelingValveCount	= 1;
//	*System.Tanks.FuelingTimeout	= 4800;
//	//*System.Tanks.DeviationTimeout  = 100;
//	*System.Tanks.AllowedLevel 		= 5.0;
//	*System.Tanks.TotalLevelLastSave= 100.0;
//	*System.Tanks.TotalLevelLastSave= 100.0;
//	*System.Tanks.MinUpLevel 		= 3;
//	*System.Tanks.MinUpLevelTimeout = 1800;
//
//	for(Counter=0; Counter< MAX_TANK_COUNT ; Counter++)
//		{
//			*System.Tanks.Capacity[Counter] 		= 10.0;
//			*System.Tanks.Density[Counter] 		= 1.0;
//			*System.Tanks.Deviation[Counter] 	= 3.5;
//			*System.Tanks.Differance[Counter] 	= 3.0;
//			*System.Tanks.Len[Counter] 			= 4.2;
//			*System.Tanks.EllipticalLen[Counter] = 0.375;
//			*System.Tanks.Diameter[Counter] 		= 1.65;
//		}
//
//	*System.Tanks.FillingValveCloseTime  	= 600;
//	*System.Tanks.ValveOpenLevelDiffrence 	= 2.0;
//
//	System.Tanks.FillingStatus->Allowed		=  0;
//	System.Tanks.FillingStatus->CloseTank	=  0;
//	System.Tanks.FillingStatus->OpenTank	=  0;
//
//	*System.Probes.Protocol				= 0;
//	*System.Probes.Timeout   			= 150;
//	*System.Probes.Enable				= 0;
//	*System.Probes.ActiveSeq			= 0;
//
//	for(Counter = 0; Counter < PROBE_COUNT; Counter++)
//		{
//			*System.Probes.State[Counter]			= 0;
//			*System.Probes.SerialNo[Counter]		= 30770;
//			*System.Probes.HighOfLiquid[Counter]	= 1.0;
//			*System.Probes.TankAllocation[Counter]	= 0;
//			*System.Probes.Temperature[Counter]		= 0.0;
//			*System.Probes.TankOffset[Counter]		= 0.005;
//		}
//
//	*System.Pumps.Count  				= 1;
//	*System.Pumps.RunMode  				= 0;
//	*System.Pumps.PeriodicallyWaitToRun	= 3600;
//	*System.Pumps.PeriodicallyRunTime	= 300;
//	*System.Pumps.StopTime				= 1800;
//}
//
//void SystemRegisterDataDefault(void)
// {
//	unsigned char i;
//
//	for (i=0;i< TIMER_COUNT;i++ )
//		{
// 			*Registers.Timers.Counter[i] = 0;
// 			*Registers.Timers.TimeOut[i] = 0;
//
//		}
// }
//
//void UsartRegisterDataDefault(void)
// {
//  	//
// 	// UART OFFSET DEFAULT
// 	//
//
// 	*Uart[0].BufferSize = UART_0_BUFFER_SIZE;
// 	*Uart[1].BufferSize = UART_1_BUFFER_SIZE;
// 	*Uart[2].BufferSize = UART_2_BUFFER_SIZE;
// 	*Uart[3].BufferSize = UART_3_BUFFER_SIZE;
// 	*Uart[4].BufferSize = UART_4_BUFFER_SIZE;
// 	*Uart[5].BufferSize = UART_5_BUFFER_SIZE;
// 	*Uart[6].BufferSize = UART_6_BUFFER_SIZE;
//
// }
//

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

extern strcPLC Plc;
extern strcGSM GSM;
extern strcSYSTEM System;
extern strcMASTERCODE MasterCode;
extern strcREGISTERS  Registers;
extern strcRTC RtcData;
extern strcRTCCounter RtcCounter;
extern strcDATASENDCENTER DataSendCenter;
extern strcHMI HMI;

extern unsigned char  HoldingRegister_Data[32768] ;

extern unsigned char  StatusRegister_Data[65536] ;

extern unsigned int InputRegister_Data[4];

extern unsigned int  CoilRegister_Data[COIL_INT_COUNT];

extern unsigned char *InputParameterList[2];

extern strcUART Uart[UART_COUNT];

extern strcAnalogInput AnalogInput;


void HMIDataRegister(void)
{
	unsigned short i;

	for(i=0;i<2;i++)
		{
			HMI.LT[i] 			= (float *) &Registers.Status[SA_HMI_LT1 + (i * 4)];
			HMI.PT[i] 		= (float *) &Registers.Status[SA_HMI_PT1 + (i * 4)];
			HMI.TankCapacity[i]	= (float *) &Registers.Status[SA_HMI_TANK1_CAPACITY + (i * 4)];
			HMI.TankAmountKg[i]	= (float *) &Registers.Status[SA_HMI_TANK1_AMOUNT_KG + (i * 4)];
		}

	HMI.DigitalInput		= (unsigned short *) &Registers.Status[SA_HMI_DIGITAL_INPUTS];
	HMI.DigitalOutput		= (unsigned short *) &Registers.Status[SA_HMI_DIGITAL_OUTPUTS];
}


void TankDataRegister(void)
{
	unsigned short Counter;
	for(Counter=0; Counter< 2 ; Counter++)
		{
			System.Tanks.Capacity[Counter] 		= (float *) &Registers.Holding[HA_TANK_CAPACITY + ( Counter * 4 )];
			System.Tanks.Density[Counter] 		= (float *) &Registers.Holding[HA_TANK_DENSITY + ( Counter * 4 )];

			System.Tanks.AmoungKg[Counter] 		= (float *) &Registers.Status[SA_TANK_AMOUNT_KG + ( Counter * 4 )];
		}
}

void AdcRegisterData(void)
{
	 unsigned short Channel,ModuleNo; //,SequenceNo;

	//
	// Used For Cpu ADC
	//
	 Plc.RTU.BaudRate = (unsigned short *) &Registers.Holding[HA_RTU_BAUDRATE];
	 Plc.RTU.DataBits = (unsigned short *) &Registers.Holding[HA_RTU_DATA_BITS];
	 Plc.RTU.Parity = (unsigned short *) &Registers.Holding[HA_RTU_DATA_PARITY];
	 Plc.RTU.StopBits = (unsigned short *) &Registers.Holding[HA_RTU_STOP_BITS];

	 Plc.RunTime   	= (unsigned int *) &Registers.Holding[HA_PLC_RUN_TIMEOUT];
	 Plc.Status  	= (strcPLCSTATUS *) &Registers.Status[SA_PLC_STATUS];

	 Plc.Peripheral.AnalogInput.EnabledModule 		= (unsigned short *) &Registers.Holding[HA_AI_MODULE_ENABLE];
	 Plc.Peripheral.AnalogInput.ChannelType 		= (unsigned int *) &Registers.Holding[HA_AI_CHANNEL_TYPES];
	 Plc.Peripheral.AnalogInput.KalmanFilterEnable 	= (unsigned int *) &Registers.Holding[HA_AI_KALMAN_FILTER];
	 Plc.Peripheral.AnalogInput.AvarageEnable 		= (unsigned int *) &Registers.Holding[HA_AI_AVARAGE_CALCULATION];
	 for (Channel=0; Channel<AI_CHANNEL_COUNT; Channel++)
	 	 {
			 Plc.Peripheral.AnalogInput.AnalogValue[Channel]			= (signed int *) &Registers.Status[SA_AI_CHANNEL_VALUE + (Channel * 4 )];
			 Plc.Peripheral.AnalogInput.AnalogValueFiltered[Channel]	= (float *) &Registers.Status[SA_AI_CHANNEL_VALUE_FILTERED + (Channel * 4 )];
			 Plc.Peripheral.AnalogInput.ChannelState[Channel]			= (unsigned short *) &Registers.Status[SA_AI_CHANNEL_STATE + (Channel * 2 )];
			 Plc.Peripheral.AnalogInput.Calculated[Channel]				= (float *) &Registers.Holding[HA_AI_CALC + (4 * Channel)];
			 Plc.Peripheral.AnalogInput.Scale[Channel].Bottom			= (float *) &Registers.Holding[HA_AI_BOTTOM + (4 * Channel)];
			 Plc.Peripheral.AnalogInput.Scale[Channel].Top				= (float *) &Registers.Holding[HA_AI_TOP + (4 * Channel)];
			 Plc.Peripheral.AnalogInput.Calibration[Channel].Constant	= (float *) &Registers.Holding[HA_AI_CALB + (4 * Channel)];
			 Plc.Peripheral.AnalogInput.Calibration[Channel].Offset		= (float *) &Registers.Holding[HA_AI_OFFSET + (4 * Channel)];
			 Plc.Peripheral.AnalogInput.Allocation[Channel]				= (unsigned short *) &Registers.Holding[HA_AI_ALLOCATION + (2 * Channel)];

			 Plc.Peripheral.AnalogInput.ChannelBottomValuemV[Channel]		= (float *) &Registers.Holding[HA_AI_CHANNEL_BOTTOM_VALUE_mV + (4 * Channel)];
			 Plc.Peripheral.AnalogInput.ChannelTopValuemV[Channel]			= (float *) &Registers.Holding[HA_AI_CHANNEL_TOP_VALUE_mV + (4 * Channel)];
	 	 }

//	 for (SequenceNo=0; SequenceNo<CHANNEL_VALUE_SEQ_COUNT; SequenceNo++)
//		 {
//			 Plc.Peripheral.AnalogInput.ChannelValue[SequenceNo] 	= (float *) &Registers.Status[SA_CHANNEL_VALUE + (4 * SequenceNo)];
//		 }

	 for (ModuleNo =0; ModuleNo<AI_MODULE_COUNT; ModuleNo++)
	 	 {
			 Plc.Peripheral.AnalogInput.ModuleChannelPos[ModuleNo] 	= (unsigned short *) &Registers.Holding[HA_AI_MODULE_CHANNEL_POS + (ModuleNo * 2 )];
			 Plc.Peripheral.AnalogInput.SeqNo[ModuleNo] 			= (unsigned short *) &Registers.Status[SA_AI_CHANNEL_SEQUENCE + (ModuleNo * 2 )];

			 Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ModuleNo] = (double *) &Registers.Holding[HA_AI_MODULE_RESOLUTION_MULTIPLIER + (8 * ModuleNo)];
	 	 }
	 for (ModuleNo =0; ModuleNo<MODULE_SLOT_COUNT; ModuleNo++)
	 	 {
			 Plc.Peripheral.AnalogInput.ModuleType[ModuleNo] 	= (unsigned short *) &Registers.Holding[HA_AI_MODULE_CHANNEL_MODULE_TYPE_SPI + (ModuleNo * 2 )];
	 	 }

//	 Plc.ModBusSequenceNo 	= (unsigned short *) &Registers.Status[SA_MODBUS_ADDRESS_SEQ_NO ];
//	 for (SequenceNo=0; SequenceNo<CHANNEL_VALUE_SEQ_COUNT; SequenceNo++)
//		 {
//			// Plc.ModBusAddress[SequenceNo] 	= (unsigned short *) &Registers.Status[SA_MODBUS_ADDRESS + (2 * SequenceNo)];
//		 }

	 Plc.Peripheral.AnalogInput.KalmanPar.Len 		= (unsigned short *) &Registers.Holding[HA_AI_KALMAN_LEN];
	 Plc.Peripheral.AnalogInput.KalmanPar.fP 		= (float *) &Registers.Holding[HA_AI_KALMAN_fP];
	 Plc.Peripheral.AnalogInput.KalmanPar.fQ 		= (float *) &Registers.Holding[HA_AI_KALMAN_fQ];
	 Plc.Peripheral.AnalogInput.KalmanPar.fR 		= (float *) &Registers.Holding[HA_AI_KALMAN_fR];
	 Plc.Peripheral.AnalogInput.KalmanPar.fKGain	= (float *) &Registers.Holding[HA_AI_KALMAN_fKGain];
}

void PlcRegisterData(void)
{

	Plc.Constant.PI_Const				= 3.14;

	Plc.SerialNo 									= (unsigned int *)  &Registers.Holding[HA_PLC_SERIAL_NO];
	Plc.SlaveAddress 								= (unsigned short *)&Registers.Holding[HA_SLAVE_ADDRESS];
	Plc.Control 									= (strcPLCCONTROL *)&Registers.Holding[HA_PLC_CONTROL];

	Plc.Peripheral.DigitalOutput.EnabledModule	  	= (unsigned short *)&Registers.Holding[HA_DO_MODULE_ENABLE];
	Plc.Peripheral.DigitalOutput.Master[0]	  		= (unsigned int *)&Registers.Holding[HA_DO_MASTER];
	Plc.Peripheral.DigitalOutput.Master[1]	  		= (unsigned int *)&Registers.Holding[HA_DO_MASTER + 4];
	Plc.Peripheral.DigitalOutput.Master[2]	  		= (unsigned int *)&Registers.Holding[HA_DO_MASTER + 8];
	Plc.Peripheral.DigitalOutput.Master[3]	  		= (unsigned int *)&Registers.Holding[HA_DO_MASTER + 12];


	Plc.Peripheral.DigitalInput.EnabledModule	  	= (unsigned short *)&Registers.Holding[HA_DI_MODULE_ENABLE];
	Plc.Peripheral.DigitalInput.DebugMode			= (union unionDI *)&Registers.Holding[HA_DI_DEBUG_MODE];
	Plc.Peripheral.DigitalInput.Debug				= (union unionDI *)&Registers.Holding[HA_DI_DEBUG];
	Plc.Peripheral.DigitalInput.StandBy				= (union unionDI *)&Registers.Holding[HA_DI_STANDBY];
	Plc.Peripheral.DigitalInput.State				= (union unionDI *)&Registers.Status[SA_DI_STATE];

	Plc.Warning 									= (strcWARNING *)&Registers.Status[SA_PLC_WARNING];

	Plc.DOout 										=(union unionDO *)&CoilRegister_Data[0];
	Plc.DInput										=(union unionDI *)Plc.Peripheral.DigitalInput.State;

}

void DataSendReceiveRegisterData(void)
{
	DataSendCenter.DataSendControl	     			= (strcDATASENDCONTROL *)&Registers.Status[SA_DATA_SEND_CONTROL];
	DataSendCenter.SendPacketNo 					= (unsigned short *)&Registers.Status[SA_DATA_SEND_PACKET_NO];
	DataSendCenter.ToBeSendPacket 					= (unsigned int *)&Registers.Status[SA_DATA_TO_BE_SEND_PACKET];
	DataSendCenter.ActiveToBeSendPacket 			= (unsigned int *)&Registers.Status[SA_DATA_ACTIVE_TO_BE_SEND_PACKET];
	DataSendCenter.ToBeSendSubPacket 				= (unsigned int *)&Registers.Status[SA_DATA_TO_BE_SEND_SUB_PACKET];
	DataSendCenter.SendSubPacketNo 					= (unsigned short *)&Registers.Status[SA_DATA_SEND_SUB_PACKET_NO];
	DataSendCenter.DataSendPeriod 					= (unsigned int *)&Registers.Holding[HA_DATA_SEND_PERIOD];
	DataSendCenter.DataChannelValueMultiplier 		= (signed int *)&Registers.Holding[HA_DATA_CHANNEL_VALUE_MULTIPLIER];
	DataSendCenter.DataAnalogInputValueMultiplier	= (signed int *)&Registers.Holding[HA_DATA_ANALOG_INPUT_VALUE_MULTIPLIER];
	DataSendCenter.DefaultPacket 					= (unsigned int *)&Registers.Holding[HA_DATA_DEFAULT_PACKET];
	DataSendCenter.SendArray 						= (unsigned char  *)&Registers.Holding[SA_DATA_SEND_ARRAY];
}

void CommonRegisterData(void)
{
	System.Button0 			= (union unionButton0 *) &Registers.Holding[HA_BUTTON_00];
	System.Button1 			= (union unionButton1 *) &Registers.Holding[HA_BUTTON_01];
	System.Button2 			= (union unionButton2 *) &Registers.Holding[HA_BUTTON_02];

	System.State 		= (unsigned short *)&Registers.Holding[HA_SYSTEM_STATE];
	System.Substate 	= (unsigned short *)&Registers.Holding[HA_SYSTEM_SUBSTATE];
	System.Control	 	= (strcSYSTEMCONTROL *)&Registers.Holding[HA_SYSTEM_CONTROL];
	System.Indicator	= (strcSYSTEMINDICATOR *)&Registers.Status[SA_SYSTEM_INDICATOR];
	System.Warning		= (strcSYSTEMWARNING *)&Registers.Status[SA_SYSTEM_WARNING];

}

void SystemRegisterData(void)
 {
	unsigned short i;

 	Registers.Holding 				= &HoldingRegister_Data[0];
 	Registers.Status	 			= &StatusRegister_Data[0];
 	Registers.Input 				= &InputRegister_Data[0];
 	Registers.Coil  				= &CoilRegister_Data[0];

 	for (i=0;i< TIMER_COUNT;i++ )
		{
 			Registers.Timers.Counter[i] = (unsigned int *)&Registers.Status[SA_TIMER_COUNTER + (i * LENGTH_OF_INTEGER)];
 			Registers.Timers.TimeOut[i] = (unsigned int *)&Registers.Status[SA_TIMER_TIMEOUT + (i * LENGTH_OF_INTEGER)];
 			Registers.Timers.Control[i] = (strcTIMERCONTROL *)&Registers.Status[SA_TIMER_CONTROL + (i * LENGTH_OF_SHORT)];
		}
 }
void MasterCodeDataRegister(void)
{
	unsigned short i;

	MasterCode.SavePosition 	= (unsigned short *) &Registers.Holding[HA_MASTER_CODE_SAVE_POSITION];
 	for (i=0;i< MASTER_CODE_COUNT; i++ )
		{
 			MasterCode.Code[i] 			= (unsigned int *) &Registers.Holding[HA_MASTER_CODE + (i * LENGTH_OF_INTEGER)];
		}
}

void RtcRegisterData(void)
 {

	RtcData.Date 		= (unsigned char *) &Registers.Status[SA_DATE];

	RtcData.Control 	= (unsigned int *) &Registers.Status[SA_RTC_CONTROL];

 	RtcData.MiliSecond 	= (unsigned char *) &Registers.Status[SA_DATE + RTC_MILISECOND_POS];
 	RtcData.Second 		= (unsigned char *) &Registers.Status[SA_DATE + RTC_SECOND_POS];
 	RtcData.Minute 		= (unsigned char *) &Registers.Status[SA_DATE + RTC_MINUTE_POS];
 	RtcData.Hour 		= (unsigned char *) &Registers.Status[SA_DATE + RTC_HOUR_POS];
 	RtcData.DayOfWeek 	= (unsigned char *) &Registers.Status[SA_DATE + RTC_DAYOFWEEK_POS];
 	RtcData.Day 		= (unsigned char *) &Registers.Status[SA_DATE + RTC_DAY_POS];
 	RtcData.Month 		= (unsigned char *) &Registers.Status[SA_DATE + RTC_MONTH_POS];
 	RtcData.Year 		= (unsigned char *) &Registers.Status[SA_DATE + RTC_YEAR_POS];

 	RtcCounter.Master  	= (unsigned int *) &Registers.Status[SA_RTC_MASTER_COUNTER];
 	RtcCounter.Count  	= (unsigned int *) &Registers.Status[SA_RTC_REAL_TIME_COUNTER];
 }

void InputParameterListRegisterData(void)
{
	InputParameterList[0]		= &Registers.Status[SA_INPUT_PARAMETER_SAVE_00];
	InputParameterList[1]		= &Registers.Status[SA_INPUT_PARAMETER_SAVE_01];

}

void UsartRegisterData(void)
 {
 	unsigned char i;
 	//
 	// UART DATA
 	//
 	Uart[0].Data = (unsigned char *)&Registers.Status[SA_UART_0_DATA];
 	Uart[1].Data = (unsigned char *)&Registers.Status[SA_UART_1_DATA];
 	Uart[2].Data = (unsigned char *)&Registers.Status[SA_UART_2_DATA];
 	Uart[3].Data = (unsigned char *)&Registers.Status[SA_UART_3_DATA];
 	Uart[4].Data = (unsigned char *)&Registers.Status[SA_UART_4_DATA];
 	Uart[5].Data = (unsigned char *)&Registers.Status[SA_UART_5_DATA];
 	Uart[6].Data = (unsigned char *)&Registers.Status[SA_UART_6_DATA];

 	//
 	// UART OFFSET
 	//
 	for(i=0;i<UART_COUNT;i++)
 		Uart[i].Offset = (unsigned short *)&Registers.Status[SA_UART_DATA_OFFSET + ( i * LENGTH_OF_SHORT)];

 	//
 	// Buffer Size
 	//
 	for(i=0;i<UART_COUNT;i++)
 		Uart[i].BufferSize = (unsigned short *)&Registers.Status[SA_UART_BUFFER_SIZE + ( i * LENGTH_OF_SHORT)];

 	//
 	// Uart Status
 	//
 	for(i=0;i<UART_COUNT;i++)
 		Uart[i].Status = (unsigned short *)&Registers.Status[SA_UART_STATUS + ( i * LENGTH_OF_SHORT) ];

 	//
 	// Usart Timeout
  	//
 	for(i=0;i<UART_COUNT;i++)
 		Uart[i].Timeout = (unsigned short *)&Registers.Status[SA_UART_TIMEOUT + ( i * LENGTH_OF_SHORT) ];

 	//
 	// Usart Data End
  	//
 	for(i=0;i<UART_COUNT;i++)
 		Uart[i].DataEnd = (unsigned short *)&Registers.Holding[HA_USART_PORT_DATA_END + ( i * LENGTH_OF_SHORT) ];

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



void SetRegisterData(void)
{
	SystemRegisterData();

	CommonRegisterData();

	TankDataRegister();

	DataSendReceiveRegisterData();

	PlcRegisterData();

	InputParameterListRegisterData();

	UsartRegisterData();

	AdcRegisterData();

	//GsmRegisterData();

	RtcRegisterData();

	MasterCodeDataRegister();

	HMIDataRegister();
}

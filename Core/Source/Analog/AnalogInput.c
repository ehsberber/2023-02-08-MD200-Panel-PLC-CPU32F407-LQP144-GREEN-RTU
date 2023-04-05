#include "MicroPeripheral.h"   
#include "Registers.h"
#include <math.h>
#include "LTC_I2C_249X.h" 
#include "AnalogInput.h"

#include "Kalman.h"
#include "PlcDefinition.h"
#include "RegisterOperation.h"
#include "Peripheral.h"
#include "DataPositionStatus.h"
#include "stdlib.h"
#include "SPI_MAX1254.h"
#include "LTC_241X_SPI.h"
#include "ADS_1220.h"
#include "MicroAdc.h"

extern strcPLC Plc;
extern unsigned short REINITIALIZE_PERIPHERAL;

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc3;

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

extern unsigned char *InputParameterList2;
extern unsigned int  *RtcSecondMaster;
extern strcADC ADC_Modules[MAX_AI_BOARD_COUNT];
extern strcREGISTERS  Registers;
extern strcALERT Alerts;

extern uint8_t convEnd;			//conv end flag

extern uint16_t adcBuff[100] ;		//to store converted values
extern uint16_t adcData[100] ;

////
//// Read Analog Input Port
////
//#define CURRENT_4ma_mV		664.0 	//165.24
//#define CURRENT_16ma_mV		2620.0 	//660.96
//#define VOLTAGE_3300_mV		840.00

void SPIModuleChipSelect(strcAdcINSTANCE AdcInstance, unsigned char Enable)
{

	if(AdcInstance.ModuleSeq == 0)
		{
			if(Enable == SPI_MODULE_ENABLE)
				{	SPI_MODULE_CS1_ENABLE; HAL_Delay(2);	}
			else
				{	SPI_MODULE_CS1_DISABLE; HAL_Delay(1);}
		}

	else
		{
			if(Enable == SPI_MODULE_ENABLE)
				{	SPI_MODULE_CS2_ENABLE; HAL_Delay(2);	}
			else
				{	SPI_MODULE_CS2_DISABLE; HAL_Delay(1);}
		}

}

 void AnalogInputCalculate(unsigned char FromChannel, signed short ToChannel)
{
	unsigned int short Mask = 0x0001;
	float CalculatedValue;
	float ChannelBottommV,ChannelTopmV;

	if (ToChannel < 0 || ToChannel > AI_CHANNEL_COUNT ) return;

	if (*Plc.Peripheral.AnalogInput.ChannelType & (Mask << ToChannel))
		{
			ChannelBottommV = *Plc.Peripheral.AnalogInput.ChannelBottomValuemV[ToChannel];
		}
	else
		{
			ChannelBottommV = 0;
		}

	ChannelTopmV = *Plc.Peripheral.AnalogInput.ChannelTopValuemV[ToChannel];

	CalculatedValue = *Plc.Peripheral.AnalogInput.AnalogValueFiltered[FromChannel]; // *Plc.Peripheral.AnalogInput.ChannelValue[SequenceNo];
	CalculatedValue -=  ChannelBottommV;

	*Plc.Peripheral.AnalogInput.Calculated[ToChannel] = CalculatedValue * (*Plc.Peripheral.AnalogInput.Scale[ToChannel].Top - *Plc.Peripheral.AnalogInput.Scale[ToChannel].Bottom) / (ChannelTopmV-ChannelBottommV);
	*Plc.Peripheral.AnalogInput.Calculated[ToChannel] = *Plc.Peripheral.AnalogInput.Calculated[ToChannel] * (*Plc.Peripheral.AnalogInput.Calibration[ToChannel].Constant);
	*Plc.Peripheral.AnalogInput.Calculated[ToChannel] = *Plc.Peripheral.AnalogInput.Calculated[ToChannel] + *Plc.Peripheral.AnalogInput.Scale[ToChannel].Bottom + *Plc.Peripheral.AnalogInput.Calibration[ToChannel].Offset;

}

 void ChannelValueCalculate(unsigned char SequenceNo,signed int ChannelValue)
 {
	 unsigned char i;
	 unsigned int Mask = 0x0001;
	//
	// Kalman Filter
	//

	 if (*Plc.Peripheral.AnalogInput.KalmanFilterEnable & (Mask << SequenceNo))
		 {
		 	 *Plc.Peripheral.AnalogInput.AnalogValueFiltered[SequenceNo] = dCalculateKalmanDataSet(SequenceNo,ChannelValue );
		 }
	 else
		 {
		 	 *Plc.Peripheral.AnalogInput.AnalogValueFiltered[SequenceNo] =  ChannelValue;
		 }

	 for(i=0; i <AI_CHANNEL_COUNT ; i++)
		{
			if(*Plc.Peripheral.AnalogInput.Allocation[i] == SequenceNo)
				{
					//*Plc.Peripheral.AnalogInput.ChannelValue[i] = *Plc.Peripheral.AnalogInput.AnalogValueFiltered[SequenceNo];
					//
					// Calculate Analog Input
					//
					AnalogInputCalculate(*Plc.Peripheral.AnalogInput.Allocation[i], i );
				}
		}
 }

void AnalogInputs(void)
{
	static unsigned char FirstTime=1;
	static unsigned short EnabledModule=0,ModuleNo=0,ModuleSlotNo;
	static unsigned char  LSB = 0;
	unsigned char i;

	//*Plc.Peripheral.AnalogInput.EnabledModule = ADC_MODULE_MAX1254_00;

	if ( *Plc.Peripheral.AnalogInput.EnabledModule == 0 ) return;  // There is No Enabled Board

	if(!LSB || !EnabledModule)
		{
			LSB = 0x00000001;
			ModuleNo = 0;
			EnabledModule = *Plc.Peripheral.AnalogInput.EnabledModule;
		}

	while(!(EnabledModule & LSB ) && LSB) { LSB <<= 1; ModuleNo++;}
	EnabledModule &= ~LSB;

	if (FirstTime)
		{
			ADC_Modules[ModuleNo].Channel = 0;
			ADC_Modules[ModuleNo].NextChannel = 0;
			
			for	(i=0;i<MAX_AI_BOARD_COUNT;i++) ADC_Modules[i].FirstRead = 1;

			FirstTime=0;
		}

 	switch (LSB)
		{
			case ADC_ON_CPU_00:
			case ADC_ON_CPU_01:
				 	 	 OnChipAdcChannelDataRead(ModuleNo);
					break;

			case ADC_ONBAORD_IC_00:
			case ADC_ONBOARD_IC_01:
						AdcModuleLTC2499(ModuleNo);
					break;

			case ADC_MODULE_00:
			case ADC_MODULE_01:

				 if(ModuleNo == ADC_MODULE_NO_00)
					 ModuleSlotNo = 0;
				 else
					 ModuleSlotNo = 1;

			 	 if(*Plc.Peripheral.AnalogInput.ModuleType[ModuleSlotNo] == AI_MODULE_TYPE_LTC241x)
					 {
						AdcModuleLTC241X(ModuleNo);
					 }
			 	 else
					 {
						 if(*Plc.Peripheral.AnalogInput.ModuleType[ModuleSlotNo] == AI_MODULE_TYPE_MAX1254)
							 {
								AdcModuleMAX125X(ModuleNo);
							 }
						 else
						 {
							 if(*Plc.Peripheral.AnalogInput.ModuleType[ModuleSlotNo] == AI_MODULE_TYPE_ADS1220)
								 {
								 	 AdcModuleADS1220(ModuleNo);
								 }
						 }
					 }
				break;

		}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(hadc == &hadc3)								//check which adc made interrupt
	{
		for(int i = 0; i < 80; i++)
		{
			adcData[i] = adcBuff[i];				//copy data to second buffer
		}
		convEnd = 1;								//set conv end flag
//		HAL_Delay(200);
//		HAL_ADC_Start_IT(&hadc3);
//		HAL_ADC_Start_DMA(&hadc3, (uint32_t *)adcBuff, 8);
//		HAL_ADC_Start_IT(&hadc3);
	}
}

//
//extern ADC_HandleTypeDef hadc3;
//extern strcPLC Plc;
//extern  long unsigned int AI_Data[8];




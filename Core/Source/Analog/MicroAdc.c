/*
 * MicroAdc.c
 *
 *  Created on: Oct 5, 2022
 *      Author: Sezgin Berber
 */

#include "MicroPeripheral.h"
#include "Registers.h"
#include "AnalogInput.h"
#include "DataFilter.h"

extern unsigned int DataArray[AI_CHANNEL_COUNT][10];

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc3;

extern strcPLC Plc;

 void OnChipAnalogChannelSet(ADC_HandleTypeDef *hadc, unsigned int Channel)
 {
 	ADC_ChannelConfTypeDef sConfig = {0};
 	unsigned int AdcInputNo;

 	if(hadc->Instance == ADC1)
 		{
 			switch(Channel)
 				{
 					case 0:	AdcInputNo = ADC_CHANNEL_8;		break;

 					case 1: AdcInputNo = ADC_CHANNEL_15;	break;

 					case 2: AdcInputNo = ADC_CHANNEL_14;	break;

 					case 3: AdcInputNo = ADC_CHANNEL_4;		break;

 					case 4: AdcInputNo = ADC_CHANNEL_13;	break;

 					case 5: AdcInputNo = ADC_CHANNEL_12;	break;

 					case 6: AdcInputNo = ADC_CHANNEL_11;	break;

 					case 7: AdcInputNo = ADC_CHANNEL_10;	break;

 					default:
 						AdcInputNo = ADC_CHANNEL_8;
 				}
 		}
 	else
 		{
 			if(hadc->Instance == ADC3)
 				{
 					switch(Channel)
 						{
 							case 0:	AdcInputNo = ADC_CHANNEL_8;		break;

 							case 1: AdcInputNo = ADC_CHANNEL_7;	break;

 							case 2: AdcInputNo = ADC_CHANNEL_6;	break;

 							case 3: AdcInputNo = ADC_CHANNEL_5;		break;

 							case 4: AdcInputNo = ADC_CHANNEL_4;		break;

 							case 5: AdcInputNo = ADC_CHANNEL_15;		break;

 							case 6: AdcInputNo = ADC_CHANNEL_14;		break;

 							case 7: AdcInputNo = ADC_CHANNEL_9;		break;

 							default:
 								AdcInputNo = ADC_CHANNEL_8;
 						}
 				}
 		}

 	sConfig.Channel = AdcInputNo;
 	sConfig.Rank = 1;
 	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
 	sConfig.Offset = 0;
 	 //sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

 	HAL_ADC_ConfigChannel(hadc, &sConfig);

 }

 void OnChipAdcChannelDataRead(unsigned short  ModuleNo)
 {
 	static unsigned short State[AI_MODULE_COUNT] = {0,0};
 	unsigned short SequenceNo;
 	unsigned int  AdcValue,Mask = 0x0001;
 	double dblValue;
 	ADC_HandleTypeDef *hadc;

 	//for(ModuleNo=0; ModuleNo<2; ModuleNo++)
 		{
 			if(ModuleNo == 0)
 				{
 					hadc = &hadc3;
 				}
 			else
 				{
 					hadc = &hadc1;
 				}

 			switch(State[ModuleNo])
 				{
 					case 0:
							*Plc.Peripheral.AnalogInput.SeqNo[ModuleNo] = 0;
							OnChipAnalogChannelSet(hadc, *Plc.Peripheral.AnalogInput.SeqNo[ModuleNo]);
							State[ModuleNo] = 1;
							break;

 					case 1:
							HAL_ADC_Start(hadc);
							//HAL_Delay(1);
							State[ModuleNo] = 2;
							break;

 					case 2:
 							if (HAL_ADC_PollForConversion(hadc, 1000)== HAL_OK)
 								 {
 									 State[ModuleNo] = 3;
 								 }
 							break;

 					case 3:
							if ((HAL_ADC_GetState(hadc) & HAL_ADC_STATE_REG_EOC ) == HAL_ADC_STATE_REG_EOC)
								{
									//HAL_Delay(1);
									SequenceNo =  *Plc.Peripheral.AnalogInput.ModuleChannelPos[ModuleNo] + *Plc.Peripheral.AnalogInput.SeqNo[ModuleNo];

									AdcValue = HAL_ADC_GetValue(hadc);

									HAL_ADC_Stop (hadc);

									if (*Plc.Peripheral.AnalogInput.AvarageEnable & (Mask << SequenceNo))
										{
											DataFilterValue(SequenceNo, AdcValue);
											dblValue = DataFilter(SequenceNo);
										}
									else
										{
											dblValue = AdcValue;
										}

									dblValue = dblValue * *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ModuleNo] / 1000;
									*Plc.Peripheral.AnalogInput.AnalogValue[SequenceNo] = dblValue;

									ChannelValueCalculate( SequenceNo, *Plc.Peripheral.AnalogInput.AnalogValue[SequenceNo]);


									State[ModuleNo] = 5;
								}
 							break;

// 					case 4:
//							HAL_Delay(1);
//							SequenceNo =  *Plc.Peripheral.AnalogInput.ModuleChannelPos[ModuleNo] + *Plc.Peripheral.AnalogInput.SeqNo[ModuleNo];
//
//							AdcValue = HAL_ADC_GetValue(hadc);
//
//							if (*Plc.Peripheral.AnalogInput.AvarageEnable & (Mask << SequenceNo))
//								{
//									DataFilterValue(SequenceNo, AdcValue);
//									dblValue = DataFilter(SequenceNo);
//									dblValue = dblValue * *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ModuleNo] / 1000;
//								}
//							else
//								{
//									dblValue = AdcValue;
//								}
//
//
//							*Plc.Peripheral.AnalogInput.AnalogValue[SequenceNo] = dblValue;
//
//							ChannelValueCalculate( SequenceNo, *Plc.Peripheral.AnalogInput.AnalogValue[SequenceNo]);
//
//							HAL_ADC_Stop (hadc);
//							State[ModuleNo] = 5;
// 							break;

 					case 5:
								*Plc.Peripheral.AnalogInput.SeqNo[ModuleNo] = *Plc.Peripheral.AnalogInput.SeqNo[ModuleNo]  + 1;
								if(*Plc.Peripheral.AnalogInput.SeqNo[ModuleNo] >= 8)
									{
										*Plc.Peripheral.AnalogInput.SeqNo[ModuleNo] = 0;
									}
								OnChipAnalogChannelSet(hadc, *Plc.Peripheral.AnalogInput.SeqNo[ModuleNo]);
								State[ModuleNo] = 1;
 							break;
 				}
 		}
 }

#include "MicroPeripheral.h"
#include "ConvertInteger.h"
#include "ConvertDouble.h"
#include "AnalogInput.h"
#include "LTC_241X_SPI.h" 

extern SPI_HandleTypeDef hspi1;
extern strcADC ADC_Modules[MAX_AI_BOARD_COUNT];
extern strcPLC Plc;

unsigned char LTC241XEOC(strcAdcINSTANCE *AdcInstance)
{
	unsigned char State=0;

	SPIModuleChipSelect(*AdcInstance, SPI_MODULE_ENABLE);

	if(AdcInstance->SPIx == &hspi1)
		{
			State = !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
		}

	SPIModuleChipSelect(*AdcInstance, SPI_MODULE_DISABLE);

	return State;
}


void LTC241XConfig(strcAdcINSTANCE *AdcInstance)
{
	AdcInstance->SetupRegister = 0;

	switch(AdcInstance->ChannelSeqNo)
		{
			case 0: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_ODD | 0x00;
							break;

			case 1: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_SGN | 0x00;
							break;

			case 2: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_ODD | 0x01;
							break;

			case 3: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_SGN | 0x01;
							break;

			case 4: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_ODD | 0x02;
							break;

			case 5: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_SGN | 0x02;
							break;

			case 6: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_ODD | 0x03;
							break;

			case 7: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_SGN | 0x03;
							break;

			case 8: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_ODD | 0x04;
							break;

			case 9: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_SGN | 0x04;
							break;

			case 10: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_ODD | 0x05;
							break;

			case 11: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_SGN | 0x05;
							break;

			case 12: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_ODD | 0x06;
							break;

			case 13: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_SGN | 0x06;
							break;

			case 14: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_ODD | 0x07;
							break;

			case 15: AdcInstance->SetupRegister = CONFIG_MUST | CONFIG_EN | CONFIG_SGL | CONFIG_SGN | 0x07;
							break;
		}

}


void LTC241XWriteChannel(strcAdcINSTANCE *AdcInstance)
{
		LTC241XConfig(AdcInstance);

		SPIModuleChipSelect(*AdcInstance, SPI_MODULE_ENABLE);
		
		HAL_SPI_Transmit(AdcInstance->SPIx , &AdcInstance->SetupRegister, 1, LTC241X_SPI_TIMEOUTS) ; //
		
		AdcInstance->SetupRegister = 0x00;
		HAL_SPI_Transmit(AdcInstance->SPIx , &AdcInstance->SetupRegister, 1, LTC241X_SPI_TIMEOUTS) ; //
		HAL_SPI_Transmit(AdcInstance->SPIx , &AdcInstance->SetupRegister, 1, LTC241X_SPI_TIMEOUTS) ; //
		HAL_SPI_Transmit(AdcInstance->SPIx , &AdcInstance->SetupRegister, 1, LTC241X_SPI_TIMEOUTS) ; //

		SPIModuleChipSelect(*AdcInstance, SPI_MODULE_DISABLE);

}

void LTC241XReadStatus(strcAdcINSTANCE *AdcInstance)
{

	SPIModuleChipSelect(*AdcInstance, SPI_MODULE_ENABLE);

	AdcInstance->SetupRegister = CONFIG_MUST ;
	HAL_SPI_Transmit(AdcInstance->SPIx, &AdcInstance->SetupRegister, 1 , LTC241X_SPI_TIMEOUTS );
	
	while( HAL_SPI_Receive(AdcInstance->SPIx, &AdcInstance->Status, 1 ,1000 ) != HAL_OK);

	SPIModuleChipSelect(*AdcInstance, SPI_MODULE_DISABLE);
}

void LTC241XReadChannelData(strcAdcINSTANCE *AdcInstance)
{

	unsigned char  Byte;
	unsigned char ReceivedByte[4];

	//
	// Next Channel To Be Read
	//

	AdcInstance->ChannelSeqNo = AdcInstance->ChannelSeqNo + 1;
	if(AdcInstance->ChannelSeqNo >= 8)
		{
			AdcInstance->ChannelSeqNo = 0;
		}
	LTC241XConfig(AdcInstance);
	
	//
	// Send Next Channel To Converted while Reading
	//
 	ReceivedByte[0] = AdcInstance->SetupRegister;

 	SPIModuleChipSelect(*AdcInstance, SPI_MODULE_ENABLE);

	while( HAL_SPI_Receive(AdcInstance->SPIx, ReceivedByte, 4 ,1000 ) != HAL_OK); //ChannelValue = 0;
	
	SPIModuleChipSelect(*AdcInstance, SPI_MODULE_DISABLE);

	AdcInstance->AdcValue = 0;
	for (Byte=0; Byte<4; Byte++)
		{
			AdcInstance->AdcValue <<= 8; AdcInstance->AdcValue |= ReceivedByte[Byte];
		}
}

void LTC241XDataAnalyse(unsigned char ModuleSeq, strcAdcINSTANCE *AdcInstance)
{
	unsigned char ChannelNoData;
	double dblChannelValue;
	signed int  ChannelValue=0;
	signed int AdcValue;

	AdcValue = AdcInstance->AdcValue;

	ChannelNoData = AdcValue;
	ChannelNoData = (ChannelNoData >> 1) & 0x1F;

	//
	// Check Conversion Status
	//
	ADC_Modules[ModuleSeq].Status = ADC_DATA_STATUS_CONVERSION_COMPLETED;
	if ( (AdcValue & LTC_2414_SIGN) &&  !(AdcValue & LTC_2414_MSB)) 	// 0V <= Vin  < 0.5*Vref
		{

			AdcValue >>= 6;
			AdcValue &= 0x007FFFFF;

			dblChannelValue = AdcValue; // / 1000;
			//dblChannelValue = dblChannelValue * 1800 / 8388.608;	//mV Olarak
			ChannelValue = dblChannelValue;
		}
	else
		{
			if ( !(AdcValue & LTC_2414_SIGN) &&  (AdcValue & LTC_2414_MSB)	)	// -0.5*Vref <= Vin < 0
				{

						//
						// Negatif Number
						//
						AdcValue >>= 6;
						AdcValue -= 1;
						AdcValue = ~AdcValue;
						AdcValue &= 0x007FFFFF;

						dblChannelValue = AdcValue; //;/ 1000;
						//dblChannelValue = dblChannelValue * 1800 / 8388.608;	//mV Olarak
						ChannelValue = dblChannelValue;
						ChannelValue *= -1;

				}
			else
				{
					if ( (AdcValue & LTC_2414_SIGN)  &&  (AdcValue & LTC_2414_MSB)	)	//    Vin >= 0.5*Vref
						{
							ChannelValue = 900;
						}
					else
						{
							if ( !(AdcValue & LTC_2414_SIGN)  &&  !(AdcValue & LTC_2414_MSB)	)	//    Vin <= -0.5*Vref
								{
									ChannelValue = -900;
								}
							else
								{
									ChannelValue = 0;
								}
						}
				}
		}

	switch(ChannelNoData)
		{

			case 0x10: ADC_Modules[ModuleSeq].Channel = 0; break;
			case 0x18: ADC_Modules[ModuleSeq].Channel = 1; break;
			case 0x11: ADC_Modules[ModuleSeq].Channel = 2; break;
			case 0x19: ADC_Modules[ModuleSeq].Channel = 3; break;
			case 0x12: ADC_Modules[ModuleSeq].Channel = 4; break;
			case 0x1A: ADC_Modules[ModuleSeq].Channel = 5; break;
			case 0x13: ADC_Modules[ModuleSeq].Channel = 6; break;
			case 0x1B: ADC_Modules[ModuleSeq].Channel = 7; break;

			default: ADC_Modules[ModuleSeq].Status = 	ADC_DATA_STATUS_NOT_READ;
		}
	AdcInstance->ReadChannelNo = ADC_Modules[ModuleSeq].Channel;
	AdcInstance->AdcValue = ChannelValue;
}


void LTC241XDataCalculate(unsigned char ModuleNo, strcAdcINSTANCE *AdcInstance)
{
	unsigned short SequenceNo;
	double dblValue;

	SequenceNo =  *Plc.Peripheral.AnalogInput.ModuleChannelPos[ModuleNo] + AdcInstance->ReadChannelNo;

	dblValue = AdcInstance->AdcValue;
	dblValue = dblValue * *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ModuleNo] / 1000;

	*Plc.Peripheral.AnalogInput.AnalogValue[SequenceNo] = dblValue;

	ChannelValueCalculate( SequenceNo, *Plc.Peripheral.AnalogInput.AnalogValue[SequenceNo]);
}

unsigned short AdcModuleLTC241XData(unsigned char ModuleNo,strcAdcINSTANCE *AdcInstance )
{
	unsigned short ModuleSeq = 0;
	switch (ModuleNo)
		{
			case ADC_MODULE_NO_00:
					ModuleSeq = 0;
					AdcInstance[0].ModuleSeq = 0;
					AdcInstance[0].SPIx = &hspi1;
					AdcInstance[0].EnableInput = 0;
					AdcInstance[0].InputConfigRegister = 0;
					AdcInstance[0].SetupRegister = 0;
					break;

			case ADC_MODULE_NO_01:
					ModuleSeq = 1;
					AdcInstance[1].ModuleSeq = 1;
					AdcInstance[1].SPIx = &hspi1;
					AdcInstance[1].EnableInput = 0;
					AdcInstance[1].InputConfigRegister = 0;
					AdcInstance[1].SetupRegister = 0;
					break;
		}
	return ModuleSeq;
}

void AdcModuleLTC241X(unsigned char ModuleNo)
{
	static unsigned char State[2]= {0,0};
	static strcAdcINSTANCE AdcInstance[2];
	unsigned short ModuleSeq;

	ModuleSeq =  AdcModuleLTC241XData(ModuleNo, &AdcInstance[0]);

	switch(State[ModuleSeq])
		{
			case 0:
					LTC241XReadChannelData(&AdcInstance[ModuleSeq]);

					State[ModuleSeq] = 2;
				break;

			case 2:
					if(LTC241XEOC(&AdcInstance[ModuleSeq]))
						{
							ADC_Modules[ModuleSeq].Status = ADC_DATA_STATUS_WILL_BE_READ;
							State[ModuleSeq] = 4;
						}
					break;

			case 4:

					LTC241XReadChannelData(&AdcInstance[ModuleSeq]);

					LTC241XDataAnalyse(ModuleSeq, &AdcInstance[ModuleSeq]);

					LTC241XDataCalculate(ModuleNo, &AdcInstance[ModuleSeq]);

					State[ModuleSeq] = 2;
					break;
		}
}
 

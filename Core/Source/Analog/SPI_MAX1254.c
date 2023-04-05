#include "MicroPeripheral.h"
#include "Registers.h"
#include <SPI_MAX1254.h>

extern strcADC ADC_Modules[MAX_AI_BOARD_COUNT];
extern strcPLC Plc;

unsigned char MAX1254ChannelNo(strcAdcINSTANCE AdcInstance)
{
	unsigned char ChannelNo = 2;
	switch(AdcInstance.ChannelSeqNo)
		{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
					ChannelNo = AdcInstance.ChannelSeqNo + 2;
				break;

			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
					ChannelNo = (AdcInstance.ChannelSeqNo % 8) + 2;
				break;
		}
	return ChannelNo;
}


void MAX1254StartManualConversion(strcAdcINSTANCE AdcInstance)
{
	unsigned char SendChar;
	unsigned char ChannelNo ;
	ChannelNo =  MAX1254ChannelNo(AdcInstance);

	SendChar = MAX1254_START_MANUAL_TRIGGER_CONVERSION | ChannelNo;

	HAL_SPI_Transmit(AdcInstance.SPIx, &SendChar , 1,  MAX1254_SPI_TIMEOUTS);
}

void MAX1254ReadAlert(SPI_HandleTypeDef* SPIx, unsigned  int *Alert)
{
	unsigned char SendChar = MAX1254_READ_ALARM_REG;
	unsigned char ReceivedByte;

	HAL_SPI_Transmit(SPIx, &SendChar, 1,  MAX1254_SPI_TIMEOUTS);

	 HAL_SPI_Receive(SPIx, &ReceivedByte , 1, MAX1254_SPI_TIMEOUTS);  *Alert = ReceivedByte;  *Alert <<= 8;
	 HAL_SPI_Receive(SPIx, &ReceivedByte , 1, MAX1254_SPI_TIMEOUTS);  *Alert = ReceivedByte;  *Alert <<= 8;
	 HAL_SPI_Receive(SPIx, &ReceivedByte , 1, MAX1254_SPI_TIMEOUTS);  *Alert = ReceivedByte;  *Alert <<= 8;
	 HAL_SPI_Receive(SPIx, &ReceivedByte , 1, MAX1254_SPI_TIMEOUTS);  *Alert = ReceivedByte;

}

void MAX1254ReadChannelData(strcAdcINSTANCE *AdcInstance)
{
	unsigned char SendChar,HighByte,LowByte;
	unsigned short  ChannelValue;
	unsigned char ChannelNo;

	ChannelNo = MAX1254ChannelNo(*AdcInstance);

	SendChar = MAX1254_READ_CURRENT_DATA_REG_FOR_SELECTED_CHANNEL | ChannelNo;

	HAL_SPI_Transmit(AdcInstance->SPIx, &SendChar , 1,  MAX1254_SPI_TIMEOUTS);

	HAL_SPI_Receive(AdcInstance->SPIx, &HighByte, 1, MAX1254_SPI_TIMEOUTS);
	HAL_SPI_Receive(AdcInstance->SPIx, &LowByte, 1, MAX1254_SPI_TIMEOUTS);

	ChannelValue = (HighByte * 0x100)+ LowByte;
	ChannelValue >>= 4;

	AdcInstance->AdcValue = ChannelValue;

}



void MAX1254ReadConfig(strcAdcINSTANCE *AdcInstance)
{
	unsigned char SendChar,HighByte,LowByte;
	SendChar = MAX1254_READ_GLOBAL_CONFIG_REG;

	SPIModuleChipSelect(*AdcInstance, 1); // Enable  	SPI_MAX1254_CS2_ENABLE;

	HAL_SPI_Transmit(AdcInstance->SPIx, &SendChar, 1, MAX1254_SPI_TIMEOUTS);
	HAL_Delay(3);

	HAL_SPI_Receive(AdcInstance->SPIx, &HighByte, 1, MAX1254_SPI_TIMEOUTS);
	HAL_SPI_Receive(AdcInstance->SPIx, &LowByte, 1, MAX1254_SPI_TIMEOUTS);

	AdcInstance->EnableInput = ((HighByte * 0x100) + LowByte) >> 4;
	HAL_Delay(3);

	HAL_SPI_Receive(AdcInstance->SPIx, &HighByte, 1, MAX1254_SPI_TIMEOUTS);
	HAL_SPI_Receive(AdcInstance->SPIx, &LowByte, 1, MAX1254_SPI_TIMEOUTS);

	AdcInstance->InputConfigRegister = ((HighByte * 0x100) + LowByte) >> 4;
	
	HAL_Delay(3);
	HAL_SPI_Receive(AdcInstance->SPIx, &AdcInstance->SetupRegister, 1, MAX1254_SPI_TIMEOUTS);

	SPIModuleChipSelect(*AdcInstance, 0); // Disable SPI_MAX1254_CS2_DISABLE;

}


void MAX1254Reset(strcAdcINSTANCE *AdcInstance)
{
	unsigned char SendChar;

	SPIModuleChipSelect(*AdcInstance, 1);

	SendChar = MAX1254_RESET_DEVICE;

	HAL_SPI_Transmit(AdcInstance->SPIx, &SendChar,1, MAX1254_SPI_TIMEOUTS );

	SPIModuleChipSelect(*AdcInstance, 1);
}

void MAX1254ClearChannelAlarm(SPI_HandleTypeDef* SPIx, unsigned char Channel)
{
	unsigned char SendChar;
	SendChar = MAX1254_CLEAR_ALARM_FOR_SELECTED_CHANNEL | Channel;
	HAL_SPI_Transmit(SPIx, &SendChar ,1, MAX1254_SPI_TIMEOUTS );
}

void MAX1254ClearAlarm(SPI_HandleTypeDef* SPIx)
{
	unsigned char SendChar;
	SendChar = MAX1254_CLEAR_ALARM_FOR_ALL_CHANNELS;

	HAL_SPI_Transmit(SPIx, &SendChar, 1, MAX1254_SPI_TIMEOUTS );
}

void MAX1254WriteChannelConfig(strcAdcINSTANCE AdcInstance, unsigned  char Config )
{
	unsigned char SendChar;
	unsigned char ChannelNo;
	ChannelNo =  MAX1254ChannelNo(AdcInstance);

	SendChar = MAX1254_WRITE_CONFIG_REG_FOR_SELECTED_CHANNEL | ChannelNo;

	SPIModuleChipSelect(AdcInstance, 1);

	HAL_SPI_Transmit(AdcInstance.SPIx, &SendChar, 1, MAX1254_SPI_TIMEOUTS);

	HAL_SPI_Transmit(AdcInstance.SPIx, &Config,5,MAX1254_SPI_TIMEOUTS) ;

	SPIModuleChipSelect(AdcInstance, 0);
}

void MAX1254ReadChannelConfig(strcAdcINSTANCE AdcInstance,unsigned char *Config)
{
	unsigned char SendChar;
	unsigned char ChannelNo;

	ChannelNo =  MAX1254ChannelNo(AdcInstance);
	SendChar = MAX1254_READ_CONFIG_REG_FOR_SELECTED_CHANNEL | ChannelNo ;

	SPIModuleChipSelect(AdcInstance, 1);

	HAL_SPI_Transmit(AdcInstance.SPIx, &SendChar,1 ,MAX1254_SPI_TIMEOUTS );
	HAL_SPI_Receive(AdcInstance.SPIx, Config, 1, MAX1254_SPI_TIMEOUTS);

	SPIModuleChipSelect(AdcInstance, 0);

}

void  MAX1254Config(strcAdcINSTANCE AdcInstance)
{
	unsigned char SendByte ,HighByte, LowByte;
	SendByte = MAX1254_WRITE_GLOBAL_CONFIG_REG;

	SPIModuleChipSelect(AdcInstance, 1);

	HAL_SPI_Transmit( AdcInstance.SPIx, &SendByte, 1, MAX1254_SPI_TIMEOUTS );

	AdcInstance.EnableInput = AdcInstance.EnableInput << 4;

	HighByte = AdcInstance.EnableInput >> 8;
	LowByte	 = AdcInstance.EnableInput & 0x00FF;

	HAL_SPI_Transmit(AdcInstance.SPIx, &HighByte, 1, MAX1254_SPI_TIMEOUTS);
	HAL_SPI_Transmit(AdcInstance.SPIx, &LowByte, 1, MAX1254_SPI_TIMEOUTS);
	

	AdcInstance.InputConfigRegister  =  AdcInstance.InputConfigRegister  >> 4;

	HighByte = AdcInstance.InputConfigRegister >>8;
	LowByte  = AdcInstance.InputConfigRegister & 0x00FF;


	HAL_SPI_Transmit(AdcInstance.SPIx,&HighByte, 1, MAX1254_SPI_TIMEOUTS);
	HAL_SPI_Transmit(AdcInstance.SPIx,&LowByte, 1, MAX1254_SPI_TIMEOUTS);

	HAL_SPI_Transmit(AdcInstance.SPIx, &AdcInstance.SetupRegister, 1, MAX1254_SPI_TIMEOUTS);

	SPIModuleChipSelect(AdcInstance, 0);

}

void MAX1254ChannelStart(strcAdcINSTANCE AdcInstance)
{
	//
	// Start Convertion
	//

	SPIModuleChipSelect(AdcInstance, 1);	//SPI_MAX1254_CS2_ENABLE;


	MAX1254StartManualConversion(AdcInstance);

	SPIModuleChipSelect(AdcInstance, 0);	//SPI_MAX1254_CS2_DISABLE;

}

void MAX1254ChannelRead(strcAdcINSTANCE *AdcInstance)
{
	//
	// Read Convertion
	//

	SPIModuleChipSelect(*AdcInstance, 1);

	MAX1254ReadChannelData(AdcInstance);

	SPIModuleChipSelect(*AdcInstance, 0);

}


void AdcModuleMAX125X(unsigned char ModuleNo)
{
	unsigned char i, ModuleSeq=0;
	unsigned char SequenceNo;
	unsigned char ReadConfig;
	double dblValue;
	static unsigned char Config = 6;
	static unsigned short Status[2]= {0,0};

	#define MAX1254_SETUP_REG			0x05
	#define MAX1254_ENABLE_CHANNEL		0x0FFF
	#define MAX1254_INPUT_CONFIG_REG	0x0000

	static unsigned short WaitCounter[2]= {0,0};
	static strcAdcINSTANCE AdcInstance[2];
	static unsigned char RepeatNeed = 0;

	switch (ModuleNo)
		{
			case ADC_MODULE_NO_00:
					ModuleSeq=0;
					AdcInstance[ModuleSeq].ModuleSeq = 0;
					AdcInstance[ModuleSeq].SPIx = &hspi1;
					AdcInstance[ModuleSeq].EnableInput = MAX1254_ENABLE_CHANNEL;
					AdcInstance[ModuleSeq].InputConfigRegister = MAX1254_INPUT_CONFIG_REG;
					AdcInstance[ModuleSeq].SetupRegister = MAX1254_SETUP_REG;				// Internal Voltage Ref
					break;

			case ADC_MODULE_NO_01:
					ModuleSeq = 1;
					AdcInstance[ModuleSeq].ModuleSeq = 1;
					AdcInstance[ModuleSeq].SPIx = &hspi1;
					AdcInstance[ModuleSeq].EnableInput = MAX1254_ENABLE_CHANNEL;
					AdcInstance[ModuleSeq].InputConfigRegister = MAX1254_INPUT_CONFIG_REG;
					AdcInstance[ModuleSeq].SetupRegister = MAX1254_SETUP_REG;
					break;
		}


		if(ADC_Modules[ModuleNo].FirstRead )
			{
				ADC_Modules[ModuleNo].Channel     = 0;
				ADC_Modules[ModuleNo].NextChannel = 1;

				ADC_Modules[ModuleNo].FirstRead = 0;
			}

		SequenceNo = ADC_Modules[ModuleNo].Channel  + *Plc.Peripheral.AnalogInput.ModuleChannelPos[ModuleNo];

		switch(Status[ModuleSeq])
			{
				case 0:
						WaitCounter[ModuleSeq] 	= 0;

						MAX1254Config(AdcInstance[ModuleSeq]);
						HAL_Delay(200);

						Status[ModuleSeq] = 1;
					break;

				case 1:
						//
						// Config Register Checking
						//
						RepeatNeed = 0;
					 	for(i=0;i<8;i++)
							 {
								 MAX1254ReadChannelConfig(AdcInstance[ModuleSeq], &ReadConfig);
								 if(ReadConfig != Config)
									 {
										MAX1254WriteChannelConfig(AdcInstance[ModuleSeq], Config );
										RepeatNeed = 1;
									 }
							 }
					 	if(RepeatNeed == 0 )
							 {
								 MAX1254ReadConfig(&AdcInstance[ModuleSeq]);
								 if(AdcInstance[ModuleSeq].EnableInput == MAX1254_ENABLE_CHANNEL   && AdcInstance[ModuleSeq].InputConfigRegister == MAX1254_INPUT_CONFIG_REG  &&  AdcInstance[ModuleSeq].SetupRegister  == MAX1254_SETUP_REG)
									 {
										 AdcInstance[ModuleSeq].ChannelSeqNo = 0;
										Status[ModuleSeq] = 4;
									 }
								 else
									 {
										 if(WaitCounter[ModuleSeq]<5)
											 {
												 WaitCounter[ModuleSeq] = WaitCounter[ModuleSeq] + 1;
											 }
										 else
										 {
											 Status[ModuleSeq] = 0;
										 }
									 }
							 }
					break;

				case 2:
						ADC_Modules[ModuleNo].Channel = ADC_Modules[ModuleNo].Channel + 1;
						if (ADC_Modules[ModuleNo].Channel >= 8 )
							{
								ADC_Modules[ModuleNo].Channel  = 0;
							}
						AdcInstance[ModuleSeq].ChannelSeqNo = ADC_Modules[ModuleNo].Channel;

						MAX1254ChannelStart(AdcInstance[ModuleSeq]);

						WaitCounter[ModuleSeq] 	= 0;
						Status[ModuleSeq] = 3;
					break;

				case 3:
						if(++WaitCounter[ModuleSeq]>= 2 )
							{
								Status[ModuleSeq] = 4;
							}
					break;

				case 4:
						for(ADC_Modules[ModuleNo].Channel =0; ADC_Modules[ModuleNo].Channel <8 ;ADC_Modules[ModuleNo].Channel ++ )
							{
								AdcInstance[ModuleSeq].ChannelSeqNo = ADC_Modules[ModuleNo].Channel;

								MAX1254ChannelRead(&AdcInstance[ModuleSeq]);
								SequenceNo = ADC_Modules[ModuleNo].Channel  + *Plc.Peripheral.AnalogInput.ModuleChannelPos[ModuleNo];

								dblValue = AdcInstance[ModuleSeq].AdcValue;
								dblValue = dblValue * *Plc.Peripheral.AnalogInput.ModuleResolutionMultiplier[ModuleNo] / 1000;

								*Plc.Peripheral.AnalogInput.AnalogValue[SequenceNo] = dblValue;

								ChannelValueCalculate(SequenceNo, *Plc.Peripheral.AnalogInput.AnalogValue[SequenceNo]);
							}

					break;
			}
}


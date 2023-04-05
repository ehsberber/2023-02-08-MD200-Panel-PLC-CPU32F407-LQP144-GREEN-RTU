#include "MicroPeripheral.h"

#ifndef ANALOG_INPUT_DEF
#define 	ANALOG_INPUT_DEF



	typedef struct
			{
				SPI_HandleTypeDef* SPIx;
				unsigned char ModuleSeq;
				unsigned char ChannelSeqNo;
				unsigned char ReadChannelNo;
				unsigned short EnableInput;
				unsigned short InputConfigRegister;
				unsigned char SetupRegister;
				signed int AdcValue;
				long lAdcValue;
				unsigned char Status;
			} strcAdcINSTANCE;


	#define LTC241X_SPI_TIMEOUTS								100

	#define MAX1254_START_MANUAL_TRIGGER_CONVERSION 			0x00
	#define MAX1254_READ_ALARM_REG 								0x10
	#define MAX1254_READ_CURRENT_DATA_REG_FOR_SELECTED_CHANNEL	0x20
	#define MAX1254_READ_CURRENT_DATA_REG_FOR_ALL_CHANNELS 		0x30
	#define MAX1254_READ_CONFIG_REG_FOR_SELECTED_CHANNEL 		0x40
	#define MAX1254_READ_GLOBAL_CONFIG_REG						0x50
	#define MAX1254_RESET_DEVICE 								0x70
	#define MAX1254_CLEAR_ALARM_FOR_SELECTED_CHANNEL 			0x80
	#define MAX1254_CLEAR_ALARM_FOR_ALL_CHANNELS 				0x90
	#define MAX1254_WRITE_CURRENT_DATA_REG_FOR_SELECTED_CHANNEL 0xA0
	#define MAX1254_WRITE_CURRENT_DATA_REG_FOR_ALL_CHANNELS		0xB0
	#define MAX1254_WRITE_CONFIG_REG_FOR_SELECTED_CHANNEL		0xC0
	#define MAX1254_WRITE_GLOBAL_CONFIG_REG 					0xD0

	#define MAX1254_SPI_TIMEOUTS 								100
	#define ADS1220_SPI_TIMEOUTS								100

	#define SPI_MODULE_ENABLE									1
	#define SPI_MODULE_DISABLE									0

	#define SPI_MODULE_CS1_ENABLE			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET)
	#define SPI_MODULE_CS1_DISABLE			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET)

	#define SPI_MODULE_CS2_ENABLE			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_RESET)
	#define SPI_MODULE_CS2_DISABLE			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_SET)


	#define MAX_AI_BOARD_COUNT 								8
	#define ADC_DATA_STATUS_CONVERSION_COMPLETED 			0x80
	#define	ADC_DATA_STATUS_NOT_READ 						0x01
	#define ADC_DATA_STATUS_NOT_RESPONDING					0x02
	#define ADC_DATA_STATUS_WILL_BE_READ					0x04


	#define ADC_DATA_STATUS_OUT_OF_RANGE_HIGH 				0x10
	#define ADC_DATA_STATUS_OUT_OF_RANGE_LOW 				0x20


	#define AI_BOARD_NO_ACTIVE_CHANNEL						0x01
	#define AI_BOARD_NO_FINISHED							0x02
	#define AI_BOARD_NO_CHANNEL_IN_USE						0x04
	#define AI_BOARD_WAITING_EOC							0x08
	#define AI_BOARD_NO_CHANNEL 							0x08
	//#define AI_BOARD_NO_NEXT								0x40
	#define AI_BOARD_NO_FIRST_START							0x80

	#define TYPE_OF_CALCULATE_MASK							0x00FF
		#define TYPE_OF_CALCULATE_ANALOG_INPUT				0x0000
		#define	TYPE_OF_CALCULATE_CLOCK_INPUT				0x0001
		#define	TYPE_OF_CALCULATE_PT_100					0x0002
		#define	TYPE_OF_CALCULATE_ZIRCONIA_OXYGEN_PROBE		0x0003
		#define TYPE_OF_CALCULATE_ANALOG_INPUT_0_20			0x0004
		#define TYPE_OF_CALCULATE_ZIRCONIA_THERMO_COUPLE_R	0x0005
		#define TYPE_OF_CALCULATE_FROM_TABLE				0x0006
	#define TYPE_OF_CALCULATE_PARAMETER						0xFF00


	#define TYPE_COUNT_OF_AI_SENSOR 						6
	#define AI_TYPE_COUNT									16
	#define AI_TYPE_LEVEL									0x00
	#define AI_TYPE_GD										0x01
	#define AI_TYPE_PRESSURE								0x02
	#define AI_TYPE_TEMPERATURE								0x03
	#define AI_TYPE_FLAME_DETECTOR   						0x04
	#define AI_TYPE_CATHODIC_PROTECTION						0x05


	#define ON_BOARD_LTC_249X_SLAVE_ADDRESS					0x28


	#define  ADC_ON_CPU_NO_00 			0
	#define  ADC_ON_CPU_NO_01 			1

	#define  ADC_ONBAORD_IC_NO_00 	  	2
	#define  ADC_ONBAORD_IC_NO_01 	  	3
	#define  ADC_MODULE_NO_00 	  		4
	#define  ADC_MODULE_NO_01 	  		5

	#define  ADC_ON_CPU_00 		(0x00000001 << ADC_ON_CPU_NO_00)
	#define  ADC_ON_CPU_01 		(0x00000001 << ADC_ON_CPU_NO_01)
	#define  ADC_ONBAORD_IC_00 	(0x00000001 << ADC_ONBAORD_IC_NO_00)
	#define  ADC_ONBOARD_IC_01 	(0x00000001 << ADC_ONBAORD_IC_NO_01)
	#define  ADC_MODULE_00 	  	(0x00000001 << ADC_MODULE_NO_00)
	#define  ADC_MODULE_01 	  	(0x00000001 << ADC_MODULE_NO_01)

	#define  AI_MODULE_TYPE_LTC241x		0
	#define  AI_MODULE_TYPE_MAX1254		1
	#define  AI_MODULE_TYPE_ADS1220		2

	#define ADC_RESOLUTION 				1024

	void ChannelValueUpDown(void);
	void ChannelValueChange(void);
	void AnalogInputs(void);
	void AdcCritical(void);
	void FindErrorNumber(unsigned char Channel);
	void AnalogInputReadFromOnBoardADC(void);
	void SPIModuleChipSelect(strcAdcINSTANCE AdcInstance, unsigned char Enable);
	void ChannelValueCalculate(unsigned char SequenceNo,signed int ChannelValue);

#endif

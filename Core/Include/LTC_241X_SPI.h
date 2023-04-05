
#ifndef APPLICATION_USER_HEADER_LTC_241X_SPI_H_
#define APPLICATION_USER_HEADER_LTC_241X_SPI_H_

	#include "MicroPeripheral.h"
	#include "AnalogInput.h"
	#include "Registers.h"
	//
	// CONFIG REGISTER

	//7:6 Always 1:0
	//5: EN 	EN : 1, the following 5 bits are used to update EN:0 previous channel selection is kept and the following bits are ignored
	//4: SGL 	SGL:1 SINGLE ENDED , SGL:0 DIFFERANTIAL INPUT
	#define CONFIG_MUST		0x80
	#define CONFIG_EN 		0x20
	#define CONFIG_SGL		0x10
	#define CONFIG_ODD		0x00
	#define CONFIG_SGN		0x08

	#define CONFIG_EN_PREVIOUS 		0x00



	#define LTC_2414_EOC	0x80000000
	#define LTC_2414_SIGN	0x20000000
	#define LTC_2414_MSB	0x10000000


	void LTC241X(strcAdcINSTANCE *AdcInstance, strcADC *ADC_Data);
	void LTC241XReadChannelData(strcAdcINSTANCE *AdcInstance);
	void LTC241XReadStatus(strcAdcINSTANCE *AdcInstance);
	void LTC241Xwritechannel(strcAdcINSTANCE *AdcInstance);
	void LTC241XConfig(strcAdcINSTANCE *AdcInstance);
	unsigned char LTC241XEOC(strcAdcINSTANCE *AdcInstance);
	void AdcModuleLTC241X(unsigned char ModuleNo);

#endif

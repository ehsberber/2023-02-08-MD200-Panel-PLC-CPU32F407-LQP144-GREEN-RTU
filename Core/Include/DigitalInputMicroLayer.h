#ifndef DIGITAL_INPUT_MICRO_LAYER_DEF
	#define DIGITAL_INPUT_MICRO_LAYER_DEF
	//
	// DIGITAL INPUT MICRO PIN
	//
	#define DIGITAL_INPUT_00_IDR							GPIOB->IDR
	#define DIGITAL_INPUT_00								0x00001000				// PB.12

	#define DIGITAL_INPUT_01_IDR							GPIOE->IDR
	#define DIGITAL_INPUT_01								0x00000400				// PE.10

	#define DIGITAL_INPUT_02_IDR							GPIOB->IDR
	#define DIGITAL_INPUT_02								0x00004000				// PB.14

	#define DIGITAL_INPUT_03_IDR							GPIOB->IDR
	#define DIGITAL_INPUT_03								0x00008000				// PB.15

	#define DIGITAL_INPUT_04_IDR							GPIOG->IDR
	#define DIGITAL_INPUT_04								0x00000020				// PG.5

	#define DIGITAL_INPUT_05_IDR							GPIOG->IDR
	#define DIGITAL_INPUT_05								0x00000040				// PG.6

	#define DIGITAL_INPUT_06_IDR							GPIOD->IDR
	#define DIGITAL_INPUT_06								0x00000400				// PD.10

	#define DIGITAL_INPUT_07_IDR							GPIOD->IDR
	#define DIGITAL_INPUT_07								0x00000800				// PD.11

	#define DIGITAL_INPUT_08_IDR							GPIOG->IDR
	#define DIGITAL_INPUT_08								0x00000080				// PG.7

	#define DIGITAL_INPUT_09_IDR							GPIOG->IDR
	#define DIGITAL_INPUT_09								0x00000100				// PG.8

	#define DIGITAL_INPUT_10_IDR							GPIOG->IDR
	#define DIGITAL_INPUT_10								0x00004000				// PG.14

	#define DIGITAL_INPUT_11_IDR							GPIOG->IDR
	#define DIGITAL_INPUT_11								0x00002000				// PG.13

	#define DIGITAL_INPUT_12_IDR							GPIOG->IDR
	#define DIGITAL_INPUT_12								0x00001000				// PG.12

	#define DIGITAL_INPUT_13_IDR							GPIOG->IDR
	#define DIGITAL_INPUT_13								0x00000800				// PG.11

	#define DIGITAL_INPUT_14_IDR							GPIOD->IDR
	#define DIGITAL_INPUT_14								0x00000400				// PG.10

	#define DIGITAL_INPUT_15_IDR							GPIOD->IDR
	#define DIGITAL_INPUT_15								0x00000200				// PG.9



	void DigitalInputReadFromMicroPort(unsigned char InputPosition);

#endif

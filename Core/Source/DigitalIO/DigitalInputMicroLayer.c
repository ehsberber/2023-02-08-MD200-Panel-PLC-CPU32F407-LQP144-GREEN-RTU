#include "MicroPeripheral.h"
#include "DigitalInputMicroLayer.h" 
#include "Registers.h"

extern strcREGISTERS  Registers; 
extern strcPLC Plc;

void DigitalInputReadFromMicroPort(unsigned char InputPosition)
{
	unsigned short DebugMod,Debug;
	unsigned short LSB = 0x0001;

	DebugMod = Plc.Peripheral.DigitalInput.DebugMode->DIs;
	Debug = Plc.Peripheral.DigitalInput.Debug->DIs;

	//
	// DIGITAL INPUT 0
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_00_IDR  & DIGITAL_INPUT_00) ) 	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}


	LSB <<= 1;

	//
	// DIGITAL INPUT 1
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_01_IDR  & DIGITAL_INPUT_01) )	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}
	LSB <<= 1;		

	//
	// DIGITAL INPUT 2
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_02_IDR  & DIGITAL_INPUT_02) )	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}
	LSB <<= 1;

	//
	// DIGITAL INPUT 3
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_03_IDR  & DIGITAL_INPUT_03) )	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}
	LSB <<= 1;

	//
	// DIGITAL INPUT 4
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_04_IDR  & DIGITAL_INPUT_04) )	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}

	LSB <<= 1;
	//
	// DIGITAL INPUT 5
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_05_IDR  & DIGITAL_INPUT_05) )	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}
	LSB <<= 1;
	//
	// DIGITAL INPUT 6
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_06_IDR  & DIGITAL_INPUT_06) )	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}
	LSB <<= 1;

	//
	// DIGITAL INPUT 7
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_07_IDR  & DIGITAL_INPUT_07) )	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}

	LSB <<= 1;
	//
	// DIGITAL INPUT 8
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_08_IDR  & DIGITAL_INPUT_08) )	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}
	LSB <<= 1;
	//
	// DIGITAL INPUT 9
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_09_IDR  & DIGITAL_INPUT_09) )	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}
	LSB <<= 1;
	//
	// DIGITAL INPUT 10
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_10_IDR  & DIGITAL_INPUT_10) )	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}
	LSB <<= 1;
	//
	// DIGITAL INPUT 11
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_11_IDR  & DIGITAL_INPUT_11) )	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}
	LSB <<= 1;
	//
	// DIGITAL INPUT 12
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_12_IDR  & DIGITAL_INPUT_12) )	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}
	LSB <<= 1;
	//
	// DIGITAL INPUT 13
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_13_IDR  & DIGITAL_INPUT_13) )	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}
	LSB <<= 1;
	//
	// DIGITAL INPUT 14
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_14_IDR  & DIGITAL_INPUT_14) )	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}
	LSB <<= 1;
	//
	// DIGITAL INPUT 15
	//
	if(DebugMod & LSB)
		{
			if( Debug & LSB ) 									Registers.Input[InputPosition] |= LSB ; else   Registers.Input[InputPosition] &= ~LSB;
		}
	else
		{
			if( (DIGITAL_INPUT_15_IDR  & DIGITAL_INPUT_15) )	Registers.Input[InputPosition] &= ~LSB ; else   Registers.Input[InputPosition] |= LSB;
		}

 
}


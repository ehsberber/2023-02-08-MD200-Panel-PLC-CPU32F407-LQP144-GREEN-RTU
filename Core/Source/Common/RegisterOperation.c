#include "ModBusRegister.h"
#include "ConvertString.h"
#include "Registers.h"
#include "DataType.h"

extern strcREGISTERS  Registers; 

void IntToArray(unsigned char *DataRegister,unsigned short DataStartPosition,unsigned int Value)
{
	(*(unsigned int *)&DataRegister[DataStartPosition ]) = Value;
}

void signedIntToArray(unsigned char *DataRegister,unsigned short DataStartPosition,signed int Value)
{
	(*(signed int *)&DataRegister[DataStartPosition ]) = Value;
}

unsigned int *IntOrArray2(unsigned char *DataRegister,unsigned short DataStartPosition,unsigned int Value)
{
	unsigned int *IntValue;
	unsigned int returnValue;
	IntValue = &returnValue;
	*(unsigned int *)&DataRegister[DataStartPosition] |= Value; 
	IntValue = (unsigned int *)&DataRegister[DataStartPosition];
	return IntValue;
}


void IntOrArray(unsigned char *DataRegister,unsigned short DataStartPosition,unsigned int Value)
{
	*(unsigned int *)&DataRegister[DataStartPosition ] |= Value; 
}

void IntAndArray(unsigned char *DataRegister,unsigned short DataStartPosition,unsigned int Value)
{
	*(unsigned int *)&DataRegister[DataStartPosition ] &= Value; 
}

void ShortToArray(unsigned char *DataRegister,unsigned short DataStartPosition,unsigned short Value)
{
	(*(unsigned short *)&DataRegister[DataStartPosition ]) = Value;
}
void ShortOrArray(unsigned char *DataRegister,unsigned short DataStartPosition,unsigned short Value)
{
	*(unsigned short *)&DataRegister[DataStartPosition ] |= Value; 
}

void ShortAndArray(unsigned char *DataRegister,unsigned short DataStartPosition,unsigned short Value)
{
	*(unsigned short *)&DataRegister[DataStartPosition ] &= Value; 
}
unsigned int IntFromArray(unsigned char *DataRegister,unsigned short DataStartPosition)
{
	unsigned int Value = 0;
	Value = *(unsigned int *)&DataRegister[DataStartPosition];
	return Value;
}

void IntAddArray(unsigned char *DataRegister,unsigned short DataStartPosition,unsigned int Value)
{
	unsigned int Current;
	Current = IntFromArray(DataRegister, DataStartPosition);
	Current += Value;
	*(unsigned int *)&DataRegister[DataStartPosition] = Current;
}

unsigned int IntFromConstArray(const unsigned char *DataRegister,unsigned int DataStartPosition)
{
	unsigned int Value = 0;
	Value = *(unsigned int *)&DataRegister[DataStartPosition];
	return Value;
}

signed int signedIntFromArray(unsigned char *DataRegister,unsigned short DataStartPosition)
{
	signed int Value = 0;
	Value = *(signed int *)&DataRegister[DataStartPosition];
	
	return Value;
}

signed int signedIntFromArrayReverse(unsigned char *DataRegister,unsigned short DataStartPosition)
{
	unsigned char ByteCounter;
	signed int Value = 0;
	for(ByteCounter=0; ByteCounter<4; ByteCounter++)
		{
			Value <<= 8;	
			Value = DataRegister[DataStartPosition++];
		}
	return Value;
}

signed short signedShortFromArrayReverse(unsigned char *DataRegister,unsigned int DataStartPosition)
{
	unsigned char ByteCounter;
	signed short Value = 0;
	for(ByteCounter=0;ByteCounter<2;ByteCounter++)
		{
			Value <<= 8;	
			Value = DataRegister[DataStartPosition++];
		}
	return Value;
}


unsigned int IntFromArrayReverse(unsigned char *DataRegister,unsigned short DataStartPosition)
{
	unsigned char ByteCounter;
	unsigned int Value = 0;
	for(ByteCounter=0; ByteCounter<4; ByteCounter++)
		{
			Value <<= 8;	
			Value = DataRegister[DataStartPosition++];
		}
	return Value;
}

unsigned int ShortFromArrayReverse(unsigned char *DataRegister,unsigned short DataStartPosition)
{
	unsigned char ByteCounter;
	unsigned int Value = 0;
	for(ByteCounter=0; ByteCounter<2; ByteCounter++)
		{
			Value <<= 8;	
			Value = DataRegister[DataStartPosition++];
		}
	return Value;
}

signed int signedIntFromConstArray(unsigned char const *DataRegister,unsigned int DataStartPosition)
{
	signed int Value = 0;

	Value = *(signed int *)&DataRegister[DataStartPosition];
	return Value;
}
unsigned short ShortFromArray(unsigned char *DataRegister,unsigned short DataStartPosition)
{
	unsigned short Value;
	Value = *(unsigned short *)&DataRegister[DataStartPosition];
	return Value;
}

unsigned short ShortFromConstArray(const unsigned char *DataRegister,unsigned int DataStartPosition)
{
	unsigned short Value;
	Value = *(const unsigned short *)&DataRegister[DataStartPosition];
	return Value;
}

signed short signedShortFromArray(unsigned char *DataRegister,unsigned int DataStartPosition)
{
	signed short Value;
	Value = *(signed short *)&DataRegister[DataStartPosition];
	return Value;
}
//
//short getRegisterShort(unsigned char RegisterType,unsigned short Address )
//{
//	unsigned short Value = 0;
//	switch(RegisterType)
//		{
//			case 	MDB_FNC_CR:
//					Value = ShortFromArray(Registers.Coil, Address);
//					break;
//
//			case 	MDB_FNC_SR:
//					Value = ShortFromArray(Registers.Status, Address);
//					break;
//
//			case 	MDB_FNC_IS:
//					Value = ShortFromArray(Registers.Input, Address);
//					break;
//
//			case 	MDB_FNC_HR:
//					Value = ShortFromArray(Registers.Holding, Address);
//					break;
//		}
//	return Value;
//}
//
//int getRegisterInt(unsigned char RegisterType,unsigned short Address )
//{
//	int Value = 0;
//	switch(RegisterType)
//		{
//			case 	MDB_FNC_CR:
//					Value = IntFromArray(Registers.Coil, Address);
//					break;
//
//			case 	MDB_FNC_SR:
//					Value = IntFromArray(Registers.Status, Address);
//					break;
//
//			case 	MDB_FNC_IS:
//					Value = IntFromArray(Registers.Input, Address);
//					break;
//
//			case 	MDB_FNC_HR:
//					Value = IntFromArray(Registers.Holding, Address);
//					break;
//
//		}
//
//	return Value;
//}


unsigned char getRegisterChar(unsigned int RegisterType,unsigned int Address)
{
	unsigned char Value = 0;
	switch(RegisterType)
		{
			case 	MDB_FNC_CR:
					Value= Registers.Coil[Address];
					break;

			case MDB_FNC_SR:
					Value= Registers.Status[Address];
					break;

			case MDB_FNC_IS:
					Value= Registers.Input[Address];
					break;

			case 	MDB_FNC_HR:
					Value= Registers.Holding[Address];
					break;
		}

	return Value;
}


//
//
//void writeRegisterInt(unsigned char RegisterType,unsigned short Address, unsigned int intValue)
//{
//	switch(RegisterType)
//		{
//			case 	MDB_FNC_CR:
//					IntToArray(Registers.Coil, Address, intValue);
//					break;
//
//			case 	MDB_FNC_SR:
//					IntToArray(Registers.Status, Address, intValue);
//					break;
//
//			case 	MDB_FNC_IS:
//					IntToArray(Registers.Input, Address, intValue);
//					break;
//
//			case 	MDB_FNC_HR:
//					IntToArray(Registers.Holding, Address, intValue);
//					break;
//
////			case 	PLC_RTC_COUNTER:
////					RtcSeconds[Address] = intValue;
////					break;
//		}
//}

//void writeRegisterShort(unsigned char RegisterType,unsigned short Address, unsigned short ShortValue)
//{
//	switch(RegisterType)
//		{
//			case 	MDB_FNC_CR:
//					ShortToArray(Registers.Coil, Address, ShortValue);
//					break;
//
//			case 	MDB_FNC_SR:
//					ShortToArray(Registers.Status, Address, ShortValue);
//					break;
//
//			case 	MDB_FNC_IS:
//					ShortToArray(Registers.Input, Address, ShortValue);
//					break;
//
//			case 	MDB_FNC_HR:
//					ShortToArray(Registers.Holding, Address, ShortValue);
//					break;
//		}
//}


void writeRegisterChar(unsigned int RegisterType,unsigned int Address, unsigned char Value)
{
	switch(RegisterType)
		{
			case 	MDB_FNC_CR:
					Registers.Coil[Address] = Value;
					break;

			case 	MDB_FNC_SR:
					Registers.Status[Address] = Value;
					break;

			case 	MDB_FNC_IS:
					Registers.Input[Address] = Value;
					break;

			case 	MDB_FNC_HR:
					Registers.Holding[Address] = Value;
					break;
		}
}


//void OrRegister(unsigned char RegisterType,unsigned short Address, unsigned short OrValue)
//{
//	switch(RegisterType)
//		{
//			case 	MDB_FNC_CR:
//					ShortOrArray(Registers.Coil, Address, OrValue);
//					break;
//
//			case 	MDB_FNC_SR:
//					ShortOrArray(Registers.Status, Address, OrValue);
//					break;
//
//			case 	MDB_FNC_IS:
//					ShortOrArray(Registers.Input, Address, OrValue);
//					break;
//
//			case 	MDB_FNC_HR:
//					ShortOrArray(Registers.Holding, Address, OrValue);
//					break;
//		}
//}


//
// Data Type Length
//
unsigned char DataTypeSize(enumDATATYPE DataType)
{
	switch(DataType)
		{
			case dataTypeNone:					return 0;
			case dataTypeChar:							
			case dataTypeSignedChar:			return 1;
			case dataTypeShort:
			case dataTypeSignedShort:			return 2;
			case dataTypeInteger:		
			case dataTypeSignedInteger:			return 4;
			case dataTypeDouble:				return 8;
			case dataTypeCharArray:				return 0;
			case dataTypeHexToCharArray:		return 0;
			case dataTypeCharArrayToHex:		return 0;
			case dataTypeCharArrayToBCD:		return 0;
			case dataTypeBCDDateToLong:			return 4;
			case dataTypeIntegerShortFlip:		return 2;
			case dataTypeFloatIEEE754S:			return 4;
			case dataTypeFloatIEEE754D:			return 8;
			
		}
	return 0;
}
 
void RegisterDataGet(unsigned char *DataRegister,unsigned short DataStartPosition,unsigned char *Data, signed short DataSize)
{
	unsigned char Reverse = 0;
	unsigned char i;
	if(DataSize<0) { Reverse = 1; DataSize *= -1;}

	if(Reverse)
		{
			for(i=0;i<DataSize ;i++) Data[i] = DataRegister[DataStartPosition + DataSize - i - 1];
		}
	else
		{
			for(i=0;i<DataSize ;i++) Data[i] = DataRegister[DataStartPosition + i];
		}		
	Data[i] = '\0';
}

unsigned short  RegisterDataGetEndChar(unsigned char *DataRegister, unsigned short DataStartPosition, unsigned char *Data, signed short DataSize, signed short EndChar)
{
	unsigned char Reverse = 0;
	unsigned short i;
	unsigned short EndPos=0;
	
	if(DataSize<0) { Reverse = 1; DataSize *= -1;}

	//
	// Find End Of Char Pos
	// 
	if(EndChar>=0)
		{
			EndPos = 0;
			for(i=0;i<DataSize ;i++) { if(DataRegister[DataStartPosition+ i]==EndChar) break;  EndPos++;}
		}
	else
		{
			EndPos = DataSize;
		}

	if(Reverse)
		{
			for(i=0;i<EndPos ;i++) Data[i] = DataRegister[DataStartPosition + EndPos - i - 1];
		}
	else
		{
			for(i=0;i<EndPos ;i++) Data[i] = DataRegister[DataStartPosition + i];
		}		
		
	Data[i] = '\0';
	return i;
}

void RegisterConstShortDataUpdate(unsigned char *DataRegister,unsigned short DataStartPosition,const char *Data,unsigned char DataSize)
{
	unsigned short i;
	union unionShortInteger shortValue;
	
	for(i=0; i< DataSize * 2 ; i+=4) 
		{
			shortValue.Bytes.Byte0 = ((HexByte(Data[i + 0])<< 4) + HexByte(Data[i + 1]));
			shortValue.Bytes.Byte1 = ((HexByte(Data[i + 2])<< 4) + HexByte(Data[i + 3]));
			(*(unsigned short *)&DataRegister[DataStartPosition + ((i/4) *2) ])= shortValue.ShortInteger;	
		}
}

void RegisterConstShortDataUpdateWithEndChar(unsigned char *DataRegister,unsigned short DataStartPosition,const char *Data,unsigned char DataSize)
{
	unsigned short i;
	union unionShortInteger shortValue;
	
	for(i=0; i< DataSize *2 ; i+=4) 
		{
			shortValue.Bytes.Byte0 = ((HexByte(Data[i + 0])<< 4) + HexByte(Data[i + 1]));
			shortValue.Bytes.Byte1 = ((HexByte(Data[i + 2])<< 4) + HexByte(Data[i + 3]));

			(*(unsigned short *)&DataRegister[DataStartPosition + ((i/4) *2) ])= shortValue.ShortInteger;	
		}
		
	DataRegister[DataStartPosition + i] = '\0';
}

void RegisterConstDataUpdate(unsigned char *DataRegister,unsigned short DataStartPosition,const char *Data,unsigned char DataSize)
{
	unsigned short i;
	for(i=0;i<DataSize;i++) DataRegister[DataStartPosition + i] = Data[i];	
}

void RegisterConstDataUpdateWithEndChar(unsigned char *DataRegister,unsigned short DataStartPosition,const char *Data,unsigned char DataSize)
{
	unsigned short i;
	for(i=0;i<DataSize;i++) DataRegister[DataStartPosition + i] = Data[i];	
	DataRegister[DataStartPosition + i] = '\0';
}

void RegisterDataUpdate(unsigned char *DataRegister,unsigned short DataStartPosition,unsigned char *Data,unsigned char DataSize)
{
	unsigned short i;
	for(i=0;i<DataSize;i++) DataRegister[DataStartPosition + i] = Data[i];	
}

void RegisterDataUpdateWithEndChar(unsigned char *DataRegister,unsigned short DataStartPosition,unsigned char *Data,unsigned char DataSize)
{
	unsigned short i;
	for(i=0;i<DataSize;i++) DataRegister[DataStartPosition + i] = Data[i];	
	DataRegister[DataStartPosition + i] = '\0';
}

unsigned char BitsCount(unsigned int Value)
{
	unsigned int Mask = 0x80000000;
	unsigned char Count;

	for (Count = 0; Mask != 0; Mask >>= 1)
		{
			if (Value & Mask) Count++;
		}

	return Count;
}

signed char FirstSetBitPos(unsigned int Value)
{
	unsigned int Mask = 0x00000001;
	signed char Pos=-1;

	if(Value)
		{
			for (Mask = 0x00000001; Mask != 0; Mask <<= 1)
				{
					Pos++;
					if (Value & Mask) break;
				}
		}
	return Pos;	
}

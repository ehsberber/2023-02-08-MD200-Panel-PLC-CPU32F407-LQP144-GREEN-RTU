/*
 * DataType.h
 *
 *  Created on: Aug 3, 2022
 *      Author: Sezgin Berber
 */

#ifndef INCLUDE_DATATYPE_H_
#define INCLUDE_DATATYPE_H_

	typedef enum
		{
			dataTypeNone				= 0,
			dataTypeChar				= 1,
			dataTypeSignedChar			= 2,
			dataTypeShort				= 3,
			dataTypeSignedShort			= 4,
			dataTypeInteger				= 5,
			dataTypeSignedInteger		= 6,
			dataTypeDouble				= 7,
			dataTypeCharArray			= 8,
			dataTypeHexToCharArray		= 9,
			dataTypeCharArrayToHex		= 10,
			dataTypeCharArrayToBCD		= 11,
			dataTypeBCDDateToLong		= 12,

			dataTypeIntegerShortFlip	= 13,

			dataTypeFloatIEEE754S   	= 14,
			dataTypeFloatIEEE754D   	= 15

		}enumDATATYPE;

		typedef struct
			{
				unsigned char 	DataLength;
				unsigned char 	IntegerLength;
				unsigned char 	DecimalLength;
				unsigned char 	Format;
				unsigned char 	TotalSize;
				unsigned char 	Type;
				signed short 	FillChar;
				enumDATATYPE 	DataType;

			} strcDATAFORMAT;

			typedef struct
				{
					float	Celsius;
					float  Fahrenheit;

				} strcTEMPERATURE;

		union unionSignedShortInteger
			{
				struct
					{
						unsigned char Byte1;
						unsigned char Byte0;
					} Bytes;
				signed short ShortInteger;
			};
		union unionShortInteger
			{
				struct
					{
						unsigned char Byte1;
						unsigned char Byte0;
					} Bytes;
				unsigned short ShortInteger;
			};

		union unionInteger
			{
				struct
					{
						unsigned char Byte3;
						unsigned char Byte2;
						unsigned char Byte1;
						unsigned char Byte0;
					} Bytes;

				struct
					{
						unsigned short Short1;
						unsigned short Short0;
					} Shorts;
				unsigned int Integer;
			};
#endif /* INCLUDE_DATATYPE_H_ */

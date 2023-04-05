#include "String.h"
 
#include "ConvertInteger.h"

extern unsigned char *TEMP;

extern const unsigned char HexArray[];
unsigned char ctobcd(unsigned char ConvertChar)
{			
	unsigned char bcd,bcdl,bcdh;
	bcdl 	= ConvertChar % 10;
	bcdh 	= (ConvertChar- bcdl) / 10;
	bcd 	= bcdh <<4 | bcdl;
	return bcd ;
}

unsigned char bcdtod(unsigned char bcd)
{			
	unsigned char Decimal;
	Decimal 	= ((bcd >> 4 ) * 10) + (bcd & 0x0F ) ;
	return Decimal ;
}

unsigned long int ConvertStringToLong(unsigned char *ConvertString,unsigned int LenghtOfString)
{
  
  unsigned long int Data=0,Multiplier=1;
  unsigned int j,i;
  
  for (i=0;i<LenghtOfString;i++) 
  {
    Multiplier = 1 ;
    for( j=1; j < (LenghtOfString-i) ; j ++ ) Multiplier *= 10;  
    Data += Multiplier * ConvertString[i];
  }
  return Data;
}


signed long int ConvertStringToSignedLong(unsigned char *ConvertString,unsigned int LenghtOfString)
{
	signed long Data=0;  
	signed char Minus = 1;
  unsigned long int Multiplier=1;
  unsigned int j,i;
  
  for (i=0;i<LenghtOfString;i++) 
  {
    Multiplier = 1 ;
    for( j=1; j < (LenghtOfString-i) ; j ++ ) Multiplier *= 10;  
		if (ConvertString[i] == '-')
			Minus = -1;
		else
			if (ConvertString[i] != '+') Data += Multiplier * ConvertString[i];
  }
	Data *= Minus;	
  return Data;
}

//unsigned long int ConvertAlphaStringToLong(unsigned char *ConvertString,unsigned int LenghtOfString)
//{
//  
//  unsigned long int Data=0,Multiplier=1;
//  unsigned int j,i;
//	
//	  
//  for (i=0;i<LenghtOfString;i++) 
//  {
//    Multiplier = 1 ;
//    for( j=1; j < (LenghtOfString-i) ; j ++ ) Multiplier *= 10;  
//    Data += Multiplier * (ConvertString[i] - 0x30);
//  }
//  return Data;
//}
unsigned char IsAlphaNumeric(unsigned char Char)
{
	switch(Char)
		{
			
			case '0':	
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
					return Char;
			default:
				return 0;
		}
}


unsigned char IsHexChar(unsigned char Char)
{
	switch(Char)
		{
			case '0':	
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':	
			case 'F':	
					return Char;
			default:
				return 0;
		}
}

unsigned long int ConvertAlphaStringToLong(unsigned char *ConvertString,unsigned int LenghtOfString)
{
  
  unsigned long int Data=0,Multiplier=1;
  unsigned int j,i;
 	if (ConvertString[0] == '-') 
				++ConvertString;
	
	if (ConvertString[0] == '+')
			++ConvertString;
	
	if(!LenghtOfString)
		{
			for(i=0;i<0x20;i++)
				{
					if (IsAlphaNumeric(ConvertString[i]))
						LenghtOfString++;
					else
						break;
				}
			}
			
	if ( LenghtOfString >= 0x20) return 0; //else LenghtOfString = i;
	
  
  for (i=0;i<LenghtOfString;i++) 
  {
		if (!(IsAlphaNumeric(ConvertString[i]))) break;
    Multiplier = 1 ;
    for( j=1; j < (LenghtOfString-i) ; j ++ ) Multiplier *= 10;  
    Data += Multiplier * (ConvertString[i] - 0x30);
  }
  return Data;
}


signed long int ConvertAlphaStringToSignedLong(unsigned char *ConvertString,unsigned char LenghtOfString)
{
	  
	signed long int Data=0;								 	
	signed char Minus = 1;
  unsigned long int Multiplier=1;
  unsigned int j,i;

	if (ConvertString[0] == '-') 
		{	
			++ConvertString;
			if(LenghtOfString) LenghtOfString--;
			Minus = -1;
		}
	if (ConvertString[0] == '+')
		{
			++ConvertString;
			if(LenghtOfString) LenghtOfString--;
		}
				
	if(!LenghtOfString)
		{
			for(i=0;i<0x20;i++)
				{
					if (IsAlphaNumeric(ConvertString[i]))
						LenghtOfString++;
					else
						break;
				}
			}
		
  for (i=0;i<LenghtOfString;i++) 
 	 	{
			if (!IsAlphaNumeric(ConvertString[i])) break;
			
			Multiplier = 1 ;
			for( j=1; j < (LenghtOfString-i) ; j ++ ) Multiplier *= 10;  
	
//			if (ConvertString[i] == '-')
//				{
//					Minus = -1;
//					break;
//				}
//			else
			Data += Multiplier * (ConvertString[i] - 0x30);
			//	if (ConvertString[i] != '+') {Data += Multiplier * (ConvertString[i] - 0x30);} else break;
		}
	Data *= Minus;
  return Data;
}


double ConvertAlphaStringToDouble(unsigned char *ConvertString,unsigned char LenghtOfString)
{
	  
	double Data=0;								 	
	signed char Minus = 1;
  unsigned long int Multiplier=1;
  unsigned int j,i;

	strltrim(ConvertString);

	if (ConvertString[0] == '-') 
		{	
			++ConvertString;
			if(LenghtOfString) LenghtOfString--;
			Minus = -1;
		}
	if (ConvertString[0] == '+')
		{
			++ConvertString;
			if(LenghtOfString) LenghtOfString--;
		}
				
	if(!LenghtOfString)
		{
			for(i=0;i<0x20;i++)
				{
					if (IsAlphaNumeric(ConvertString[i]))
						LenghtOfString++;
					else
						break;
				}
			}
		
  for (i=0;i<LenghtOfString;i++) 
 	 	{
			if (!IsAlphaNumeric(ConvertString[i])) break;
			
			Multiplier = 1 ;
			for( j=1; j < (LenghtOfString-i) ; j ++ ) Multiplier *= 10;  
	
//			if (ConvertString[i] == '-')
//				{
//					Minus = -1;
//					break;
//				}
//			else
			Data += Multiplier * (ConvertString[i] - 0x30);
			//	if (ConvertString[i] != '+') {Data += Multiplier * (ConvertString[i] - 0x30);} else break;
		}
	Data *= Minus;
  return Data;
}

//unsigned char IsHexChar(unsigned char CharValue)
//{
//	if ( (CharValue >= 0x30 && CharValue <= 0x39) || (CharValue >= 'A' && CharValue <= 'F')) return 1 ; else return 0;
//}

unsigned char HexByte(unsigned char HexChar)
{
	
	if (HexChar >= '0' && HexChar <= '9') HexChar -= 48;
	if (HexChar >= 'A' && HexChar <= 'F') HexChar -= 55;
	return HexChar;
}

unsigned char ConvertHexStringToCharArray(unsigned char *HexString,signed char LengthOfString,unsigned char *CharArray)
{
	//unsigned char LengthOfString;
	unsigned char CharCounter;
	
	if(!LengthOfString)	
		LengthOfString = strlength(HexString);
	
	if (LengthOfString  % 2 ) return 0;
	//
	// VERININ TAMAMININ HEX OLMASI GEREKIR
	//
	for(CharCounter=0;CharCounter<LengthOfString;CharCounter++)	 {if(!IsHexChar(HexString[CharCounter])) return 0;}
	LengthOfString /= 2;
		
	for(CharCounter = 0; CharCounter < LengthOfString ; CharCounter++)
		{
			CharArray[CharCounter] = (HexByte(HexString[CharCounter * 2]) * 16 ) + HexByte( HexString[(CharCounter *2) + 1] );
		}
	CharArray[CharCounter] = '\0';
	return CharCounter;
}

unsigned char ConvertHexStringToCharArrayReverse(unsigned char *HexString,signed char LengthOfString,unsigned char *CharArray)
{
	//unsigned char LengthOfString;
	unsigned char CharCounter;
	
	if(!LengthOfString)	
		LengthOfString = strlength(HexString);
	
	if (LengthOfString  % 2 ) return 0;
	//
	// VERININ TAMAMININ HEX OLMASI GEREKIR
	//
	for(CharCounter=0;CharCounter<LengthOfString;CharCounter++)	 {if(!IsHexChar(HexString[CharCounter])) return 0;}
	LengthOfString /= 2;
		
	for(CharCounter = 0; CharCounter < LengthOfString ; CharCounter++)
		{
			CharArray[LengthOfString - CharCounter - 1] = (HexByte(HexString[CharCounter * 2]) * 16 ) + HexByte( HexString[(CharCounter *2) + 1] );
		}
	CharArray[CharCounter] = '\0';
	return CharCounter;
}

unsigned char ConvertConstHexStringToCharArray(const char *HexString,unsigned char *CharArray)
{
	unsigned char LengthOfString;
	unsigned char CharCounter;
	LengthOfString = ConstStrLength(HexString);
	if (LengthOfString  % 2 ) return 0;
	//
	// VERININ TAMAMININ HEX OLMASI GEREKIR
	//
	for(CharCounter=0;CharCounter<LengthOfString;CharCounter++)	 {if(!IsHexChar(HexString[CharCounter])) return 0;}
	LengthOfString /= 2;
		
	for(CharCounter = 0; CharCounter < LengthOfString ; CharCounter++)
		{
			CharArray[CharCounter] = (HexByte(HexString[CharCounter * 2]) * 16 ) + HexByte( HexString[(CharCounter *2) + 1] );
		}
	CharArray[CharCounter] = '\0';
	return CharCounter;
}

unsigned char ConvertConstHexStringToReverseCharArray(const char *HexString,unsigned char *CharArray)
{
	unsigned char LengthOfString;
	unsigned char CharCounter;
	LengthOfString = ConstStrLength(HexString);
	if (LengthOfString  % 2 ) return 0;
	//
	// VERININ TAMAMININ HEX OLMASI GEREKIR
	//
	for(CharCounter=0;CharCounter<LengthOfString;CharCounter++)	 {if(!IsHexChar(HexString[CharCounter])) return 0;}
	LengthOfString /= 2;
		
	for(CharCounter = 0; CharCounter < LengthOfString ; CharCounter++)
		{
			CharArray[LengthOfString - CharCounter - 1] = (HexByte(HexString[CharCounter * 2]) * 16 ) + HexByte( HexString[(CharCounter *2) + 1] );
		}
	CharArray[CharCounter] = '\0';
	return CharCounter;
}


unsigned long ConvertHexStringToLong(unsigned char *ConvertString,unsigned char LenghtOfString)
{
	unsigned char CharCounter;
	unsigned long int LongData=0;
	unsigned long int Multiplier = 1;

	if(!LenghtOfString)
		for(CharCounter=0;CharCounter<0x20;CharCounter++)
			{
				if (IsHexChar(ConvertString[CharCounter]))
					LenghtOfString++;
				else
					break;
			}

	for(CharCounter=0; CharCounter < LenghtOfString; CharCounter++)	 {if(!IsHexChar(ConvertString[CharCounter])) return 0;}

	while(LenghtOfString)
		{
			LenghtOfString--;
			LongData += HexByte(ConvertString[LenghtOfString]) * Multiplier ;
			Multiplier *= 16;
		}

	return LongData;
}

double ConvertHexStringToDouble(unsigned char *ConvertString,unsigned char LenghtOfString)
{
	unsigned char CharCounter;
	double DoubleData=0;
	unsigned long int Multiplier = 1;

	if(!LenghtOfString)
		for(CharCounter=0;CharCounter<0x20;CharCounter++)
			{
				if (IsHexChar(ConvertString[CharCounter]))
					LenghtOfString++;
				else
					break;
			}

	for(CharCounter=0; CharCounter < LenghtOfString; CharCounter++)	 {if(!IsHexChar(ConvertString[CharCounter])) return 0;}

	while(LenghtOfString)
		{
			LenghtOfString--;
			DoubleData += HexByte(ConvertString[LenghtOfString]) * Multiplier ;
			Multiplier *= 16;
		}

	return DoubleData;
}
 

unsigned long int ConvertHexORAlphaStringToLong(unsigned char *ConvertString,unsigned int LenghtOfString)
{
  unsigned char CharCounter;
  unsigned long int Data=0;
	if(!LenghtOfString)
		{
			for(CharCounter=0;CharCounter<0x20;CharCounter++)
				{
					if (IsHexChar(ConvertString[CharCounter]))
						LenghtOfString++;
					else
						break;
				}
		}
  
	if( (ConvertString[0] == '0') && (ConvertString[1] == 'x') )
		{
			if(LenghtOfString>2)
				Data = ConvertHexStringToLong( &ConvertString[2], LenghtOfString -2);
			else
				Data = ConvertHexStringToLong( &ConvertString[2], 0);
		}
	else
		{
			Data = ConvertAlphaStringToLong(ConvertString, LenghtOfString);
		}
  return Data;
}

signed long int ConvertHexORAlphaStringToSignedLong(unsigned char *ConvertString,unsigned int LenghtOfString)
{
  signed long int Data=0;
	unsigned char CharCounter;
	
	if(!LenghtOfString)
		{
			for(CharCounter=0;CharCounter<0x20;CharCounter++)
				{
					if (IsHexChar(ConvertString[CharCounter]))
						LenghtOfString++;
					else
						break;
				}
		}
  
	if( (ConvertString[0] == '0') && (ConvertString[1] == 'x') )
		{
			if(LenghtOfString>2)
				Data = ConvertHexStringToLong( &ConvertString[2], LenghtOfString -2);
			else			
				Data = ConvertHexStringToLong( &ConvertString[2], 0);
		}
	else
		{
			Data = ConvertAlphaStringToSignedLong(ConvertString, LenghtOfString);
		}
  return Data;
}

double ConvertHexORAlphaStringToDouble(unsigned char *ConvertString,unsigned int LenghtOfString)
{
  double Data=0;
  
	if( (ConvertString[0] == '0') && (ConvertString[1] == 'x') )
		{
			if(LenghtOfString>2)
				Data = ConvertHexStringToDouble( &ConvertString[2], LenghtOfString -2);
			else			
				Data = ConvertHexStringToDouble( &ConvertString[2], 0);
		}
	else
		{
			Data = ConvertAlphaStringToDouble(ConvertString, LenghtOfString);
		}
  return Data;
}

unsigned long ConvertHexStringToLongMid(unsigned char *HexString,unsigned char StartPosition,unsigned char DataLength)
{
	unsigned char CharCounter;
	unsigned long int LongData=0;
	unsigned long int Multiplier = 1;

	for(CharCounter=0;CharCounter<DataLength;CharCounter++)	 {if(!IsHexChar(HexString[StartPosition + CharCounter])) return 0;}
	while(DataLength)
		{
			DataLength--;
			LongData += HexByte(HexString[StartPosition + DataLength]) * Multiplier ;
			Multiplier *= 16;
		}

	return LongData;
}

unsigned char ConvertCharArrayToHexString(unsigned char *CharArray,	signed char LengthOfString,unsigned char *HexString)
{
	unsigned char CharCounter;
 
	
	if(LengthOfString<0) 
		{ 
			LengthOfString *= -1;
			
			for(CharCounter = 0; CharCounter < LengthOfString ; CharCounter++)
				{
					HexString[ (LengthOfString * 2) -  ((CharCounter * 2)	+	1	) -1] = HexArray[CharArray[CharCounter] >> 4  ];
					HexString[ (LengthOfString * 2) -  ((CharCounter * 2)     ) -1] = HexArray[CharArray[CharCounter] & 0x0F];
				}
			HexString[CharCounter * 2 ]  = '\0';		
		}
	else
		{
			for(CharCounter = 0; CharCounter < LengthOfString ; CharCounter++)
				{
					HexString[ CharCounter * 2 			] = HexArray[CharArray[CharCounter] >> 4  ];
					HexString[(CharCounter * 2) + 1 ] = HexArray[CharArray[CharCounter] & 0x0F];
				}
			HexString[CharCounter * 2 ]  = '\0';		
		}
	return CharCounter *2 ;
}


unsigned char ConvertCharArrayToString(unsigned char *CharArray,	unsigned char LengthOfString,unsigned char CharSize, unsigned char *String)
{
	unsigned char CharCounter,j=0,i;
	unsigned char CharStr[20];
		
	for(CharCounter = 0; CharCounter < LengthOfString ; CharCounter++)
		{
			ltostr(CharArray[CharCounter],	CharSize,1, &CharStr[0]); 
			for(i=0;i<CharSize;i++)	 String[j++]=  CharStr[i];
		}
	String[j]  = '\0';
	
	return j ;
}

// unsigned char ConvertCharArrayToBCD(unsigned char *CharArray,	unsigned char LengthOfString,unsigned char CharSize, unsigned char *String)
// {
// 	unsigned char CharCounter,j=0,i;
// 	unsigned char CharStr[20];
// 		
// 	for(CharCounter = 0; CharCounter < LengthOfString ; CharCounter++)
// 		{
// 			ltostr(CharArray[CharCounter],	CharSize,1, &CharStr[0]); 
// 			for(i=0;i<CharSize;i++)	 String[j++]=  CharStr[i];
// 		}
// 	String[j]  = '\0';
// 	
// 	return j ;
// }

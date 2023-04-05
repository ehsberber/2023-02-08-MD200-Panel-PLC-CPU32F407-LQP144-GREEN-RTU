
#include <stdio.h>
#include "ConvertInteger.h"

extern const unsigned char HexArray[];

void chartohex(unsigned char value,unsigned char *HexString)
{
	HexString[0] = '0';
	HexString[1] = 'x';

	HexString[2] = HexArray[value >> 4];
	HexString[3] = HexArray[value & 0x0F];
	HexString[4] = '\0';
}

void chartohex2(unsigned char value,unsigned char *HexString)
{
	HexString[0] = HexArray[value >> 4];
	HexString[1] = HexArray[value & 0x0F];
	HexString[2] = '\0';
}

void CharHexByte(unsigned char Character, unsigned char *HexByte1,unsigned char *HexByte2)
{

	*HexByte1 = HexArray[Character >> 4];
	*HexByte2 = HexArray[Character & 0x0F];

}

unsigned char hexnumbertochar(unsigned char HiByteHex, unsigned char LowByteHex)
{
	unsigned char i;
	i=0;		while(HexArray[i] != HiByteHex && (i<16) ) i++;  HiByteHex = i;
	i=0;		while(HexArray[i] != LowByteHex && (i<16) ) i++; LowByteHex = i;

	return ((HiByteHex * 16) + LowByteHex);
	
} 

void ltohex(unsigned int *Number,unsigned char Length,unsigned char *ReturnString )
{
	
	unsigned char *HexByte1;
	unsigned char *HexByte2;
	unsigned char Byte1,Byte2;
	unsigned char i=0;
//	unsigned char CharByte;
	unsigned char Counter=0;
	
	unsigned char *longNumber;
	longNumber = (unsigned char *) Number;

	HexByte1 = &Byte1;
	HexByte2 = &Byte2;

//	unionNumber.Long = Number;
	i = Length/2;
	ReturnString[Length] = '\0';
	while(i)
		{
			i--;
			CharHexByte(longNumber[i],HexByte1,HexByte2);
			ReturnString[ Counter * 2] =  *HexByte1; ReturnString[(Counter *2) + 1 ] =  *HexByte2; Counter++;
		}
}

void ltochararray(unsigned int *Number,unsigned char Length,unsigned char *ReturnString )
{
	 
	unsigned char i=0;
	
	unsigned char *longNumber;
	longNumber = (unsigned char *) Number;
	if (Length >4) Length = 4; 
	for(i=0; i< Length; i++) ReturnString[i] = longNumber[i];
 
}

void sltochararray(signed int *Number,unsigned char Length,unsigned char *ReturnString )
{
	 
	unsigned char i=0;
	
	unsigned char *longNumber;
	longNumber = (unsigned char *) Number;
	if (Length >4) Length = 4; 
	for(i=0; i< Length; i++) ReturnString[i] = longNumber[i];
}


void ltohex0x(unsigned int *Number,unsigned char Length,unsigned char *ReturnString )
{
	
	unsigned char *HexByte1;
	unsigned char *HexByte2;
	unsigned char Byte1,Byte2;
	unsigned char i=0;
//	unsigned char CharByte;
	unsigned char Counter=0;
	
	unsigned char *longNumber;
	longNumber = (unsigned char *) Number;

	HexByte1 = &Byte1;
	HexByte2 = &Byte2;

//	unionNumber.Long = Number;
	i = Length/2;
	ReturnString[Length] = '\0';
	ReturnString[0] = '0'; ReturnString[1] = 'x';
	while(i)
		{
			i--;
			CharHexByte(longNumber[i],HexByte1,HexByte2);
			ReturnString[2 + (Counter * 2)] =  *HexByte1; ReturnString[2 + (Counter *2) + 1 ] =  *HexByte2; Counter++;
		}
}

unsigned int shortflip(unsigned int intValue)
{
	int ShortValue1;
	int ShortValue2;
		
	ShortValue1 = intValue >> 16;
	ShortValue2 = intValue << 16;
	return (ShortValue1 | ShortValue2);
}

unsigned char ltostr(unsigned long int  Number,unsigned char Length,unsigned char FillLeft, unsigned char *ReturnString )
{
  unsigned long int DecimalBolen=1; 
  unsigned char DecimalOffset=0,k;
  unsigned char NumberIsStart = 0;
  
  for (k=Length-1;k>0;k--) DecimalBolen*=10;
  
  for (k=0; k < Length ;k++)
    {
	    if (Number>=DecimalBolen) 
	      {
	      NumberIsStart=1;
	      ReturnString[DecimalOffset] = Number / DecimalBolen;
	      Number = Number % DecimalBolen;
	      ReturnString[DecimalOffset] += 48;
	      DecimalOffset++;
	      }
	    else if (FillLeft & 0x01 || NumberIsStart == 1 ) 
							{
								if (NumberIsStart)
									{ 
										ReturnString[DecimalOffset++] = '0'; 
									}
								else
									{
										if (FillLeft & 0x02)
											ReturnString[DecimalOffset++] = ' ';
										else
											ReturnString[DecimalOffset++] = '0';
									}
										
							}
	    	DecimalBolen  /= 10;
    }
	if(!DecimalOffset) ReturnString[DecimalOffset++] = '0';
	ReturnString[DecimalOffset] = '\0';
	return DecimalOffset;
}

unsigned char sltostr(signed long int  Number,unsigned char Length,unsigned char FillLeft, unsigned char *ReturnString )
{
  unsigned long int DecimalBolen=1; 
  unsigned char DecimalOffset=0,k;
  unsigned char NumberIsStart = 0;
	unsigned char Minus=0;
	if (Number < 0) { Minus = 1; Number *= -1;}
  
  for (k=Length-1;k>0;k--) DecimalBolen*=10;

	
  for (k=0; k < Length ;k++)
    {
			if (Number>=DecimalBolen) 
	      {
			if (Minus & !NumberIsStart) ReturnString[DecimalOffset++] = '-';
		      NumberIsStart=1;
		      ReturnString[DecimalOffset] = Number / DecimalBolen;
		      Number = Number % DecimalBolen;
		      ReturnString[DecimalOffset] += 48;
		      DecimalOffset++;
	      }
	    else 
				{
					if(Minus) 
						{
							Minus = 0; 
							ReturnString[DecimalOffset++] = '-';
						} 
					else
						{
							if ((FillLeft & 0x01) || NumberIsStart ) 
								{ 
									ReturnString[DecimalOffset++] = '0'; 
								}
							else
								{								
									if ((FillLeft & 0x02) || NumberIsStart ) 
										{ 
											ReturnString[DecimalOffset++] = ' '; 
										}
								}
						}
				}
	    DecimalBolen  /= 10;
    }
	 if(!DecimalOffset) ReturnString[DecimalOffset++] = '0'; 
   ReturnString[DecimalOffset] = '\0';
	 return DecimalOffset;
}

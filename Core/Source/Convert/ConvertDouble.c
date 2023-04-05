#include "stdlib.h"
#include "Math.h"
#include "DataType.h"


unsigned char dbltoBCD(double dblValue,unsigned char Length, unsigned char *StringArray )
{
	unsigned long int v; 
	unsigned char k,MaskValue;
	unsigned int uiValue;
 
	uiValue = dblValue;
	 
	//----------- NUMBER IS ROUNDED ----------//
	//Multiplier = 1 ;
	//for( k=0; k <= DecimalLength ; k++ ) Multiplier *= 10;  
	uiValue = dblValue * 10;
	k = uiValue % 10;
	if (k < 5) uiValue -= k ; else uiValue += (10-k);
	uiValue /= 10;

	// 
	// BCD
	//
	MaskValue = 0x0F;
	k = 0;
	//j = 0; //StringDataIntegerLength-1;
	v = pow(10, (Length * 2 ) -1); // VMAX;
	while (k < Length)
		{
			StringArray[k] &= MaskValue;
				
			while (uiValue >= v)
				{
					uiValue = uiValue - v;
					if(MaskValue == 0x0F)  
						StringArray[k] +=   0x10;
					else
						StringArray[k] +=   0x01;
				}
			v = v / 10;
			//j++;
			MaskValue <<= 4;
			if(!MaskValue) {MaskValue = 0x0F; k++;}
		}
	return k;
}

//unsigned char Length,unsigned char DecimalLength,unsigned char Format,
unsigned char CheckNumberForConvertion(double dblNumber,strcDATAFORMAT *DataFormat,unsigned char *dblString )
{
	double MaxVal; 
	unsigned char k=0;
	unsigned char IntegerLength;
	IntegerLength = DataFormat->IntegerLength;
	
	if (dblNumber<0)
		{
			 dblNumber *= -1; 
			 IntegerLength -= 1;
		} 
	//
	// Check Number for  Convertion
	//
	MaxVal = pow(10, (IntegerLength + DataFormat->DecimalLength)) -1;
	MaxVal /= pow(10, DataFormat->DecimalLength);
	
	if(dblNumber >MaxVal)
		{
			//
			// long number to convertion
			//
			for(k=0;k< IntegerLength;k++)
				dblString[k] = 'X';
			if(DataFormat->DecimalLength)
				{
					dblString[k] = '.';	
					
					for(k=IntegerLength + 1; k < IntegerLength + DataFormat->DecimalLength + 1 ; k++)
						dblString[k] = 'x';
				}
			dblString[k] = '\0';
		}
	return k;
}

unsigned char dbltostr(double dblNumber,strcDATAFORMAT *DataFormat,unsigned char *dblString )
{
  unsigned long int DecimalBolen=1,Multiplier; 
  unsigned int DecimalOffset=0,k;
  unsigned char NumberIsStart = 0;
  unsigned long Number,Number_Decimal;
	unsigned char  Minus=0;		// FillChar=0,
	
	//
	// Check Number Length for Convertion
	//
	k = CheckNumberForConvertion(dblNumber,DataFormat,dblString);
	if(k) return k;
	
	if((!DataFormat->IntegerLength) || (DataFormat->IntegerLength>16))  
		{
			dblString[DecimalOffset] = '\0';	
			return DecimalOffset;	
		}
		
  if (dblNumber<0) 
    {
      Minus = 1;
      dblNumber *=-1;
				
      DataFormat->IntegerLength--;
    }
  else
    {
      if (DataFormat->Format & 0x80)
        {
          dblString[DecimalOffset++] = '+';
          DataFormat->IntegerLength--;
        }
    }
	
  //----------- NUMBER IS ROUNDED ----------//
  Multiplier = 1 ;
  for( k=0; k <= DataFormat->DecimalLength ; k++ ) Multiplier *= 10;  
  Number = dblNumber * Multiplier;
  k = Number % 10;
  if (k < 5) Number -= k ; else Number += (10-k);
//  if (k) Number += (10-k);
  Number /= 10;
  Multiplier /= 10;
  Number_Decimal = Number % Multiplier ;
  Number /= Multiplier ;
  
//----------- INTEGER VALUE -----------------// 
	//if(!Number) dblString[DecimalOffset++] = '0';
	
  for (k=DataFormat->IntegerLength-1;k>0;k--) DecimalBolen*=10;
  for (k=0; k < DataFormat->IntegerLength ;k++)
    {
			if (Number>=DecimalBolen) 
				{
					NumberIsStart=1;
					if(Minus) 
						{
							 //DecimalOffset--;
							 dblString[DecimalOffset++] = '-';
							 //DataFormat->IntegerLength--;
							 Minus = 0;
						}
					dblString[DecimalOffset] = Number / DecimalBolen;
					Number = Number % DecimalBolen;
					dblString[DecimalOffset] += 48;
					DecimalOffset++;
				}
	//    else if ( Format || NumberIsStart ) dblString[DecimalOffset++] = FillChar; 
			else 
				{
					if(NumberIsStart)	
						dblString[DecimalOffset++] = '0';
					else
						{
							if(Minus && (k == (DataFormat->IntegerLength-2))) 
								{
									 dblString[DecimalOffset++] = '-';
									 //DataFormat->IntegerLength--;
									 Minus = 0;
								}
							else
								{
									if( k== (DataFormat->IntegerLength-1))
										{
											dblString[DecimalOffset++] = '0';  
										}
									else if ( DataFormat->FillChar>= 0 ) 
										dblString[DecimalOffset++] = DataFormat->FillChar;  
								}
						}
				}

			DecimalBolen  /= 10;
    }
		
  if(DataFormat->DecimalLength)
		{
			dblString[DecimalOffset++] = '.';
			//------------- DECIMAL VALUE -------------------//
			//-------------------------------------------//
			DecimalBolen = 1;
			for (k=1; k < DataFormat->DecimalLength ;k++) DecimalBolen*=10;
			for (k=0; k < DataFormat->DecimalLength ;k++)
				{
					if (Number_Decimal >= DecimalBolen) 
						{
							NumberIsStart=1;
							dblString[DecimalOffset] = Number_Decimal / DecimalBolen;
							Number_Decimal %= DecimalBolen;
							dblString[DecimalOffset] += 48;
							DecimalOffset++;
						}
					else  dblString[DecimalOffset++] = '0'; 
					DecimalBolen  /= 10;
				}
			}
	if(!DecimalOffset)	
		{
			dblString[DecimalOffset++] = '0';
		}
  dblString[DecimalOffset] = '\0';
	return DecimalOffset;
}

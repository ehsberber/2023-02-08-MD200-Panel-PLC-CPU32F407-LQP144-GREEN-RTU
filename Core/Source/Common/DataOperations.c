#include "DataOperations.h"
#include "DataType.h"

extern unsigned char *InputParameterList[2] ;

void AddDataList(unsigned char ListNo, unsigned short DataStartPosition, unsigned char DataLength, unsigned char Control)
{
	unsigned char i;
	unsigned char ParameterCount;
	unsigned Address;
 

	ParameterCount = InputParameterList[ListNo][0] & 0x7F;

	 InputParameterList[ListNo][0]  |= Control;

	//
	// AYNI PARAMETRE LISTEDE VARMI KONTROLU YAPILIYOR
	//
	for(i=1 ; i<= ParameterCount;i++)
		{
			Address = ( InputParameterList[ListNo][ (3*(i-1)) + 1] * 0x100) +  InputParameterList[ListNo][ (3*(i-1)) + 2] ;
			if (Address == DataStartPosition) break;
		}

	if (i>ParameterCount)
		{
			//
			// YENI PARAMETRE
			//
			++ InputParameterList[ListNo][0];
			
			*((unsigned short *)& InputParameterList[ListNo][(ParameterCount * 3) + 1]) = DataStartPosition;
			 InputParameterList[ListNo][(ParameterCount * 3) + 3] = DataLength;
		}
}


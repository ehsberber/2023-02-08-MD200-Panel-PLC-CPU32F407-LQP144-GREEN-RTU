/*
 * DataFilter.c
 *
 *  Created on: Oct 4, 2022
 *      Author: Sezgin Berber
 */
#include "PlcDefinition.h"
#include "DataFilter.h"

static unsigned int DataArray[AI_CHANNEL_COUNT][DATA_FILTER_ARRAY_COUNT];

void DataFilterValue(unsigned short ArrayNo, unsigned int ArrayData)
{
	unsigned char Counter;
	for(Counter = 1; Counter < DATA_FILTER_ARRAY_COUNT ; Counter++)
		{
			DataArray[ArrayNo][Counter-1] = DataArray[ArrayNo][Counter];
		}
	DataArray[ArrayNo][DATA_FILTER_ARRAY_COUNT -1 ] = ArrayData;
}

unsigned int  DataFilter(unsigned short ArrayNo)
{
	unsigned int MaxVal,MinVal;
	unsigned int Total;
	unsigned short Index;
	MinVal = 0xFFFFF;
	MaxVal = 0;
	Total = 0;

	for(Index=0;Index < DATA_FILTER_ARRAY_COUNT;  Index++)
		{
			if(MaxVal < DataArray[ArrayNo][Index] )
				{
					MaxVal = DataArray[ArrayNo][Index];
				}

			if(MinVal > DataArray[ArrayNo][Index] )
				{
					MinVal = DataArray[ArrayNo][Index];
				}

			Total = Total + DataArray[ArrayNo][Index];
		}

	return  (Total - MaxVal - MinVal) / (DATA_FILTER_ARRAY_COUNT -2);

}

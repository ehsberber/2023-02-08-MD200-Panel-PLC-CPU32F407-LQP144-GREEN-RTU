#include "MicroPeripheral.h"
#include "DataPositionStatus.h"
#include "DataPositionHolding.h"
#include "Registers.h"
#include "Uarts.h"

extern strcREGISTERS  Registers;
extern strcUART Uart[UART_COUNT];

void CheckUsartPortDataEndTimeOut(void)
{
	unsigned char PortNo;

	for (PortNo=0; PortNo < UART_COUNT ; PortNo++)
		{
			if( ((*Uart[PortNo].Status & (PORT_DATA_START | PORT_DATA_STOP)) == PORT_DATA_START ) && Uart[PortNo].PortDataEndCounter >= *Uart[PortNo].DataEnd )
				{
					*Uart[PortNo].Status  = *Uart[PortNo].Status | PORT_DATA_STOP;
					Uart[PortNo].Data[*Uart[PortNo].Offset] = '\0';
				}
		}
}
//void CheckUsartPortTimeOut(void)
//{
//	unsigned char PortNo;
//
//	for (PortNo=0; PortNo < UART_COUNT; PortNo++)
//		{
//
//			if(*Uart[PortNo].Timeout  && (Uart[PortNo].PortDataEndCounter >= (*Uart[PortNo].Timeout * 10)))
//				{
//
//					*Uart[PortNo].Timeout= 0x0000;
//					//
//					// IF SERIAL PORT DATA RECEIVED BEFORE SET PORT DATA STOP BIT (END OF THE  WAIT TIME). IT IS POSSIBLE WHEN PORT_WAIT_TO_TIME IS ENABLE
//					//
//					if( *Uart[PortNo].Status & PORT_DATA_START)
//						*Uart[PortNo].Status  |= PORT_DATA_STOP;
//					else
//						*Uart[PortNo].Status  = 0x00;
//				}
//		}
//}



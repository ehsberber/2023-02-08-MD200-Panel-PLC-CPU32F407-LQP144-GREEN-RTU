/*
 * Modbus_Communication.c
 *
 *  Created on: 7 Oca 2022
 *      Author: SBerber
 */


#include "UartPortProcess.h"
#include "ModBus.h"
#include "ModBusTcp.h"
#include "Registers.h"
#include "Uarts.h"
#include "StringCompare.h"

extern strcUART Uart[UART_COUNT];
extern strcDATASENDCENTER DataSendCenter;
extern strcREGISTERS Registers;
void ModbusActiveClear(void)
{
	static unsigned char state=0;

	switch(state)
		{
			case 0:
					TimerRestart(TIM_NO_MODBUS_ACTIVE_TIMEOUT, 100);
					state = 1;
				break;

			case 1:

				if(DataSendCenter.DataSendControl->ModBusCommActiveTimerRestart)
					{
						DataSendCenter.DataSendControl->ModBusCommActiveTimerRestart = 0;
						state = 0;
					}

				if(Registers.Timers.Control[TIM_NO_MODBUS_ACTIVE_TIMEOUT]->Timeout )
					{
						DataSendCenter.DataSendControl->ModBusCommActive = 0;
						state = 0;
					}
				break;
		}
}

 void ProtocolModbus(void)
 {

	unsigned short DataLength;
	unsigned char Response[250];

	ModbusActiveClear();

//	//
//	// COM1 Modbus Communication
//	//
//	if ( (*Uart[1].Status & (PORT_DATA_START | PORT_DATA_STOP)) ==  (PORT_DATA_START | PORT_DATA_STOP))
//		{
//			DataLength = ModBusCommunication(Uart[1].Data, Response, 1);
//			if( DataLength )
//				{
//					uarttxdata(1, &Response[0], DataLength);
//					*Uart[1].Status = 0x00;
//					*Uart[1].Offset = 0;
//				}
//		}
	//
	// COM2 Modbus Communication
	//

	if ( (*Uart[1].Status &  PORT_DATA_STOP )) // & (PORT_DATA_START | PORT_DATA_STOP)) ==  (PORT_DATA_START | PORT_DATA_STOP))
		{
			DataLength = ModBusCommunication(Uart[1].Data, Response, 1);
			if( DataLength )
				{
					UART1_RS485_TRANSMIT_ENABLE;
					uarttxdata(1, &Response[0], DataLength);
					UART1_RS485_RECEIVE_ENABLE;
				}

			*Uart[1].Status = 0x00;
			*Uart[1].Offset = 0;
		}
	//
	// COM2 Modbus Communication
	//

	if ( (*Uart[2].Status &  PORT_DATA_STOP )) // & (PORT_DATA_START | PORT_DATA_STOP)) ==  (PORT_DATA_START | PORT_DATA_STOP))
		{
			DataLength = ModBusCommunication(Uart[2].Data, Response, 1);
			if( DataLength )
				{
					uarttxdata(2, &Response[0], DataLength);
				}

			*Uart[2].Status = 0x00;
			*Uart[2].Offset = 0;
		}
	//
	// COM3 Modbus Communication
	//
	if ( (*Uart[3].Status & (PORT_DATA_START | PORT_DATA_STOP)) ==  (PORT_DATA_START | PORT_DATA_STOP))
		{
			DataLength = ModBusCommunication(Uart[3].Data, Response, 1);
			//DataLength = ModBusTcpCommunication(Uart[3].Data, Response);
			if( DataLength )
				{

					UART3_RS485_TRANSMIT_ENABLE;

					uarttxdata(3, &Response[0], DataLength);

					DataSendCenter.DataSendControl->ModBusCommActive = 1;
					DataSendCenter.DataSendControl->ModBusCommActiveTimerRestart = 1;
					DataSendCenter.DataSendControl->DataReceive = 1;

					UART3_RS485_RECEIVE_ENABLE;
				}
			else
				{
					//DataLength = ModBusCommunication(Uart[3].Data, Response, 1);
					DataLength = ModBusTcpCommunication(Uart[3].Data, Response);
					if( DataLength )
						{
							UART3_RS485_TRANSMIT_ENABLE;

							uarttxdata(3, &Response[0], DataLength);
							DataSendCenter.DataSendControl->ModBusCommActive = 1;
							DataSendCenter.DataSendControl->ModBusCommActiveTimerRestart = 1;

							UART3_RS485_RECEIVE_ENABLE;

						}
					else
						{
							if( strncompConst( Uart[3].Data,"LGSEG:", 6) == 0 )
								{
									//LGSEG:CONNECTED{0D}{0A}
									DataLength = ModBusTcpCommunication(&Uart[3].Data[17], Response);
									if( DataLength )
										{
											UART3_RS485_TRANSMIT_ENABLE;

											uarttxdata(3, &Response[0], DataLength);
											DataSendCenter.DataSendControl->ModBusCommActive = 1;
											DataSendCenter.DataSendControl->ModBusCommActiveTimerRestart = 1;

											UART3_RS485_RECEIVE_ENABLE;

										}
								}
							else
								{
									if( strncompConst( Uart[3].Data,"Date:", 5) == 0 )
										{
											DataSendCenter.DataSendControl->DataReceive = 1;
										}
								}
						}
				}

			*Uart[3].Status = 0x00;
			*Uart[3].Offset = 0;
		}
}

//
// void ProtocolModbusTCP(void)
// {
//
//	unsigned short DataLength;
//	unsigned char Response[250];
//
//	ModbusActiveClear();
//
//
//	if ( (*Uart[2].Status &  PORT_DATA_STOP ))
//		{
//			DataLength = ModBusCommunication(Uart[2].Data, Response, 1);
//			if( DataLength )
//				{
//					uarttxdata(2, &Response[0], DataLength);
//				}
//
//			*Uart[2].Status = 0x00;
//			*Uart[2].Offset = 0;
//		}
//	//
//	// COM3 Modbus Communication
//	//
//	if ( (*Uart[3].Status & PORT_DATA_STOP) )
//		{
//			DataLength = ModBusTcpCommunication(Uart[3].Data, Response);
//			if( DataLength )
//				{
//					UART3_RS485_TRANSMIT_ENABLE;
//
//					uarttxdata(3, &Response[0], DataLength);
//
//					DataSendCenter.DataSendControl->ModBusCommActive = 1;
//
//					UART3_RS485_RECEIVE_ENABLE;
//				}
//			else
//				{
//					if( strncompConst( Uart[3].Data,"Date:", 5) == 0 )
//						{
//							DataSendCenter.DataSendControl->DataReceive = 1;
//						}
//				}
//
//			*Uart[3].Status = 0x00;
//			*Uart[3].Offset = 0;
//		}
//
//}

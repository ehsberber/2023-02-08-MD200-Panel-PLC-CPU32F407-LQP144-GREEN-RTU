/*
 * DataPacket.c
 *
 *  Created on: Sep 26, 2022
 *      Author: Sezgin Berber
 */

#include "Registers.h"
#include "DataPacket.h"
#include "UartPortProcess.h"
#include "ConvertInteger.h"
#include "Uarts.h"

//Data	Serial No	Packet No	Sub Packet No
//	A8080C0C883DFF0000000000000000														202147901	FF	00
//	A8080C0C883D0000105000000000000000													202147901	00	00
//	A8080C0C883D0100100000000000000000													202147901	01	00
//	A8080C0C883D02004038000000E8FFFFFF000000000000000000000000000000000000000001000000	202147901	02	00
//	A8080C0C883D020140599EFFFF599EFFFF599EFFFF599EFFFF599EFFFF599EFFFF599EFFFF599EFFFF	202147901	02	01
//	A8080C0C883D0202403800E8FF380000000000000000000100599E599E599E599E0000000000000000	202147901	02	02
//	A8080C0C883D0203400000000000000000000000000000000000000000000000000000000000000000	202147901	02	03
//	A8080C0C883D0300400000000000000000000000000000000000000000000000000000000000000000	202147901	03	00
//	A8080C0C883D0301400000000000000000000000000000000000000000000000000000000000000000	202147901	03	01
//	A8080C0C883D0302400400040000000000040004000400040000000000000000000000000000000000	202147901	03	02
//	A8080C0C883D0303400000000000000000000000000000000000000000000000000000000000000000	202147901	03	03

//	Seq.	Value Name					V.Type  V.TypeSeq.  D.Packet	D.Sub Packet	Start  	Len
//	1		Tank1						257		NULL		2			0				1		8
//	3		GD1							658		NULL		2			0				33		8
//	4		GD2							1794	NULL		2			0				41		8
//	5		GD3							NULL	NULL		2			0				49		8
//	6		GD4							NULL	NULL		2			0				57		8
//	7		Probe 1						NULL	NULL		2			0				17		8
//	50		Constant Level				3842	NULL		2			10				251		8
//	51		Illegal Fueling				3841	NULL		2			10				251		8
//	70		I-Button					756		NULL		8			10				1		4


//	08A10C0DE061FF0000000000000000
//	08A10C0DE061000008F0010000
//	08A10C0DE06101000858000000
//	08A10C0DE061020040260000004B000000000000000000000000000000000000001200000002000000
//	08A10C0DE0610201400000000000000000000000000000000000000000000000004B00000026000000
//	08A10C0DE061030040A30100009A0200000300000003000000030000000300000020010000B3000000
//	08A10C0DE0610301400000000000000000000000000000000000000000000000009A020000A3010000

extern strcDATASENDCENTER DataSendCenter;
extern strcPLC Plc;
extern strcRTC RtcData;
extern strcREGISTERS Registers;

void GetToBeSendSubPacketNo(void)
{
	unsigned char SubPacketNo;
	unsigned int Mask = 0x00000001;
	if(DataSendCenter.ToBeSendPacket)
		{
			for(SubPacketNo=0; SubPacketNo<32; SubPacketNo++)
				{
					if(*DataSendCenter.ToBeSendSubPacket & Mask)
						{
							*DataSendCenter.SendSubPacketNo	= SubPacketNo;
							*DataSendCenter.ToBeSendSubPacket = *DataSendCenter.ToBeSendSubPacket & ~Mask;
							break;
						}
					Mask <<= 1;
				}
		}
}

void DataPacketHeader(void)
{
	uarttxshorthex(TCP_UDP_PORT, DATA_PLC_TYPE);
	uarttxinthex(TCP_UDP_PORT, *Plc.SerialNo);
}

void DataPacketTimeBody(void)
{
	unsigned char i;
	uarttxcharhex(TCP_UDP_PORT, DATA_DATE_PACKET_NO);
	for(i=0;i<8;i++)
		{
			uarttxcharhex(TCP_UDP_PORT, RtcData.Date[i]);
		}
	uarttxchar(TCP_UDP_PORT, RETURN);
	uarttxchar(TCP_UDP_PORT, LINEFEED);
}

void SendDataPacketTime(void)
{
	UART3_RS485_TRANSMIT_ENABLE;

	DataPacketHeader();
	DataPacketTimeBody();

	UART3_RS485_RECEIVE_ENABLE;
}


void DataPacketBodyDigitalInput(void)
{
	unsigned char DataLen = 8;
	uarttxcharhex(TCP_UDP_PORT, DataLen);
	uarttxinthexrev(TCP_UDP_PORT, Registers.Input[0]);
}

void DataPacketBodyDigitalOutput(void)
{
	unsigned char DataLen = 8;
	uarttxcharhex(TCP_UDP_PORT, DataLen);
	uarttxinthexrev(TCP_UDP_PORT, Registers.Coil[0]);
}

void DataPacketBodyAnalogInput(void)
{
	unsigned short Channel;
	unsigned char DataLen = 64;
	signed int DataValueMultiplier;
	unsigned char ByteSort = 0;

	DataValueMultiplier = *DataSendCenter.DataChannelValueMultiplier;

	if(DataValueMultiplier<0)
		{
			DataValueMultiplier = DataValueMultiplier * -1;
			ByteSort = 1;
		}

	uarttxcharhex(TCP_UDP_PORT, DataLen);

	if(DataValueMultiplier)
		{
			for(Channel = 0; Channel < 8; Channel++)
					{
						if(ByteSort)
							{
								uarttxinthex(TCP_UDP_PORT, *Plc.Peripheral.AnalogInput.Calculated[(*DataSendCenter.SendSubPacketNo * 8 ) + Channel] * DataValueMultiplier);
							}
						else
							{
								uarttxinthexrev(TCP_UDP_PORT, *Plc.Peripheral.AnalogInput.Calculated[(*DataSendCenter.SendSubPacketNo * 8 ) + Channel] * DataValueMultiplier);
							}

					}
		}
	else
		{
			for(Channel = 0; Channel < 8; Channel++)
					{

						uarttxfloathex(TCP_UDP_PORT, *Plc.Peripheral.AnalogInput.Calculated[(*DataSendCenter.SendSubPacketNo * 8 ) + Channel]);
					}
		}
}

void DataPacketBodyAnalogInputChannelValue(void)
{
	unsigned short Channel;
	unsigned char DataLen = 64;
	signed int AnalogValueMultiplier;
	unsigned char ByteSort = 0;

	AnalogValueMultiplier = *DataSendCenter.DataAnalogInputValueMultiplier;

	uarttxcharhex(TCP_UDP_PORT, DataLen);

	if(AnalogValueMultiplier)
		{
			for(Channel = 0; Channel < 8; Channel++)
					{
						if(ByteSort)
							{
								uarttxinthex(TCP_UDP_PORT, *Plc.Peripheral.AnalogInput.AnalogValue[(*DataSendCenter.SendSubPacketNo * 8 ) + Channel] * AnalogValueMultiplier);
							}
						else
							{
								uarttxinthexrev(TCP_UDP_PORT, *Plc.Peripheral.AnalogInput.AnalogValue[(*DataSendCenter.SendSubPacketNo * 8 ) + Channel] * AnalogValueMultiplier);
							}

					}
		}
	else
		{
			for(Channel = 0; Channel < 8; Channel++)
					{

						uarttxfloathex(TCP_UDP_PORT, *Plc.Peripheral.AnalogInput.AnalogValue[(*DataSendCenter.SendSubPacketNo * 8 ) + Channel]);
					}
		}
}

void DataPacketBody(void)
{

	uarttxcharhex(TCP_UDP_PORT, *DataSendCenter.SendPacketNo);
	uarttxcharhex(TCP_UDP_PORT, *DataSendCenter.SendSubPacketNo);

	switch(*DataSendCenter.SendPacketNo)
		{
			case 0:
				DataPacketBodyDigitalInput();
			break;

			case 1:
				DataPacketBodyDigitalOutput();
			break;

			case 2:
				DataPacketBodyAnalogInput();
			break;

			case 3:
				DataPacketBodyAnalogInputChannelValue();
			break;

			break;
		}

	uarttxchar(TCP_UDP_PORT, RETURN);
	uarttxchar(TCP_UDP_PORT, LINEFEED);
}

void SendDataPacket(void)
{
	UART3_RS485_TRANSMIT_ENABLE;
	DataPacketHeader();

	GetToBeSendSubPacketNo();
	DataPacketBody();

	UART3_RS485_RECEIVE_ENABLE;
}


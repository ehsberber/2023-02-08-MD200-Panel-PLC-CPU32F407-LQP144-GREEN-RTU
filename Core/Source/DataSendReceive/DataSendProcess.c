/*
 * DataSendProcess.c
 *
 *  Created on: Sep 19, 2022
 *      Author: Sezgin Berber
 */

#include "Registers.h"
#include "TimerProcess.h"
#include "DataPacket.h"
#include "Uarts.h"
#include "DigitalOutput.h"

extern strcPLC Plc;
extern strcDATASENDCENTER DataSendCenter;
extern strcREGISTERS Registers;
extern strcALERTES AlertES;
extern strcHMI HMI;
extern strcSYSTEM System;

void DataSendCondition(void)
{
	static unsigned int DILast = 0, DOLast =0;
	static unsigned int AlertMasterLT = 0,AlertMasterGD = 0;
	unsigned char SendData = 0;


	if( (DILast != Registers.Input[0]) )
		{
			SendData = 1;
		}

	if(  DOLast !=  ( Registers.Coil[0] & ~(0x0001 << DO_NO_ALERT) ))
		{
			SendData = 1;
		}

	if(AlertMasterLT != (*AlertES.Master.LT.AlertState | *AlertES.Master.LT.ESState))
		{
			SendData = 1;
		}

	if(AlertMasterGD != (*AlertES.Master.GD.AlertState | *AlertES.Master.GD.ESState))
		{
			SendData = 1;
		}

	if(SendData)
		{
			*DataSendCenter.ToBeSendPacket = *DataSendCenter.DefaultPacket;
			//TimerRestart(TIM_NO_DATA_SEND, *DataSendCenter.DataSendPeriod);
		}

	AlertMasterLT = *AlertES.Master.LT.AlertState | *AlertES.Master.LT.ESState;
	AlertMasterGD = *AlertES.Master.GD.AlertState | *AlertES.Master.GD.ESState;
	DILast = Registers.Input[0];
	DOLast = ( Registers.Coil[0] & ~(0x0001 << DO_NO_ALERT) );
}

void DataNoActivityTimeout(void)
{
	static unsigned short State=0;

	if(DataSendCenter.DataSendControl->ModBusCommActive || DataSendCenter.DataSendControl->DataReceive)
		{
			State = 0;
		}

	switch(State)
		{
			case 0:
					UART3_ETHERNET_ENABLE;

					State = 1;
				break;

			case 1:
					if(*DataSendCenter.DataSendPeriod > 0)
						{
							TimerRestart(TIM_NO_NO_DATA_ACTIVITY, (*DataSendCenter.DataSendPeriod * 2) + 300);
							State = 2;
						}
					else
						{
							UART3_ETHERNET_ENABLE;
						}
				break;

			case 2:
					if(Registers.Timers.Control[TIM_NO_NO_DATA_ACTIVITY]->Timeout )
						{
							UART3_ETHERNET_DISABLE;

							TimerRestart(TIM_NO_NO_DATA_ACTIVITY, 300);
							State = 3;
						}
					break;
			case 3:
					if(Registers.Timers.Control[TIM_NO_NO_DATA_ACTIVITY]->Timeout )
						{
							State = 0;
						}
					break;
		}
}


void DataSendTimeout(void)
{
	static unsigned short State=0;
	static unsigned int DataSendPeriod=0;
	static unsigned char ModBusCommActive=0;


	if(DataSendPeriod != *DataSendCenter.DataSendPeriod)
		{
			State = 1;
			DataSendPeriod = *DataSendCenter.DataSendPeriod;
		}

	if(ModBusCommActive == 0 && DataSendCenter.DataSendControl->ModBusCommActive)
		{
			State = 1;
		}
	ModBusCommActive = DataSendCenter.DataSendControl->ModBusCommActive ;


	if(*DataSendCenter.DataSendPeriod)
		{
			switch(State)
				{
					case 0:
							UART3_ETHERNET_ENABLE;

							*DataSendCenter.ToBeSendPacket = *DataSendCenter.DefaultPacket;
							if(*DataSendCenter.DataSendPeriod)
								{
									DataSendCenter.DataSendControl->DataSent = 0;
									TimerRestart(TIM_NO_DATA_SEND, *DataSendCenter.DataSendPeriod);
									State = 2;
								}
						break;

					case 1:
							TimerRestart(TIM_NO_DATA_SEND, *DataSendCenter.DataSendPeriod);
							State = 2;
						break;

					case 2:
							if(Registers.Timers.Control[TIM_NO_DATA_SEND]->Timeout )
								{
									*DataSendCenter.ToBeSendPacket = *DataSendCenter.DefaultPacket;

									TimerRestart(TIM_NO_DATA_SEND, *DataSendCenter.DataSendPeriod);
									State = 1;
								}

							if(!Registers.Timers.Control[TIM_NO_DATA_SEND]->Enable || Registers.Timers.Control[TIM_NO_DATA_SEND]->Hang)
								{
									State = 1;
								}
				}
		}
}

void GetToBeSendSubPacket(void)
{
	switch(*DataSendCenter.SendPacketNo)
		{
			case 0:
			case 1:
					*DataSendCenter.ToBeSendSubPacket = 0x0001;
			break;

			case 2:
					*DataSendCenter.ToBeSendSubPacket = 0x0003;
				break;

			case 3:
					*DataSendCenter.ToBeSendSubPacket = 0x0003;
				break;

			case 8:
					*DataSendCenter.ToBeSendSubPacket = 0x0001;
				break;

			default:
					*DataSendCenter.ToBeSendSubPacket = 0x0000;
			break;

		}

	}

void GetToBeSendPacketNo(void)
{

	unsigned char PacketNo;
	unsigned int Mask = 0x00000001;
	if(DataSendCenter.ToBeSendPacket)
		{
			for(PacketNo=0; PacketNo<32; PacketNo++)
				{
					if(*DataSendCenter.ActiveToBeSendPacket & Mask)
						{
							*DataSendCenter.SendPacketNo 			= PacketNo;
							*DataSendCenter.ActiveToBeSendPacket = *DataSendCenter.ActiveToBeSendPacket & ~Mask;

							GetToBeSendSubPacket();
							break;
						}
					Mask <<= 1;
				}
		}
}


void DataSendProcess(void)
{
	static unsigned short State=0;

	if(DataSendCenter.DataSendControl->ModBusCommActive) return;

	switch(State)
		{
			case 0:

					if(Plc.Status->ProcessStart && *DataSendCenter.ToBeSendPacket)
						{
							*DataSendCenter.ActiveToBeSendPacket 	= *DataSendCenter.ToBeSendPacket;
							*DataSendCenter.ToBeSendPacket 			= 0;

							DataSendCenter.DataSendControl->DataSent 	= 0;
							DataSendCenter.DataSendControl->DataReceive	= 0;
							DataSendCenter.DataSendControl->DataSendInprogress = 1;
							State = 1;
						}
				break;

			case 1:
					//
					// Time Data Packet
					//
					SendDataPacketTime();
					State = 2;
				break;

			case 2:
					GetToBeSendPacketNo();
					State = 3;
				break;

			case 3:
					SendDataPacket();
					State = 4;
				break;

			case 4:
				if(*DataSendCenter.ToBeSendSubPacket)
					{
						State = 3;
					}
				else
					{
						if(*DataSendCenter.ActiveToBeSendPacket)
							{
								State = 2;
							}
						else
							{
								DataSendCenter.DataSendControl->DataSent 			= 1;
								DataSendCenter.DataSendControl->DataSendInprogress 	= 0;
								State = 0;
							}
					}
				break;
		}
}

void TcpDataSend(void)
{
	DataNoActivityTimeout();
	DataSendCondition();
	DataSendTimeout();
	DataSendProcess();
}

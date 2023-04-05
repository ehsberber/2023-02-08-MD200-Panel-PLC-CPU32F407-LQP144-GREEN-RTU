/*
 * ModemProcess.c
 *
 *  Created on: Feb 3, 2023
 *      Author: Sezgin Berber
 */
#include "Registers.h"
#include "Modem.h"

extern strcGSM GSM;


void SmsReplyToBeSend(void)
{
	unsigned short Counter , Mask = 0x0001 ;
	//
	// Check To Be Send Sms
	//
	if(*GSM.Sms.ActiveReplyGsm) return;

	for(Counter=1; Counter <= 16 ;Counter++ )
		{
			if(*GSM.Sms.SendStatus & *GSM.Sms.SendStatusEnable & Mask)
				{
					*GSM.Sms.ActiveReplyGsm =  *GSM.Sms.ReplyGsm[Counter];
				}
		}
}

void ModemStateSet(void)
{

	if(*GSM.Modem.Status != stateNone) return;

	if(GSM.Modem.Response->ResponseState.Initialize != INITIALIZE_STATE_OK)
		{
			*GSM.Modem.Status = stateInitialize;
			return;
		}

	SmsReplyToBeSend();

	if(*GSM.Sms.ActiveReplyGsm)
		{
			*GSM.Modem.Status = stateSmsSend;
		}

}

void ModemProcess(void)
{
	switch( *GSM.Modem.Status)
		{
			case stateNone:

				break;
			case  stateInitialize:
					*GSM.Modem.Status = 2;
				break;

			default:
				*GSM.Modem.Status = 0;
				break;

		}
}

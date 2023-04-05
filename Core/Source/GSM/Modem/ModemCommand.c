/*
 * ModemCommand.c
 *
 *  Created on: Feb 3, 2023
 *      Author: Sezgin Berber
 */
#include "Registers.h"
#include "string.h"

extern strcGSM GSM;

void ModemCommandPrepare(void)
{
	switch (*GSM.Modem.CommandNo)
		{
			case cmdAT:
					strcopyFromConst(GSM.Modem.Command, "AT");
				break;

			case cmdATE:
					strcopyFromConst(GSM.Modem.Command, "ATE");
				break;

			case cmdCMGF:
					strcopyFromConst(GSM.Modem.Command, "AT+CMGF=1");
				break;


			default:
					GSM.Modem.Command[0] = '\0';
				break;

		}
}

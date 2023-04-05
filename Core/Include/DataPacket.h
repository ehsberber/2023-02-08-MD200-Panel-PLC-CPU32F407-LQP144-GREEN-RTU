/*
 * DataPacket.h
 *
 *  Created on: Sep 26, 2022
 *      Author: Sezgin Berber
 */

#ifndef INCLUDE_DATAPACKET_H_
#define INCLUDE_DATAPACKET_H_



#define DATA_PLC_TYPE				0xD8A1
#define DATA_DATE_PACKET_NO			0xFF

	void SendDataPacketTime(void);
	void SendDataPacket(void);

#endif /* INCLUDE_DATAPACKET_H_ */

/*
 * ModbusRegister.h
 *
 *  Created on: 30 Ara 2021
 *      Author: SBerber
 */

#ifndef HEADER_MODBUSREGISTER_H_
#define HEADER_MODBUSREGISTER_H_
	#define MODBUS_CR			0x00010000
	#define MODBUS_SR			0x00020000
	#define MODBUS_HR			0x00030000
	#define	MODBUS_IR			0x00040000


	#define MDB_FNC_CR 		0x01
	#define MDB_FNC_IS 		0x02
	#define MDB_FNC_HR 		0x03
	#define MDB_FNC_HR_R 	0x53
	#define MDB_FNC_HRA		0x63
	#define MDB_FNC_SR 		0x04
	#define MDB_FNC_SR_R 	0x54
	#define MDB_FNC_SRA 	0x64
	#define MDB_FNC_FSC		0x05
	#define MDB_FNC_PSR		0x06
	#define MDB_FNC_FPC		0x0F
	#define MDB_FNC_PMR		0x10
	#define MDB_FNC_PMR_R 	0x60
	#define MDB_FNC_SMR		0x20
	#define MDB_FNC_SMR_R 	0x80


	#define MDB_FNC_RLC 	0x81


#endif /* HEADER_MODBUSREGISTER_H_ */

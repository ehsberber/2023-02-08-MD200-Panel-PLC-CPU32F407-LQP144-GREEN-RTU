//#include "STM32F4XX_HAL_UART.h"

#ifndef APPLICATION_USER_HEADER_UARTPORTPROCESS_H_
#define APPLICATION_USER_HEADER_UARTPORTPROCESS_H_

	#define	UART_TX_NO_CR_LF		0
	#define	UART_TX_LF				1
	#define	UART_TX_CR				2
	#define	UART_TX_CR_LF			3

	#include "MicroPeripheral.h"

	UART_HandleTypeDef *UartHandle(unsigned char UartPortNo, UART_HandleTypeDef *HandledUart);
	int uarttxchar(unsigned char uartPort,unsigned char ch);
	int uarttxcharctrl(unsigned char uartPort,unsigned char ch);
	unsigned short uarttxstring(unsigned char uartPort,unsigned char *p,unsigned char EndOfAndLineFeed) ;
	unsigned short uarttxstringLength(unsigned char uartPort,unsigned char *p, unsigned short MaxLength, unsigned char EndOfAndLineFeed) ;
	unsigned short uarttxConststring(unsigned char uartPort,const char *p,unsigned char EndOfAndLineFeed);
	unsigned short uarttxstringmid(unsigned char uartPort,unsigned char *p,unsigned char Start, unsigned short Length, unsigned char EndOfAndLineFeed);
	void uarttxstringNC(unsigned char uartPort,unsigned char *p,unsigned char ncChar,unsigned char EndOfAndLineFeed) ;
	void uarttxdata(unsigned char uartport,unsigned char *p,unsigned short datalength);
	void uarttxdatahex(unsigned char uartport,unsigned char *p,unsigned short datalength);
	void uarttxdatahexmid(unsigned char uartport,unsigned char *p,unsigned short StartPosition,unsigned short datalength);
	void uarttxcharhex(unsigned char uartport,unsigned char p);
	void uarttxdatahexwithdelay(unsigned char uartport,unsigned char *p,unsigned short datalength,unsigned int delay);
	void uarttxshorthex(unsigned char uartport,unsigned short p);
	void uarttxinthex(unsigned char uartport,unsigned int p);
	void uarttxinthexrev(unsigned char uartport,unsigned int p);
	void uarttxlonghex(unsigned char uartport,unsigned long int p);

	void uarttxshort(unsigned char uartport,unsigned short p);
	void uarttxint(unsigned char uartport,unsigned int p);
	void uarttxdatawithdelay(unsigned char uartport,unsigned char *p,unsigned short datalength,unsigned int delay);

	void uarttxfloathex(unsigned char uartport,float p);

#endif

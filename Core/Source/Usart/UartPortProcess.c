#include "MicroPeripheral.h"

//#define RETURN     0x0D

extern const unsigned char HexArray[];

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;


UART_HandleTypeDef *UartHandle(unsigned char UartPortNo, UART_HandleTypeDef *HandledUart)
{
	switch(UartPortNo)
		{
			case 1:
					*HandledUart = huart1;
					break;
			
			case 2:
					*HandledUart = huart2;
					break;
			
			case 3:
					*HandledUart = huart3;
					break;
			
//			case 4:
//					*HandledUart = huart4;
//					break;
//
//			case 5:
//					*HandledUart = huart5;
//					break;
//
//			case 6:
//					*HandledUart = huart6;
//					break;
					
//			default:
//					*HandledUart = huart1;
		}
	return HandledUart;
}

int uarttxchar(unsigned char UartPortNo,unsigned char ch)
{
	UART_HandleTypeDef HandledUartPort ;
		
	UartHandle(UartPortNo, &HandledUartPort);
	
	while(HAL_UART_Transmit( &HandledUartPort, &ch, 1, 1000) != HAL_OK);
 
	return 1;
}

int uarttxcharctrl(unsigned char UartPortNo,unsigned char ch)
{
	UART_HandleTypeDef HandledUartPort ;
		
	UartHandle(UartPortNo, &HandledUartPort);

	while(HAL_UART_Transmit( &HandledUartPort, &ch, 1, 1000) != HAL_OK);
	return 1;
}

unsigned short uarttxstring(unsigned char UartPortNo, unsigned char *p, unsigned char EndOfAndLineFeed) 
{                   
	UART_HandleTypeDef HandledUartPort ;
		
	unsigned short LengthOfString=0;
	unsigned char CtrlChar;
	
	UartHandle(UartPortNo, &HandledUartPort);

	for(LengthOfString=0; p[LengthOfString] != '\0'; LengthOfString++);
	 
	while(HAL_UART_Transmit( &HandledUartPort, p, LengthOfString, 1000) != HAL_OK);
  
	
	if(EndOfAndLineFeed &0x02) { CtrlChar = 13; while(HAL_UART_Transmit( &HandledUartPort, &CtrlChar, 1, 1000) != HAL_OK);}
	if(EndOfAndLineFeed &0x01) { CtrlChar = 10; while(HAL_UART_Transmit( &HandledUartPort, &CtrlChar, 1, 1000) != HAL_OK);}
	
	return LengthOfString;
}

void uarttxdatawithdelay(unsigned char uartport,unsigned char *p,unsigned short datalength, unsigned int delay)
{
	unsigned int i;
	if (uartport >= 15 || datalength == 0) return;
	while(datalength--) { uarttxcharctrl(uartport,*p++); for(i=0;i<delay;i++); }
}

unsigned short uarttxstringLength(unsigned char uartPort,unsigned char *p, unsigned short MaxLength, unsigned char EndOfAndLineFeed) 
{                   
	unsigned short LengthOfString=0;
	if(uartPort >= 15) return 0;
  while (*p && LengthOfString < MaxLength ) 	{ LengthOfString++; uarttxchar(uartPort,*p++);}

	if(EndOfAndLineFeed &0x02) uarttxchar (uartPort,13);
	if(EndOfAndLineFeed &0x01) uarttxchar (uartPort,10);
	return LengthOfString;
}

unsigned short uarttxConststring(unsigned char uartPort,const char *p,unsigned char EndOfAndLineFeed) 
{                   
	unsigned short LengthOfString=0;
	if(uartPort >= 15) return 0;
  while (*p) 	{ LengthOfString++; uarttxchar (uartPort,*p++);}
	if(EndOfAndLineFeed &0x02) uarttxchar (uartPort,13);
	if(EndOfAndLineFeed &0x01) uarttxchar (uartPort,10);
	return LengthOfString;
}

void uarttxstringNC(unsigned char uartPort,unsigned char *p,unsigned char ncChar,unsigned char EndOfAndLineFeed) 
{                   /* Write string */
	int Index=0;
	if(uartPort >= 15) return ;
  	while (p[Index]) 	{ if(p[Index] != ncChar) uarttxchar(uartPort,p[Index]); Index++;}
	if(EndOfAndLineFeed &0x02) uarttxchar (uartPort,13);
	if(EndOfAndLineFeed &0x01) uarttxchar (uartPort,10);
}

unsigned short uarttxstringmid(unsigned char uartPort,unsigned char *p,unsigned char Start, unsigned short Length, unsigned char EndOfAndLineFeed) 
{	unsigned char Counter=0;                   
	unsigned short LengthOfString=0;
	if(uartPort >= 15) return 0;
  	while (*(p+Start) && Counter <Length ) 	{ LengthOfString++; uarttxchar (uartPort,*p++);Counter++;}
	if(EndOfAndLineFeed &0x02) uarttxchar (uartPort,13);
	if(EndOfAndLineFeed &0x01) uarttxchar (uartPort,10);
	return LengthOfString;
}

//void uarttxstringNC(unsigned char uartPort,unsigned char *p,unsigned char ncChar,unsigned char EndOfAndLineFeed) 
//{                   /* Write string */
//	if(uartPort >= 15) return ;
//  while (*p) 	{ if(*p != ncChar) uarttxchar(uartPort,*p); *p++;}
//	if(EndOfAndLineFeed &0x02) uarttxchar (uartPort,13);
//	if(EndOfAndLineFeed &0x01) uarttxchar (uartPort,10);
//}

void uarttxdata(unsigned char UartPortNo,unsigned char *p,unsigned short datalength)
{
	UART_HandleTypeDef HandledUartPort ;
		
	UartHandle(UartPortNo, &HandledUartPort);
	
	while(HAL_UART_Transmit(&HandledUartPort, p, datalength , 1000) != HAL_OK);
	
	//while(datalength--) uarttxcharctrl(uartport,*p++);
}

void uarttxcharhex(unsigned char uartport,unsigned char p)
{
	if(uartport >= 15) return ;
	uarttxchar(uartport,HexArray[p >> 4]); uarttxchar(uartport,HexArray[p & 0x0F]);
}

void uarttxdatahexwithdelay(unsigned char uartport,unsigned char *p,unsigned short datalength,unsigned int delay)
{
	unsigned int i;
	if(uartport >= 15) return ;
	while(datalength--) { uarttxcharhex(uartport,*p++); for(i=0;i<delay;i++); }
}

void uarttxdatahexReversewithdelay(unsigned char uartport,unsigned char *p,unsigned short datalength,unsigned int delay)
{
	unsigned int i;
	if(uartport >= 15) return ;
	while(datalength--) 
		{ 
			uarttxcharhex(uartport,p[datalength]); 
			for(i=0;i<delay;i++); 
		}
}

void uarttxfloathex(unsigned char uartport,float p)
{
	unsigned char *c;
	c = (unsigned char *)&p;
	if(uartport >= 15) return ;
	uarttxchar(uartport,HexArray[c[3] >> 4]); uarttxchar(uartport,HexArray[c[3] & 0x0F]);
	uarttxchar(uartport,HexArray[c[2] >> 4]); uarttxchar(uartport,HexArray[c[2] & 0x0F]);
	uarttxchar(uartport,HexArray[c[1] >> 4]); uarttxchar(uartport,HexArray[c[1] & 0x0F]);
	uarttxchar(uartport,HexArray[c[0] >> 4]); uarttxchar(uartport,HexArray[c[0] & 0x0F]);
}

void uarttxshorthex(unsigned char uartport,unsigned short p)
{
	unsigned char *c;
	c = (unsigned char *)&p;
	if(uartport >= 15) return ;

	uarttxchar(uartport,HexArray[c[1] >> 4]); uarttxchar(uartport,HexArray[c[1] & 0x0F]);
	uarttxchar(uartport,HexArray[c[0] >> 4]); uarttxchar(uartport,HexArray[c[0] & 0x0F]);
}

void uarttxinthex(unsigned char uartport,unsigned int p)
{
	unsigned char *c;
	c = (unsigned char *)&p;
	if(uartport >= 15) return ;
	uarttxchar(uartport,HexArray[c[3] >> 4]); uarttxchar(uartport,HexArray[c[3] & 0x0F]);
	uarttxchar(uartport,HexArray[c[2] >> 4]); uarttxchar(uartport,HexArray[c[2] & 0x0F]);
	uarttxchar(uartport,HexArray[c[1] >> 4]); uarttxchar(uartport,HexArray[c[1] & 0x0F]);
	uarttxchar(uartport,HexArray[c[0] >> 4]); uarttxchar(uartport,HexArray[c[0] & 0x0F]);
}

void uarttxinthexrev(unsigned char uartport,unsigned int p)
{
	unsigned char *c;
	c = (unsigned char *)&p;
	if(uartport >= 15) return ;
	uarttxchar(uartport,HexArray[c[0] >> 4]); uarttxchar(uartport,HexArray[c[0] & 0x0F]);
	uarttxchar(uartport,HexArray[c[1] >> 4]); uarttxchar(uartport,HexArray[c[1] & 0x0F]);
	uarttxchar(uartport,HexArray[c[2] >> 4]); uarttxchar(uartport,HexArray[c[2] & 0x0F]);
	uarttxchar(uartport,HexArray[c[3] >> 4]); uarttxchar(uartport,HexArray[c[3] & 0x0F]);
}

void uarttxlonghex(unsigned char uartport,unsigned long int p)
{
	unsigned char *c;
	c = (unsigned char *)&p;
	if(uartport >= 15) return ;
//	uarttxchar(uartport,HexArray[c[7] >> 4]); uarttxchar(uartport,HexArray[c[7] & 0x0F]);
//	uarttxchar(uartport,HexArray[c[6] >> 4]); uarttxchar(uartport,HexArray[c[6] & 0x0F]);
//	uarttxchar(uartport,HexArray[c[5] >> 4]); uarttxchar(uartport,HexArray[c[5] & 0x0F]);
//	uarttxchar(uartport,HexArray[c[4] >> 4]); uarttxchar(uartport,HexArray[c[4] & 0x0F]);
	uarttxchar(uartport,HexArray[c[3] >> 4]); uarttxchar(uartport,HexArray[c[3] & 0x0F]);
	uarttxchar(uartport,HexArray[c[2] >> 4]); uarttxchar(uartport,HexArray[c[2] & 0x0F]);
	uarttxchar(uartport,HexArray[c[1] >> 4]); uarttxchar(uartport,HexArray[c[1] & 0x0F]);
	uarttxchar(uartport,HexArray[c[0] >> 4]); uarttxchar(uartport,HexArray[c[0] & 0x0F]);
}

void uarttxshort(unsigned char uartport,unsigned short p)
{
	unsigned char *c;
	c = (unsigned char *)&p;
	if(uartport >= 15) return ;

	uarttxchar(uartport,c[1]); uarttxchar(uartport,c[0]);
}

void uarttxint(unsigned char uartport,unsigned int p)
{
	unsigned char *c;
	c = (unsigned char *)&p;
	if(uartport >= 15) return ;

	uarttxchar(uartport,c[3]); uarttxchar(uartport,c[2]); uarttxchar(uartport,c[1]); uarttxchar(uartport,c[0]);
}
void uarttxdatahex(unsigned char uartport,unsigned char *p, unsigned short datalength)
{
	//while(datalength--) { uarttxchar(uartport,HexArray[*p >> 4]); uarttxchar(uartport,HexArray[*p++ & 0x0F]); }
	if(uartport >= 15) return ;
	while(datalength--) { uarttxcharhex(uartport,*p++);}
}

void uarttxdatahexReverse(unsigned char uartport,unsigned char *p, unsigned short datalength)
{
	//while(datalength--) { uarttxchar(uartport,HexArray[*p >> 4]); uarttxchar(uartport,HexArray[*p++ & 0x0F]); }
	if(uartport >= 15) return ;
	while(datalength--) 
		{ 
			uarttxcharhex(uartport, p[datalength]);
		}
}

void uarttxdatahexmid(unsigned char uartport,unsigned char *p,unsigned short StartPosition,unsigned short datalength)
{
	//while(datalength--) { uarttxchar(uartport,HexArray[*p >> 4]); uarttxchar(uartport,HexArray[*p++ & 0x0F]); }
	if(uartport >= 15) return ;
	while(datalength--) { uarttxcharhex(uartport,p[StartPosition++]);}
}

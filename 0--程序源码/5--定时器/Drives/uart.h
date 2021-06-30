#ifndef __UART_H__
#define __UART_H__

extern unsigned short RxDataBuf[100];
extern unsigned short RxDataLen;
extern unsigned short RxDataFlag;

void Initial_Uart(void);

void putByte(unsigned char Byte);
void printStr(char *pStr);


#endif
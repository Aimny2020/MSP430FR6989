#include "uart.h"
#include "io430.h"
#include "stdio.h"

unsigned short RxDataBuf[100];
unsigned short RxDataLen = 0;
unsigned short RxDataFlag = 0;

void Initial_Uart(void)
{
    /* ������������  P3.4/UCA1TXD  P3.5/UCA1RXD */
    P3DIR |= BIT4;
    P3OUT |= BIT4;
    P3SEL0 |= BIT4;    
    P3SEL1 &= ~BIT4;

    P3DIR &= ~BIT5;
    P3SEL0 |= BIT5;    
    P3SEL1 &= ~BIT5;
    /* ʹ������ɵ�IO����Ч����LPMx.5�˳� */
    PM5CTL0 &= ~LOCKLPM5;

    /* ���ڲ������� */
    UCA1CTLW0 = UCSWRST;            // ----------------- ʹ�ܴ�������
    
    UCA1CTLW0 |= UCSSEL__SMCLK ;     // ʱ��=SMCLK 8M, 8 N 1 , LSB
    UCA1BRW_L = 04;                  // 115200bps
    UCA1BRW_H = 0;   
    UCA1MCTLW_L = UCOS16 | UCBRF_5;
    UCA1MCTLW_H = 0x55;
    
    UCA1CTLW0 &= ~UCSWRST;          // ----------------- ��ֹ��������

    UCA1IE &= ~UCTXIE;              // ��ֹ�����ж�
    UCA1IE |= UCRXIE;               // ��������ж�
    
}

void putByte(unsigned char Byte)
{
    while (!(UCA1IFG&UCTXIFG)); // �ȴ���־λ
	
    UCA1TXBUF = Byte; 
}

void printStr(char *pStr)
{
    while ((*pStr != '\0'))
    {
        putByte(*pStr++);
    }
    return;
}

/*****************************************************************************
 * �� �� ��  : putchar
 * ��    ��  : Lemon
 * ��������  : 2021��5��8��
 * ��������  : ��дputchar������ʵ��printf������ʹ��
 * �������  : int c  
 * �� �� ֵ  : int
 * ���ù�ϵ  : 
 * ��    ��  : 
*****************************************************************************/
int putchar(int c)
{
	if(c == '\n')
	{
		while (!(UCA1IFG&UCTXIFG)); // �ȴ���־λ
		UCA1TXBUF = '\r';
	}
	while (!(UCA1IFG&UCTXIFG)); 
	UCA1TXBUF = c;
	return c;
}

unsigned short RxChar;
#pragma vector = USCI_A1_VECTOR
__interrupt void ISR_USCI_A1(void)
{
    switch(UCA1IV)
    {
        case 0x00: // Vector 0: No interrupts
            break;
        case 0x02: // Vector 2: UCRXIFG
        {
            UCA1IFG &=~ UCRXIFG;                    // ����жϱ�־
            RxChar = UCA1RXBUF;
               
            RxDataBuf[RxDataLen] = RxChar;
            RxDataLen++; 
           
            if(RxChar == '\n')
            {
                RxDataFlag = 1;
            }
            
            break;
        }
        case 0x04:  // Vector 4: UCTXIFG
            break;
        case 0x06:  // Vector 6: UCSTTIFG
            break;
        case 0x08:  // Vector 8: UCTXCPTIFG
            break;
        default:
            break;
    }
}
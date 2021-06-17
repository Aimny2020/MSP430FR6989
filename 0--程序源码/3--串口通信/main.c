#include "io430.h"
#include "stdio.h"

#define CPU_CLOCK       8000000
#define Delay_Us(us)    __delay_cycles(CPU_CLOCK / 1000000 * (us))
#define Delay_Ms(ms)    __delay_cycles(CPU_CLOCK / 1000 * (ms))

#define S1_IN       P1IN_bit.P1IN1
#define S2_IN       P1IN_bit.P1IN2

void Initial_Clock(void);
void Initial_Uart(void);
void Initial_Led(void);

void putByte(unsigned char Byte);
void printStr(char *pStr);

int main( void )
{
    /* �رտ��Ź� */
    WDTCTL = WDTPW | WDTHOLD;
    
    Initial_Clock();
    Initial_Uart();
    Initial_Led();
    
    __bis_SR_register(GIE);//ʹ��ȫ���ж�
    /* ʹ������ɵ�IO����Ч����LPMx.5�˳� */
    PM5CTL0 &= ~LOCKLPM5; 
    
    while(1)
    {
        putByte('a');
        printStr(" Hello ");
        printf("Shandong University!\n"); 
        
        Delay_Ms(1000);
    }
}

unsigned short RxChar;
#pragma vector = USCI_A1_VECTOR
__interrupt void ISR_USCI_A1(void)
{
    switch(__even_in_range(UCA1IV, 8))
    {
        case 0x00: // Vector 0: No interrupts
            break;
        case 0x02: // Vector 2: UCRXIFG
        {
            UCA1IFG &=~ UCRXIFG;                    // ����жϱ�־
            RxChar = UCA1RXBUF;
            
            UCA1TXBUF = RxChar;          
            
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


void Initial_Clock(void)
{
    /* �ⲿ32.768kʹ�� */ 
    PJSEL0 |= BIT4;    
    PJSEL1 &= ~BIT4;
    
    PJSEL0 |= BIT5;    
    PJSEL1 &= ~BIT5;
    /* ʹ������ɵ�IO����Ч����LPMx.5�˳� */
    PM5CTL0 &= ~LOCKLPM5;
    
	/* ʹ��ʱ�ӼĴ������� */ 
    CSCTL0_H = CSKEY_H;  
    
    CSCTL1 = DCOFSEL_6;                                     // DCO = 8M
    CSCTL2 = SELA__LFXTCLK + SELS__DCOCLK + SELM__DCOCLK;   // ACLK = LFXT ��SMCLK��MCLK=DCO
    CSCTL3 = 0;                                             // ACLK/SMCLK/MCLK ��Ƶ=1
    CSCTL4 = HFXTOFF + VLOOFF + LFXTDRIVE_3;                // �ر�HFXT VLO ����LFXT

	/* ��ֹʱ�ӼĴ������� */ 
    CSCTL0_H = 0;       
}


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

void Initial_Led(void)
{
    P1DIR |= BIT0;              // ����P10����Ϊ���
    P1OUT &= ~BIT0;              // P10���Ϊ0��Ϩ��LED1
    
    P9DIR |= BIT7;              // ����P97����Ϊ���
    P9OUT &= ~BIT7;              // P97���Ϊ0��Ϩ��LED2
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

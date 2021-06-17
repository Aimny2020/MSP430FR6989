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
    /* 关闭看门狗 */
    WDTCTL = WDTPW | WDTHOLD;
    
    Initial_Clock();
    Initial_Uart();
    Initial_Led();
    
    __bis_SR_register(GIE);//使能全局中断
    /* 使配置完成的IO口生效，从LPMx.5退出 */
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
            UCA1IFG &=~ UCRXIFG;                    // 清除中断标志
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
    /* 外部32.768k使能 */ 
    PJSEL0 |= BIT4;    
    PJSEL1 &= ~BIT4;
    
    PJSEL0 |= BIT5;    
    PJSEL1 &= ~BIT5;
    /* 使配置完成的IO口生效，从LPMx.5退出 */
    PM5CTL0 &= ~LOCKLPM5;
    
	/* 使能时钟寄存器设置 */ 
    CSCTL0_H = CSKEY_H;  
    
    CSCTL1 = DCOFSEL_6;                                     // DCO = 8M
    CSCTL2 = SELA__LFXTCLK + SELS__DCOCLK + SELM__DCOCLK;   // ACLK = LFXT ，SMCLK和MCLK=DCO
    CSCTL3 = 0;                                             // ACLK/SMCLK/MCLK 分频=1
    CSCTL4 = HFXTOFF + VLOOFF + LFXTDRIVE_3;                // 关闭HFXT VLO ，打开LFXT

	/* 禁止时钟寄存器设置 */ 
    CSCTL0_H = 0;       
}


void Initial_Uart(void)
{
    /* 串口引脚配置  P3.4/UCA1TXD  P3.5/UCA1RXD */
    P3DIR |= BIT4;
    P3OUT |= BIT4;
    P3SEL0 |= BIT4;    
    P3SEL1 &= ~BIT4;

    P3DIR &= ~BIT5;
    P3SEL0 |= BIT5;    
    P3SEL1 &= ~BIT5;
    /* 使配置完成的IO口生效，从LPMx.5退出 */
    PM5CTL0 &= ~LOCKLPM5;

    /* 串口参数配置 */
    UCA1CTLW0 = UCSWRST;            // ----------------- 使能串口设置
    
    UCA1CTLW0 |= UCSSEL__SMCLK ;     // 时钟=SMCLK 8M, 8 N 1 , LSB
    UCA1BRW_L = 04;                  // 115200bps
    UCA1BRW_H = 0;   
    UCA1MCTLW_L = UCOS16 | UCBRF_5;
    UCA1MCTLW_H = 0x55;
    
    UCA1CTLW0 &= ~UCSWRST;          // ----------------- 禁止串口设置

    UCA1IE &= ~UCTXIE;              // 禁止传输中断
    UCA1IE |= UCRXIE;               // 允许接受中断
    
}

void Initial_Led(void)
{
    P1DIR |= BIT0;              // 设置P10方向为输出
    P1OUT &= ~BIT0;              // P10输出为0，熄灭LED1
    
    P9DIR |= BIT7;              // 设置P97方向为输出
    P9OUT &= ~BIT7;              // P97输出为0，熄灭LED2
}

void putByte(unsigned char Byte)
{
    while (!(UCA1IFG&UCTXIFG)); // 等待标志位
	
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
 * 函 数 名  : putchar
 * 作    者  : Lemon
 * 创建日期  : 2021年5月8日
 * 函数功能  : 重写putchar函数，实现printf函数的使用
 * 输入参数  : int c  
 * 返 回 值  : int
 * 调用关系  : 
 * 其    它  : 
*****************************************************************************/
int putchar(int c)
{
	if(c == '\n')
	{
		while (!(UCA1IFG&UCTXIFG)); // 等待标志位
		UCA1TXBUF = '\r';
	}
	while (!(UCA1IFG&UCTXIFG)); 
	UCA1TXBUF = c;
	return c;
}

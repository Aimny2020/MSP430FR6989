#include "io430.h"
#include "stdio.h"
#include "uart.h"
#include "pwm.h"


#define CPU_CLOCK       8000000
#define Delay_Us(us)    __delay_cycles(CPU_CLOCK / 1000000 * (us))
#define Delay_Ms(ms)    __delay_cycles(CPU_CLOCK / 1000 * (ms))

#define S1_IN       P1IN_bit.P1IN1
#define S2_IN       P1IN_bit.P1IN2

void Initial_Clock(void);
void Initial_LED(void);

int main( void )
{
    /* 关闭看门狗 */
    WDTCTL = WDTPW | WDTHOLD;
    
    Initial_Clock();
    Initial_Uart();
    Initial_LED();
    Initial_PWM();
    
    __bis_SR_register(GIE);//使能全局中断
    /* 使配置完成的IO口生效，从LPMx.5退出 */
    PM5CTL0 &= ~LOCKLPM5; 
    
    while(1)
    {
        if(RxDataFlag){
                
            if(RxDataBuf[0] == 'l' && RxDataBuf[1] == 'e' && RxDataBuf[2] == 'd' && RxDataLen == 4)
            {
              printStr("hello\n");
            }
            RxDataFlag = 0;
            RxDataLen = 0;
        }
        Delay_Ms(10);
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

void Initial_LED(void)
{
//    P1DIR |= BIT0;              // 设置P10方向为输出
//    P1OUT &= ~BIT0;              // P10输出为0，熄灭LED1
    
    P9DIR |= BIT7;              // 设置P97方向为输出
    P9OUT |= BIT7;              // P97输出为0，熄灭LED2
}


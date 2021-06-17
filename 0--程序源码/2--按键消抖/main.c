#include "io430.h"

#define CPU_CLOCK       8000000
#define Delay_Us(us)    __delay_cycles(CPU_CLOCK / 1000000 * (us))
#define Delay_Ms(ms)    __delay_cycles(CPU_CLOCK / 1000 * (ms))

#define S1_IN       P1IN_bit.P1IN1
#define S2_IN       P1IN_bit.P1IN2

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

void Initial_Led(void)
{
    P1DIR |= BIT0;              // 设置P10方向为输出
    P1OUT &= ~BIT0;              // P10输出为0，熄灭LED1
    
    P9DIR |= BIT7;              // 设置P97方向为输出
    P9OUT &= ~BIT7;              // P97输出为0，熄灭LED2
}

void Initial_Button(void)
{
    /* 初始化 S1 按键 ，设置为上拉电阻 */
    P1DIR &= ~BIT1;             // 设置P11方向为输入
    P1REN |= BIT1;              // 使能P11上下拉电阻
    P1OUT |= BIT1;              // 设置P11为上拉电阻
    
    /* 初始化 S2 按键 ，设置为上拉电阻 */
    P1DIR &= ~BIT2;             // 设置P12方向为输入
    P1REN |= BIT2;              // 使能P12上下拉电阻
    P1OUT |= BIT2;              // 设置P12为上拉电阻
}

int main( void )
{
    /* 关闭看门狗 */
    WDTCTL = WDTPW | WDTHOLD;
    
    Initial_Clock();
    
    Initial_Led();

    Initial_Button();

    /* 使配置完成的IO口生效，从LPMx.5退出 */
    PM5CTL0 &= ~LOCKLPM5; 
    
    while(1)
    {
        if(!S1_IN){
            Delay_Ms(10);
            if(!S1_IN){
                P1OUT ^= BIT0; // 电平反转
                while(!S1_IN);
            }
        }
        
    }
}

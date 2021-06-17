#include "io430.h"

int main( void )
{
    /* 关闭看门狗 */
    WDTCTL = WDTPW | WDTHOLD;
    
    P1DIR |= BIT0;              // 设置P10方向为输出
    P1OUT |= BIT0;              // P10输出为1，点亮LED1
    
    P9DIR |= BIT7;              // 设置P97方向为输出
    P9OUT |= BIT7;              // P97输出为1，点亮LED2
    
    P1DIR &= ~BIT1;             // 设置P11方向为输入
    P1REN |= BIT1;              // 使能P11上下拉电阻
    P1OUT |= BIT1;              // 设置P11为上拉电阻
    
    /* 使配置完成的IO口生效，从LPMx.5退出 */
    PM5CTL0 &= ~LOCKLPM5; 
    
    while(1)
    {
        /* 检测按键是否按下，如果按下LED1点亮，松手LED1熄灭*/
        if(P1IN_bit.P1IN1 == 1){
            P1OUT &= ~BIT0;
        }
        else{
            P1OUT |= BIT0;
        }
      
        /* LED1闪烁 */
        P9OUT |= BIT7;
        for(int i = 0; i < 30000; i++);
        P9OUT &= ~BIT7;
        for(int i = 0; i < 30000; i++);
    }
}

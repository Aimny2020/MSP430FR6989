#include "io430.h"
#include "led_button.h"

void Initial_LED(void)
{
    P1DIR |= BIT0;               // 设置P10方向为输出
    P1OUT &= ~BIT0;              // P10输出为0，熄灭LED1
    
    P9DIR |= BIT7;               // 设置P97方向为输出
    P9OUT |= BIT7;               // P97输出为0，熄灭LED2
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

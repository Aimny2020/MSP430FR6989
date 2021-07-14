#include "io430.h"
#include "led_button.h"
#include "uart.h"

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

void Initial_IO_IV(void)
{
    P1DIR &= ~BIT1;//P1.1为输入
    P1OUT |=  BIT1;//GPIO作输入时，PxOUT和PxREN一起配合设置输入上/下拉方式，PxOUT置1时上拉，置0时下拉
    P1REN |=  BIT1;//P1.1为上拉，PxREN使能开关
    
    P1DIR &= ~BIT2;//P1.2为输入
    P1OUT |=  BIT2;//GPIO作输入时，PxOUT和PxREN一起配合设置输入上/下拉方式，PxOUT置1时上拉，置0时下拉
    P1REN |=  BIT2;//P1.1为上拉，PxREN使能开关

    P1IE  |=  BIT1;//打开中断使能
    P1IES |=  BIT1;//设置边沿触发方式为由高到低
    P1IFG &= ~BIT1;//清除P1.1标志位
    
    P1IE  |=  BIT2;//打开中断使能
    P1IES |=  BIT2;//设置边沿触发方式为由高到低
    P1IFG &= ~BIT2;//清除P1.2标志位
}

#pragma vector=PORT1_VECTOR//中断向量地址
__interrupt void Port_1(void)
{
    if(P1IFG_bit.P1IFG1 == 1)
    {
        P1IFG&=~BIT1;//清除标志位
        
        printStr( "button1 press!\n"); //打印发送

    }
    if(P1IFG_bit.P1IFG2 == 1)
    {
        P1IFG&=~BIT2;//清除标志位
        
        printStr( "button2 press!\n"); //打印发送

    }
    
}
#include "io430.h"
#include "led_button.h"
#include "uart.h"
#include "stdio.h"

void Initial_LED(void)
{
    P1DIR |= BIT0;               // 设置P10方向为输出
    P1OUT &= ~BIT0;              // P10输出为0，熄灭LED1
    
    P9DIR |= BIT7;               // 设置P97方向为输出
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

void Key(void)  //10ms 执行一次即可
{
    static unsigned char s_KeyState = 0;
    
    switch(s_KeyState)
    {
        case 0:  // 无按键按下
            if(!S1_IN || !S2_IN)
                s_KeyState = 1;
            break;
        case 1: 
            if(!S1_IN)
            {
                P1OUT ^= BIT0;
            }
            else if(!S2_IN)
            {
                P9OUT ^= BIT7;
            }
            s_KeyState = 2;
            break;
        case 2: // 松手检测
            if(S1_IN && S2_IN)
                s_KeyState = 0;
            break;
    }
}

void Key_Long(void)  //10ms 执行一次即可
{
    static unsigned char s_KeyState = 0;
    static long s_Count = 0;
    
    
    switch(s_KeyState)
    {
        case 0:  // 无按键按下      
            if(!S1_IN)
                s_KeyState = 1;
            break;
        case 1: 
            if(++s_Count == 100) // 长按
            {
                P1OUT ^= BIT0;
                printf("button press long!");
            }
            if(S1_IN)  // 松手检测 
              s_KeyState = 2;
            break;
        case 2: 
            if(s_Count < 100) // 短按
            {
                P9OUT ^= BIT7;
                printf("button press short!");
            }
            s_Count = 0;
            s_KeyState = 0;
            break;
    }
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
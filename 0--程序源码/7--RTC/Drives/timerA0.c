#include "timerA0.h"
#include "io430.h"
#include "uart.h"

#define ACLK_Frequency_HZ   32768
#define A0_TICK_RATE_HZ         2          //2Hz  ==  0.5s
#define A1_TICK_RATE_HZ         1          //1Hz  ==  1s

void Initial_Timer0(void)
{
    TA0CTL = TASSEL_1;                           // 使用辅助时钟
    TA0CTL |= TACLR;                             // 清除配置运行
    TA0CCR0 = ACLK_Frequency_HZ / A0_TICK_RATE_HZ;  //根据想要的嘀嗒速率设置匹配值
    TA0CTL |= MC_1;                              // 向上计数模式
    TA0CCTL0 = CCIE;                             // 使用捕获中断
}

void Initial_Timer1(void)
{
    TA1CCR0 = ACLK_Frequency_HZ / A1_TICK_RATE_HZ;   //根据想要的嘀嗒速率设置匹配值
    TA1CTL |= TACLR;                                // 清除配置运行
    TA1CTL = TASSEL_1 + MC_1 + TAIE;                // 使用辅助时钟   向上计数模式    中断启用
}


#pragma vector = TIMER1_A1_VECTOR
__interrupt void ISR_USCI_TimerA1(void)
{
    TA1CTL &= ~TAIFG;    // 清除中断标志位
    P9OUT ^= BIT7;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void ISR_USCI_TimerA0(void)
{
    P1OUT ^= BIT0;
}

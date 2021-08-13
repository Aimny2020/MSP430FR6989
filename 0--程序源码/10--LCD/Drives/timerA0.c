#include "timerA0.h"
#include "io430.h"
#include "uart.h"

#define ACLK_Frequency_HZ   32768
#define A0_TICK_RATE_HZ         2          //2Hz  ==  0.5s
#define A1_TICK_RATE_HZ         1          //1Hz  ==  1s

void Initial_Timer0(void)
{
    TA0CTL = TASSEL_1;                           // ʹ�ø���ʱ��
    TA0CTL |= TACLR;                             // �����������
    TA0CCR0 = ACLK_Frequency_HZ / A0_TICK_RATE_HZ;  //������Ҫ�������������ƥ��ֵ
    TA0CTL |= MC_1;                              // ���ϼ���ģʽ
    TA0CCTL0 = CCIE;                             // ʹ�ò����ж�
}

void Initial_Timer1(void)
{
    TA1CCR0 = ACLK_Frequency_HZ / A1_TICK_RATE_HZ;   //������Ҫ�������������ƥ��ֵ
    TA1CTL |= TACLR;                                // �����������
    TA1CTL = TASSEL_1 + MC_1 + TAIE;                // ʹ�ø���ʱ��   ���ϼ���ģʽ    �ж�����
}


#pragma vector = TIMER1_A1_VECTOR
__interrupt void ISR_USCI_TimerA1(void)
{
    TA1CTL &= ~TAIFG;    // ����жϱ�־λ
    P9OUT ^= BIT7;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void ISR_USCI_TimerA0(void)
{
    P1OUT ^= BIT0;
}

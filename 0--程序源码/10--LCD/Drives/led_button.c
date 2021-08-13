#include "io430.h"
#include "led_button.h"

void Initial_LED(void)
{
    P1DIR |= BIT0;               // ����P10����Ϊ���
    P1OUT &= ~BIT0;              // P10���Ϊ0��Ϩ��LED1
    
    P9DIR |= BIT7;               // ����P97����Ϊ���
    P9OUT |= BIT7;               // P97���Ϊ0��Ϩ��LED2
}

void Initial_Button(void)
{
    /* ��ʼ�� S1 ���� ������Ϊ�������� */
    P1DIR &= ~BIT1;             // ����P11����Ϊ����
    P1REN |= BIT1;              // ʹ��P11����������
    P1OUT |= BIT1;              // ����P11Ϊ��������
    
    /* ��ʼ�� S2 ���� ������Ϊ�������� */
    P1DIR &= ~BIT2;             // ����P12����Ϊ����
    P1REN |= BIT2;              // ʹ��P12����������
    P1OUT |= BIT2;              // ����P12Ϊ��������
}

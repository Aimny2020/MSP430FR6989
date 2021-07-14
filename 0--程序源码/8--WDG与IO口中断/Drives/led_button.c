#include "io430.h"
#include "led_button.h"
#include "uart.h"

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

void Initial_IO_IV(void)
{
    P1DIR &= ~BIT1;//P1.1Ϊ����
    P1OUT |=  BIT1;//GPIO������ʱ��PxOUT��PxRENһ���������������/������ʽ��PxOUT��1ʱ��������0ʱ����
    P1REN |=  BIT1;//P1.1Ϊ������PxRENʹ�ܿ���
    
    P1DIR &= ~BIT2;//P1.2Ϊ����
    P1OUT |=  BIT2;//GPIO������ʱ��PxOUT��PxRENһ���������������/������ʽ��PxOUT��1ʱ��������0ʱ����
    P1REN |=  BIT2;//P1.1Ϊ������PxRENʹ�ܿ���

    P1IE  |=  BIT1;//���ж�ʹ��
    P1IES |=  BIT1;//���ñ��ش�����ʽΪ�ɸߵ���
    P1IFG &= ~BIT1;//���P1.1��־λ
    
    P1IE  |=  BIT2;//���ж�ʹ��
    P1IES |=  BIT2;//���ñ��ش�����ʽΪ�ɸߵ���
    P1IFG &= ~BIT2;//���P1.2��־λ
}

#pragma vector=PORT1_VECTOR//�ж�������ַ
__interrupt void Port_1(void)
{
    if(P1IFG_bit.P1IFG1 == 1)
    {
        P1IFG&=~BIT1;//�����־λ
        
        printStr( "button1 press!\n"); //��ӡ����

    }
    if(P1IFG_bit.P1IFG2 == 1)
    {
        P1IFG&=~BIT2;//�����־λ
        
        printStr( "button2 press!\n"); //��ӡ����

    }
    
}
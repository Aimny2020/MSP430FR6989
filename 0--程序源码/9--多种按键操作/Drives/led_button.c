#include "io430.h"
#include "led_button.h"
#include "uart.h"
#include "stdio.h"

void Initial_LED(void)
{
    P1DIR |= BIT0;               // ����P10����Ϊ���
    P1OUT &= ~BIT0;              // P10���Ϊ0��Ϩ��LED1
    
    P9DIR |= BIT7;               // ����P97����Ϊ���
    P9OUT &= ~BIT7;              // P97���Ϊ0��Ϩ��LED2
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

void Key(void)  //10ms ִ��һ�μ���
{
    static unsigned char s_KeyState = 0;
    
    switch(s_KeyState)
    {
        case 0:  // �ް�������
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
        case 2: // ���ּ��
            if(S1_IN && S2_IN)
                s_KeyState = 0;
            break;
    }
}

void Key_Long(void)  //10ms ִ��һ�μ���
{
    static unsigned char s_KeyState = 0;
    static long s_Count = 0;
    
    
    switch(s_KeyState)
    {
        case 0:  // �ް�������      
            if(!S1_IN)
                s_KeyState = 1;
            break;
        case 1: 
            if(++s_Count == 100) // ����
            {
                P1OUT ^= BIT0;
                printf("button press long!");
            }
            if(S1_IN)  // ���ּ�� 
              s_KeyState = 2;
            break;
        case 2: 
            if(s_Count < 100) // �̰�
            {
                P9OUT ^= BIT7;
                printf("button press short!");
            }
            s_Count = 0;
            s_KeyState = 0;
            break;
    }
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
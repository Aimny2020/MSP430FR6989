#include "io430.h"

int main( void )
{
    /* �رտ��Ź� */
    WDTCTL = WDTPW | WDTHOLD;
    
    P1DIR |= BIT0;              // ����P10����Ϊ���
    P1OUT |= BIT0;              // P10���Ϊ1������LED1
    
    P9DIR |= BIT7;              // ����P97����Ϊ���
    P9OUT |= BIT7;              // P97���Ϊ1������LED2
    
    P1DIR &= ~BIT1;             // ����P11����Ϊ����
    P1REN |= BIT1;              // ʹ��P11����������
    P1OUT |= BIT1;              // ����P11Ϊ��������
    
    /* ʹ������ɵ�IO����Ч����LPMx.5�˳� */
    PM5CTL0 &= ~LOCKLPM5; 
    
    while(1)
    {
        /* ��ⰴ���Ƿ��£��������LED1����������LED1Ϩ��*/
        if(P1IN_bit.P1IN1 == 1){
            P1OUT &= ~BIT0;
        }
        else{
            P1OUT |= BIT0;
        }
      
        /* LED1��˸ */
        P9OUT |= BIT7;
        for(int i = 0; i < 30000; i++);
        P9OUT &= ~BIT7;
        for(int i = 0; i < 30000; i++);
    }
}

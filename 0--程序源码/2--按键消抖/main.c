#include "io430.h"

#define CPU_CLOCK       8000000
#define Delay_Us(us)    __delay_cycles(CPU_CLOCK / 1000000 * (us))
#define Delay_Ms(ms)    __delay_cycles(CPU_CLOCK / 1000 * (ms))

#define S1_IN       P1IN_bit.P1IN1
#define S2_IN       P1IN_bit.P1IN2

void Initial_Clock(void)
{
    /* �ⲿ32.768kʹ�� */ 
    PJSEL0 |= BIT4;    
    PJSEL1 &= ~BIT4;
    
    PJSEL0 |= BIT5;    
    PJSEL1 &= ~BIT5;
    /* ʹ������ɵ�IO����Ч����LPMx.5�˳� */
    PM5CTL0 &= ~LOCKLPM5;
    
	/* ʹ��ʱ�ӼĴ������� */ 
    CSCTL0_H = CSKEY_H;  
    
    CSCTL1 = DCOFSEL_6;                                     // DCO = 8M
    CSCTL2 = SELA__LFXTCLK + SELS__DCOCLK + SELM__DCOCLK;   // ACLK = LFXT ��SMCLK��MCLK=DCO
    CSCTL3 = 0;                                             // ACLK/SMCLK/MCLK ��Ƶ=1
    CSCTL4 = HFXTOFF + VLOOFF + LFXTDRIVE_3;                // �ر�HFXT VLO ����LFXT

	/* ��ֹʱ�ӼĴ������� */ 
    CSCTL0_H = 0;       
}

void Initial_Led(void)
{
    P1DIR |= BIT0;              // ����P10����Ϊ���
    P1OUT &= ~BIT0;              // P10���Ϊ0��Ϩ��LED1
    
    P9DIR |= BIT7;              // ����P97����Ϊ���
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

int main( void )
{
    /* �رտ��Ź� */
    WDTCTL = WDTPW | WDTHOLD;
    
    Initial_Clock();
    
    Initial_Led();

    Initial_Button();

    /* ʹ������ɵ�IO����Ч����LPMx.5�˳� */
    PM5CTL0 &= ~LOCKLPM5; 
    
    while(1)
    {
        if(!S1_IN){
            Delay_Ms(10);
            if(!S1_IN){
                P1OUT ^= BIT0; // ��ƽ��ת
                while(!S1_IN);
            }
        }
        
    }
}

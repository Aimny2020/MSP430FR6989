#include "io430.h"
#include "rtc.h"

void Initial_Rtc(void)
{
    RTCCTL0_H = RTCKEY_H;               // ----------------- ����RTC
    RTCCTL1 |= RTCHOLD;                // �ر�RTC��ʱ
    
    RTCCTL1 |= (RTCBCD + RTCMODE);     // BCDģʽ
    RTCCTL0_L = 0;
    RTCOCAL = 0;                        // ������ʱ��ƫ��У׼
    RTCTCMP = 0;                        // �������¶Ȳ��� 
    
    RTCYEAR = 0x2021;                    // 2021 ��
    RTCMON  = 0x07;                      //    7 ��
    RTCDAY  = 0x06;                      //    6 ��
    RTCDOW  = 0x02;                      //    2 ����
    RTCHOUR = 0x23;                      //    23 ��
    RTCMIN  = 0x59;                      //    59 ��
    RTCSEC  = 0x50;                      //    50 ��

    RTCAMIN = 0;                         // �رվ���
    RTCAHOUR = 0;
    RTCADAY = 0;
    RTCADOW = 0;

    /* Real-Time Prescale Timer 0 Counter ʹ��ACLK  */
    RTCPS0CTL = 0;
    /* ʹ��Prescale timer 1 interrupt���жϼ�� = 128Hz/128��Ƶ=1s  */
    RTCPS1CTL = RT1IP2 + RT1IP1 + RT1PSIE;

    RTCCTL13 &= ~RTCHOLD;       // ��RTC��ʱ
    RTCCTL0_H = 0;              // ----------------- ����RTC
}

#pragma vector = RTC_VECTOR
__interrupt void ISR_RTC(void)
{
    switch (__even_in_range(RTCIV, RTC_RT1PSIFG))
    {
        case RTCIV_NONE:
        case RTCIV_RTCRDYIFG:
        case RTCIV_RTCOFIFG:
        case RTCIV_RTCTEVIFG:
        case RTCIV_RTCAIFG:
        case RTCIV_RT0PSIFG:
        {
            break;
        }
        case RTCIV_RT1PSIFG:  // ���ж�
        {
            
            break;
        }
        default:
            break;
    }
}





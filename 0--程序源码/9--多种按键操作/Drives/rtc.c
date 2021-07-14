#include "io430.h"
#include "rtc.h"

void Initial_Rtc(void)
{
    RTCCTL0_H = RTCKEY_H;               // ----------------- 解锁RTC
    RTCCTL1 |= RTCHOLD;                // 关闭RTC计时
    
    RTCCTL1 |= (RTCBCD + RTCMODE);     // BCD模式
    RTCCTL0_L = 0;
    RTCOCAL = 0;                        // 不设置时钟偏移校准
    RTCTCMP = 0;                        // 不设置温度补偿 
    
    RTCYEAR = 0x2021;                    // 2021 年
    RTCMON  = 0x07;                      //    7 月
    RTCDAY  = 0x06;                      //    6 日
    RTCDOW  = 0x02;                      //    2 星期
    RTCHOUR = 0x23;                      //    23 点
    RTCMIN  = 0x59;                      //    59 分
    RTCSEC  = 0x50;                      //    50 秒

    RTCAMIN = 0;                         // 关闭警告
    RTCAHOUR = 0;
    RTCADAY = 0;
    RTCADOW = 0;

    /* Real-Time Prescale Timer 0 Counter 使用ACLK  */
    RTCPS0CTL = 0;
    /* 使能Prescale timer 1 interrupt，中断间隔 = 128Hz/128分频=1s  */
    RTCPS1CTL = RT1IP2 + RT1IP1 + RT1PSIE;

    RTCCTL13 &= ~RTCHOLD;       // 打开RTC计时
    RTCCTL0_H = 0;              // ----------------- 锁定RTC
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
        case RTCIV_RT1PSIFG:  // 秒中断
        {
            
            break;
        }
        default:
            break;
    }
}





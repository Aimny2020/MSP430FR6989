#include "pwm.h"
#include "io430.h"

void Initial_PWM()
{
    P1SEL0 |= BIT0;    
    P1SEL1 &= ~BIT0;
    P1DIR |= BIT0;
    
    /* 使配置完成的IO口生效，从LPMx.5退出 */
    PM5CTL0 &= ~LOCKLPM5;
    
    TA0CTL = TASSEL_2 + MC_1 + ID_0;
    TA0CCTL1 = OUTMOD_7;
    
    TA0CCR0 = 800;   //10K
    TA0CCR1 = 80;    //10%占空比    //0.33v
}


#include "io430.h"
#include "stdio.h"
#include "uart.h"
#include "pwm.h"
#include "rtc.h"
#include "led_button.h"
#include "initial.h"

void Initial_All(void)
{
    /* 关闭看门狗 */
    WDTCTL = WDTPW | WDTHOLD;
    /* 使配置完成的IO口生效，从LPMx.5退出 */
    PM5CTL0 &= ~LOCKLPM5; 
    
    Initial_Clock();
    Initial_Uart();
    printStr("\n");
    printStr("       _                                     \n");                            
    printStr("      | |    ___ _ __ ___   ___  _ __        \n");
    printStr("      | |   / _ \\ '_ ` _ \\ / _ \\| '_ \\       \n");
    printStr("      | |__|  __/ | | | | | (_) | | | |      \n");
    printStr("      |_____\\___|_| |_| |_|\\___/|_| |_|      \n");
    printStr("                                        sdu  \n"); 
    printStr("\n");
    printStr("Time:" __DATE__ " " __TIME__ "\r\n");
    
    
    Initial_Rtc();
    Initial_LED();
    
    __bis_SR_register(GIE);//使能全局中断

}

void Initial_Clock(void)
{
    /* 外部32.768k使能 */ 
    PJSEL0 |= BIT4;    
    PJSEL1 &= ~BIT4;
    
    PJSEL0 |= BIT5;    
    PJSEL1 &= ~BIT5;
    /* 使配置完成的IO口生效，从LPMx.5退出 */
    PM5CTL0 &= ~LOCKLPM5;
    
	/* 使能时钟寄存器设置 */ 
    CSCTL0_H = CSKEY_H;  
    
    CSCTL1 = DCOFSEL_6;                                     // DCO = 8M
    CSCTL2 = SELA__LFXTCLK + SELS__DCOCLK + SELM__DCOCLK;   // ACLK = LFXT ，SMCLK和MCLK=DCO
    CSCTL3 = 0;                                             // ACLK/SMCLK/MCLK 分频=1
    CSCTL4 = HFXTOFF + VLOOFF + LFXTDRIVE_3;                // 关闭HFXT VLO ，打开LFXT

	/* 禁止时钟寄存器设置 */ 
    CSCTL0_H = 0;       
}
#include "io430.h"
#include "stdio.h"
#include "uart.h"
#include "pwm.h"
#include "rtc.h"
#include "led_button.h"
#include "initial.h"
#include "lcd.h"

void Initial_All(void)
{
    /* �رտ��Ź� */
    WDTCTL = WDTPW | WDTHOLD;
    /* ʹ������ɵ�IO����Ч����LPMx.5�˳� */
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
    
    Lcd_Initial();
    
    

//    Lcd_Display(3,3);
//    Lcd_Display(4,4);
//    Lcd_Display(5,5);
    
    __bis_SR_register(GIE);//ʹ��ȫ���ж�

}

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
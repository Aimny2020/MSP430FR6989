#include "io430.h"
#include "stdio.h"
#include "uart.h"

#define CPU_CLOCK       8000000
#define Delay_Us(us)    __delay_cycles(CPU_CLOCK / 1000000 * (us))
#define Delay_Ms(ms)    __delay_cycles(CPU_CLOCK / 1000 * (ms))

#define S1_IN       P1IN_bit.P1IN1
#define S2_IN       P1IN_bit.P1IN2

void Initial_Clock(void);


char Cmd[] = {"ledadsasasdasdasdfsddasfda"};
int Count = 0;

int main( void )
{
    /* 关闭看门狗 */
    WDTCTL = WDTPW | WDTHOLD;
    
    Initial_Clock();
    Initial_Uart();
    
    __bis_SR_register(GIE);//使能全局中断
    /* 使配置完成的IO口生效，从LPMx.5退出 */
    PM5CTL0 &= ~LOCKLPM5; 
    
    while(1)
    {
        if(RxDataFlag){
                
            for(int i = 0; i < (RxDataLen-1); i++)
            {
                if(RxDataBuf[i] == Cmd[i])
                {
                    Count++;
                }
            }
            if(Count == (RxDataLen-1))
            {
                printf("hello\n");
            }
           
            Count = 0;
            RxDataFlag = 0;
            RxDataLen = 0;
        }
        Delay_Ms(10);
    }
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




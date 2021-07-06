#include "io430.h"
#include "stdio.h"
#include "uart.h"
#include "pwm.h"
#include "rtc.h"
#include "led_button.h"
#include "initial.h"

#define CPU_CLOCK       8000000
#define Delay_Us(us)    __delay_cycles(CPU_CLOCK / 1000000 * (us))
#define Delay_Ms(ms)    __delay_cycles(CPU_CLOCK / 1000 * (ms))

int main( void )
{
    Initial_All();
    while(1)
    {
        printf("System Time: %x-%x-%x\n",RTCHOUR,RTCMIN,RTCSEC); 
        Delay_Ms(1000);
    }
}




#include "io430.h"
#include "stdio.h"
#include "uart.h"
#include "pwm.h"
#include "rtc.h"
#include "led_button.h"
#include "initial.h"
#include "lcd.h"
#include "string.h"

#define CPU_CLOCK       8000000
#define Delay_Us(us)    __delay_cycles(CPU_CLOCK / 1000000 * (us))
#define Delay_Ms(ms)    __delay_cycles(CPU_CLOCK / 1000 * (ms))

#define ADDR_SAVE   0x1800      //Info 1800 - 19ff
#define KEY         0x1234567

typedef struct FRAM
{
    unsigned long key;
    unsigned char count;
}FRAM_SAVE;


FRAM_SAVE * const Save = (FRAM_SAVE *)ADDR_SAVE;

//int * i = (int * )ADDR_SAVE;    //Info 1800 - 19ff


int main( void )
{ 
    //*i = 0;
  
    if(Save->key != KEY)
    {   
        memset(Save,0,sizeof(FRAM_SAVE));
        /* ... */
        Save->key = KEY;
    }
    Initial_All();
    while(1)
    {
//        *i = *i + 1;
//        Lcd_Display_Number(1,*i / 100);
//        Lcd_Display_Number(2,*i / 10  % 10);
//        Lcd_Display_Number(3,*i % 10);
//        Delay_Ms(1000);
      
        Save->count++;
        Lcd_Display_Number(1,Save->count / 100);
        Lcd_Display_Number(2,Save->count / 10  % 10);
        Lcd_Display_Number(3,Save->count % 10);
        Delay_Ms(1000);
    }
}




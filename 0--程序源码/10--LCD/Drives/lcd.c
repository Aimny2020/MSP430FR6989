#include "io430.h"
#include "lcd.h"

const char digit[10][2] =
{
    {0xFC, 0x28},  /* "0" LCD segments a+b+c+d+e+f+k+q */
    {0x60, 0x20},  /* "1" */
    {0xDB, 0x00},  /* "2" */
    {0xF3, 0x00},  /* "3" */
    {0x67, 0x00},  /* "4" */
    {0xB7, 0x00},  /* "5" */
    {0xBF, 0x00},  /* "6" */
    {0xE4, 0x00},  /* "7" */
    {0xFF, 0x00},  /* "8" */
    {0xF7, 0x00}   /* "9" */
};

// LCD memory map for uppercase letters
const char alphabetBig[26][2] =
{
    {0xEF, 0x00},  /* "A" LCD segments a+b+c+e+f+g+m */
    {0xF1, 0x50},  /* "B" */
    {0x9C, 0x00},  /* "C" */
    {0xF0, 0x50},  /* "D" */
    {0x9F, 0x00},  /* "E" */
    {0x8F, 0x00},  /* "F" */
    {0xBD, 0x00},  /* "G" */
    {0x6F, 0x00},  /* "H" */
    {0x90, 0x50},  /* "I" */
    {0x78, 0x00},  /* "J" */
    {0x0E, 0x22},  /* "K" */
    {0x1C, 0x00},  /* "L" */
    {0x6C, 0xA0},  /* "M" */
    {0x6C, 0x82},  /* "N" */
    {0xFC, 0x00},  /* "O" */
    {0xCF, 0x00},  /* "P" */
    {0xFC, 0x02},  /* "Q" */
    {0xCF, 0x02},  /* "R" */
    {0xB7, 0x00},  /* "S" */
    {0x80, 0x50},  /* "T" */
    {0x7C, 0x00},  /* "U" */
    {0x0C, 0x28},  /* "V" */
    {0x6C, 0x0A},  /* "W" */
    {0x00, 0xAA},  /* "X" */
    {0x00, 0xB0},  /* "Y" */
    {0x90, 0x28}   /* "Z" */
};

/*��ʼ��*/
void Lcd_Initial(void)
{
   // Initialize LCD segments ;
   LCDCPCTL0 = LCDS4 + LCDS6 + LCDS7 + LCDS8 + LCDS9 + LCDS10 + LCDS11 + LCDS12 + LCDS13 + LCDS14 + LCDS15;  //T�˿ڿ��ƼĴ��� 4��15
   LCDCPCTL1 = LCDS16 + LCDS17 + LCDS18 + LCDS19 + LCDS20 + LCDS21 + LCDS27 + LCDS28 + LCDS29 + LCDS30 + LCDS31;      // 16-21,27��31
   LCDCPCTL2 = LCDS38 + LCDS39 + LCDS36 + LCDS37 + LCDS35;//35��39
   
   //flcd Ƶ�ʵ�����ѡ��29��Ƶ�� ��·����4���͹���ģʽ
   LCDCCTL0 = LCDDIV_29 + LCDPRE_3 + LCD4MUX + LCDLP;
   //���LCD�ڴ�
   LCDCMEMCTL = LCDCLRM;  
   //��lcd
   LCDCCTL0 |= LCDON;

}

/*������ʾ*/
void Lcd_Display_Number(unsigned short LcdPort,unsigned short LcdNum)
{
    switch(LcdPort)
    {
		//��һλ�����
        case 1:
		      {  
                    LCDM10 = digit[LcdNum][0];
                    LCDM11 = digit[LcdNum][1];
                    break;
        	  }
        //�ڶ�λ�����
        case 2:
              {     LCDM6 = digit[LcdNum][0];
                    LCDM7 = digit[LcdNum][1];
                    break;
					
        	  }
        //����λ�����
        case 3:
		      { 
                    LCDM4 = digit[LcdNum][0];
                    LCDM5 = digit[LcdNum][1];
					break;
                    
        	  }
         //����λ�����
        case 4:
		      {  
					LCDM19 = digit[LcdNum][0];
                    LCDM20 = digit[LcdNum][1];
					break;
        	  }
          //����λ�����
        case 5:
		      {  
					LCDM15 = digit[LcdNum][0];
                    LCDM16 = digit[LcdNum][1];
					break;
        	  } 
          //����λ�����
        case 6:
		      {  
					LCDM8 = digit[LcdNum][0];
                    LCDM9 = digit[LcdNum][1];
					break;
        	  }    
		default:
			break;
			
    }
}
/*�ַ���ʾ*/
void Lcd_Display_String(unsigned short LcdPort,unsigned short LcdNum)
{
    switch(LcdPort)
    {
		//��һλ�����
        case 1:
		      {  
					LCDM10 = alphabetBig[LcdNum][0];
                    LCDM11 = alphabetBig[LcdNum][1];
					break;
        	  }
         //�ڶ�λ�����
        case 2:
              {     LCDM6 = alphabetBig[LcdNum][0];
                    LCDM7 = alphabetBig[LcdNum][1];
                    break;
        	  }
        //����λ�����
        case 3:
		      { 
                    LCDM4 = alphabetBig[LcdNum][0];
                    LCDM5 = alphabetBig[LcdNum][1];
					break;
                    
        	  }
         //����λ�����
        case 4:
		      {  
					LCDM19 = alphabetBig[LcdNum][0];
                    LCDM20 = alphabetBig[LcdNum][1];
					break;
        	  }
          //����λ�����
        case 5:
		      {  
					LCDM15 = alphabetBig[LcdNum][0];
                    LCDM16 = alphabetBig[LcdNum][1];
					break;
        	  } 
          //����λ�����
        case 6:
		      {  
					LCDM8 = alphabetBig[LcdNum][0];
                    LCDM9 = alphabetBig[LcdNum][1];
					break;
        	  }    
		default:
			break;
    }
}

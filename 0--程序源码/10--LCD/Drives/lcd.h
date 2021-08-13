#ifndef __LCD_H__
#define __LCD_H__

void Lcd_Initial(void);
void Lcd_Display_Number(unsigned short LcdPort,unsigned short LcdNum);
void Lcd_Display_String(unsigned short LcdPort,unsigned short LcdNum);

#endif 
#ifndef __LED_BUTTON_H__
#define __LED_BUTTON_H__

#define S1_IN       P1IN_bit.P1IN1
#define S2_IN       P1IN_bit.P1IN2

void Initial_LED(void);
void Initial_Button(void);
void Initial_IO_IV(void);
void Key(void);
void Key_Long(void);

#endif 
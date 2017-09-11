
#ifndef _LCD_4BIT_H

#define _LCD_4BIT_H
#include <avr/io.h>

#include "StdTypes.h"

#define HIGH_NIBBLE(hVar,var) hVar= (var & 0xf0)  // hVar will hold value of high nibble of var
#define LOW_NIBBLE(lVar,var) lVar= (var<<4) // lVar will hold the value of low nibble of var
#define CLR_BIT(var, bit) var &= (~(1<<bit))
#define SET_BIT(var, bit) var |= (1<<bit)
#define TOG_BIT(var, bit) var ^= (1<<bit)

#define PORT_NAME PORTA
#define PORT_DIRECTION DDRA

void lcd_displayChar(unsigned char data);
void lcd_init(void);
void lcd_gotoxy(unsigned char x , unsigned char y );
void lcd_clrScreen(void);
void lcd_dispString(char * ptr);
void lcd_disp_string_xy(char * ptr , int y , int x);
void Welcome_Lcd(void);


#endif  


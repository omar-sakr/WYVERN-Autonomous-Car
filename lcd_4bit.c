/**
* @file LCD_Driver_4bit_MODE.c
* @brief 4 bit mode lcd driver for ATMEGA16 or 32 .
* @author Islam Mohamed.
*/

#include "lcd_4bit.h"
#include <avr/io.h>
#include <util/delay.h>

/////////////////////////////////////////////////////////////////////
//	lcd enable triggering function to make lcd aware about command or
//   data changes.
////////////////////////////////////////////////////////////////////
static void lcd_sendCommand(unsigned char cmd);
void enableTrigger(void)
{

	CLR_BIT(PORT_NAME,2);
	
	_delay_us(500);

	SET_BIT(PORT_NAME,2);
	_delay_us(1500);


}
///////////////////////////////////////////////////////////////////////////////////////
// LCD initialization API : set portB from pinB.4 to pinB.7 as o/p for data and commands
//							 and pinB.0 to pinB.2 o/p for control pins
//////////////////////////////////////////////////////////////////////////////////////
void lcd_init(void)
{

	PORT_DIRECTION=0xff; // init port B as O/P port
	PORT_NAME=0x04; // activate LCD enable

	lcd_sendCommand(0x33); // 4-bit mode
	lcd_sendCommand (0x32);
	lcd_sendCommand (0x28);



	lcd_sendCommand(0x0c); // turn on lcd

	
}


static void lcd_sendCommand(unsigned char cmd)
{

	unsigned char high_nibble , low_nibble ;
	
	HIGH_NIBBLE(high_nibble,cmd);
	LOW_NIBBLE(low_nibble,cmd);

	CLR_BIT(PORT_NAME,0); // to enable command mode
	CLR_BIT(PORT_NAME,1); // write signal to lcd

	PORT_NAME &=0x0f;
	PORT_NAME |=high_nibble;// to send high nibble command
	enableTrigger(); // triggre lcd enable

	PORT_NAME &=0x0f;
	PORT_NAME |=low_nibble; // to send low nibble command
	enableTrigger();

}

void lcd_displayChar (unsigned char data)
{

	unsigned char high_nibble , low_nibble ;

	SET_BIT(PORT_NAME,0); //  enable data mode
	CLR_BIT(PORT_NAME,1); // activate lcd write

	HIGH_NIBBLE(high_nibble,data); // get high nibble data
	LOW_NIBBLE(low_nibble,data); // get low nibble data
	
	PORT_NAME &= 0x0f;
	PORT_NAME |=high_nibble;// to send high nibble data
	enableTrigger(); // triggre lcd enable
	
	PORT_NAME &=0x0f;
	PORT_NAME |=low_nibble; // to send low nibble data
	enableTrigger();
	

}


void lcd_gotoxy(unsigned char y , unsigned char x )
{
	unsigned char position = 0x80;
	
	switch(y)
	{
		case 0:

		position=position+x;
		
		break;

		case 1:

		position=0xc0;
		position=position+x;

		break;

		case 2:

		position=position+x;

		break;

		case 3:
		position=position+x;
		break;
		
		
	}
	
	lcd_sendCommand(position);


}


void lcd_clrScreen(void)
{

	lcd_sendCommand(0x01);


}


void lcd_dispString(char * ptr)
{

	while(* ptr!= '\0')
	{
		lcd_displayChar(* ptr);
		ptr++;
		
	}



}

void lcd_disp_string_xy(char * ptr , int y , int x)
{

	lcd_gotoxy(y,x);
	lcd_dispString(ptr);

}




void Welcome_Lcd()
{
	char str[] = "Test!";
	int i,Max_go,S_size;
	
	S_size=sizeof(str)-1;
	Max_go=16-S_size;
	
	for(i=0;i<Max_go;i++)
	{
		lcd_disp_string_xy(str,0,i);
		_delay_ms(300);
		if (i<Max_go-1)
		{
			lcd_gotoxy(0,i);
		}
		lcd_displayChar(' ');

	}
	for(i=Max_go-1;i>=0;i--)
	{
		lcd_disp_string_xy(str,0,i);
		_delay_ms(300);
		if(i==0)
		lcd_gotoxy(0,i+(S_size));
		else
		lcd_gotoxy(0,i+(S_size-1));
		lcd_displayChar(' ');
	}
}


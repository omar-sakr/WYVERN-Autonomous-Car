/*
 * Motor_Timer0.c
 *
 * Created: 2/26/2017 3:03:41 PM
 *  Author: omar
 */ 

#include "Motor_Timer0.h"

void Motor_Timer0_Init()
{
	DIO_InitPortDirection(PB,OUTPUT,0x10);
	DIO_InitPortDirection(DIRECTION_PORT,OUTPUT,DIRECTION_PIN);
	
	TCCR0=0x00;
	//Fast PWM, non-inverting mode, clk/8 (From prescaler)
	TCCR0|=(1<<WGM00) |(1<<WGM01) |(1<<COM01) |(1<<CS01);	
	
}

void Motor_Speed_Dir(u8 speed,u8 Direction)
{
	DIO_WritePort(DIRECTION_PORT,Direction,DIRECTION_PIN);
	OCR0=speed;
	
}
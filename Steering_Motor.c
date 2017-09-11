/*
 * Steering_Motor.c
 *
 * Created: 2/28/2017 5:02:49 PM
 *  Author: omar
 */ 

#include "Steering_Motor.h"
#include "Lights_Indicators.h"

	static u8 Flag=CLEAR_FLAG;
	volatile u16 count=0;
	u8 Right_flag=CLEAR_FLAG;
	u8 Left_flag=CLEAR_FLAG;

void Steering_Motor_Init()
{
	DIO_InitPortDirection(F_M_PORT,OUTPUT,F_M_DIR_PIN1);
	DIO_InitPortDirection(F_M_PORT,OUTPUT,F_M_DIR_PIN2);
	DIO_InitPortDirection(F_M_PORT,OUTPUT,F_M_PIN);

	//Timer2 Normal mode & prescaled /1024 & overflow interrupt enabled
	TCCR2=0x00;
	TIMSK=0x00;
	TCNT2=0x00;
	TIMSK|=(1<<TOIE2);
}

void Front_Motor_Steering(u8 Dir)
{

	if(!Flag)
	{
		if (Dir==RIGHT)
		{
			Flag=RIGHT;

			DIO_WritePort(F_M_PORT,HIGH,F_M_DIR_PIN1); //Direction
			DIO_WritePort(F_M_PORT,ZERO,F_M_DIR_PIN2);
			
			DIO_WritePort(F_M_PORT,HIGH,F_M_PIN);
			Right_flag=SET_FLAG;
			Left_flag=CLEAR_FLAG;
			DIO_WritePort(INDICATORS_PORT,ZERO,LEFT_INDICATOR);
			count=0;
			TCNT2=0;
			TCCR2|=(1<<CS22) | (1<<CS20);

		}
		else if(Dir==LEFT)
		{
			Flag=LEFT;

			DIO_WritePort(F_M_PORT,ZERO,F_M_DIR_PIN1); //Direction
			DIO_WritePort(F_M_PORT,HIGH,F_M_DIR_PIN2);
			
			DIO_WritePort(F_M_PORT,HIGH,F_M_PIN);
			Left_flag=SET_FLAG;
			Right_flag=CLEAR_FLAG;
			DIO_WritePort(INDICATORS_PORT,ZERO,RIGHT_INDICATOR);
			count=0;
			TCNT2=0;
			TCCR2|=(1<<CS22) | (1<<CS20);

		}
		else if (Dir==NEUTRAL)
		{
			Flag=NEUTRAL;
			
			PORTD^=(1<<5);
			PORTD^=(1<<6);
			DIO_WritePort(F_M_PORT,HIGH,F_M_PIN);
			count=0;
			TCNT2=0;
			TCCR2|=(1<<CS22) | (1<<CS20);
			Right_flag=CLEAR_FLAG;
			Left_flag=CLEAR_FLAG;
			DIO_WritePort(INDICATORS_PORT,ZERO,RIGHT_INDICATOR);
			DIO_WritePort(INDICATORS_PORT,ZERO,LEFT_INDICATOR);
			
		}
	}
	else 
	{
		
	}
	
	
}



ISR(TIMER2_OVF_vect)
{
	count++;
	if (Flag==RIGHT||Flag==LEFT)
	{
		if (count==30) // 400ms 25*16ms
		{
			DIO_WritePort(F_M_PORT,ZERO,F_M_PIN);
			Flag=CLEAR_FLAG;
		}
	}
	else if(Flag==NEUTRAL)
	{
		if (count==13) // 128ms 8*16ms
		{
			DIO_WritePort(F_M_PORT,ZERO,F_M_PIN);
			Flag=CLEAR_FLAG;
			TCCR2&=~(1<<CS22) ;
			TCCR2&=~(1<<CS20);
			count=0;
		}
	}
	 // 500ms 32*16ms
	if (count==32)
	{
		if (Right_flag)
		{
			PORTG^=(1<<0);
		} 
		else if(Left_flag)
		{
			PORTG^=(1<<1);
		}
		
		count=0;
	}
}

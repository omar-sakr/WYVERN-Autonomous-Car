/*
 * HC_SR04.c
 *
 * Created: 11/1/2016 1:01:20 PM
 *  Author: omar
 */ 
#include "HCSR04.h"

	 volatile u16 pulse1 = 0;//interger  to access all though the program
	 volatile u16 pulse2 = 0;//interger  to access all though the program
	 volatile u16 pulse3 = 0;//interger  to access all though the program
	 volatile u8 i = 0;// interger  to access all though the program
	 volatile u8 j = 0;// interger  to access all though the program
	 volatile u8 y = 0;// interger  to access all though the program
	 	
void HCSR04_Inti()
{
	// Enable Interrupt ,Interrupt Sense Control:logical change
	EICRB=0x00;
	EIMSK=0x00;
	EIMSK|=(1<<INT5) | (1<<INT6) | (1<<INT7);
	EICRB|=(1<<ISC50) | (1<<ISC60) | (1<<ISC70);
	
	
	DIO_InitPortDirection(ECHO_PORT,INPUT,ECHO_PIN1);
		
	DIO_InitPortDirection(TRIGER_PORT,OUTPUT,TRIGER_PIN1);
	
	DIO_InitPortDirection(ECHO_PORT,INPUT,ECHO_PIN2);
	
	DIO_InitPortDirection(TRIGER_PORT,OUTPUT,TRIGER_PIN2);	
		
	DIO_InitPortDirection(ECHO_PORT,INPUT,ECHO_PIN3);
		
	DIO_InitPortDirection(TRIGER_PORT,OUTPUT,TRIGER_PIN3);
		
}

void HCSR04_Trig(u8 S)
{
		switch(S)
		{
			case 0x01:
			{
					DIO_WritePort(TRIGER_PORT,HIGH,TRIGER_PIN1);
					_delay_us(15);
					DIO_WritePort(TRIGER_PORT,ZERO,TRIGER_PIN1);
			}
			break;
			case 0x02:
			{
					DIO_WritePort(TRIGER_PORT,HIGH,TRIGER_PIN2);
					_delay_us(15);
					DIO_WritePort(TRIGER_PORT,ZERO,TRIGER_PIN2);
			}
			break;
			case 0x03:
			{
				DIO_WritePort(TRIGER_PORT,HIGH,TRIGER_PIN3);
				_delay_us(15);
				DIO_WritePort(TRIGER_PORT,ZERO,TRIGER_PIN3);
			}
			break;
	
	}
}


ISR(INT5_vect)//interrupt service routine when there is a change in logic level

{
	if (i==1)//when logic from HIGH to LOW

	{
		TCCR3B&=~(1<<CS31);//disabling counter
		if (TCNT3>650)
		{
			pulse1=TCNT3;//count memory is updated to integer
		}
		else
		{
			
		}
		TCNT3=0;//resetting the counter memory
		i=0;
		

	}

	if (i==0)//when logic change from LOW to HIGH

	{

		TCCR3B|=(1<<CS31);//enabling counter
		i=1;
		

	}

}

ISR(INT6_vect)//interrupt service routine when there is a change in logic level

{
	if (j==1)//when logic from HIGH to LOW

	{
		TCCR1B&=~(1<<CS11);//disabling counter
		if (TCNT1>650)
		{
			pulse2=TCNT1;//count memory is updated to integer
		}
		else
		{
			
		}
		TCNT1=0;//resetting the counter memory
		j=0;

	}

	if (j==0)//when logic change from LOW to HIGH

	{

		TCCR1B|=(1<<CS11);//enabling counter
		j=1;

	}

}

ISR(INT7_vect)//interrupt service routine when there is a change in logic level

{
	if (y==1)//when logic from HIGH to LOW

	{
		TCCR3B&=~(1<<CS31);//disabling counter
		if (TCNT3>650)
		{
			pulse3=TCNT3;//count memory is updated to integer
		}
		else
		{
			
		}
		TCNT3=0;//resetting the counter memory
		y=0;

	}

	if (y==0)//when logic change from LOW to HIGH

	{

		TCCR3B|=(1<<CS31);//enabling counter
		y=1;

	}

}
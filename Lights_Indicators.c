/*
 * Lights_Indicators.c
 *
 * Created: 4/13/2017 7:08:45 PM
 *  Author: omar
 */ 
#include "Lights_Indicators.h"


void Light_Indicators_Init()
{
	DIO_InitPortDirection(LIGHTS_PORT,OUTPUT,LIGHTS_PIN);
	DIO_InitPortDirection(INDICATORS_PORT,OUTPUT,RIGHT_PIN);
	DIO_InitPortDirection(INDICATORS_PORT,OUTPUT,LEFT_PIN);
	
	DIO_WritePort(INDICATORS_PORT,ZERO,RIGHT_PIN);
	DIO_WritePort(INDICATORS_PORT,ZERO,LEFT_PIN);

}
void Front_Lights(u8 state)
{
	if (state==ON)
	{
		DIO_WritePort(LIGHTS_PORT,HIGH,LIGHTS_PIN);
	}
	else if (state==OFF)
	{
		DIO_WritePort(LIGHTS_PORT,ZERO,LIGHTS_PIN);
	}
}

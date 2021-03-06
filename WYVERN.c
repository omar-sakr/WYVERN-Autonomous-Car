/*
 * WYVERN.c
 *
 * Created: 3/30/2017 8:52:13 PM
 *  Author: omar
 */ 


#include <avr/io.h>
#include <stdlib.h>
#include "LidarLite_v3.h"
#include "HCSR04.h"
#include "SPI.h"
#include "Motor_Timer0.h"
#include "Steering_Motor.h"
#include "Lights_Indicators.h"
#include "lcd_4bit.h"
#include "Macros.h"
#include <util/delay.h>


//Functions prototypes
u16 Get_Distance(u8 Dis);
u16 Rear_Distance(void);
static void inline Go_Forward(void);
// Initialize Global Variables
	extern char Received_Data;
	extern u16 pulse1 ; //integer  to access all though the program
	extern u16 pulse2 ;//integer  to access all though the program
	extern u16 pulse3 ;//integer  to access all though the program	
	u16 Front_Dis=0;
	u16 Right_Dis=0;
	u16 Left_Dis=0;
	u16 Rear_Dis=0;
	u8 State=NEUTRAL;
	u8 Speed=STOP;
	u8 stop_flag=0;
	char str1[4];
	

int main(void)
{
	// Initialize Drivers
	Lidar_V3_Init();
	HCSR04_Inti();
	Spi_Init();
	Motor_Timer0_Init();
	Steering_Motor_Init();
	Light_Indicators_Init();
	lcd_init();
	
	sei();  // Global interrupt enable
	
    while(1)
    {
		Front_Dis=Get_Distance(FRONT_S);
			
		Right_Dis=Get_Distance(S1);

		Left_Dis=Get_Distance(S2);

		switch (Received_Data)
		{
			case STOP_RECEIVED:
					if (!stop_flag)
					{
						Rear_Dis=Rear_Distance();
						if(Rear_Dis>50)
						{
							Speed=STOP;
							Motor_Speed_Dir(Speed,FORWARD);
							stop_flag=SET_FLAG;
						}
						else
						{
							Speed=SPEED1;
							Motor_Speed_Dir(Speed,FORWARD);
						}
					}
				   break;
			case SLOWDOWN_RECEIVED:
					if (Front_Dis>100&&Front_Dis<300)
					{
						Speed=SPEED1;
						Motor_Speed_Dir(Speed,FORWARD);			
					}
					else if (Front_Dis>=2&&Front_Dis<=100)
					{
						Speed=STOP;
						Motor_Speed_Dir(Speed,FORWARD);
					}
					else
					{
						Speed=SPEED2;
						Motor_Speed_Dir(Speed,FORWARD);
					}			
				   break;
				case TURNLEFT_RECEIVED:
						if(Left_Dis>30)
						{
							if (State!=LEFT)
							{
								Front_Motor_Steering(LEFT);
								State=LEFT;
							}
							_delay_ms(50);
								if (Front_Dis>=2&&Front_Dis<=100)
								{
									Speed=STOP;
									Motor_Speed_Dir(Speed,FORWARD);
								}
								else
								{
									Speed=SPEED2;
									Motor_Speed_Dir(Speed,FORWARD);
								}
							
						}
						else 
						{
							if (State!=NEUTRAL)
							{
								Front_Motor_Steering(NEUTRAL);
								State=NEUTRAL;
							}
							_delay_ms(50);
							if (Front_Dis>=2&&Front_Dis<=100)
							{
								Speed=STOP;
								Motor_Speed_Dir(Speed,FORWARD);
							}
							else
							{
								Speed=SPEED1;
								Motor_Speed_Dir(Speed,FORWARD);
							}
						}
						break;
				case TURNRIGHT_RECEIVED:
						if(Right_Dis>30)
						{
							if (State!=RIGHT)
							{
								Front_Motor_Steering(RIGHT);
								State=RIGHT;
							}
							_delay_ms(50);
								if (Front_Dis>=2&&Front_Dis<=100)
								{
									Speed=STOP;
									Motor_Speed_Dir(Speed,FORWARD);
								}
								else
								{
									Speed=SPEED2;
									Motor_Speed_Dir(Speed,FORWARD);
								}

						}
						else
						{
							if (State!=NEUTRAL)
							{
								Front_Motor_Steering(NEUTRAL);
								State=NEUTRAL;
							}
							_delay_ms(50);
							if (Front_Dis>=2&&Front_Dis<=100)
							{
								Speed=STOP;
								Motor_Speed_Dir(Speed,FORWARD);
							}
							else
							{
								Speed=SPEED1;
								Motor_Speed_Dir(Speed,FORWARD);
							}
						}
						break;
				case NEUTRAL_RECEIVED:
						if (State!=NEUTRAL)
						{
							Front_Motor_Steering(NEUTRAL);
							State=NEUTRAL;
							Received_Data=FORWARD_RECEIVED;
						}	
					break;
				case REVERSE_RECEIVED:
						Rear_Dis=Rear_Distance();
						if (Rear_Dis>50)
						{
							Speed=SPEED1;
							Motor_Speed_Dir(Speed,REVERSE);
						}
						else
						{
							Speed=STOP;
							Motor_Speed_Dir(Speed,REVERSE);
						}	
					break;
				case FORWARD_RECEIVED:
							Go_Forward();
					break;
				case TURNON_LIGHT_RECEIVED:
						Front_Lights(ON);				
					break;
				
		}
		
    }
}



u16 Get_Distance(u8 Dis)
{
	u16 distance=0;
	if (Dis==FRONT_S)
	{
		distance=Lidar_V3_Read();
	}
	else if (Dis==S1)
	{
		HCSR04_Trig(S1);
		distance=(pulse1)/(58*2);   // (/58 = (*340*100*10^-6)/2 )
	}
	else if (Dis==S2)
	{
		HCSR04_Trig(S2);
		distance=(pulse2)/(58*2);   // (/58 = (*340*100*10^-6)/2 )
	}
		return distance;
}


u16 Rear_Distance()
{
	u16 Dis;
			HCSR04_Trig(S3);
			Dis = (pulse3)/(58*2);   // (/58 = (*340*100*10~-6)/2 )
			return Dis;
}

static void inline Go_Forward()
{
	stop_flag=CLEAR_FLAG;
	if (Front_Dis>=2&&Front_Dis<=100)
	{
		if (Left_Dis>50)
		{
			if (State!=LEFT)
			{
				Front_Motor_Steering(LEFT);
				State=LEFT;
			}
			Speed=SPEED1;
			Motor_Speed_Dir(Speed,FORWARD);
			lcd_clrScreen();
			itoa(Left_Dis,str1,10);
			lcd_disp_string_xy("L:",0 ,1);
			lcd_dispString(str1);
			itoa(Right_Dis,str1,10);
			lcd_disp_string_xy("R:",0 ,8);
			lcd_dispString(str1);
			lcd_disp_string_xy("LEFT:",1 ,1);
			_delay_ms(100);
			
		}
		else if (Right_Dis>50&&Left_Dis<=50)
		{
			if (State!=RIGHT)
			{
				Front_Motor_Steering(RIGHT);
				State=RIGHT;
			}
			Speed=SPEED1;
			Motor_Speed_Dir(Speed,FORWARD);
			lcd_clrScreen();
			itoa(Left_Dis,str1,10);
			lcd_disp_string_xy("L:",0 ,1);
			lcd_dispString(str1);
			itoa(Right_Dis,str1,10);
			lcd_disp_string_xy("R:",0 ,8);
			lcd_dispString(str1);
			lcd_disp_string_xy("Right:",1 ,1);
			_delay_ms(100);
			
		}
		else if(Right_Dis<=50&&Left_Dis<=50)
		{
			if (State!=NEUTRAL)
			{
				Front_Motor_Steering(NEUTRAL);
				State=NEUTRAL;
			}
			Speed=STOP;
			Motor_Speed_Dir(Speed,FORWARD);
			lcd_clrScreen();
			itoa(Left_Dis,str1,10);
			lcd_disp_string_xy("L:",0 ,1);
			lcd_dispString(str1);
			itoa(Right_Dis,str1,10);
			lcd_disp_string_xy("R:",0 ,8);
			lcd_dispString(str1);
			lcd_disp_string_xy("STOP!",1 ,1);
			_delay_ms(100);
			
		}
	}
	
	else if (Front_Dis>100&&Front_Dis<=300)
	{
		if (State!=NEUTRAL)
		{
			Front_Motor_Steering(NEUTRAL);
			State=NEUTRAL;
		}
		Speed=SPEED1;
		Motor_Speed_Dir(Speed,FORWARD);
		lcd_clrScreen();
		lcd_disp_string_xy("speed1",1 ,1);
	}
	else if (Front_Dis>300&&Front_Dis<=400)
	{
		if (State!=NEUTRAL)
		{
			Front_Motor_Steering(NEUTRAL);
			State=NEUTRAL;
		}
		Speed=SPEED2;
		Motor_Speed_Dir(Speed,FORWARD);
		lcd_clrScreen();
		lcd_disp_string_xy("speed2",1 ,1);
	}
	else if (Front_Dis>400&&Front_Dis<=500)
	{
		if (State!=NEUTRAL)
		{
			Front_Motor_Steering(NEUTRAL);
			State=NEUTRAL;
		}
		Speed=SPEED3;
		Motor_Speed_Dir(Speed,FORWARD);
		lcd_clrScreen();
		lcd_disp_string_xy("speed3",1 ,1);
	}
	else
	{
		if (State!=NEUTRAL)
		{
			Front_Motor_Steering(NEUTRAL);
			State=NEUTRAL;
		}
		Speed=SPEED4;
		Motor_Speed_Dir(Speed,FORWARD);
		lcd_clrScreen();
		lcd_disp_string_xy("speed4",1 ,1);
	}
}
/*
 * Motor_Timer0.h
 *
 * Created: 2/26/2017 3:03:54 PM
 *  Author: omar
 */ 


#ifndef MOTOR_TIMER0_H_
#define MOTOR_TIMER0_H_
#include <avr/io.h>
#include "DIO.h"

#define DIRECTION_PORT PB
#define DIRECTION_PIN 0x40
#define FORWARD 0x00
#define REVERSE 0xff

#define STOP 0
#define SPEED1 70
#define SPEED2 120
#define SPEED3 160
#define SPEED4 180

void Motor_Timer0_Init(void);
void Motor_Speed_Dir(u8 speed,u8 Direction);



#endif /* MOTOR_TIMER0_H_ */
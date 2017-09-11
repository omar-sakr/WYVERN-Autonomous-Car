/*
 * Steering_Motor.h
 *
 * Created: 2/28/2017 5:02:39 PM
 *  Author: omar
 */ 


#ifndef STEERING_MOTOR_H_
#define STEERING_MOTOR_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "DIO.h"



#define F_M_PORT PD
#define F_M_PIN 0x80

#define F_M_DIR_PIN1 0x40
#define F_M_DIR_PIN2 0x20

#define LEFT 0x01
#define RIGHT 0x02
#define NEUTRAL 0x03
#define R_FORWARD 0x04
#define L_FORWARD 0x05


void Steering_Motor_Init(void);
void Front_Motor_Steering(u8 Dir);




#endif /* STEERING_MOTOR_H_ */
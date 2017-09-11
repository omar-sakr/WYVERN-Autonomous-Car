/*
 * Lights_Indicators.h
 *
 * Created: 4/13/2017 7:08:30 PM
 *  Author: omar
 */ 


#ifndef LIGHTS_INDICATORS_H_
#define LIGHTS_INDICATORS_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "DIO.h"

#define LIGHTS_PORT PC
#define LIGHTS_PIN 0x01
#define INDICATORS_PORT PG
#define RIGHT_PIN 0x01
#define LEFT_PIN 0x02
#define RIGHT_INDICATOR 0x01
#define LEFT_INDICATOR 0x02
#define STOP_INDICATOR 0x03
#define ON 0xff
#define OFF 0x00

void Light_Indicators_Init(void);
void Front_Lights(u8 state);
void Indicators_On(u8 Dir);


#endif /* LIGHTS_INDICATORS_H_ */
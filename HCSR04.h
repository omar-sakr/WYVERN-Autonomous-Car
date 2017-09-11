/*
 * HC_SR04.h
 *
 * Created: 11/1/2016 1:01:09 PM
 *  Author: omar
 */ 


#ifndef HCSR04_H_
#define HCSR04_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "StdTypes.h"
#include "DIO.h"
#define F_CPU 16000000ul
#include <util/delay.h>

#define TRIGER_PORT PF
#define ECHO_PORT PE

#define TRIGER_PIN1 0x01
#define ECHO_PIN1 0x20

#define TRIGER_PIN2 0x02
#define ECHO_PIN2 0x40

#define TRIGER_PIN3 0x04
#define ECHO_PIN3 0x80

#define S1 0x01
#define S2 0x02
#define S3 0x03

void HCSR04_Inti(void);
void HCSR04_Trig(u8 S);




#endif /* HC-SR04_H_ */
/*
 * I2C.h
 */ 


#ifndef I2C_H_
#define I2C_H_

#include<avr/io.h>

#define I2C_READ    1

#define I2C_WRITE   0

void TWI_Init(void);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_Write(unsigned char data);
unsigned char TWI_Read_With_ACK(void); //read with send Ack
unsigned char TWI_Read_With_NACK(void); //read without send Ack
unsigned char TWI_Get_Status(void);


#endif /* I2C_H_ */
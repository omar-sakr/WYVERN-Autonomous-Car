/*
 * SPI.h
 *
 * Created: 5/1/2017 1:58:23 PM
 *  Author: omar
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "DIO.h"

#define SS 0x01
#define SCK 0x02
#define MOSI 0x04
#define MISO 0x08

#define MODE_0 0x00
#define MODE_1 0x04
#define MODE_2 0x08
#define MODE_3 0x0C

void Spi_Init();

u8 SPI_u8TransfereByte(u8 u8Byte);


#endif /* SPI_H_ */
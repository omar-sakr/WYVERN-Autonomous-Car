/*
 * SPI.c
 *
 * Created: 5/1/2017 1:58:09 PM
 *  Author: omar
 */ 

#include "SPI.h"

char Received_Data=0xff;

void Spi_Init()
{
	DIO_InitPortDirection(PB,INPUT,SS);
	DIO_InitPortDirection(PB,INPUT,SCK);
	DIO_InitPortDirection(PB,INPUT,MOSI);
	DIO_InitPortDirection(PB,OUTPUT,MISO);
	
	SPCR=0x00;
	// Enable SPI ,Enable interrupt ,slave mode ,MSB, SPI mode 0
	SPCR|=(1<<SPIE) | (1<<SPE) ;
}

/*u8 SPI_u8TransfereByte(u8 u8Byte)
{
	SPDR = u8Byte;
	while((SPSR&(1<<SPIF))== 0x00)
	;
	u8Byte = SPDR;
	return u8Byte;
}*/

ISR(SPI_STC_vect)
{
	Received_Data = SPDR;

}
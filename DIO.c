/*
 * DIO.c
 *
 * Created: 10/23/2016 10:59:37 PM
 *  Author: omar
 */ 
#include "DIO.h"
#include <AVR/io.h>
// write a macro to write a register with a certain value on specific bits locations
#define WRITE_REG(Reg,Value,Mask) Reg&=~(Mask); Reg|=(Value & Mask)
//read a macro to read specific bits from a register
#define READ_REG(Reg,Mask) Reg & Mask

void DIO_InitPortDirection(u8 PortName,u8 PortDirection,u8 PortMask)
{
	//check the required port, specified bits and direction on the Data Direction Register
	switch(PortName)
	{
		case PA:
		{
			WRITE_REG(DDRA,PortDirection,PortMask);
		}
		break;
		case PB:
		{
			WRITE_REG(DDRB,PortDirection,PortMask);
		}
		break;
		case PC:
		{
			WRITE_REG(DDRC,PortDirection,PortMask);
		}
		break;
		case PD:
		{
			WRITE_REG(DDRD,PortDirection,PortMask);
		}
		break;
		case PE:
		{
			WRITE_REG(DDRE,PortDirection,PortMask);
		}
		break;
		case PF:
		{
			WRITE_REG(DDRF,PortDirection,PortMask);
		}
		break;
		case PG:
		{
			WRITE_REG(DDRG,PortDirection,PortMask);
		}
		break;
	}
}

void DIO_WritePort(u8 PortName,u8 PortData,u8 PortMask)
{
	//check the required port, specified bits and value on the Port Data Register
	switch(PortName)
	{
		case PA:
		{
			WRITE_REG(PORTA,PortData,PortMask);
		}
		break;
		case PB:
		{
			WRITE_REG(PORTB,PortData,PortMask);
		}
		break;
		case PC:
		{
			WRITE_REG(PORTC,PortData,PortMask);
		}
		break;
		case PD:
		{
			WRITE_REG(PORTD,PortData,PortMask);
		}
		break;
		case PE:
		{
			WRITE_REG(PORTE,PortData,PortMask);
		}
		break;
		case PF:
		{
			WRITE_REG(PORTF,PortData,PortMask);
		}
		break;
		case PG:
		{
			WRITE_REG(PORTG,PortData,PortMask);
		}
		break;
	}
}
u8 DIO_ReadPort(u8 PortName,u8 PortMAsk)
{
	//check the required port, specified bits and value from the Port input Register
	u8 Data;
	switch(PortName)
	{
		case PA:
		{
			Data = READ_REG(PINA,PortMAsk);
		}
		break;
		case PB:
		{
			Data = READ_REG(PINB,PortMAsk);
		}
		break;
		case PC:
		{
			Data = READ_REG(PINC,PortMAsk);
		}
		break;
		case PD:
		{
			Data = READ_REG(PIND,PortMAsk);
		}
		break;
		case PE:
		{
			Data = READ_REG(PINE,PortMAsk);
		}
		break;
		case PF:
		{
			Data = READ_REG(PINF,PortMAsk);
		}
		break;
		case PG:
		{
			Data = READ_REG(PING,PortMAsk);
		}
		break;		
	}
	return Data;
	
}
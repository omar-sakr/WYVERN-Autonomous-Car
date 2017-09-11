/*
 * LidarLite_v3.c
 *
 * Created: 1/28/2017 11:24:57 AM
 *  Author: omar
 */ 

#include "lidarLite_V3.h"
#include <util/delay.h>

void Lidar_V3_Init()
{
	TWI_Init();

	TWI_Start();
	TWI_Write((Lidar_Address<<1)|I2C_WRITE );
	TWI_Write(0x02);
	TWI_Write(0x80);
	TWI_Stop();
	_delay_us(1);
	TWI_Start();
	TWI_Write((Lidar_Address<<1)|I2C_WRITE );
	TWI_Write(0x04);
	TWI_Write(0x08);
	TWI_Stop();
	_delay_us(1);
	TWI_Start();
	TWI_Write((Lidar_Address<<1)|I2C_WRITE );
	TWI_Write(0x1c);
	TWI_Write(0x00);
	TWI_Stop();


}

u16 Lidar_V3_Read()
{
	 u16 Distance=0x0000;
	 
		TWI_Start();
		TWI_Write((Lidar_Address<<1)|I2C_WRITE );
		TWI_Write(0x00);
		TWI_Write(0x04);
		TWI_Stop();
		_delay_us(1);	
		

	TWI_Start();
	TWI_Write((Lidar_Address<<1)|I2C_WRITE );
	TWI_Write(0x0f);            // High Bytes
	TWI_Stop();
	_delay_us(1);
	TWI_Start();
	TWI_Write((Lidar_Address<<1)|I2C_READ );
	Distance=(TWI_Read_With_NACK()<<8);
	//Distance|=TWI_Read_With_NACK();
	TWI_Stop();
	_delay_us(1);
	
		TWI_Start();
		TWI_Write((Lidar_Address<<1)|I2C_WRITE );
		TWI_Write(0x10);            // LOW Bytes
		TWI_Stop();
		_delay_us(1);
		TWI_Start();
		TWI_Write((Lidar_Address<<1)|I2C_READ );
		Distance|=TWI_Read_With_NACK();
		TWI_Stop();
		
		return Distance;
}



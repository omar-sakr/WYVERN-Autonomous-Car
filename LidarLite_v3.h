/*
 * LidarLite_v3.h
 *
 * Created: 1/28/2017 11:25:07 AM
 *  Author: omar
 */ 


#ifndef LIDARLITE_V3_H_
#define LIDARLITE_V3_H_
#include "I2C.h"
#include "StdTypes.h"

#define Lidar_Address 0x62
#define FRONT_S 0x05


void Lidar_V3_Init(void);
u16 Lidar_V3_Read(void);



#endif /* LIDARLITE_V3_H_ */
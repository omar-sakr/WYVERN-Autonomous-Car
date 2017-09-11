/*
 * I2C.c
 *
 * 
 *  
 */ 
#include "I2C.h"

void TWI_Init(void)
{
    // Bit Rate: 400.000 kHz												  //                  CPU Clock frequency
    TWBR=0x0C;	              // TWBR = ((F_CPU / 400000UL) - 16) / 2;		 // SCL frequency = ------------------------------ 
																			//                    16 + 2(TWBR) * 4TWPS				
	TWSR=0x00;
    TWCR=(1<<TWEN); //enable TWI

}

void TWI_Start(void)
{
    /* Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    // Wait for TWINT flag set in TWCR Register (start bit is send successfully) 
    while (!(TWCR & (1 << TWINT)));
}

void TWI_Stop(void)
{
    /* Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void TWI_Write(unsigned char data)
{
    // Put data On TWI Register
    TWDR = data;
    /* Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN) ;
    // Wait for TWINT flag set in TWCR Register(data is send successfully) 
    while (!(TWCR & (1 << TWINT)));
	
}

unsigned char TWI_Read_With_ACK(void)
{
	/* Clear the TWINT flag before reading the data TWINT=1
	 * enable sending ACK TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN) | (1<<TWEA);
    // Wait for TWINT flag set in TWCR Register (data received successfully) 
    while (!(TWCR & (1 << TWINT)));
    // Read Data
    return TWDR;
}

unsigned char TWI_Read_With_NACK(void)
{
	/* Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    // Wait for TWINT flag set in TWCR Register (data received successfully) 
    while (!(TWCR & (1 << TWINT)));
    // Read Data
    return TWDR;
}

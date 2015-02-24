/*
 * Functions needed to send and retrieve data over I2C
 *
 * Created: 12/24/2014 11:47:03 PM
 * Author: Devon
 */ 

#include <inttypes.h>
#include <avr/io.h>
#include "i2c.h"

/**
* Initialize the I2C hardware
* 
* @param	none
* 
* @return	none
*/
void SetupI2C(void)
{
	// Set baud rate to fast mode (400KHz) - section 21.5.2
	TWBR = 2; // This works when we use the default prescaler of one
	
	// Enable the I2C module
	TWCR |= _BV(TWEN);
}

/**
* Sends a single byte of data to a device's register
*
* @param	devAddr 7-bit address of device to send to
* @param	regAddr 8-bit address of register to send to
* @param	data 8-bits of data to put into the register
*
* @return	none
*/
void I2CSendByte(uint8_t devAddr, uint8_t regAddr, uint8_t data)
{
	/* Section 21.6 describes this code in full detail */
	
	// Send start condition
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	
	// Wait for start condition to finish transmitting
	while(!(TWCR & _BV(TWINT)));
	
	// Load device address into data register and send
	TWDR = devAddr << 1; // 7-bit address, plus a "0" to indicate write mode
	TWCR = _BV(TWINT) | _BV(TWEN);
	
	// Wait for address to finish sending
	while(!(TWCR & _BV(TWINT)));
	
	// Load register address into data register and send
	TWDR = regAddr;
	TWCR = _BV(TWINT) | _BV(TWEN);
	
	// Wait for register address to finish sending
	while(!(TWCR & _BV(TWINT)));
	
	// Load data into data register and send
	TWDR = data;
	TWCR = _BV(TWINT) | _BV(TWEN);
	
	// Wait for data to finish sending
	while(!(TWCR & _BV(TWINT)));
	
	// Transmit stop condition
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}

/**
* Reads a single byte of data from a device's register
*
* @param	devAddr 7-bit address of device to read from
* @param	regAddr 8-bit address of register to read from
*
* @return	The 8-bits of data returned from the device
*/
uint8_t I2CReadByte(uint8_t devAddr, uint8_t regAddr)
{
	uint8_t data = 0;
	
	// Send start condition
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	
	// Wait for start condition to finish transmitting
	while(!(TWCR & _BV(TWINT)));
	
	// Load device address into data register and send
	TWDR = devAddr << 1; // 7-bit address, plus a "0" to indicate write mode
	TWCR = _BV(TWINT) | _BV(TWEN);
	
	// Wait for address to finish sending
	while(!(TWCR & _BV(TWINT)));
	
	// Load register address into data register and send
	TWDR = regAddr;
	TWCR = _BV(TWINT) | _BV(TWEN);
	
	// Wait for register address to finish sending
	while(!(TWCR & _BV(TWINT)));
	
	// Send a repeated start condition to turn the bus around
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	
	// Wait for repeated start condition to finish transmitting
	while(!(TWCR & _BV(TWINT)));
	
	// Load device address into data register and send
	TWDR = devAddr << 1 | 1; // 7-bit address, plus a "1" to indicate read mode
	TWCR = _BV(TWINT) | _BV(TWEN);
	
	// Wait for address to finish sending
	while(!(TWCR & _BV(TWINT)));
	
	// Send a NACK
	TWCR = _BV(TWINT) | _BV(TWEN);
	
	// Wait for NACK to finish sending
	while(!(TWCR & _BV(TWINT)));
	
	// Get the data
	data = TWDR;
	
	// Transmit stop condition
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
	
	return data;
}

/**
* Reads multiple bytes of data from a device
*
* @param	devAddr 7-bit address of device to read from
* @param	regAddr 8-bit address of register to start from
* @param	data	A pointer to an array of bytes to place the read data into
* @param	numBytes The number of bytes to retrieve
*
* @return	The 8-bits of data returned from the device
*/
void I2CReadMultiple(uint8_t devAddr, uint8_t regAddr, uint8_t data[], uint8_t numBytes)
{
	// Send start condition
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	
	// Wait for start condition to finish transmitting
	while(!(TWCR & _BV(TWINT)));
	
	// Load device address into data register and send
	TWDR = devAddr << 1; // 7-bit address, plus a "0" to indicate write mode
	TWCR = _BV(TWINT) | _BV(TWEN);
	
	// Wait for address to finish sending
	while(!(TWCR & _BV(TWINT)));
	
	// Load register address into data register and send
	TWDR = regAddr;
	TWCR = _BV(TWINT) | _BV(TWEN);
	
	// Wait for register address to finish sending
	while(!(TWCR & _BV(TWINT)));
	
	// Send a repeated start condition to turn the bus around
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	
	// Wait for repeated start condition to finish transmitting
	while(!(TWCR & _BV(TWINT)));
	
	// Load device address into data register and send
	TWDR = devAddr << 1 | 1; // 7-bit address, plus a "1" to indicate read mode
	TWCR = _BV(TWINT) | _BV(TWEN);
	
	// Wait for address to finish sending
	while(!(TWCR & _BV(TWINT)));
	
	// Retrieve multiple bytes of data
	for(int i = 0; i < numBytes; ++i)
	{
		// Send ACK
		TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN);
		
		// Wait for ACK to finish sending
		while(!(TWCR & _BV(TWINT)));
		
		// Get data
		data[i] = TWDR;
	}
	
	// Send a NACK
	TWCR = _BV(TWINT) | _BV(TWEN);
	
	// Wait for NACK to finish sending
	while(!(TWCR & _BV(TWINT)));
	
	// Transmit stop condition
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}
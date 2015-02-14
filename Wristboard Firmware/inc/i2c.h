/*
 * Functions needed to send and retrieve data over I2C
 *
 * Created: 12/24/2014 11:46:39 PM
 * Author: Devon
 */ 
#ifndef I2C_H_
#define I2C_H_

#include <inttypes.h>

// Initialize the I2C hardware
void SetupI2C(void);

// Sends a single byte of data to a device's register
void I2CSendByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);

// Reads a single byte of data from a device's register
uint8_t I2CReadByte(uint8_t devAddr, uint8_t regAddr);

// Reads multiple bytes of data from a device
void I2CReadMultiple(uint8_t devAddr, uint8_t regAddr, uint8_t data[], uint8_t numBytes);

#endif /* I2C_H_ */
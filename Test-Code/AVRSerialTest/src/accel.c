/*
 * accel.c
 *
 * Created: 12/27/2014 5:36:06 PM
 *  Author: Devon
 */ 

#include "i2c.h"
#include "accel.h"

// Whether we're in 8-bit or 12-bit data mode
DataBits cur_bits = TWELVEBITS;

/**
* Initialize the accelerometer and prepare it for sending data
*
* @param	gscale	The sensitivity of the accelerometer to set it to
* @param	fread	Whether the F_READ bit should be set. If set, this turns
*					the accelerometer into 8-bit mode. If zero, 12-bit mode
*					will be used. Must be either '0' or '1'.
*
* @return	none
*/
void SetupAccelerometer(GScale gscale, DataBits fread)
{
	uint8_t ctrlreg = 0;
	
	// Initialize the I2C module
	SetupI2C();
	
	// Set to standby mode so we can change the registers
	ctrlreg = I2CReadByte(ACCEL_ID, CTRL_REG1);
	I2CSendByte(ACCEL_ID, CTRL_REG1, ctrlreg & ~(0x01));
	
	// Set sensitivity level
	I2CSendByte(ACCEL_ID, XYZ_DATA_CFG, gscale & 0x3);
	
	// Initialize accelerometer to active mode and set/clear the F_READ bit
	ctrlreg = I2CReadByte(ACCEL_ID, CTRL_REG1);
	I2CSendByte(ACCEL_ID, CTRL_REG1, ctrlreg | 0x01 | ((fread & 1) << 1));
	
	// Set which data
	cur_bits = fread;
}

/*
* Grabs X, Y, and Z data from the accelerometer and returns it
*
* @param	data The data structure to place the acceleration data into
*
* @return	Through the data parameter
*/
void AccelGetData(struct AccelData * data)
{
	uint8_t raw_data[6] = {0};
		
	// Grab the data from the accelerometer
	if(cur_bits == TWELVEBITS)
		I2CReadMultiple(ACCEL_ID, OUT_X_MSB, raw_data, 6);
	else
		I2CReadMultiple(ACCEL_ID, OUT_X_MSB, raw_data, 3);
		
	// Compact and sign extend the data
	for(int i = 0; i < 3 ; i++)
	{
		// If we're working with 12-bit data, compact it into one variable
		if(cur_bits == TWELVEBITS)
		{
			raw_data[i] = (raw_data[i*2] << 8) | raw_data[(i*2)+1];  //Combine the two 8 bit registers into one 12-bit number
			raw_data[i] >>= 4; //The registers are left align, here we right align the 12-bit integer
		}

		// If the number is negative, we have sign extend it manually (no 12-bit data type)
		if (raw_data[(i*2) >> cur_bits] > 0x7F)
		{
			raw_data[i] = ~raw_data[i] + 1;
			raw_data[i] *= -1;  // Transform into negative 2's complement #
		}
	}

	data->x = raw_data[0];
	data->y = raw_data[1];
	data->z = raw_data[2];
}
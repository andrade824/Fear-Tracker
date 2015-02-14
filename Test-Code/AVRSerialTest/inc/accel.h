/*
 * accel.h
 *
 * Created: 12/27/2014 5:35:55 PM
 *  Author: Devon
 */ 


#ifndef ACCEL_H_
#define ACCEL_H_

#include <inttypes.h>

// Device ID of the accelerometer
#define ACCEL_ID 0x1D

// Defines for the accelerometer registers
#define OUT_X_MSB 0x01
#define XYZ_DATA_CFG  0x0E
#define CTRL_REG1  0x2A

// Type for the scale (sensitivity)
typedef enum { TWOG = 0, FOURG, EIGHTG } GScale;

// Type for the number of data bits
typedef enum { TWELVEBITS = 0, EIGHTBITS } DataBits;

// Data structure used to store accelerometer data
struct AccelData
{
	uint16_t x;
	uint16_t y;
	uint16_t z;
};

// Initialize the accelerometer
void SetupAccelerometer(GScale gscale, DataBits fread);

// Grab data from the accelerometer
void AccelGetData(struct AccelData * data);

#endif /* ACCEL_H_ */
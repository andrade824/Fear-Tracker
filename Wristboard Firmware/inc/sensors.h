/*
 * sensors.h
 *
 * Created: 1/28/2015 7:05:22 PM
 *  Author: Jerome Selig
 */ 

#ifndef SENSORS_H
#define SENSORS_H

#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <inttypes.h>	// gives us uint8_t, uint16_t, etc.

//Device ID of the accelerometer
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
struct SensorData
{
	uint8_t pulse_val;
	uint8_t gsr_val;
	uint8_t accel_x;
	uint8_t accel_y;
	uint8_t accel_z;
};

// Initialize the accelerometer
void SetupAccelerometer(GScale gscale, DataBits fread);

//Initialize the ADC
void InitADC(void);

//Initialize the Pulse Sensor
void SetupPulseSensor(void);

//initialize the Galvanic Skin Response Sensor
void SetupGSR(void);

// Grab data from the accelerometer
void AccelGetData(struct SensorData * data);

#endif
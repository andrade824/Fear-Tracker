/*
 * Fear.c
 *
 *  Created on: Jan 29, 2015
 *      Author: B-Chan
 */

#include "..\inc\Accel.h"
#include "..\inc\UART.h"
#include <stdint.h>
#include <stdbool.h>

#define SAMPLE 10
 volatile uint8_t x_data[SAMPLE];
 volatile uint8_t y_data[SAMPLE];
 volatile uint8_t z_data[SAMPLE];

 volatile uint8_t sig[5];
int Displacement()
{
	int avg = 0;
	int xavg = 0;
	int yavg = 0;
	int zavg = 0;
	sig[0] += 100;
	sig[1] += 100;
	sig[2] += 100;

	int i = 0;
	for (i = 0; i <= (SAMPLE - 2); i++)
	{

		x_data[i] += x_data[i+1];
		y_data[i] += x_data[i+1];
		z_data[i] += x_data[i+1];
	}

	x_data[SAMPLE-1] = sig[0];
	y_data[SAMPLE-1] = sig[1];
	z_data[SAMPLE-1] = sig[2];

	for(i = 0; i < SAMPLE; i++)
	{
		xavg += x_data[i];
		yavg += y_data[i];
		zavg += z_data[i];
	}

	xavg /= SAMPLE;
	yavg /= SAMPLE;
	zavg /= SAMPLE;

	avg = xavg + yavg + zavg;

	avg = avg/3;

	return avg;
}


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
 volatile uint8_t x_datara[SAMPLE];
 volatile uint8_t y_datara[SAMPLE];
 volatile uint8_t z_datara[SAMPLE];

volatile uint8_t x_data;
volatile uint8_t y_data;
volatile uint8_t z_data;
 volatile uint8_t sig[5];
int Displacement()
{
	int32_t xavg = x_data;
	int32_t yavg = y_data;
	int32_t zavg = z_data;

	uint32_t avg = 0;

	if(xavg > 126)
		xavg += 127;
	if(yavg > 126)
		xavg += 127;
	if(zavg > 126)
		xavg += 127;

	xavg = xavg * xavg;
	yavg = yavg * yavg;
	zavg = zavg * zavg;

	avg = xavg + yavg + zavg;
	sqrt(avg);

	return avg;
}

int32_t sqrt(int32_t n)
{
	int32_t root = 0, bit, trial;
		bit = (n >= 0x10000) ? 1<<30 : 1<<14;
	do
	{
		trial = root+bit;
		if (n >= trial)
		{
			n -= trial;
			root = trial+bit;
		}
		root >>= 1;
		bit >>= 2;
	} while (bit);

	return root;
}

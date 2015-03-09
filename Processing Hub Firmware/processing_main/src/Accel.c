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


volatile uint8_t x_data;
volatile uint8_t y_data;
volatile uint8_t z_data;


#define MAX 100
#define MIN 1
int Displacement()
{

	int32_t xavg = x_data;
	int32_t yavg = y_data;
	int32_t zavg = z_data;

	xavg = xavg * xavg;
	yavg = yavg * yavg;
	zavg = zavg * zavg;

	int32_t avg =  yavg + zavg + xavg;
	avg = sqrt(avg);

	//avg = (MAX-MIN)/(445-0)*(avg-445)+MAX;

	uint8_t diplacement = avg;
	return diplacement;
}

uint32_t sqrt(uint32_t n)
{
    int i;
	unsigned long rem = 0;
	unsigned long root = 0;
	for (i = 0; i < 16; i++)
	{
		root <<= 1;
		rem = (rem << 2) | (n >> 30);
		n <<= 2;
		if(root < rem)
		{
			root++;
			rem -= root;
			root++;
		}
	}
	   return root >> 1;

}

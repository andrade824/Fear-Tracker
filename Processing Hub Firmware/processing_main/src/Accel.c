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

uint32_t prevx_data = 0;
uint32_t prevy_data = 0;
uint32_t prevz_data = 0;

uint8_t Displacement()
{
	/*uint32_t x_dataavg = 0;
	uint32_t y_dataavg = 0;
	uint32_t z_dataavg = 0;
	uint32_t x_dis = 0;
	uint32_t y_dis = 0;
	uint32_t z_dis = 0;

	int i = 0;
	uint8_t displacement = 0;
	for(i = 0; i < MAXITEMS; i++)
	{
		x_dataavg += sensor[i].x_data;
		y_dataavg += sensor[i].y_data;
		z_dataavg += sensor[i].z_data;
	}

	x_dataavg /= MAXITEMS;
	y_dataavg /= MAXITEMS;
	z_dataavg /= MAXITEMS;

	x_dis = x_dataavg - prevx_data;
	y_dis = y_dataavg - prevy_data;
	z_dis = z_dataavg - prevz_data;

	displacement = (x_dis + y_dis + z_dis) / 3;

	prevx_data = x_dataavg;
	prevy_data = y_dataavg;
	prevz_data = z_dataavg;*/

	uint8_t displacement = (sensor[curr_item].x_data + sensor[curr_item].y_data + sensor[curr_item].z_data) / 3;


	return displacement;
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

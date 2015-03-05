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

 volatile uint8_t x_data;
 volatile uint8_t y_data;
 volatile uint8_t z_data;
int Displacement()
{
	int avg = 0;
	x_data += 100;
	y_data += 100;
	z_data += 100;

	avg = x_data + y_data + z_data;

	avg = avg/3;

	return avg;
}


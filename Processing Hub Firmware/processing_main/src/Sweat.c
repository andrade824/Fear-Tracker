/*
 * Sweat.c
 *
 *  Created on: Jan 29, 2015
 *      Author: B-Chan
 */
#include "..\inc\UART.h"
#include "..\inc\Sweat.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

volatile int threshold = 0;

void GSRinit()
{

}
void GSRsetup()
{
	int i = 0;
	int sum = 0;
	for(i = 0;i<500;i++)
	{
		sum += sig[1];
	}

	threshold = sum/500;

}
void GSRProcessing()
{

}

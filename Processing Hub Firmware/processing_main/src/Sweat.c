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
volatile int GSR_val = 0;
volatile float GSRfloat = 0;
volatile uint8_t gsr_data;
//void GSRsetup()
//{
//	int i = 0;
//	int sum = 0;
//	for(i = 0;i<MAXITEMS;i++)
//	{
//		sum += sensor[curr_item].gsr_data;
//	}
//
//	threshold = sum/500; // avg skin resistance
//	//for a hig pass filter
//
//}
//void GSRProcessing()
//{
//	GSRfloat = (135 - sensor[curr_item].gsr_data)/(sensor[curr_item].gsr_data);
//	GSR_val = GSRfloat*100;
//}

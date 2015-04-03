/*
 * ScareScore.c
 *
 *  Created on: Jan 29, 2015
 *      Author: B-Chan
 */

#include "..\inc\ScareScore.h"
#include "..\inc\Sweat.h"
#include "..\inc\Accel.h"
#include "..\inc\BPM.h"
#include "..\inc\UART.h"
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

volatile uint8_t pulse_data;
volatile uint8_t gsr_data;
volatile uint8_t x_data;
volatile uint8_t y_data;
volatile uint8_t z_data;

int CalcScareScore(void)
{
	int scare_score = 0;

	// Heart rate
	int rate = GetBPM();
	if(rate >= 70 && rate <= 120)
		scare_score += rate - 70;
	else if(rate > 120)
		scare_score += 50;

	if( gsr_data  < 80)
		scare_score += 5;
	else if( gsr_data  < 60)
		scare_score += 10;
	else if( gsr_data  < 40)
		scare_score += 15;
	else if( gsr_data  < 20)
		scare_score += 25;

	int dis = Displacement();
	if(dis > 160)
		scare_score += 25;
	if(dis < 80)
		scare_score += 25;

	return scare_score;

}


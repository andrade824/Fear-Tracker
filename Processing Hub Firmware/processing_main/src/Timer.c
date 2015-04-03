/*
 * Timer.c
 *
 *  Created on: Mar 4, 2015
 *      Author: Beatrix
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "utils/uartstdio.h"
#include "..\inc\Timer.h"

volatile _Bool send_flag;

void Timer1init(void)
{
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	SysCtlDelay(3);
	// Configure 32-bit periodic timer
	ROM_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
	ROM_TimerLoadSet(TIMER1_BASE, TIMER_A, ROM_SysCtlClockGet()/15);
	//set interrupts
	ROM_IntEnable(INT_TIMER1A);
	ROM_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT); // timeout mode
	//enable timer
	ROM_TimerEnable(TIMER1_BASE, TIMER_A);
}

void Timer1IntHandler(void)
{
	ROM_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
	//timer interrupt for every 10ms
	send_flag = true;
}



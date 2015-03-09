/*
 * BPM.c
 *
 *  Created on: Jan 29, 2015
 *      Author: B-Chan
 */

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

#define SAMPLESIZE  10

volatile _Bool firstBeat = true;
volatile _Bool secondBeat = false;
volatile int hRate[SAMPLESIZE]; //sample of
volatile int time;

volatile unsigned long sampleCounter = 0;          // used to determine pulse timing
volatile unsigned long lastBeatTime = 0;           // used to find IBI
volatile int P = 128;                      // used to find peak in pulse wave, seeded
volatile int T = 128;                     // used to find trough in pulse wave, seeded
volatile int thresh = 128;                // used to find instant moment of heart beat, seeded
volatile int Pulse = false;     // true when pulse wave is high, false when it's low
volatile _Bool QS = false;        // becomes true when Arduoino finds a beat.
int amp = 100;

volatile uint8_t signal = 0; // signal from wristboard adc
volatile int BPM;
volatile int IBI = 600;
volatile _Bool flag = false;


int GetBPM()
{
	return BPM;
}
_Bool getFlag()
{
  return flag;
}
void clearBPMFlag()
{
	flag = false;

}
void BPMTimerSetUp()
{
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0); // timer 0
	SysCtlDelay(3);
	 //
	// Enable processor interrupts.
	//

	//IntPrioritySet(INT_TIMER0A_TM4C123, 2);
	//
	// Configure the two 32-bit periodic timers.
	//
	ROM_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
	ROM_TimerLoadSet(TIMER0_BASE, TIMER_A, ROM_SysCtlClockGet()/500);
	//ROM_SysCtlClockGet()/100000
	//ROM_SysCtlClockGet()/500

	// Setup the interrupts for the timer timeouts.
    ROM_IntEnable(INT_TIMER0A);
    ROM_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //
	// Enable the timers.
	//
	ROM_TimerEnable(TIMER0_BASE, TIMER_A);
	
}

//A timeout event for Timer A of
// GPTM 32/64-Bit Timer 1 is
// triggered
void Timer0IntHandler(void)
{
	ROM_IntMasterDisable();
	ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	//isr triggers every 2 ms
	volatile int i = 0;
	signal = sensor[curr_item].pulse_data;
	sampleCounter += 2; // plus 2 ms
	volatile int N = sampleCounter - lastBeatTime;


		if( (signal < thresh) && (N > (IBI/5)*3))
		{
			if(signal < T)
			{
				T = signal;
			}
		}

		if( (signal > thresh) && (signal > P) ) // thresh condition helps avoid noise
		{
			P = signal;
		}


		//look for heart beat here
		if(N > 250) // high frequency response filtering
		{
			if( (signal > thresh) && (Pulse == false) && (N > (IBI/5)*3 ) )
			{

				Pulse = true ;
				IBI = sampleCounter - lastBeatTime;
				lastBeatTime = sampleCounter;


				if(secondBeat == true)
				{
					secondBeat = false;
					for(i = 0; i <=( SAMPLESIZE - 1); i++)
					{
						hRate[i] = IBI;
					}
				}


				if(firstBeat == true)
				{
					firstBeat = false;
					secondBeat = true;
					ROM_IntMasterEnable();
					return;
				}

				volatile int runningTotal = 0;

				for( i = 0; i <=( SAMPLESIZE - 2); i++)
				{
					hRate[i] = hRate[i+1];
					runningTotal = runningTotal + hRate[i];
				}

				hRate[SAMPLESIZE - 1] = IBI;
				runningTotal = runningTotal + hRate[SAMPLESIZE - 1];
				runningTotal = runningTotal / SAMPLESIZE;
				BPM = 60000/runningTotal;
				//BPM = BPM / 3;
				flag = true;

		}
	}

		if( (signal < thresh)  && (Pulse == true) )
		{   // when the values are going down, the beat is over

		   Pulse = false;                         // reset the Pulse flag so we can do it again
		   amp = P - T;                           // get amplitude of the pulse wave
		   thresh = (amp/2) + T;                    // set thresh at 50% of the amplitude
		   P = thresh;                            // reset these for next time
		   T = thresh;
		 }

		 // 2.5 sec without heart beat
		  //reset values


		if( N > 2500)
		{
			thresh = 128;                          // set thresh default
			P = 128;                               // set P default
			T = 128;
			firstBeat = true;
			secondBeat = false;
			lastBeatTime = sampleCounter;

		}

	ROM_IntMasterEnable();
}

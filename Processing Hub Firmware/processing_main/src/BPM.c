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
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"


volatile bool firstBeat = true;
volatile bool secondBeat = false;
volatile int hRate[10]; //sample of
volatile int time;

volatile unsigned long sampleCounter = 0;          // used to determine pulse timing
volatile unsigned long lastBeatTime = 0;           // used to find IBI
volatile int P =512;                      // used to find peak in pulse wave, seeded
volatile int T = 512;                     // used to find trough in pulse wave, seeded
volatile int thresh = 525;                // used to find instant moment of heart beat, seeded
volatile bool Pulse = false;     // true when pulse wave is high, false when it's low
volatile bool QS = false;        // becomes true when Arduoino finds a beat.
int amp = 0;

volatile int signal = 0; // signal from wristboard adc
volatile int BPM;
volatile int IBI = 600;

int GetBPM()
{
	return BPM;
}
void BPMTimerSetUp()
{

	 // Enable lazy stacking for interrupt handlers.
	ROM_FPULazyStackingEnable();

	//clear timer interrupt flag
    ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Configure the two 32-bit periodic timers.
    //
    ROM_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    ROM_TimerLoadSet(TIMER0_BASE, TIMER_A, ROM_SysCtlClockGet());

    // Setup the interrupts for the timer timeouts.
    ROM_IntEnable(INT_TIMER0A);
    ROM_TimerEnable(TIMER0_BASE, TIMER_A);
	
	//
    // Enable the timers.
    //

    ROM_IntMasterEnable();
}

//A timeout event for Timer A of
// GPTM 32/64-Bit Timer 1 is
// triggered
void Timer0IntHandler(void)
{
	int i = 0;
	signal = GetSig();

    // Clear the timer interrupt.
    ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	sampleCounter += 2; // plus 2 ms
		int N = sampleCounter - lastBeatTime;
		bool Pulse = true;

		if( signal < (thresh && N) > (IBI/5)*3 )
		{
			if(signal < T)
				T = signal;
		}

		if(signal > thresh && signal > P)
			P = signal;

		if(N > 250) // high frequency response filtering
		{
			if( (signal > thresh) && (Pulse == false) && (N > (IBI/5)*3 ) )
			{

				Pulse = true ;
				IBI = sampleCounter - lastBeatTime;
				lastBeatTime = sampleCounter;

			}
			if(secondBeat == true)
			{
				secondBeat = false;
				for(i = 0; i <10; i++)
				{
					hRate[i] = IBI;
				}
			}

			if(firstBeat)
			{
				firstBeat = false;
				secondBeat = true;
				return;
			}

			int runningTotal = 0;

			for( i = 0; i <9; i++)
			{
				hRate[i] = hRate[i+1];
				runningTotal = runningTotal + hRate[i];
			}

			hRate[9] = IBI;
			runningTotal  += hRate[9];
			runningTotal /= 10;
			BPM = 60000/runningTotal;
			//clear flag

		}


		if( (signal < thresh ) && (Pulse == true) )
		{   // when the values are going down, the beat is over

		   Pulse = false;                         // reset the Pulse flag so we can do it again
		   amp = P - T;                           // get amplitude of the pulse wave
		   thresh = amp/2 + T;                    // set thresh at 50% of the amplitude
		   P = thresh;                            // reset these for next time
		   T = thresh;
		 }

		 // 2.5 sec without heart beat
		  //reset values


		if( N > 2500)
		{
			thresh = 512;                          // set thresh default
			P = 512;                               // set P default
			T = 512;
			firstBeat = true;
			secondBeat - false;

		}

}

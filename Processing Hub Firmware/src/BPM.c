/*
 * BPM.c
 *
 *  Created on: Jan 29, 2015
 *      Author: B-Chan
 */


#include <stdbool.h>
#include "BPM.h"
#include "tm4c123gh6pm.h"

volatile bool firstBeat = true;
volatile bool secondBeat = false;
volatile int signal = 0; // signal from wristboard adc
volatile int hRate[10]; //sample of
volatile int time;
volatile int BPM = 0;
volatile unsigned long sampleCounter = 0;          // used to determine pulse timing
volatile unsigned long lastBeatTime = 0;           // used to find IBI
volatile int P =512;                      // used to find peak in pulse wave, seeded
volatile int T = 512;                     // used to find trough in pulse wave, seeded
volatile int thresh = 525;                // used to find instant moment of heart beat, seeded


void BPMTimerSetUp()
{
	//TIMER A
	//One-Shot/Periodic Timer Mode
	//The GPTM is configured for One-Shot and Periodic modes by the following sequence:
	///1. Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making
	//any changes.
	TIMER0_CTL |= 0// disable timer A

	//2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000.
	TIMER0_CFG  |= 0x00000000;

	//3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
	//a. Write a value of 0x1 for One-Shot mode.
	//b. Write a value of 0x2 for Periodic mode.
	TIMER0_TAMR   |= 0x2; //count down & periodic

	/*4. Optionally configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
	to select whether to capture the value of the free-running timer at time-out, use an external
	trigger to start counting, configure an additional trigger or interrupt, and count up or down.*/

	/*5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).
	722 June 12, 2014*/
	TIMER0_TAILR  |= 0x20;
}


#pragma vector=TIMER_SYNC_SYNCWT1_TA
//A timeout event for Timer A of
// GPTM 32/64-Bit Timer 1 is
// triggered
BPM()
{
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

			if( (signal > thresh) && (Pulse == false) && (N > (IBI/5)*3 ) )
			{

				Pulse = true ;
				IBI = sampleCounter - lastBeatTime;
				lastBeatTime = sampleCounter;

			}
			if(secondBeat == true)
			{
				secondBeat = false;
				for(int i = 0; i <10; i++)
				{
					hRate[i] = IBI;
				}
			}

			if(firstBeat)
			{
				firstBeat = false;
				secondBeat = true;s
				return;
			}

			int runningTotal = 0;

			for(int i = 0; i <9; i++)
			{
				hRate[i] = hRate[i+1];
				runnin
			}

			hRate[9] = IBI;
			runningTotal  += rate[9];
			runningTotal /= 10;
			BPM = 60000/runningTotal;
			//clear flag

		}


		if (signal < thresh && Pulse == true){   // when the values are going down, the beat is over

		   Pulse = false;                         // reset the Pulse flag so we can do it again
		   amp = P - T;                           // get amplitude of the pulse wave
		   thresh = amp/2 + T;                    // set thresh at 50% of the amplitude
		   P = thresh;                            // reset these for next time
		   T = thresh;
		 }

		/*// 2.5 sec without heart beat
		  //reset values */

		if( N > 2500)
		{
			thresh = 512;                          // set thresh default
			P = 512;                               // set P default
			T = 512;
			firstBeat = true;
			secondBeat - false;

		}
	return BPM;
}

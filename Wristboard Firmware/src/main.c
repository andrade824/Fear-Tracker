/*
 * This code represents the starting point for the wristboard firmware.
 * It initializes any needed hardware, then captures and sends data
 * out to the processing hub.
 *
 * Created: 12/23/2014 6:50:10 PM
 * Author: Devon Andrade
 *
 */ 

#include "config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "uart.h"
#include "timer.h"
#include "accel.h"
#include "i2c.h"

int main(void)
{
	// Setup any needed hardware
	SetupUART(UBRR);
	SetupTimer();
	SetupAccelerometer(FOURG, EIGHTBITS);
	
	// Enable global interrupts
	sei();
	
	// Test data
	struct AccelData data;
	
	while(1)
	{
		if(ready_to_send)
		{
			// Grab the data
			AccelGetData(&data);
			
			// Send the data
			UARTTransmit(data.x);
			UARTTransmit(data.y);
			UARTTransmit(data.z);
			
			// Send some bytes so RealTerm can sync to it
			UARTTransmit('A');
			UARTTransmit('B');
			
			ready_to_send = false;
		}
	}
}
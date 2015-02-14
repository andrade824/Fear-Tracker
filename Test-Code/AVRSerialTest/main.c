/*
 * This code represents the starting point for the wristboard firmware.
 * It initializes any needed hardware, then captures and sends data
 * out to the processing hub.
 *
 * Created: 12/23/2014 6:50:10 PM
 * Author: Devon Andrade
 *
 */ 
#include <stdlib.h>
#include "config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "uart.h"
#include "timer.h"

int main(void)
{
	// Setup any needed hardware
	SetupUART(UBRR);
	SetupTimer();
	
	// Enable global interrupts
	sei();
	
	srand(37);
	
	while(1)
	{
		if(ready_to_send)
		{	
			// Send the data
			UARTTransmit(170);
			UARTTransmit(0);
			UARTTransmit(rand() % 60 + 60);
			UARTTransmit(rand() % 30);
			UARTTransmit(rand() % 100);
			
			ready_to_send = false;
		}
	}
}
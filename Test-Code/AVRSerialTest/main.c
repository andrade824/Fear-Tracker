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
#include "sensors.h"

int main(void)
{
	// Setup any needed hardware
	SetupUART(UBRR);
	SetupTimer();
	
	// Enable global interrupts
	sei();
	
	srand(37);
	
	struct SensorData acceldata;
	SetupAccelerometer(TWOG, EIGHTBITS);
	InitADC();
	SetupPulseSensor();
	uint8_t heart = 0;
	
	while(1)
	{
		if(ready_to_send)
		{	
			AccelGetData(&acceldata);
			
			while(ADCSRA & _BV(ADSC));	//wait for conversion to finish USE RESULT
			
			heart = ADCH;	//save result of pulse sensor
			
			// Send the data
			UARTTransmit(170);
			UARTTransmit(0);
			UARTTransmit(heart);
			UARTTransmit(acceldata.accel_y + 128);
			UARTTransmit(acceldata.accel_z + 128);
			UARTTransmit('A');
			UARTTransmit('B');
			
			ADCSRA |= _BV(ADSC); //Start real conversion
			
			ready_to_send = false;
		}
	}
}
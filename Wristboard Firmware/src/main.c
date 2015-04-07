/*
 * This code represents the starting point for the wristboard firmware.
 * It initializes any needed hardware, then captures and sends data
 * out to the processing hub.
 *
 * Created: 12/23/2014 6:50:10 PM
 * Author: Devon Andrade, Jerome Selig, Beatrix Tarjoto
 *
 */ 
#include "config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "uart.h"
#include "timer.h"
#include "sensors.h"
#include "i2c.h"

int main(void)
{
	// Setup any needed hardware
	SetupUART(8);
	SetupTimer();
	SetupAccelerometer(TWOG, EIGHTBITS);
	InitADC();
	
	// Enable global interrupts
	sei();
	
	PORTB &= ~(_BV(PORTB5));	// Clear PB5, so it drives low by default (need to do this before switching it to an output)
	DDRB |= _BV(PORTB5);		// Set PB5 as an output
	
	// Test data
	struct SensorData data;
	
	while(1)
	{
		if(ready_to_send)
		{
			SetupPulseSensor();
			while(ADCSRA & _BV(ADSC));	//wait for conversion to finish DISCARD RESULT
			ADCSRA |= _BV(ADSC); //Start real conversion
			
			while(ADCSRA & _BV(ADSC));	//wait for conversion to finish USE RESULT
			
			data.pulse_val = ADCH;	//save result of pulse sensor
			_delay_us(9);
			
			SetupGSR();
			while(ADCSRA & _BV(ADSC));	//wait for conversion to finish DISCARD RESULT
			ADCSRA |= _BV(ADSC); //Start real conversion
			
			while(ADCSRA & _BV(ADSC));	//wait for conversion to finish USE RESULT
			
			data.gsr_val = ADCH;	//save result of GSR sensor
			_delay_us(9);
			
			// Grab the accelerometer data
			AccelGetData(&data);
			
			// Send some bytes so RealTerm can sync to it
			UARTTransmit(0xAA);
			UARTTransmit(24);
			// Send the data
			UARTTransmit(data.pulse_val);
			UARTTransmit(data.gsr_val + 15);
			UARTTransmit(data.accel_x + 128);
			UARTTransmit(data.accel_y + 128);
			UARTTransmit(data.accel_z + 128);
			
			UARTTransmit(0); 
			UARTTransmit(0); //to fill the UART receive fifo buffer in the tiva board for interrupt 
			
			
			ready_to_send = false;
		}
	}
}
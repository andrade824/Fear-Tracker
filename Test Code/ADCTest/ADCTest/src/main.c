/*
 * ADCTest.c
 *
 * Created: 11/3/2014 9:56:02 PM
 *  Author: B-Chan
 */ 


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "../inc/config.h"
#include "../inc/UART.h"

void InitADC(void);

int main(void)
{
	const char const * string = "The UART Works!\n\r";
	UARTInit(UBRR);
	int length = strlen(string);

	while(1)
	{
		for(int i = 0; i < length; i++)
		UARTTransmit(string[i]);
	}

	PORTB &= ~(_BV(PORTB5));	// Clear PB5, so it drives low by default (need to do this before switching it to an output)
	DDRB |= _BV(PORTB5);		// Set PB5 as an output
	
	InitADC();
	
    while(1)
   {	 
	   while(ADSC);	//wait for conversion to finish
	   
       if( ADCH >= 1 )	// if there is a converted voltage
		{
			PORTB |= (1<<PORTB5);
			//_delay_ms(500);			// Delay half a second
		}
		else
		{
			PORTB &= ~(1<<PORTB5);						
		
			//_delay_ms(500);			// Delay half a second		
		}
		
   }
	return 0;
}

void InitADC(void)
{
	ADCSRA |= (1<<ADPS0) | (1 << ADPS1) | (1<<ADPS2); // set ADC sample rate to 128 - 62.5kHz @ 8Mhz
	
	ADMUX |= (1<<REFS0) | (1<<REFS1); //internal 1.1v voltage reference  
	
	ADMUX |= (1 << ADLAR); // Left adjust ADC
	ADMUX |= (1 << MUX2); //a2 is input
	
	DIDR0 |= _BV(ADC2D); //disabling digital input for pin A2
	
 	ADCSRA |= _BV(ADEN);//enable ADC
	PRR &= ~(_BV(PRADC)); // Disable the power reduction ADC bit
	ADCSRA |= _BV(ADSC); // start conversion, use this when ADC is in free running mode to start conversion
	//otherwise it is triggered by something
}


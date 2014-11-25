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
	UARTInit(UBRR);
	InitADC();

	PORTB &= ~(_BV(PORTB5));	// Clear PB5, so it drives low by default (need to do this before switching it to an output)
	DDRB |= _BV(PORTB5);		// Set PB5 as an output

    while(1)
   {	 
	   while(ADCSRA & _BV(ADSC));	//wait for conversion to finish
	   
	   UARTTransmit(ADCH);
	   _delay_ms(10);
	   ADCSRA |= _BV(ADSC);
   }
	return 0;
}

void InitADC(void)
{
	ADCSRA |= _BV(ADPS1) | _BV(ADPS2); // set ADC sample rate to - 125kHz @ 8Mhz (div 64 prescaler)
	
	ADMUX |= _BV(REFS0) | _BV(REFS1); //internal 1.1v voltage reference  
	
	ADMUX |= _BV(ADLAR); // Left adjust ADC
	ADMUX |= _BV(MUX0); // a1 is input
	
	DIDR0 |= _BV(ADC1D); //disabling digital input for pin A2
	
 	ADCSRA |= _BV(ADEN);//enable ADC
	PRR &= ~(_BV(PRADC)); // Disable the power reduction ADC bit
	ADCSRA |= _BV(ADSC); // start conversion, use this when ADC is in free running mode to start conversion
	//otherwise it is triggered by something
}


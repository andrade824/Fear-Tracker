/*
 * ADCTest.c
 *
 * Created: 11/3/2014 9:56:02 PM
 *  Author: B-Chan
 */ 


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void InitADC(void);

int main(void)
{
	
	PORTB &= ~(_BV(PORTB5));	// Clear PB5, so it drives low by default (need to do this before switching it to an output)
	DDRB |= _BV(PORTB5);		// Set PB5 as an output
	
	InitADC();
	
    while(1)
   {	  
       if( ADCH // somthing something)
		{
			PORTB |= (1<<PORTB5);
			_delay_ms(500);			// Delay half a second
		}
		else
		{
			PORTB &= ~(1<<PORTB5);						
		
			_delay_ms(500);			// Delay half a second		
		}
		
   }
	return 0;
}

void InitADC(void)
{
	ADCSRA |= (1<<ADPS0) | (1 << ADPS1) | (1<<ADPS2); // set ADC sample rate to 128 - 62.5kHz @ 8Mhz
	
	ADMUX |= (1<<REFS0) | (1<<REFS1); //internal 1.1v voltage reference  
	
	ADMUX |= (1 << ADLAR); // Left adjust ADC
	ADMUX |= (1 << MUX0); //a1 is input
	
 	ADCSRA |= _BV(ADEN);//enable ADC
	ADCSRA |= _BV(ADSC); // start conversion, use this when ADC is in free running mode to start conversion
	//otherwise it is triggered by something
}
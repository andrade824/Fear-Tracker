/*
 * INTERRUPTS.c
 *
 * Created: 11/1/2014 10:44:09 PM
 *  Author: B-Chan
 */

#include <avr/io.h>
#include <avr/interrupt.h> 

void TIMER1_init(void);

int main(void)
{
	PORTB &= ~(_BV(PORTB5));	// Clear PB5, so it drives low by default (need to do this before switching it to an output)
	DDRB |= _BV(PORTB5);//Configure led pin
	
	TIMER1_init();
	
	sei(); //Enable global interrupts, so our interrupt service routine can be called
		//note:  disables interrupts	
    while(1); // infinite loop

	
	return 0;
}
void TIMER1_init(void)
{
	//15.11
	TCCR1B = (1<<WGM12)|(1<<CS12); //Configure timer in Clear Timer on Compare (CTC) Mode.
	OCR1A =  31249; //set count
	TIMSK1  = (1<<OCIE1A); //Enable timer1 interrupts 15.11.8
}

//Timer/Counter1 Capture Event
ISR(TIMER1_CAPT_vect) //interrupt service routine
{
	PINB |= _BV(PORTB5); //toggle pin
}

/*
 * Functions needed to utilize the Timer
 *
 * Created: 12/23/2014 8:07:17 PM
 * Author: Devon
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "timer.h"
#include "uart.h"

/*
* Ok kids, it's story time:
*
* This NEEDS to be "volatile". I spent four god damn hours trying
* to figure out why this code only worked half of the time, only
* to realize that depending on how I coded it, the compiler would 
* optimize out any code with this variable. For some reason, adding debug 
* prints (over the UART) changed the optimization enough to make it 
* work, but if I tried to run it without the UART transmits it would 
* stop working.
*
* If the compiler sees a variable whose value doesn't change, it will
* optimize that variable out of the code. The C standard states that the 
* volatile? keyword should be used in the definition of a variable when 
* there's a chance that the variable's value could change outside the  
* normal flow of execution of the program. And guess what interrupts are?
* That's right! They're code that runs outside the normal flow of execution.
*
* Moral of the story: if you need a global variable to be written and read
* from both interrupts and main code, you NEED to make it volatile so the
* compiler doesn't screw you 10 ways from Sunday without your consent.
*
* - Devon
*/
// Tells the main routine to retrieve and send out data
volatile bool ready_to_send;

/**
* Initializes Timer 1 to trigger an interrupt every 1ms.
*
* Documentation for the timer registers is in section 15.11
* 
* @param none
*
* @return none
*/
void SetupTimer(void)
{
	// Configure timer in Clear Timer on Compare (CTC) Mode, and a divide by 64 prescaler
	TCCR1B = _BV(WGM12)| _BV(CS11) | _BV(CS10); 
	
	// Set cycle count at which to trigger interrupt
	OCR1A = 125;
	
	// Enable timer1 interrupt (section 15.11.8)
	TIMSK1 = _BV(OCIE1A); 
}

/**
* Timer1 Capture Event Interrupt Service Routine
*
* Tells the main routine to start retrieving and sending data.
*/
ISR(TIMER1_COMPA_vect)
{
	ready_to_send = true;
}
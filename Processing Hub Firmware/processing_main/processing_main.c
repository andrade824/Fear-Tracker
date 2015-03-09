#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "driverlib/timer.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "inc\BPM.h"
#include "inc\UART.h"
#include "inc\Accel.h"
#include "inc\ScareScore.h"
#include "inc\Timer.h"

volatile _Bool send_flag;
volatile uint8_t pulse_data;
volatile uint8_t gsr_data;
volatile uint8_t x_data;
volatile uint8_t y_data;
volatile uint8_t z_data;
 int main(void)
{

	// Set clock to 80 Mhz.
	  ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL |
	                     SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);


	// Set the clocking to run directly from the crystal.
	//
	//ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
	  //               SYSCTL_XTAL_16MHZ);


     BPMTimerSetUp();
     Timer1init();
	 UART0init();
	 UART1init();

   // Enable interrupts
   //
   //ROM_IntMasterEnable();


	 while(1)
	 {

		 clearBPMFlag();
		if(send_flag)
		{

			ROM_UARTCharPut( UART0_BASE, 0xAA );

			ROM_UARTCharPut( UART0_BASE, Displacement());
			ROM_UARTCharPut( UART0_BASE, sensor[curr_item].gsr_data);
			ROM_UARTCharPut( UART0_BASE, GetBPM() );
			ROM_UARTCharPut( UART0_BASE, CalcScareScore() );

 			send_flag = false;

		}
	 }
}

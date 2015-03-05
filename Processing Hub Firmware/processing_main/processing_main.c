
#include <stdint.h>
#include <stdbool.h>
#include "inc\BPM.h"
#include "inc\UART.h"
#include "inc\Timer.h"
#include "inc/hw_types.h"
#include "driverlib/timer.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"

volatile _Bool send_flag;
 int main(void)
{

	//
	// Enable lazy stacking for interrupt handlers.  This allows floating-point
	// instructions to be used within interrupt handlers, but at the expense of
	// extra stack usage.
	//
	ROM_FPUEnable();
	ROM_FPULazyStackingEnable();

	// Set clock to 80 Mhz.
	  ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL |
	                     SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);


	// Set the clocking to run directly from the crystal.
	//
	//ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
	  //               SYSCTL_XTAL_16MHZ);


    // BPMTimerSetUp();
    // Timer1init();
	 UART0init();
	 UART1init();

   // Enable interrupts
   //
   //ROM_IntMasterEnable();

	 while(1)
	 {

		//if(send_flag)
//		{

		 	//uint8_t hoopla = GetBPM();
		 	//ROM_UARTCharPut( UART0_BASE, hoopla );
			//ROM_UARTCharPut( UART0_BASE, 'A' );
			//ROM_UARTCharPut( UART0_BASE, 'B' );
			//setFlag(false);
			//send_flag = false;

	//	}
	 }
}

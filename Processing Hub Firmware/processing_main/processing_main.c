
#include <stdint.h>
#include <stdbool.h>
#include "inc\BPM.h"
#include "inc\UART.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"


 int main(void)
{
	 // Setup the system clock to run at 50 Mhz from PLL with crystal reference
	 //
	 SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|
	                     SYSCTL_OSC_MAIN);
	 BPMTimerSetUp();
	 UARTinit();

	 while(1)
	 {
		UARTSend((uint8_t *)GetBPM(), 16);
	 }
}

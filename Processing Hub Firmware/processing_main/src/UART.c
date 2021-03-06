#include "..\inc\UART.h"
#include "../inc/Accel.h"
#include "../inc/BPM.h"

volatile struct sensor_data sensor[MAXITEMS];

volatile int curr_item = 0;

volatile extern _Bool send_flag;

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void
UARTIntHandler(void)
{
	ROM_IntMasterDisable();
	volatile char temp=0;
	volatile int i = 0;
    uint32_t ui32Status;
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
    //
    // Get the interrrupt status.
    //
    ui32Status = ROM_UARTIntStatus(UART1_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    ROM_UARTIntClear(UART1_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //

    if(ROM_UARTCharsAvail(UART1_BASE))
    {
		if( ROM_UARTCharGetNonBlocking(UART1_BASE) == 0xAA )
		{
			if( ROM_UARTCharGetNonBlocking(UART1_BASE) == 24 )
			{
				if(curr_item == MAXITEMS)
				{
					curr_item = 0;
					//send_flag = true;
				}
				sensor[curr_item].pulse_data = ROM_UARTCharGetNonBlocking(UART1_BASE);
				sensor[curr_item].gsr_data = ROM_UARTCharGetNonBlocking(UART1_BASE);
				sensor[curr_item].x_data = ROM_UARTCharGetNonBlocking(UART1_BASE);
				sensor[curr_item].y_data = ROM_UARTCharGetNonBlocking(UART1_BASE);
				sensor[curr_item].z_data = ROM_UARTCharGetNonBlocking(UART1_BASE);

				// Clear out dummy zeroes
				temp = ROM_UARTCharGetNonBlocking(UART1_BASE);
				temp = ROM_UARTCharGetNonBlocking(UART1_BASE);

				if(curr_item == 0) {
					CalcBPM();
					curr_item++;
				} else if(curr_item != 0 && sensor[curr_item].gsr_data >= 10) {
					CalcBPM();
					curr_item++;
				} else
					sensor[curr_item] = sensor[curr_item - 1];

				//send_flag = true;
				//curr_item++;
			}

		}

    }
    /*
    while(ROM_UARTCharsAvail(UART1_BASE))
    {
        sig[0] = ROM_UARTCharGetNonBlocking(UART1_BASE);
    }
	//ROM_UARTCharPutNonBlocking(UART0_BASE, sig[0]);

	for(i = 0; i<5 && ROM_UARTCharsAvail(UART1_BASE);i++)
		{
			sig[i] = ROM_UARTCharGetNonBlocking(UART1_BASE);
			//ROM_UARTCharPutNonBlocking(UART0_BASE, sig[i]);
		}

*/


    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
	ROM_IntMasterEnable();
}

//*****************************************************************************
//
// Send a string to the UART.
//
//*****************************************************************************
void
UART0Send(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        ROM_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}
void
UART1Send(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        ROM_UARTCharPutNonBlocking(UART1_BASE, *pui8Buffer++);
    }
}

void UART1init(void)
{

	//
	// Enable the GPIO port that is used for the on-board LED.
	//
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	//
	// Enable the GPIO pins for the LED (PF2).
	//
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    ROM_SysCtlDelay(3);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    ROM_SysCtlDelay(3);
    //
    // Enable processor interrupts.
    //
    // Set GPIO B0 and A1 as UART pins.
    //
    ROM_GPIOPinConfigure(GPIO_PB0_U1RX);
    ROM_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0| GPIO_PIN_1);
    //
    // Configure the UART for 76800, 8-N-1 operation.
    //
    ROM_UARTConfigSetExpClk(UART1_BASE, ROM_SysCtlClockGet(), 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));
    // Configure FIFO for 1/2th receive full
    ROM_UARTFIFOEnable(UART1_BASE);
    ROM_UARTFIFOLevelSet(UART1_BASE, UART_FIFO_TX4_8,UART_FIFO_RX4_8);

    //UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);

    ROM_IntEnable(INT_UART1);
    ROM_UARTIntEnable(UART1_BASE, UART_INT_RX);

}

void UART0init()
{
	//
	// Enable the UART interrupt.
	//
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0); //enable uart port
	SysCtlDelay(3);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); //enable gipoA pins
	SysCtlDelay(3);
	GPIOPinConfigure(GPIO_PA1_U0TX); //set tx pin
	ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_1);
	ROM_UARTConfigSetExpClk(UART0_BASE, (ROM_SysCtlClockGet()), 115200,
							  (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
							   UART_CONFIG_PAR_NONE) );

	  //UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
}

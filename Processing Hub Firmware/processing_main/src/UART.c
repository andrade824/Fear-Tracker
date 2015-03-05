#include "..\inc\UART.h"
volatile uint8_t sig[7];

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void
UARTIntHandler(void)
{
    uint32_t ui32Status;
    volatile uint8_t temp[7];
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

    int i = 0;
    while( (temp[6] != 66) && (temp[5] != 65) )
    {
		for(i = 0; i<7 && ROM_UARTCharsAvail(UART1_BASE);i++)
		{
			temp[i] = ROM_UARTCharGetNonBlocking(UART1_BASE);
			ROM_UARTCharPutNonBlocking(UART0_BASE, temp[0]);
		}
		if((temp[6] != 66) && (temp[5] != 65))
		SysCtlDelay(1000);
    }


    for(i = 0; i<7; i++)
    	sig[i] = temp[i];
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
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlDelay(3);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlDelay(3);
    //
    // Enable processor interrupts.
    //
    // Set GPIO B0 and A1 as UART pins.
    //
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    ROM_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0| GPIO_PIN_1);
    //
    // Configure the UART for 38400, 8-N-1 operation.
    //
    ROM_UARTConfigSetExpClk(UART1_BASE, ROM_SysCtlClockGet(), 38400,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));
    // Configure FIFO for 1/4th full
    //UARTFIFOLevelSet(UART1_BASE, UART_FIFO_TX2_8, UART_FIFO_RX2_8);S
    //

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

uint8_t GetSig()
{
	return sig[0];
}


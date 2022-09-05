//include definitions for xilinx's vector table and functions relevant to it
#include "xil_exception.h"
#define ICCIAR *((uint32_t *) 0xF8F0010C)
#define ICCEOIR *((uint32_t *) 0xF8F00110)

//Interrupt ID definitions
#define GTC_INT_ID 27
#define GPIO_INT_ID 52

void interrupt_handler(void)
{

	uint32_t id;
	id = ICCIAR;
	switch(id)
		{
			case GTC_INT_ID:	//Global Timer interrupt
				//code for GTC Interrupt Service goes here
				break;


			case GPIO_INT_ID:	//interrupt ID 52 (GPIO)



				break;


			default:
				//other interrupts
				break;

		}

	ICCEOIR = id;	//acknowledge end of interrupt by giving it the id

	return;

}

void register_my_irq_handler(void) //registers the above defined function to xilinx's table
{
	//this register's the interrupt handler to the 6th entry in Xilinx's table
	Xil_ExceptionRegisterHandler(5, interrupt_handler, NULL);

}

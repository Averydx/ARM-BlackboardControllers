#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

//All necessary registers for uart1
#define UARTControl	0xE0001000
#define UARTMode 0xE0001004
#define BAUDGEN 0xE0001018
#define BAUD_DIV 0xE0001034
#define UART_SR 0xE000102C
#define UART1_DATA 0xE0001030
#define UART_IMR 0xE0001010


//reads data from the transmit/receive fifo and returns it
uint32_t uart1_readchar()
{

	uint32_t*  uart_data = (uint32_t*)UART1_DATA;

	uint32_t n = *uart_data;

	return n;
}

//writes a char to the transmit/receive fifo
void uart1_putchar(uint32_t ascii)
{
	uint32_t* SR = (uint32_t*)UART_SR;


	uint32_t* uart_data = (uint32_t*)UART1_DATA;
	//wait for room in transmit fifo



	while((*SR & 0b10000) != 0)
	{
		//poll until transmit empty
	}

	//write to transmit fifo
	*uart_data = ascii;
}


//if a char is read on the fifo, sends it back out
void uart1_echo()
{
	uint32_t data = uart1_readchar();
	if(data != 0)
	{
	uart1_putchar(data);
	}
}




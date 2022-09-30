
//All necessary registers for uart1
#define UART1_IER	*((uint32_t *) 0xE0001008)
#define UART1_IDR	*((uint32_t *) 0xE000100C)
#define UART1_ISR	*((uint32_t *) 0xE0001014)
#define UART1_RXTG	*((uint32_t *) 0xE0001020)

#define UARTControl	0xE0001000
#define UARTMode 0xE0001004
#define BAUDGEN 0xE0001018
#define BAUD_DIV 0xE0001034
#define UART_SR 0xE000102C
#define UART1_DATA 0xE0001030
#define UART_IMR 0xE0001010

//TODO, removed references to the interrupt flags, do more research


void uart1_config()
{
	//masks bits to enable interrupts
	uint32_t* IMR = (uint32_t*)UART_IMR;
	*IMR = 0b1111111111111;

	//mode register, sets the character length, start/stop bits, and parity bits
	uint32_t* MR = (uint32_t*)UARTMode;
	*MR |= 0b00100000;

	//The bauddiv and baudgen registers, set the clock speed
	uint32_t* BG = (uint32_t *)BAUDGEN;
	uint32_t* BD = (uint32_t *)BAUD_DIV;
	*BG = 124;
	*BD = 6;

}

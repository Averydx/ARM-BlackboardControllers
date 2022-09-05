#include <stdint.h>

//Clock config register
#define TTCO_CLKCNT_X 0xf8001000

//Clock mode config
#define TTCO_CNTL_X 0xf800100c

//maximum value counter will count to before reset
#define TTCO_INTVAL_X 0xf8001024

//counter value
#define TTCO_CNTVAL_X 0xf8001018

//interrupt enable
#define TTCO_IER_X 0xf8001060

//interrupt status
#define TTCO_ISR_X 0xf8001054

void TTCIntervalSetup(uint32_t prescale)
{
	uint32_t* configReg = (uint32_t*)TTCO_CLKCNT_X;
	prescale = prescale << 1;
	prescale |= 0x1;

	*configReg = prescale;

	uint32_t* modeReg = (uint32_t*)TTCO_CNTL_X;
	*modeReg = 0xA;

	uint32_t* maxVal = (uint32_t*)TTCO_INTVAL_X;
	*maxVal |= 0b1111;

	uint32_t* ISREnable = (uint32_t*)TTCO_IER_X;
	*ISREnable = 0x1;

}

//returns the current value of the counter
uint32_t giveCount()
{
	uint32_t* countVal = (uint32_t*)TTCO_CNTVAL_X;
	return *countVal;
}

uint32_t ISRCheck()
{
	uint32_t* ISRStatus = (uint32_t*)TTCO_ISR_X;
	if ((*ISRStatus & 0x1) == 1)
	{
		return 1;
	}

	return 0;
}


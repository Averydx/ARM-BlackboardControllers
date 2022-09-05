#define MIO_PIN_16 0xF8000740
#define MIO_PIN_17 0xF8000744
#define MIO_PIN_18 0xF8000748
#define MIO_PIN_50 0xF80007C8
#define MIO_PIN_51 0xF80007CC
#define GPIO_DIRM_0 0xE000A204 // Direction mode bank 0
#define GPIO_OUTE_0 0xE000A208 // Output enable bank 0
#define GPIO_DIRM_1 0xE000A244 // Direction mode bank 1

#include <stdint.h>

void configureMIOpins()
{
	/*
	 * Write unlock code to enable writing
	 * into System Level Control Unlock Register
	 */
	*((uint32_t *) 0xF8000000+0x8/4) = 0x0000DF0D;
	// Configure MIO pins
	*((uint32_t*) MIO_PIN_50) = 0x00000600; // BTN4
	*((uint32_t*) MIO_PIN_51) = 0x00000600; // BTN5
	*((uint32_t*) MIO_PIN_16) = 0x00001600; // RGB_LED_B
	*((uint32_t*) MIO_PIN_17) = 0x00001600; // RGB_LED_R
	*((uint32_t*) MIO_PIN_18) = 0x00001600; // RGB_LED_G

	*((uint32_t*) GPIO_DIRM_0) = 0x00070000;
	*((uint32_t*) GPIO_OUTE_0) = 0x00070000;

	*((uint32_t*) GPIO_DIRM_1) = 0x00000000;
}




#include <stdint.h>
#include "sevenseg.h"
#include "TTC.h"
#include "GICConfig.h"
#include "IRQHandlers.h"
#include "MIOConfig.h"

int main()
{


	SevenSegEnable();

	TTCIntervalSetup(9999);

	disable_interrupts();
	register_my_irq_handler();
	configureMIOpins();
	configure_GIC_interrupt52();
	enable_interrupts();

	while(1);

}

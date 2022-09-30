#include <stdint.h>
#include "sevenseg.h"
#include "uart1config.h"
#include "uartFunctions.h"
#include "TTC.h"

//switch data register, each bit corresponds to on/off state of the switch
#define SW_DATA *((uint32_t*) 0x41220000)
//button data register, each bit corresponds to pressed state
#define BUTTON_DATA *((uint32_t*) 0x41200000)

//for interval, higher values slow down the counter
//for countTo, the number is the decimal number to count to



void Count(int interval,int countType, int countTo)
{
	for(int i = 0; i<countTo;i++)
			{

				int intervalCheck = 0;
				while(intervalCheck <interval)
				{
					if(ISRCheck() == 1)
					{
						intervalCheck += 1;
					}
				}

				if((SW_DATA & 0x2) == 0x2)
				{
					countType = 1;
				}

				else
				{
					countType = 0;
				}

				if(countType == 0)
					display_num_bcd(i);
				else
					display_num_hex(i);

			//pause if the switch is set to zero at any time
			while((SW_DATA & 0x1) == 0)
			{
				if((BUTTON_DATA & 0x1) == 0x1)
				{
					display_num_bcd(0);
					return;
				}
			}
			}
}


int main()
{
	SevenSegEnable();
	uart1_config();
	TTCIntervalSetup(9);

	while(1)
	{
		if((SW_DATA & 0x1) == 1)
		Count(1000,1,9999);
	}
}




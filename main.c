#include <stdint.h>
#include "sevenseg.h"
#include "uart1config.h"
#include "uartFunctions.h"
#include "TTC.h"

#define GPIO_INT_STAT_1 0xE000A258

//for interval, higher values slow down the counter
//for countType, 1 is hex, 0 is bcd
//for countTo, the number is the decimal number to count to
void Count(int interval, int countType, int countTo)
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

				if(countType == 0)
					display_num_bcd(i);
				else
					display_num_hex(i);
			}
}

int main()
{
	SevenSegEnable();
	uart1_config();
	TTCIntervalSetup(9);
	while(1)
	{
		Count(100,1,9999);
	}
}




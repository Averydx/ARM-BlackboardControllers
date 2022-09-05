//Enable the seven segment display
#define SEVEN_SEG_ENABLE 0x43C10000
#define SEVEN_SEG_DATA 0x43C10004

//flips the enable bit in 0x43c100000
void SevenSegEnable()
{
	uint32_t* enable = (uint32_t*)SEVEN_SEG_ENABLE;
	*enable = 0x1;

}

//converts a given decimal value to bcd
uint32_t dec2bcd(uint16_t dec)
{
    uint32_t result = 0;
    int shift = 0;

    while (dec)
    {
        result += (dec % 10) << shift;
        dec = dec / 10;
        shift += 4;
    }
    return result;
}

//displays a number on the seven segment display
void display_num(uint32_t n)
{

	uint32_t* seg_data = (uint32_t*)SEVEN_SEG_DATA;
	uint32_t temp = 0;
	uint32_t j = dec2bcd(n);


	for(int i = 0; i < 4; i++)
	{
		temp |= (j&0xf) << (i *8);
		j >>= 4;

	}

	*seg_data = temp;
	//clears the decimal places
	*seg_data |= 0x80808080;
	return;
}

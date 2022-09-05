#include <stdint.h>
//definitions for GIC configuration regisjters
#define ICCPMR		*((uint32_t *) 0xF8F00104)		//Priority mask reg
#define ICCICR		*((uint32_t *) 0xF8F00100)		//CPU interface control reg
#define ICDDCR		*((uint32_t *) 0xF8F01000)		//Distributor Control reg
#define ICDISER(n)	*(((uint32_t *) 0xF8F01100) + n )	//Int. set enable reg
#define ICDICER(n)	*(((uint32_t *) 0xF8F01180) + n )	//Int. Clear Enable reg
#define ICDIPR(n)	*(((uint32_t *) 0xF8F01400) + n )	//Int. Priority reg
#define ICDIPTR(n)	*(((uint32_t *) 0xF8F01800) + n )	//Int. Processor Targets reg
#define ICDICFR(n)	*(((uint32_t *) 0xF8F01C00) + n )	//Int. Configuration reg

void disable_interrupts()
{
	uint32_t cpsr_val = 0;
	__asm("mrs %0, cpsr\n" : "=r" (cpsr_val) );	//get current cpsr

	//enable bit 7
	cpsr_val |= 0x80;

	__asm("msr cpsr, %0\n" :: "r"(cpsr_val)); //use restricted instruction msr to set the cpsr register
	return;

}

void enable_interrupts()
{
	uint32_t cpsr_val = 0;
	__asm("mrs %0, cpsr\n" : "=r" (cpsr_val) );	//get current cpsr
	cpsr_val &= 0xFFFFFF7F;	//clear bit 7
	__asm("msr cpsr, %0\n" :: "r"(cpsr_val)); //use restricted instruction msr to set the cpsr register
	return ;

}

//disable GIC distributor
void disable_gic_dist() { (ICDDCR = 0); }

//Drive IRQ from the GIC
void disable_IRQ_passthrough() { (ICCICR =0x3); }

//sets the GIC priority mask to ‘priority’
void set_gic_pmr(uint32_t priority) { ICCPMR = (priority & 0xFF); }

//enables GIC distributor
void enable_gic_dist() { (ICDDCR = 1); }

//disables interrupt ID 27
void disable_interrupt52(void)
{
	ICDIPTR(13) &= ~0x3; //remove processors from interrupt
	ICDICER(1) = 0x00100000; //disable interrupts from GPIO module
}

//enables interrupt 52
void enable_interrupt52()
{
	ICDIPTR(13) |= 1; //set bit 1 of ICDIPTR13 (enable for cpu0)
	ICDISER(1) = 0x00100000;
}

//sets the interrupt priority of 52 to ‘priority_val’
void set_interrupt52_priority(uint8_t priority_val)
{
	ICDIPR(13) &= ~0xFF; //clear priority bits for interrupt 52
	ICDIPR(13) |= (priority_val) & 0xF8; //set top 5 bits based on passed value
}

//sets interrupt sensitivity of interrupt52 to ‘sens’
void set_interrupt52_sensitivity(uint8_t sens)
{
	ICDICFR(3) &= ~0x300;
	ICDICFR(3) |= (sens&0x3)<<8;
}

void configure_GIC_interrupt52(void)
{

	//disable and configure GIC
	disable_gic_dist(); //disable GIC interrupt generation
	disable_IRQ_passthrough();	//drive IRQ from GIC

	set_gic_pmr(0xFF); //set priority mask

	//disable and configure interrupt 52
	disable_interrupt52();
	set_interrupt52_priority(0xA0); //set 52’s priority to 160
	set_interrupt52_sensitivity(1); //set to high level

	enable_interrupt52();	//reenable interrupt52

	enable_gic_dist();		//reenable distributor

}









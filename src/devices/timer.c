#include "devices/timer.h"
#include "interrupts.h"
#include "printf.h"

void ack_timer_irq(int cmp_no)
{
	uint32_t timer_cs = REG_GET(TIMER_CS, uint32_t);
	timer_cs |= 1 << cmp_no;
	REG_SET(TIMER_CS, uint32_t, timer_cs);
}



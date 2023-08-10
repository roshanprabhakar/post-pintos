#include "devices/mini-uart.h"
#include "devices/timer.h"
#include "interrupts.h"
#include "printf.h"
#include "mem.h"
#include "bitmap.h"
#include "string.h"

void halt(void);

extern uint8_t kernel_end;
extern uint8_t end_addr;

void entry_l2()
{
	mini_uart_enable();
	irq_init();
	mem_init();
	
	// Increment timer.
	// uint32_t a = REG_GET(TIMER_CLO, uint32_t);
	// REG_SET(TIMER_C1, uint32_t, a + 1000000);

	// asm volatile("svc #6");

	printf("main end reached.");

	halt();
}

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

	/*
	// Test bitmap.
	struct bitmap m = 
		{
			.map_start = (void *) &kernel_end,
			.map_size = 16UL
		};

	(&kernel_end)[0] = (uint64_t) -1;

	dump((void *) &kernel_end, 16);
	*/
	
	
	// Increment timer.
	// uint32_t a = REG_GET(TIMER_CLO, uint32_t);
	// REG_SET(TIMER_C1, uint32_t, a + 1000000);

	// asm volatile("svc #6");

	printf("main end reached.");

	halt();
}

#include "devices/mini-uart.h"
#include "devices/timer.h"
#include "interrupts.h"
#include "printf.h"
#include "mem.h"
#include "bitmap.h"
#include "string.h"

void halt(void);
int practice_writing_assembly(int arg1, int arg2, int arg3);

extern uint8_t kernel_end;
extern uint8_t end_addr;

void __attribute__((naked)) entry_l2()
{
	mini_uart_enable();
	irq_init();
	mem_init();
  
  int arg1 = 5;
  int arg2 = 4;
  int arg3 = 3;
  int ret = practice_writing_assembly(arg1, arg2, arg3);

  printf("\n\narg1: %d, arg2: %d, arg3: %d, ret: %d\n\n", arg1, arg2, arg3, ret);

	printf("main end reached.\n");

	halt();
}

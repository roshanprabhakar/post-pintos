#include "interrupts.h"
#include "devices/timer.h"
#include "boot_lib.h"
#include "printf.h"


/* Responsible for verifying that the irq registers start zero'd out.
 * Also responsible for starting the system timer associated irq.
 */
void irq_init()
{
	uint32_t irq_basic_pending = REG_GET(IRQ_BASIC_PENDING, uint32_t);

	if (irq_basic_pending != 0)
		{
			printf("ATTN: Basic pending register not cleared. reg: %x\n", irq_basic_pending);
      goto fail;
		}
	
	// Enable system timer compare registers 1 and 3 (2 and 4 cannibalized by gpu).
	REG_SET(ENABLE_IRQ_1, uint32_t, (2 | 8));

	uint32_t old = REG_GET(TIMER_CLO, uint32_t);
	uint32_t new;
	for (int i = 0; i < 3000; ++i)
		{
			if (i % 1000 == 0)
				{
					new = REG_GET(TIMER_CLO, uint32_t);
					if (old == new)
						{
							printf("ATTN: Timer is not running.\n");
              goto fail;
						}
				}
		}
  return;

fail:
  printf("Interrupt init failed, halting core.\n");
  halt();

}

void general_exception_handler(uint32_t type, uint64_t currentel, uint64_t esr, uint64_t elr)
{
	printf("exception handler entered!\n");

	uint32_t irq_basic_pending = REG_GET(IRQ_BASIC_PENDING, uint32_t);
	if (irq_basic_pending & (1 << 8))
		{
			uint32_t irq_pending_1 = REG_GET(IRQ_PENDING_1, uint32_t);
			if (irq_pending_1 & 2)
				{
					uint32_t timer_cs = REG_GET(TIMER_CS, uint32_t);
					ack_timer_irq(1);
					printf("timer irq cmp 1 triggered and acknowledged.\n");
				}
			
			if (irq_pending_1 & 8)
				{
					uint32_t timer_cs = REG_GET(TIMER_CS, uint32_t);
					ack_timer_irq(3);
					printf("timer irq cmp 3 triggered and acknowledged.\n");
				}

			irq_pending_1 &= !((1 << 1) | (1 << 3));

			if (irq_pending_1)
				{
					printf("remaining irqs, irq pending 1 reg: ");
					for (int i = 0; i < 32; ++i)
						{
							printf("%d", irq_pending_1 & 1);
							irq_pending_1 >>= 1;
						}
				}
		}
	
	irq_basic_pending &= !(1 << 8);

	if (irq_basic_pending != 0)
		{
			printf("remaining irqs, basic pending reg: ");
			for (int i = 0; i < 32; ++i)
				{
					printf("%d", irq_basic_pending & 1);
					irq_basic_pending >>= 1;
				}
			printf("\n");
		}

}

void unknown_interrupt_level_handler(uint32_t type, uint64_t currentel)
{
  printf("Jumped into an unrecognizable exception level.\n");
	halt();
	return;
}

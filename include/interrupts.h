#ifndef _INTERRUPTS_
#define _INTERRUPTS_

#include <stdint.h>

#include "devices/devices.h"

#define INTR_REG MMIO_BASE + 0xB000

#define IRQ_BASIC_PENDING (INTR_REG + 0x200)
#define IRQ_PENDING_1 (INTR_REG + 0x204)
#define IRQ_PENDING_2 (INTR_REG + 0x208)
#define FIQ_CONTROL (INTR_REG + 0x20C)
#define ENABLE_IRQ_1 (INTR_REG + 0x210)
#define ENABLE_IRQ_2 (INTR_REG + 0x214)
#define ENABLE_BASIC_IRQ (INTR_REG + 0x218)
#define DISABLE_IRQ_1 (INTR_REG + 0x21C)
#define DISABLE_IRQ_2 (INTR_REG + 0x220)
#define DISABLE_BASIC_IRQ (INTR_REG + 0x224)

void irq_init(void);

void general_exception_handler(uint32_t type, uint64_t currentel, uint64_t esr, uint64_t elr);
void unknown_interrupt_level_handler(uint32_t type, uint64_t currentel);

#endif // _INTERRUPTS_


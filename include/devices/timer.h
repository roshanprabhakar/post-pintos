#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>
#include "devices/devices.h"

#define TIMER_BASE (MMIO_BASE + 0x00003000)

// [3] timer match with C3.
// [2] timer match with C2.
// [1] timer match with C1.
// [0] timer match with C0.
// These are not cleared on read,
// must be manually reset.
#define TIMER_CS (TIMER_BASE + 0x0)

// [31..0] low 32 bits of the running counter.
#define TIMER_CLO (TIMER_BASE + 0x4)

// [31..0] high 32 bits of the running counter.
#define TIMER_CHI (TIMER_BASE + 0x8)

// Compare registers against TIMER_CLO.
// If TIMER_CLO matches a value in any of these registers,
// an irq is generated.
#define TIMER_C0 (TIMER_BASE + 0xC)
#define TIMER_C1 (TIMER_BASE + 0x10)
#define TIMER_C2 (TIMER_BASE + 0x14)
#define TIMER_C3 (TIMER_BASE + 0x18)

#define GET_TIMER_LO (REG_GET(TIMER_CLO, uint32_t))
#define GET_TIMER_HI (REG_GET(TIMER_CHI, uint32_t))
#define GET_TIMER (REG_GET(TIMER_CLO, uint64_t))

void ack_timer_irq(int);

#endif // _TIMER_H_

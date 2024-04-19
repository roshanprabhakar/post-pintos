#ifndef _MEM_H_
#define _MEM_H_

#include <stdint.h>

// bitfields over ID_AA64MMFR0_EL1: memory model and management information.
#define TGRAN4 (15UL << 27)           // Support for 4KB memory translation granule size (page size).
#define PG_SIZE_4K_SUPPORTED (0)
#define PG_SIZE_4K_UNSUPPORTED TGRAN4

#define PA_RANGE (5U)                  // Query bits for address width.
#define BITWIDTH_32 (0)
#define BITWIDTH_36 (1)
#define BITWIDTH_40 (2)

void mem_init(void);

void *palloc(int);
void pfree(void *);

#endif // _MEM_H_

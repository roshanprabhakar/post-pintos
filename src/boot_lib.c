
#include <stdint.h>

#include "boot_lib.h"
#include "string.h"

extern int bss_start;
extern int bss_end;

void *clear_bss()
{
	uint64_t bss_size = (uint64_t) &bss_end - (uint64_t) &bss_start;
	if (bss_size % 4) return 0x0;

	return memset((void *) &bss_start, (uint32_t) 0, bss_size);
}

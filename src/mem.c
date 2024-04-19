#include <stdint.h>

#include "mem.h"
#include "printf.h"
#include "bitmap.h"
#include "boot_lib.h"

#define PAGE_SIZE 4096ULL

extern uint8_t kernel_end;
extern uint8_t end_addr;
void *map_end;

// Struct lives in bss, map lives in contiguous memory
// right after kernel code.
static struct bitmap mem_map;

static inline void *idx_to_ptr(int idx)
{
	return (void *) (idx * PAGE_SIZE + (uint64_t) &kernel_end);
}

static inline int ptr_to_idx(void *ptr)
{
	return ((uint64_t) ptr - (uint64_t) &kernel_end) / PAGE_SIZE;
}

void mem_init()
{
  uint64_t mm_details;
  asm volatile("mrs %0, ID_AA64MMFR0_EL1" : "=r" (mm_details));

  if (mm_details & TGRAN4 == PG_SIZE_4K_UNSUPPORTED) goto fail;
  int8_t pa_range = mm_details & PA_RANGE;
  if (pa_range == BITWIDTH_32) { printf("4GB physical address range supported.\n"); }
  if (pa_range == BITWIDTH_36) { printf("64GB physical address range supported.\n"); }
  if (pa_range == BITWIDTH_40) { printf("1TB physical address range supported.\n"); }

  printf("%ld\n", &end_addr);
  
  uint64_t pages_available = ((uint64_t) (&end_addr - &kernel_end)) / PAGE_SIZE;
  uint64_t page_map_size = (pages_available + 4096 * 8) / (1 + 4096 * 8);
  map_end = (int8_t *) &kernel_end + page_map_size * PAGE_SIZE;

  printf("pages available: %ld\n", pages_available - page_map_size);

  mem_map.map_start = (int8_t *) &kernel_end;
  mem_map.num_entries = pages_available - page_map_size;
	init_bitmap(&mem_map);

  return;
fail:
  printf("ATTN: Failed to initialize memory system, halting core.\n");
  halt();
}

// Returns a pointer to the first page of n contiguous
// allocated pages.
void *palloc(int n)
{
	int idx = bitmap_scan_and_flip(&mem_map, n, true);
	if (idx == -1)
		{
			printf("palloc error: memory store depleted.\n");
			return 0x0;
		}
	return idx_to_ptr(idx);
}

void pfree(void *ptr)
{
	bitmap_clear(&mem_map, ptr_to_idx(ptr));
}

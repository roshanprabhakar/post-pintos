#include <stdint.h>

#include "mem.h"
#include "printf.h"
#include "bitmap.h"

#define PAGE_SIZE 4096ULL

extern uint8_t kernel_end;
extern uint8_t end_addr;

// Struct lives in bss, map lives in contiguous memory
// right after kernel code.
static struct bitmap mem_map;

void mem_init()
{
	printf("-----------------------------\n");
	printf("Initializing page allocator..\n");

	// Size of remaining memory in bytes.
	uint64_t mem_size = (uint64_t) &end_addr - (uint64_t) &kernel_end;
	printf("Total usable memory: %llu\n", mem_size);

	// Number of maps that can be represented by the memory map.
	uint64_t num_mappable_pages = mem_size / (PAGE_SIZE + 1);
	printf("Total mappable pages: %llu\n", num_mappable_pages);

	mem_map.map_start = (void *) &kernel_end;
	mem_map.num_entries = num_mappable_pages;

	init_bitmap(&mem_map);

	// Mark memory map pages as in use.
	uint64_t memmap_size_bytes = (num_mappable_pages + 7) / 8;
	uint64_t memmap_size_pages = (memmap_size_bytes + PAGE_SIZE - 1) / PAGE_SIZE;

	printf("Bitmap size:  bytes_%llu_  pages_%llu_\n", 
			memmap_size_bytes, memmap_size_pages);

	for (uint64_t i = 0; i < memmap_size_pages; ++i)
		{
			bitmap_set(&mem_map, i);
		}

	printf("Page allocator initialized...\n");
	printf("-----------------------------\n");
}

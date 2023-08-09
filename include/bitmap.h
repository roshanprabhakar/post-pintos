#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <stdint.h>
#include <stdbool.h>

struct bitmap
{
	void *map_start;
	uint64_t num_entries;
};

// Expects a filled bitmap struct. Expects enough memory
// to be free at the struct's internally stored address.
void init_bitmap(struct bitmap *);

// Sets a bit in the bitmap to true. Returns the old value
// of the bit.
int bitmap_set(struct bitmap *, uint64_t);

// int scan_and_flip(struct bitmap *, int n, bool flip);

#endif // _BITMAP_H_

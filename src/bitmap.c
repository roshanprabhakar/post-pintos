
#include "bitmap.h"
#include "string.h"

static const uint64_t bitmap_cmp = (uint64_t) -1;

void init_bitmap(struct bitmap *map)
{
	memset(map->map_start, 0, map->num_entries / 8 + 1);
}

// Mark a specific bit in the map. Returns the old
// value of the bit.
int bitmap_set(struct bitmap *map, uint64_t idx)
{
	uint8_t bt = *((char *) map->map_start + idx / 8);
	int ret = (bt & (1 << (idx % 8))) > 0;
	bt |= 1 << (idx % 8);
	*((char *) map->map_start + idx / 8) = bt;
	return ret;
}

/* Scan the map for n contiguous 0's. If found,
 * flip. Returns the index into the map. Flips the
 * selected bits if flip is true. n must be le 32. */
/*
int scan_and_flip(struct bitmap *map, int n, bool flip)
{
	if (n > 32) return -1;

	register uint32_t *const map_ref = (uint32_t *) map->map_start;

	uint64_t buf;
	register uint32_t *const buf_ref = (uint32_t *) &buf;

	register uint32_t cmp;

	buf_ref[0] = map_ref[0];
	
	int num_grabs = map->map_size >> 2; // / sizeof(uint32_t);
	if (num_grabs > UINT32_MAX) return -1;

	for (uint32_t i = 1; i < num_grabs; ++i)
		{
			buf_ref[1] = map_ref[i];
			cmp = (1U << n) - 1;
			
			for (int j = 0; j < sizeof(uint32_t) * 8 - n; ++j)
				{
					if (cmp & ~buf == cmp) 
						{	
							if (flip)
								{
									buf |= cmp;
									*(uint64_t *)(map_ref + i - 1) = buf;
								}
							return i * sizeof(uint64_t) * 8 + j;
						}
					cmp <<= 1;
				}

			buf_ref[0] = buf_ref[1];
		}

	return -1;
}
*/

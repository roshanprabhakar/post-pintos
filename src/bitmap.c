#include "bitmap.h"
#include "string.h"

static const uint64_t bitmap_cmp = (uint64_t) -1;

void init_bitmap(struct bitmap *map)
{
	memset(map->map_start, 0, map->num_entries / 8 + 1);
}

// Mark a specific bit in the map. Returns the old
// value of the bit.
void bitmap_set(struct bitmap *map, uint64_t idx)
{
	*((char *) map->map_start + idx / 8) |= 1 << (idx % 8);
}

void bitmap_clear(struct bitmap *map, uint64_t idx)
{
	*((char *) map->map_start + idx / 8) &= ~(1 << (idx % 8));

}

// Scan the map for n contiguous 0's. If found,
// flip. Returns the index into the map. Flips the
// selected bits if flip is true. n must be le 32.
int bitmap_scan_and_flip(struct bitmap *map, int n, bool flip)
{
	if (n > 32) return -1;

	register uint32_t *const map_ref = (uint32_t *) map->map_start;

	uint64_t buf;
	register uint32_t *const buf_ref = (uint32_t *) &buf;

	register uint64_t cmp;
	buf_ref[0] = map_ref[0];
	
	for (uint32_t i = 1; i < map->num_entries / 32; ++i)
		{
			buf_ref[1] = map_ref[i];
			cmp = (1LU << n) - 1;

			for (uint32_t j = 0; j < 64 - n + 1; ++j)
				{
					if ((cmp & ~buf) == cmp)
						{
							if (flip)
								{
									buf |= cmp;
									*(uint64_t *)(map_ref + i - 1) = buf;
								}
							return (i - 1) * 32 + j;
						}
					cmp <<= 1;
				}
			buf_ref[0] = buf_ref[1];
		}

	return -1;
}


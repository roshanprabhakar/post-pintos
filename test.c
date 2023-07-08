#include <stdint.h>

int test(uint64_t x0)
{
	if (x0 & 3) return 5;
	return 6;
	if (!(x0 & (1L<<30)))
		{
			int x = 5;
			(void) x;

			if (x0 & 3 == 0)
				{
					return 5;
				}
		}
}

void here()
{
	int a = 10;
	(void) a;
}

int main()
{
	test(0);
	test(~(0UL));
}

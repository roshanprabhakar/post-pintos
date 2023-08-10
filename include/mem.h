#ifndef _MEM_H_
#define _MEM_H_

#include <stdint.h>

void mem_init(void);

void *palloc(int);
void pfree(void *);

#endif // _MEM_H_

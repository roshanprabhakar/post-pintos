#ifndef _DEVICES_H_
#define _DEVICES_H_

#include <stdint.h>

#define MMIO_BASE 0x3F000000

// register a bit clear i
#define REG_BIC(a, regtype, b) (*(volatile regtype*) (a) &= ~(((regtype) 1) << (b)))

// get value at register a
#define REG_GET(a, regtype) (*(volatile regtype*) (a))

// register a set value v
#define REG_SET(a, regtype, v) (*(volatile regtype*) (a) = (v))

// register a bit set i
#define REG_BIS(a, regtype, b) (*(volatile regtype*) (a) |= (((regtype) 1) << (b)))

#endif // _DEVICES_H_

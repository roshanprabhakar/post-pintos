#ifndef _DEVICE_AUXILARIES_H_
#define _DEVICE_AUXILARIES_H_

#include "devices/devices.h"

// [2] SP2 has an interrupt pending
// [1] SP1 has an interrupt pending
// [0] mini_uart has an interrupt pending
#define AUXIRQ (MMIO_BASE + 0x00215000)

// [2] SPI_2 is enabled, else disabled
// [1] SPI_1 is enabled, else disabled
// [0] mini_uart is enabled, else disabled
#define AUX_ENB (MMIO_BASE + 0x00215004)

#endif // _DEVICE_AUXILARIES_H_

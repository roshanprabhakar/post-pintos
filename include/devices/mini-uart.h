#ifndef _MINI_UART_H_
#define _MINI_UART_H_

#include "devices/devices.h"

#define MUART_BASE (MMIO_BASE + 0x00215000)

// read byte 1: read from receive fifo, write byte 1: 
// write to transmit fifo.
#define AUX_MU_IO_REG (MUART_BASE + 0x40)	

// [2,3] = 1 to enable interrupts, [1] = 1 interrupt generated
// when transmit fifo is empty. [0] = 1 interrupt generated if the
// receive fifo holds at least 1 byte.
#define AUX_MU_IER_REG (MUART_BASE + 0x44)

// [7,6] indicates fifo enabled. Always 1, as fifo always enabled.
// [2,1] read
// 	= 00: no interrupts
// 	= 01: transmit register empty
// 	= 10: receiver holds valid byte
// 	= 11: not possible
// [2,1] write [1] clears the receive fifo,
// write [2] clears the transmit fifo.
// [0] = 0 whenever an interrupt is pending.
#define AUX_MU_IIR_REG (MUART_BASE + 0x48)

// [7] = 1 provides access to the baudrate register
// [1,0] 
// 	= 0,0: uart in 7-bit mode
// 	= 1,1: uart in 8-bit mode
#define AUX_MU_LCR_REG (MUART_BASE + 0x4C)

// probably unnecessary
#define AUX_MU_MCR_REG (MUART_BASE + 0x50)

// [6] transmitter fifo empty and transmitter idle
// [5] transmitter fifo can accept a byte
// [1] receiver overrun, cleared on each read
// [0] receiver fifo ready, contains a symbol
#define AUX_MU_LSR_REG (MUART_BASE + 0x54)

// probably unnecessary
#define AUX_MU_MSR_REG (MUART_BASE + 0x58)

// probably unnecessary
#define AUX_MU_SCRATCH (MUART_BASE + 0x5C)

// [1] transmitter enabled, ![1] transmitter disabled
// [0] receiver enabled, ![0] receiver disabled
#define AUX_MU_CNTL_REG (MUART_BASE + 0x60)

// [27..24] num symbols stored in the transmit fifo (max 8)
// [19..16] num symbols stored in the receive fifo (max 8)
// [9] transmitter idle and transmitter fifo empty
// [8] transmitter fifo is empty
//
// [7] CTS status (1 -> receiver ready to be invoked)
// [6] RTS status (1 -> transmitter ready to be invoked)
//
// [5] transmit fifo is full
// [4] receiver overrun occurred. overrun characters are
// 		 discarded.
// [3] transmitter is idle
// [2] receiver is idle
// [1] transmitter fifo may accept another symbol
// [0] receiver contains at least one symbol
#define AUX_MU_STAT_REG (MUART_BASE + 0x64)

// [15..0] mini uart baud rate counter
#define AUX_MU_BAUD_REG (MUART_BASE + 0x68)

// qemu default baud rate
#define DEFAULT_BAUD 115200

void mini_uart_inspect_state(void);
void mini_uart_enable(void);
void mini_uart_putc(char);

#endif // _MINI_UART_H_

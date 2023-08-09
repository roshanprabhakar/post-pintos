#include "devices/auxilaries.h"
#include "devices/mini-uart.h"
#include "printf.h"

void mini_uart_inspect_state()
{
	uint32_t auxenb = REG_GET(AUX_ENB, uint32_t);
	uint32_t muart_io_reg = REG_GET(AUX_MU_IO_REG, uint32_t);
	uint32_t muart_ier_reg = REG_GET(AUX_MU_IER_REG, uint32_t);
	uint32_t muart_iir_reg = REG_GET(AUX_MU_IIR_REG, uint32_t);
	uint32_t muart_lcr_reg = REG_GET(AUX_MU_LCR_REG, uint32_t);
	uint32_t muart_mcr_reg = REG_GET(AUX_MU_MCR_REG, uint32_t);
	uint32_t muart_lsr_reg = REG_GET(AUX_MU_LSR_REG, uint32_t);
	uint32_t muart_msr_reg = REG_GET(AUX_MU_MSR_REG, uint32_t);
	uint32_t muart_scratch_reg = REG_GET(AUX_MU_SCRATCH, uint32_t);
	uint32_t muart_cntl_reg = REG_GET(AUX_MU_CNTL_REG, uint32_t);
	uint32_t muart_stat_reg = REG_GET(AUX_MU_STAT_REG, uint32_t);
	uint32_t muart_baud_reg = REG_GET(AUX_MU_BAUD_REG, uint32_t);
}

void mini_uart_putc(char c)
{
	for (; !(REG_GET(AUX_MU_LSR_REG, uint32_t) & 0b1100000););
	REG_SET(AUX_MU_IO_REG, uint32_t, (uint32_t) c);
}

void mini_uart_enable(void)
{
	// QEMU emulation removes the direct need for mini uart setup, this
	// funciton needs to be implemented according to the register descriptions
	// in mini-uart.h before deploying to bare metal.
	printf("Console ready.\n");
}

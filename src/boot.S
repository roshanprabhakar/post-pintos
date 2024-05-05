.section ".text.boot"

.global start
.global clear_bss
.global entry_l2
.global halt
.global vtable_el3

.global process_scr

.global enable_irq
.global disable_irq

start:
	mrs x0, mpidr_el1
	ldr x1, =0x40000000
	and x2, x0, x1
	cmp x2, x1
	b.eq master
	and x0, x0, #0xff
	cbz x0, master

halt:
	wfe
	b halt

master:
	ldr x5, =0x80000
	mov sp, x5
	bl clear_bss
	adr x0, vtable_el3
	msr vbar_el3, x0
	bl route_intr_to_el3
	bl enable_irq
	b entry_l2

route_intr_to_el3:
	mrs x0, scr_el3
	orr x0, x0, #(1 << 1) // IRQ bit
	orr x0, x0, #(1 << 2) // FIQ bit
	orr x0, x0, #(1 << 3) // EA bit
	msr scr_el3, x0
	ret	

enable_irq:
	msr daifclr, #2
	ret

disable_irq:
	msr daifset, #2
	ret

	

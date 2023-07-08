.section ".text.boot"

.global start

start:
	mrs x0, mpidr_el1
	and x1, x0, #0x40000000 // test bit 30
	cmp x1, #0x0
	b.eq master
	and x1, x0, #0x3
	cmp x1, #0x0
	b.eq master

halt:
	wfe
	b halt

master:
	nop
	nop
	nop
	wfe
	b master

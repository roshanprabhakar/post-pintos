.section ".text.evtable"

#define GP_REG_STORE_SIZE 256

.global vtable_el3
.global unknown_interrupt_level_handler
.global general_exception_handler

.macro save_gp_regs
	sub	sp, sp, #GP_REG_STORE_SIZE
	stp	x0, x1, [sp, #16 * 0]
	stp	x2, x3, [sp, #16 * 1]
	stp	x4, x5, [sp, #16 * 2]
	stp	x6, x7, [sp, #16 * 3]
	stp	x8, x9, [sp, #16 * 4]
	stp	x10, x11, [sp, #16 * 5]
	stp	x12, x13, [sp, #16 * 6]
	stp	x14, x15, [sp, #16 * 7]
	stp	x16, x17, [sp, #16 * 8]
	stp	x18, x19, [sp, #16 * 9]
	stp	x20, x21, [sp, #16 * 10]
	stp	x22, x23, [sp, #16 * 11]
	stp	x24, x25, [sp, #16 * 12]
	stp	x26, x27, [sp, #16 * 13]
	stp	x28, x29, [sp, #16 * 14]
	str	x30, [sp, #16 * 15]
.endm

.macro restore_gp_regs
	ldp	x0, x1, [sp, #16 * 0]
	ldp	x2, x3, [sp, #16 * 1]
	ldp	x4, x5, [sp, #16 * 2]
	ldp	x6, x7, [sp, #16 * 3]
	ldp	x8, x9, [sp, #16 * 4]
	ldp	x10, x11, [sp, #16 * 5]
	ldp	x12, x13, [sp, #16 * 6]
	ldp	x14, x15, [sp, #16 * 7]
	ldp	x16, x17, [sp, #16 * 8]
	ldp	x18, x19, [sp, #16 * 9]
	ldp	x20, x21, [sp, #16 * 10]
	ldp	x22, x23, [sp, #16 * 11]
	ldp	x24, x25, [sp, #16 * 12]
	ldp	x26, x27, [sp, #16 * 13]
	ldp	x28, x29, [sp, #16 * 14]
	ldr	x30, [sp, #16 * 15]
	add	sp, sp, #GP_REG_STORE_SIZE
.endm

// Stores exception type on the stack as we cannot overwrite regsiters.
.macro vector type
	.balign 0x80
	save_gp_regs
	mov x0, #\type
	b general_exception_handler_init
.endm

#define EL1 4 // 0b0100
#define EL2 8 // 0b1000
#define EL3 12 // 0b1100

general_exception_handler_init:
	save_gp_regs
	mrs x1, CurrentEL

to_el1:
	cmp x1, #EL1
	b.ne to_el2
	mrs x2, esr_el1
	mrs x3, elr_el1
	b exception_handler_entry

to_el2:
	cmp x1, #EL2
	b.ne to_el3
	mrs x2, esr_el2
	mrs x3, elr_el2
	b exception_handler_entry

to_el3:
	cmp x1, #EL3
	b.ne unknown_el_entry
	mrs x2, esr_el3
	mrs x3, elr_el3
	b exception_handler_entry

unknown_el_entry:
	bl unknown_interrupt_level_handler
	b halt // expected

exception_handler_entry:
	bl general_exception_handler

	restore_gp_regs
	eret

.balign 0x800
vtable_el3:
	vector 0
	vector 1
	vector 2
	vector 3
	vector 4
	vector 5
	vector 6
	vector 7
	vector 8
	vector 9
	vector 10
	vector 11
	vector 12
	vector 13
	vector 14
	vector 15

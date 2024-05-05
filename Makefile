cc 			:= aarch64-none-elf-gcc
as 			:= aarch64-none-elf-gcc

cc_ops	= -nostdlib \
					-nostartfiles \
					-ffreestanding \
					-mgeneral-regs-only \
					-fno-stack-protector \
					-march=armv8-a \
					-mstrict-align \
					-mcpu=cortex-a53 \
					-g \
					-I./include/ \
					-DPRINTF_DISABLE_SUPPORT_FLOAT \
					-MT $(word 2,$^) -MMD -MP -MF $(word 2,$^)

as_ops 	:= -mcpu=cortex-a53 -g -I./include/
link_ops:= -ffreestanding -nostdlib -lgcc -Wl,--no-warn-rwx-segments

asm_src	:= $(shell find . -wholename "./src/*.S")
asm_obj := $(patsubst ./src/%.S, ./build/%.o, $(asm_src))

c_src := $(shell find . -wholename "./src/*.c")
c_obj := $(patsubst ./src/%.c, ./build/%.o, $(c_src))
c_dep := $(c_src:.c=.d)

all: build_init $(c_obj) $(asm_obj)
	$(cc) -T src/linker.ld $(link_ops) -o build/kernel.o $(c_obj) $(asm_obj)

$(asm_obj): build/%.o: src/%.S
	$(as) $(as_ops) -c $< -o $@

$(c_obj): build/%.o: src/%.c src/%.d
	$(cc) $(cc_ops) -c $< -o $@

-include $(c_dep)

$(c_dep): %.d: ;

build_init:
	mkdir -p ./build/devices/

clean:
	rm -rf build/
	rm -f `find . -wholename "./src/*.d"`

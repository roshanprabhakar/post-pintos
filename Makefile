cc 			:= aarch64-linux-gnu-gcc
as 			:= aarch64-linux-gnu-gcc
cc_ops	:= -nostdlib -nostartfiles -ffreestanding -mgeneral-regs-only -fno-stack-protector -mcpu=cortex-a53 -g
as_ops 	:= -mcpu=cortex-a53 -g
link_ops:= -ffreestanding -nostdlib -lgcc

asm_src := $(shell find . -wholename "./src/*.S")
asm_obj := $(patsubst ./src/%.S, ./build/%.o, $(asm_src))

c_src 	:= $(shell find . -wholename "./src/*.c")
c_obj 	:= $(patsubst ./src/%.c, ./build/%.o, $(c_src))

all: $(c_obj) $(asm_obj)
	$(cc) -T src/linker.ld $(link_ops) -o build/kernel.o $(c_obj) $(asm_obj)

$(asm_obj): build/%.o: src/%.S
	mkdir -p ./build/ && $(as) $(as_ops) -c $< -o $@



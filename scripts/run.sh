# 
# https://wiki.osdev.org/Raspberry_Pi_Bare_Bones
# 
# hardware boot process:
#	from attached sd card, gpu executes bootcode.bin
#	then, gpu executes start.elf. Finally, the gpu starts
#	the arm core.
#	

qemu_cmd="qemu-system-aarch64 -machine raspi3b -kernel ./build/kernel.o -name lOS"
gdb_cmd="gdb-multiarch ./build/kernel.o -x ./scripts/gdbsetup.gdb"

if [ "$1" = "--gdb-start" ]; then
	echo "starting lOS with gdb host: "
	echo "$qemu_cmd -s -S"
	eval "$qemu_cmd -s -S"

elif [ "$1" = "--gdb-connect" ]; then
	echo "connecting to gdb lOS server: "
	echo "$gdb_cmd"
	eval "$gdb_cmd"

elif [ "$1" = "--start" ]; then
	echo "starting standalone lOS: "
	echo "$qemu_cmd -serial null -serial stdio"
	eval "$qemu_cmd -serial null -serial stdio"

elif [ "$1" = "--help" ]; then
	echo "usage: sh run.sh [--gdb-start | --gdb-connect]"
	echo "--gdb-start: Start qemu with a gdb runtime."
	echo "--gdb-connect: Run from ubuntu with gdb-multiarch, connectes to spawned lOS-gdb instance"
fi

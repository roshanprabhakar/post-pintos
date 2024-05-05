target remote localhost:1234
set scheduler-locking on
file build/kernel.o
break start

target remote host.docker.internal:1234

# Stop threads 2,3,4, they cannot be run until switched to and continued.
set scheduler-locking on

break start

layout regs
info threads

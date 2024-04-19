# raspi3b OS project

An effort to build out small parts of typical operating systems for a raspberry pi, with the goal to learn more about arm development (due to the increasing use of arm in non-embedded application spaces).

---

### Build
The build system runs in an Ubuntu 22.04 container running Linux, with the arm64 architecture. ```aarch64-linux-gnu-gcc``` is used for compilation and assembly. I chose to use this workflow as opposed to the silicon-native clang suite, as llvm does not support custom linking with the use of linker format files.

All build software runs within a Docker Ubuntu container version 22.04 running linux, targeting arm64.

### Development
From the QEMU forums: QEMU is not a raspberry pi emulator, it is a cortex emulator. So, not all peripherals on the bcm2837 are emulated. Specifically, the GPU is not emulated. This affects, for example, the usable timer cmp registers available to the cortex's operating system. Developing is as simple as modifying the appropriate source files from your laptop, debugging involves spinning up a qemu-gdb instance from your machine, and connecting to it via ```gdb-multiarch``` installed to the docker image.

Project structure:
```py
os
├── Makefile
├── build
│   ├── ... general project build targets ...
│   └── devices
│       └── ... peripheral build targets ...
├── docs
│   └── ... submodule documentation ...
├── include
│   ├── devices
│   │   └── ... peripheral headers ...
│   └── ... general target header files ...
├── scripts
│   ├── Dockerfile       # Used to create build container.
│   ├── create-disk.sh   # If necessary, uses qemu to create a hard disk file
│   ├── enter-ubuntu.sh  # Once docker is running, use this to enter the build environment.
│   ├── gdbsetup.gdb     # gdbinit file.
│   └── run.sh           # Invoked from local machine to run the kernel in normal or debug mode, 
│                        # or from the ubuntu container to connect to the running debug instance.
└── src
    ├── .. submodule implementation files ..
    └─── devices
         └── ... peripheral drivers ...
```

---
#### boot.S
This file contains the entry point into the kernel. The cortex processor is programmed to look for a kernel entry point at address 0x80000, and jump all cores into this instruction. QEMU's boot process loads the supplied image into main memory, and the image itself is responsible for programming a proper entry point at address 0x80000. This is easily configurable with the gnu-format linker script.

This file is responsible for:
- Turning the cortex into a uniprocessor, by halting all cores with id not equal to 1.
- Initializing a stack pointer, so that C code down the line will run as expected.
- Initializing the bss, by zeroing out memory between linker-defined bss_start and bss_end.
- Initialize the el3 vector table, and configure the cortex to route exceptions to el3 (instead of the implementation default el1).
- Jump into compiled C code.

Cortex-A53 boot information [here](http://classweb.ece.umd.edu/enee447.S2021/baremetal_boot_code_for_ARMv8_A_processors.pdf). Jump to aarch64 boot for relevant sections.

#### evtable.S
This file defines the tables used by the arm to handle various exceptions. Right now the OS only defines a table for el3, and routes all exceptions to el3. 

Microkernel x86-64 (Assembly)

"Architecture" (https://img.shields.io/badge/architecture-x86--64-blue)
"Language" (https://img.shields.io/badge/language-Assembly-orange)
"Build" (https://img.shields.io/badge/build-NASM%20%2B%20LD-lightgrey)
"Platform" (https://img.shields.io/badge/platform-Linux-black)
"Emulator" (https://img.shields.io/badge/emulator-QEMU-red)
"Status" (https://img.shields.io/badge/status-in%20development-yellow)
"License" (https://img.shields.io/badge/license-MIT-green)

---

Overview

This project is a minimal microkernel written entirely in x86-64 Assembly, designed for low-level system understanding and experimental kernel engineering.

The architecture follows a true microkernel design, where only essential mechanisms are implemented in kernel space:

- Task scheduling
- Memory management (basic paging model)
- Inter-process communication (IPC)

All other services are intended to run in user space.

---

Architecture

Hardware
   │
Bootloader
   │
Microkernel
   ├── Scheduler
   ├── Memory Manager
   └── IPC
   │
User-space Servers
   ├── File System
   ├── Drivers
   └── Other Services

---

Project Structure

microkernel/
│
├── boot/
│   └── boot.asm
│
├── kernel/
│   ├── kernel.asm
│   ├── scheduler.asm
│   ├── memory.asm
│   ├── ipc.asm
│
├── include/
│   └── kernel.inc
│
├── servers/
│   ├── fs_server.asm
│   └── driver_server.asm
│
├── link.ld
├── Makefile
└── README.md

---

Build Requirements

- NASM
- GNU LD
- QEMU
- Linux environment (recommended)

Install dependencies (Debian/Ubuntu):

sudo apt install nasm gcc ld qemu-system-x86

---

Build & Run

Build the system

make

Run in QEMU

make run

Debug mode

make debug

This enables:

- serial output
- CPU state tracing
- GDB stub ("-s -S")

---

Boot Process

1. BIOS loads bootloader at "0x7C00"
2. Bootloader loads kernel into memory ("0x100000")
3. Execution jumps to kernel entry point
4. Kernel initializes:
   - memory
   - scheduler
   - IPC
5. User-space servers are started

---

Key Components

Bootloader

- Loads kernel sectors from disk
- Transfers control to kernel memory

Kernel Core

- Entry point and initialization logic

Scheduler

- Round-robin task switching
- Task Control Block (TCB)

Memory Manager

- Simple page allocator (4KB pages)

IPC

- Message-based communication
- Decouples services from kernel

---

Debugging

Primary methods:

- Serial output (COM1) → reliable for kernel debugging
- QEMU debug flags → CPU/interrupt tracing
- GDB remote debugging

Example:

qemu-system-x86_64 -drive format=raw,file=build/os.img -serial stdio -s -S

---

Known Limitations

- No full paging implementation yet
- No user-mode isolation (ring3 not active)
- No real filesystem
- Limited interrupt handling
- Static memory model

---

Roadmap

- [ ] Protected mode transition
- [ ] Long mode activation
- [ ] Full paging (PML4)
- [ ] System call interface
- [ ] User-mode processes
- [ ] Driver abstraction
- [ ] Filesystem server
- [ ] ELF loader

---

Commit Convention

area: description

Examples:

boot: implement sector loading
kernel: add entry point
memory: implement page allocator
scheduler: add round robin logic
ipc: add message queue
debug: add serial output

---

References

- Intel Software Developer Manual
- OSDev Wiki
- Microkernel architecture research

---

License

MIT License

---

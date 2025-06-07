
# RISC-V Week 1: Toolchain, Compilation, Debugging, and System Programming

## 1. Install & Sanity-Check the Toolchain

### 📦 Extract the Toolchain
```bash
tar -xzf riscv-toolchain-rv32imac-x86_64-ubuntu.tar.gz
```

### 🛠 Add to PATH
Edit `~/.bashrc`:
```bash
export PATH="$HOME/riscv/bin:$PATH"
source ~/.bashrc
```

### ✅ Verify Installation
```bash
riscv32-unknown-elf-gcc --version
riscv32-unknown-elf-objdump --version
riscv32-unknown-elf-gdb --version
```

### 🐍 GDB Python Error Fix
Install Python 3.10:
```bash
sudo apt update
sudo apt install python3.10 python3.10-dev
```
### Output:
![Alt text](riscv/1.jpg)

---

## 2. Compile “Hello, RISC-V”

### hello.c
```c
#include <stdio.h>

int main() {
    printf("Hello, RISC-V!\n");
    return 0;
}
```

### Compile
```bash
riscv32-unknown-elf-gcc -march=rv32imc -mabi=ilp32 -o hello.elf hello.c
```

### Confirm ELF Target
```bash
file hello.elf
```
### Output:
![Alt text](riscv/2.jpg)
---

## 3. From C to Assembly

```bash
riscv32-unknown-elf-gcc -S -O0 hello.c
```

### Prologue & Epilogue Sample
```assembly
main:
  addi sp, sp, -16
  sw ra, 12(sp)
  sw s0, 8(sp)
  addi s0, sp, 16
  ...
  lw ra, 12(sp)
  lw s0, 8(sp)
  addi sp, sp, 16
  ret
```
### Output:
![Alt text](riscv/3.jpg)

---

## 4. Hex Dump & Disassembly

### Disassemble
```bash
riscv32-unknown-elf-objdump -d hello.elf > hello.dump
```
### Output:
![Alt text](riscv/4.jpg)

### Intel HEX
```bash
riscv32-unknown-elf-objcopy -O ihex hello.elf hello.hex
```
### Output:
![Alt text](riscv/5.jpg)

### Analyze
```
10074: 1141    addi sp, sp, -16
```

---

## 5. ABI & Register Cheat-Sheet

| xN  | ABI   | Role             |
|-----|-------|------------------|
| x0  | zero  | Hardwired Zero   |
| x1  | ra    | Return Address   |
| x2  | sp    | Stack Pointer    |
| x10 | a0    | Arg 0 / Return   |
| x5–x7, x28–x31 | t0–t6 | Temporaries |
| x8–x9, x18–x27 | s0–s11 | Saved Regs |

---

## 6. Debugging with GDB

```bash
riscv32-unknown-elf-gdb hello.elf
(gdb) target sim
(gdb) break main
(gdb) run
(gdb) stepi
(gdb) info registers
```
### Output:
![Alt text](riscv/6.jpg)
![Alt text](riscv/7.jpg)

---

## 7. Running in Emulator

```bash
spike --isa=rv32imc pk hello.elf
```

or

```bash
qemu-system-riscv32 -nographic -kernel hello.elf
```
### Output:
![Alt text](riscv/8.jpg)
![Alt text](riscv/9.jpg)
---

## 8. GCC Optimization

Compare:
```bash
riscv32-unknown-elf-gcc -S -O0 hello.c
riscv32-unknown-elf-gcc -S -O2 hello.c
```

Observe: dead-code elimination, inlining, etc.
### Output:
![Alt text](riscv/10.jpg)
![Alt text](riscv/11.jpg)
![Alt text](riscv/12.jpg)

---

## 9. Inline Assembly Example

```c
static inline uint32_t rdcycle(void) {
  uint32_t c;
  asm volatile("csrr %0, cycle" : "=r"(c));
  return c;
}
```
### Output:
![Alt text](riscv/13.jpg)

---

## 10. Memory-Mapped I/O Demo

```c
volatile uint32_t *gpio = (uint32_t*)0x10012000;
*gpio = 0x1;
```
### Output:
![Alt text](riscv/14.jpg)
![Alt text](riscv/15.jpg)
---

## 11. Minimal Linker Script

```ld
SECTIONS {
  .text 0x00000000 : { *(.text*) }
  .data 0x10000000 : { *(.data*) }
}
```
### Output:
![Alt text](riscv/16.jpg)
![Alt text](riscv/17.jpg)
![Alt text](riscv/18.jpg)
---

## 12. crt0.S Responsibilities

- Set up stack
- Zero `.bss`
- Call `main`
- Infinite loop after return

---
### Output:
![Alt text](riscv/19.jpg)
![Alt text](riscv/20.jpg)
---

## 13. Timer Interrupts

- Set `mtimecmp`
- Enable `mie` and `mstatus`
- Define handler using `__attribute__((interrupt))`
---
### Output:
![Alt text](riscv/21.jpg)
---
## 14. Atomic Instructions (`A` Extension)

Instructions:
- `lr.w`, `sc.w`
- `amoadd.w`, `amoswap.w`, `amoand.w`, etc.

Use: mutexes, spinlocks, semaphores.

---

## 15. Atomic Spinlock Example

```c
while (1) {
  asm volatile (
    "lr.w t0, (a0)\n"
    "sc.w t1, t2, (a0)\n"
    "bnez t1, retry\n"
    ...
  );
}
```
### Output:
![Alt text](riscv/22.jpg)
![Alt text](riscv/23.jpg)
---

## 16. Using printf with Newlib (Bare-Metal)

```c
#define UART0_TX 0x10000000
volatile char* const uart = (char*)UART0_TX;

int _write(int fd, const char* buf, int len) {
  for (int i = 0; i < len; i++) uart[0] = buf[i];
  return len;
}
```

Compile with:
```bash
riscv32-unknown-elf-gcc -nostartfiles -T linker.ld -o hello.elf hello.c syscalls.c
```

---

## 17. Endianness Check

```c
union {
  uint32_t i;
  uint8_t b[4];
} u = { .i = 0x01020304 };

printf("%02x %02x %02x %02x\n", u.b[0], u.b[1], u.b[2], u.b[3]);
```

Little-endian will print: `04 03 02 01`
### Output:
![Alt text](riscv/24.jpg)
![Alt text](riscv/25.jpg)

---

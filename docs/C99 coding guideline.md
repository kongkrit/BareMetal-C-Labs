
# Coding guidelines for `Bare-Metal C` Course using `SDCC`.

### **1. Data Types & Precision**

*Rationale: On an 8-bit Z80, an int is 16-bit, but on modern CPUs, it is 32-bit. Ambiguity is the enemy of embedded systems.*

* **Rule 1.1: Always use `<stdint.h>` types.**
  * Never use `int`, `short`, or `long` for data storage.
  * Use `uint8_t` for data bus values (8-bit).
  * Use `uint16_t` for address bus values (16-bit).
  * **Why:** This explicitly links the C variable size to the hardware bus width.
* **Rule 1.2: Use bool from `<stdbool.h>` for logic.**
  * Use `true` and `false` for flags.
  * **Why:** Clearer intent than using integers `0` or `1`.
* **Rule 1.3: Avoid Floating Point.**
  * The Z80 has no FPU. Floats are emulated in software and are incredibly slow and code-heavy.
  * **Why:** Keeps the focus on what the CPU actually does.

### **2. Memory Mapped I/O (MMIO)**

*Rationale: This is the core learning objective. Students must understand that "Writing to IO" is just "Writing to a specific memory address."*

* **Rule 2.1: The `volatile` keyword is mandatory for IO.**
  * Any pointer interacting with hardware *must* be declared `volatile`.
  * **Why:** Without `volatile`, the compiler may "optimize away" your reads/writes because it doesn't see the variable changing in code.
  * *Example:*
    ```C
    // BAD: Compiler sees 'status' isn't changed by code, might remove the loop
    uint8_t * status = (uint8_t *)0x8000;
    while (*status == 0);

    // GOOD: Compiler knows *status can change externally (by hardware)
    volatile uint8_t *status = (volatile uint8_t *)0x8000;
    while (*status == 0);
    ```
* **Rule 2.2: Use Macros for Base Addresses.**
  * Define hardware addresses at the top of the file or in a header.
  * **Why:** Magic numbers in code `(*(uint8_t*)0x1234 = 5)` are hard to debug.
  * *Example:*
    ```C
    #define LED_PORT_ADDR 0x4000
    #define LED_PORT ((volatile uint8_t *)LED_PORT_ADDR)

    // Usage
    *LED_PORT = 0xFF; // Writes 0xFF to address bus 0x4000
    ```
### **3. Memory Management**

*Rationale: There is no OS to clean up messes. Memory is finite (SRAM).*

* **Rule 3.1: No Dynamic Memory Allocation.**
  * **Strictly forbidden:** `malloc()`, `calloc()`, `free()`.
  * **Why:** There is no Heap Manager in your bare-metal environment. Using these will cause linker errors or crashes.
* **Rule 3.2: Use `const` for Read-Only Data.**
  * Lookup tables (e.g., 7-segment display fonts) should be `const`.
  * **Why:** On some architectures this saves RAM by keeping data in ROM/Flash. On Z80/SDCC, it helps prevents accidental corruption.

### **4. Functions & Control Flow**

*Rationale: The Z80 stack is small and easy to overflow.*

* **Rule 4.1: No Recursion.**
  * Functions must not call themselves.
  * **Why:** Recursion rapidly eats stack space, overwriting variables or program code, leading to "ghost" bugs.
* **Rule 4.2: Infinite Main Loop.**
  * Embedded programs never "exit". `main()` should end with `while(true)`.
  * **Why:** If main returns, the CPU executes whatever random bytes happen to be next in memory.
* **Rule 4.3: Keep Functions Short.**
  * Limit functions to ~20 lines where possible.
  * **Why:** SDCC optimizes small functions better, and it helps students trace execution logic mentally.

### **5. Bit Manipulation**

*Rationale: Hardware control often requires changing 1 bit without affecting the other 7.*

* **Rule 5.1: Use Explicit Shifts and Masks.**
  * Do not use "Bit Fields" in structs (compiler implementation varies too much).
  * **Why:** `(1 << 3)` is universal. Bit fields are not.
* **Rule 5.2: Read-Modify-Write.**
  * To change one bit, read the port, modify the bit, write it back.
  * *Example:*
    ```C
    // Set bit 3 HIGH
    *LED_PORT |= (1 << 3);

    // Set bit 3 LOW
    *LED_PORT &= ~(1 << 3);
    ```
### **6. SDCC Specific Constraints**

*Rationale: SDCC is a great compiler, but it has quirks tailored for 8-bit systems.*

* **Rule 6.1: Declare variables at the top of the scope.**
  * While C99 allows mixing declarations and code, SDCC sometimes generates better code if variables are declared first.
* **Rule 6.2: Global variables for large arrays.**
  * If you need a large array (buffer), make it static or global, not local to a function.
  * **Why:** Large local variables can overflow the stack.

### **Sample "Perfect" Student Code**

The template to demonstrate the guidelines in action:

```C
/*
 * Hardware: Z80 simulated with memory mapped LED at 0x8000
 * Goal: Blink LED
 */

#include <stdint.h>
#include <stdbool.h>

// Define hardware address (Memory Mapped IO)
// 'volatile' tells compiler: "Don't cache this, hardware changes it!"
#define IO_LED_ADDR  0x8000
#define IO_LED       ((volatile uint8_t *)IO_LED_ADDR)

// Simple delay function
// Note: In real hardware, we'd use timers, but for basics, loops are fine.
void delay_loops(uint16_t count) {
    while (count > 0) {
        count = count - 1;
        // 'nop' (No Operation) prevents compiler from optimizing this loop away completely
        __asm__("nop");
    }
}

void main(void) {
    uint8_t pattern = 0x01;

    // Super loop (Embedded programs never die)
    while (true) {
        // 1. Write to Data Bus
        *IO_LED = pattern;

        // 2. Wait
        delay_loops(5000);

        // 3. Logic: Shift pattern left
        if (pattern == 0x80) {
            pattern = 0x01;
        } else {
            pattern = pattern << 1;
        }
    }
}
```
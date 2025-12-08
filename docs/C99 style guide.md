

# **Bare Metal C: C99 Coding Standards & Style Guide**

**Language:** C (SDCC Compiler/C99 Standard)

## **1. Core Philosophy**

Moving from Python to C requires a shift in mindset. In C, you are managing the hardware directly. There is no automatic memory management, and safety features must be added by you, the programmer.

* **Be Explicit:** Nothing happens automatically. If you want a variable to be zero, you must set it to zero.
* **Be Safe:** Use types that prevent errors before they happen.
* **Be Readable:** Code is read much more often than it is written.

## **2. File Organization**

* **Header Guards:** Every .h file must be wrapped in generic include guards to prevent recursive inclusion.
* **Includes:** System headers (< >) go first, followed by project headers (" ").

```C
#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>
#include <stdbool.h>
#include "hardware_map.h"

// Prototypes go here

#endif
```

## **3. Formatting & Indentation**

* **Indentation:** Use **4 Spaces**. Do not use tab characters. Configure your text editor (VS Code/SimulIDE) to "Insert Spaces" when pressing Tab.
* **Braces:** Use "One True Brace Style" (opening brace on the same line). **Always** use braces, even for single-line statements.
* **Closing Braces Alignment:** Closing braces (`}`) must vertically align with the line that opens the brace (`{`)

**Good:**
```C
if (fail) {
    return;
}
```
*Why: the opening brace `{` starts on `if`, so the closing brace `}` aligns with the leftmost character of `if`.*

**Bad:**
```C
if (fail) {
    return;
  }
```
*Why: the opening brace `{` starts on `if`, but the closing brace `}` doesn't align with the leftmost character of `if`. This makes code harder to debug.*

* **One Statement Per Line:** Never combine logic.

**Bad:**
```C
if(fail) return; // Hard to debug
```

**Good:**
```C
if (fail) {
    return;
}
```

## **4. Data Types & Const Correctness**

Stop using generic `int` or `long`. In embedded systems, we need to know exactly how many bits a number uses.

### **4.1 Strict Types**

Always include <stdint.h> and <stdbool.h>.

| Type | Description | Use Case |
| :---- | :---- | :---- |
| `uint8_t` | Unsigned 8-bit (0 to 255) | Hardware registers, bytes, flags. |
| `int8_t` | Signed 8-bit (-128 to 127) | Small math values. |
| `uint16_t` | Unsigned 16-bit (0 to 65,535) | Counters, memory addresses. |
| `bool` | Boolean (true/false) | Logical checks. |
| `void` | Empty/Nothing | Functions returning nothing. |

### **4.2 Const by Default**

Variables should be immutable (`const`) by default. Only remove `const` if the variable **must** change (e.g., a counter or accumulator).

* **Why?** In embedded systems like the Z80, const data can be stored in ROM (Flash), saving precious RAM.
* **Rule:** If you don't assign a new value to it after initialization, it must be `const`.

```C
const uint8_t max_retries = 5;  // Good: This is a fixed setting
uint8_t current_retry = 0;      // Good: This changes in a loop
```

## **5. Naming Conventions**

* **Variables & Functions:** snake_case (lowercase with underscores).
  * `uint8_t sensor_value;`
  * `void read_data(void);`
* **Constants & Macros:** UPPER_CASE.
  * `#define MAX_BUFFER 255`
  * `const uint8_t LED_PIN = 1;`

## **6. Functions & Scope**

* **Explicit Void:** If a function takes no arguments, write void explicitly.
  * `int32_t calculate_sum(void);`
* **Variable Scope:** Declare loop counters inside the loop definition (C99 feature) to keep them local.
  ```C
  for (uint8_t i = 0; i < 10; i++) { ... }
  ```
## **7. Python vs. C Cheat Sheet**

| Feature | Python | C99 Guideline |
| :---- | :---- | :---- |
| **Blocks** | Indentation | Curly Braces { } (Indentation is purely visual) |
| **True/False** | `True` / `False` | `true` / `false` (requires `<stdbool.h>`) |
| **Variables** | Dynamic (x = 5) | Static (`const uint8_t x = 5;`) |
| **Strings** | "Hello" | Array of chars (`const char msg[] = "Hello";`) |
| **Printing** | `print("Val:", x)` | `printf("Val: %dn", x);` |
| **Main** | `if __name__ == "__main__":` | `int main(void) { ... }` |
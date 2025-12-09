#include <stdbool.h>
#include <stdint.h>

#define M_ADDR 0x4000

void main(void) {
    int16_t a;
    a = -27;
    int16_t b = 54;
    int16_t *m = (int16_t *) M_ADDR;
    *m = a * b;
}
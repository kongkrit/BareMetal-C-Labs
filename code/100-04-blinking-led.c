#include <stdbool.h>

#define LED0 0xE000U

void main(void) {

    volatile bool * led = (volatile bool *) LED0;
    
    while (true) {
        
        *led = true;
        *led = false;
        
    }
}
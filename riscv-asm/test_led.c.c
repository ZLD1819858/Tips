#include "ripes_system.h"


unsigned *led_base = LED_MATRIX_0_BASE;

void main(void) {

    unsigned v = 0;
    int y = 0;
    int x = 0;
    while(1) {
        for (y = 0; y < LED_MATRIX_0_HEIGHT; y++) {
            for (x = 0; x < LED_MATRIX_0_WIDTH; x++) {
                char r = v+(0xff * x) / LED_MATRIX_0_WIDTH;
                char g = v+(0xff * y) / LED_MATRIX_0_HEIGHT;
                char b = v+(0xff * (x+y)) / (LED_MATRIX_0_HEIGHT+LED_MATRIX_0_WIDTH);
                unsigned idx = y*LED_MATRIX_0_WIDTH+x;
                //(*(led_base + idx)) = r << 16 | g << 8 |b;
                (*(led_base + idx)) = 0;
                
            }
            v++;
        }
    }
}
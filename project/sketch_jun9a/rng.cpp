#include "rng.h"

#include <Arduino.h>

unsigned long trulyRandom(byte analogPin) {
    unsigned long r = 0;
    // last two bits are chosen
    for (int i = 0; i < 4*sizeof(unsigned long); ++i) {
        r = (r << 2) | (analogRead(analogPin) & 0x03);
        // delay(1);
    }
    return r;
}

int rngFunc(byte *dest, unsigned size) {
    for (int i = 0; i < size; ++i)
        dest[i] = random();
    return 1;
}

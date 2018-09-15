#include <stdio.h>
#include "chip_8.h"

int main() {
    CHIP_8 chip;

    for (;;) {
        // fetch next instruction
        // decode instruction
        // execute
        chip.emulate_cycle();
    }

    return 0;
}
#include <stdio.h>
#include "chip_8.h"

int main() {
    MMU mmu;
    CHIP_8 chip(mmu);

    mmu.load_game("pong.rom");
    // mmu.print_rom();

    // for (;;) {
        // fetch next instruction
        // decode instruction
        // execute
    //     chip.emulate_cycle();
    // }

    return 0;
}
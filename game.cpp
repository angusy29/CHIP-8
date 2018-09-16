#include <stdio.h>
#include "chip_8.h"
#include "mmu.h"
#include "graphics.h"

int main() {
    MMU mmu;
    Graphics graphics;
    CHIP_8 chip(mmu, graphics);

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
#include <stdio.h>
#include "chip_8.h"
#include "mmu.h"
#include "graphics.h"
#include <SDL2/SDL.h>

int main() {
    MMU mmu;
    Graphics graphics;
    CHIP_8 chip(mmu, graphics);

    mmu.load_game("pong.rom");
    // mmu.print_rom();

    int w = 1024;
    int h = 512;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL could not be initialized, SDL_Error: " << SDL_GetError() << "\n";
        exit(1);
    }

    SDL_Window* window = SDL_CreateWindow("CHIP-8 Emulator",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            w, h, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cout << "SDL could not create window, SDL_Error: " << SDL_GetError() << "\n";
        exit(1);
    }

    for (;;) {
        // fetch next instruction
        // decode instruction
        // execute
    //     chip.emulate_cycle();
    }

    return 0;
}
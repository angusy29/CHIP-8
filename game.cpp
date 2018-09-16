#include <chrono>
#include <stdio.h>
#include "chip_8.h"
#include "mmu.h"
#include "graphics.h"
#include <SDL2/SDL.h>
#include <thread>

// Keypad keymap
uint8_t keymap[16] = {
    SDLK_x,
    SDLK_1,
    SDLK_2,
    SDLK_3,
    SDLK_q,
    SDLK_w,
    SDLK_e,
    SDLK_a,
    SDLK_s,
    SDLK_d,
    SDLK_z,
    SDLK_c,
    SDLK_4,
    SDLK_r,
    SDLK_f,
    SDLK_v,
};

int main() {
    MMU mmu;
    mmu.load_game("pong.rom");

    Graphics graphics;
    CHIP_8 chip(mmu, graphics);

    chip.get_mmu().print_rom();

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

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetLogicalSize(renderer, w, h);

    SDL_Texture *sdlTexture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                64, 32);

    uint32_t pixels[2048];

    for (;;) {
        chip.emulate_cycle();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);

            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) exit(0);

                for (auto i = 0; i < 16; ++i) {
                    if (e.key.keysym.sym == keymap[i]) {
                        chip.set_key(i);
                    }
                }
            }

            if (e.type == SDL_KEYUP) {
                for (auto i = 0; i < 16; ++i) {
                    if (e.key.keysym.sym == keymap[i]) {
                        chip.unset_key(i);
                    }
                }
            }
        }

        if (chip.get_draw_flag()) {
            chip.set_draw_flag(false);

            for (auto i = 0; i < 2048; ++i) {
                uint8_t pixel = chip.get_graphics()._display_buffer[i];
                pixels[i] = (0x00FFFFFF * pixel) | 0xFF000000;
            }

            // Update SDL texture
            SDL_UpdateTexture(sdlTexture, NULL, pixels, 64 * sizeof(Uint32));
            // Clear screen and render
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, sdlTexture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }

        std::this_thread::sleep_for(std::chrono::microseconds(1200));
    }

    return 0;
}
#include "graphics.h"

Graphics::Graphics() {
    reset();
}

void Graphics::reset() {
    _display_buffer.fill(0);
}

void Graphics::load_buffer(uint16_t x, uint16_t y) {
    _display_buffer[x + y] ^= 1;
}

bool Graphics::collision(uint16_t x, uint16_t y) {
    return _display_buffer[x + y] == 1;
}

std::array<int, 2048> Graphics::get_display_buffer() {
    return _display_buffer;
}

void Graphics::print_display() {
    for (int i = 0; i < 2048; ++i) {
        std::cout << _display_buffer[i] << " ";
        if (i % 64 == 0) {
            std::cout << "\n";
        }
    }
}
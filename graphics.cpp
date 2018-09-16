#include "graphics.h"

Graphics::Graphics() {
    for (auto i = 0; i < 64 * 32; ++i) {
        _display_buffer[i] = 0;
    }
}

void Graphics::load_buffer(uint8_t x, uint8_t y) {
    _display_buffer[x * y] ^= 1;
}

bool Graphics::collision(uint8_t x, uint8_t y) {
    return _display_buffer[x * y] == 1;
}

std::array<int, 64 * 32> Graphics::get_display_buffer() {
    return _display_buffer;
}
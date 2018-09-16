#include "graphics.h"

Graphics::Graphics() {
    memset(_display_buffer, 0, sizeof(_display_buffer[0][0]) * 64 * 32);
}

void Graphics::load_buffer(uint8_t x, uint8_t y) {
    _display_buffer[x][y] ^= 1;
}

bool Graphics::collision(uint8_t x, uint8_t y) {
    return _display_buffer[x][y] == 1;
}
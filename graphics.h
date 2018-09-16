#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <array>
#include <iostream>
#include <stdint.h>

class Graphics {
    private:
        std::array<int, 64 * 32> _display_buffer;
    public:
        Graphics();
        void load_buffer(uint8_t x, uint8_t y);
        bool collision(uint8_t x, uint8_t y);
        std::array<int, 64 * 32> get_display_buffer();
};

#endif /* _GRAPHICS_H_ */
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <array>
#include <iostream>
#include <stdint.h>

class Graphics {
    public:
        std::array<int, 64 * 32> _display_buffer;

        Graphics();
        void reset();
        void load_buffer(uint16_t x, uint16_t y);
        bool collision(uint16_t x, uint16_t y);
        std::array<int, 64 * 32> get_display_buffer();
        void print_display();
};

#endif /* _GRAPHICS_H_ */
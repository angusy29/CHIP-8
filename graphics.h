#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <iostream>
#include <stdint.h>

class Graphics {
    private:
        uint8_t _display_buffer[64][32];
    public:
        Graphics();
        void load_buffer(uint8_t x, uint8_t y);
        bool collision(uint8_t x, uint8_t y);
};

#endif /* _GRAPHICS_H_ */
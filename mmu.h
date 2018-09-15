#ifndef _MMU_H_
#define _MMU_H_

#include <iostream>

class MMU {
    private:
        uint8_t _intepreter[512];       // 0x000 - 0x1FF
        uint8_t _program[3584];         // 0x200 - 0xFFF
    public:
        bool load_game(const char *file);
};

#endif /* _MMU_H_ */
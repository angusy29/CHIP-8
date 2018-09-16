#ifndef _MMU_H_
#define _MMU_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <inttypes.h>

class MMU {
    private:
        const static int INTERPRETER_MEMORY_SIZE = 512;
        const static int PROGRAM_MEMORY_SIZE = 3584;

        uint8_t _interpreter[INTERPRETER_MEMORY_SIZE];       // 0x000 - 0x1FF
        uint8_t _program[PROGRAM_MEMORY_SIZE];               // 0x200 - 0xFFF
    public:
        MMU();
        void load_game(const char *filename);
        void print_rom();

        uint16_t read_instruction(uint16_t addr);
        void write_byte(uint16_t addr, uint8_t data);
        uint8_t read_byte(uint16_t addr);
};

#endif /* _MMU_H_ */
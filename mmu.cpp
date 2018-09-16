#include "mmu.h"

MMU::MMU() {
    memset(_interpreter, 0, sizeof(_interpreter));
    memset(_program, 0, sizeof(_program));
}

void MMU::load_game(const char *filename) {
    std::cout << "Loading ROM...\n";
    std::ifstream game(filename, std::ios::binary);
    game.seekg(0, std::ios::end);

    int size = game.tellg();

    if (size > PROGRAM_MEMORY_SIZE) {
        std::cout << "ROM size " << size << "exceeds memory capacity";
        exit(3);
    }

    std::cout << "Loading ROM size: " << size << "\n";
    game.seekg(0, std::ios::beg);
    game.read((char *) _program, size);
    game.close();
    std::cout << "Loaded ROM sucessfully!" << "\n";
}

uint16_t MMU::read_instruction(uint16_t addr) {
    // chip_8 is big endian, so MSB i
    uint16_t lo = addr;
    uint16_t hi = addr + 1;

    printf("Accessing memory address %08" PRIx16 "\n", addr);

    if (0x000 <= addr && addr <= 0x1FF) {
        return (_interpreter[lo] << 8) | _interpreter[hi];
    }

    if (0x200 <= addr && addr <= 0xFFF) {
        printf("%08" PRIx8 " ", _program[addr - 0x200]);
        return (_program[lo - 0x200] << 8) | _program[hi - 0x200];
    }

    // printf("Accessing invalid memory address %08" PRIx16 "\n", addr);
    return 0;
}

void MMU::write_byte(uint16_t addr, uint8_t data) {
    if (0x000 <= addr && addr <= 0x1FF) {
        _interpreter[addr] = data;
    }

    if (0x200 <= addr && addr <= 0xFFF) {
        _program[(addr - 0x200)] = data;
    }
}

uint8_t MMU::read_byte(uint16_t addr) {
    if (0x000 <= addr && addr <= 0x1FF) {
        return _interpreter[addr];
    }

    if (0x200 <= addr && addr <= 0xFFF) {
        return _program[addr - 0x200];
    }

    printf("Accessing invalid memory address %08" PRIx16 "\n", addr);
    return 0;
}

void MMU::print_rom() {
    std::cout << "=====Printing program memory=====\n";
    for (auto i = 0; i < PROGRAM_MEMORY_SIZE; ++i) {
        printf("%08" PRIx8 " ", _program[i]);
    }
    std::cout << "\n=====End program memory=====\n";
}
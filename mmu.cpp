#include "mmu.h"

MMU::MMU() {
    memset(_interpreter, 0, sizeof(_interpreter));
    memset(_program, 0, sizeof(_program));

    // store the fontset
    // store font set
    std::array<int, 80> fontset =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    for (auto i = 0; i < 80; ++i) {
        _interpreter[i] = fontset[i];
    }
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
        return (_program[lo - 0x200] << 8) | _program[hi - 0x200];
    }

    printf("[read_instruction] Accessing invalid memory address %08" PRIx16 "\n", addr);
    exit(3);
    return 0;
}

void MMU::write_byte(uint16_t addr, uint8_t data) {
    if (0x000 <= addr && addr <= 0x1FF) {
        _interpreter[addr] = data;
        return;
    }

    if (0x200 <= addr && addr <= 0xFFF) {
        _program[(addr - 0x200)] = data;
        return;
    }

    printf("[write_byte] Accessing invalid memory address %08" PRIx16 "\n", addr);
    exit(3);
}

uint8_t MMU::read_byte(uint16_t addr) {
    if (0x000 <= addr && addr <= 0x1FF) {
        return _interpreter[addr];
    }

    if (0x200 <= addr && addr <= 0xFFF) {
        return _program[addr - 0x200];
    }

    printf("[read_byte] Accessing invalid memory address %08" PRIx16 "\n", addr);
    exit(3);
    return 0;
}

void MMU::print_rom() {
    std::cout << "=====Printing program memory=====\n";
    for (auto i = 0; i < PROGRAM_MEMORY_SIZE; ++i) {
        printf("%08" PRIx8 " ", _program[i]);
    }
    std::cout << "\n";
    std::cout << "=====End program memory=====\n";
}
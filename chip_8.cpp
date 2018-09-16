#include "chip_8.h"

CHIP_8::CHIP_8(MMU &mmu, Graphics &graphics) {
    _pc = 0x200;
    _index = 0;
    _sp = 0;

    memset(_v, 0, sizeof(_v));              // clear registers
    memset(_stack, 0, sizeof(_stack));      // clear stack
    memset(_key, 0, sizeof(_key));          // clear keypad
    _mmu = mmu;
    _graphics = graphics;

    // store font set
    _fontset =
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
}

void CHIP_8::emulate_cycle() {
    // fetch
    uint16_t instruction = _mmu.read_instruction(_pc);
    printf("Executing instruction %08" PRIx16 "\n", instruction);

    // decode and execute
    switch (instruction & 0xF000) {
        case 0x0000:
            switch (instruction & 0x00FF) {
                case 0x00E0: CLS(); break;
                case 0x00EE: RET(); break;
                default: SYS_addr(instruction); break;
            }
            break;
        case 0x1000: JP_addr(instruction); break;
        case 0x2000: CALL_addr(instruction); break;
        case 0x3000: SE_Vx_byte(instruction); break;
        case 0x4000: SNE_Vx_byte(instruction); break;
        case 0x5000: SE_Vx_Vy(instruction); break;
        case 0x6000: LD_Vx_byte(instruction); break;
        case 0x7000: ADD_Vx_byte(instruction); break;
        case 0x8000: 
            switch (instruction & 0x000F) {
                case 0x0000: LD_Vx_Vy(instruction); break;
                case 0x0001: OR_Vx_Vy(instruction); break;
                case 0x0002: AND_Vx_Vy(instruction); break;
                case 0x0003: XOR_Vx_Vy(instruction); break;
                case 0x0004: ADD_Vx_Vy(instruction); break;
                case 0x0005: SUB_Vx_Vy(instruction); break;
                case 0x0006: SHR_Vx_Vy(instruction); break;
                case 0x0007: SUBN_Vx_Vy(instruction); break;
                case 0x000E: SHL_Vx(instruction); break;
                default: break;
            }
            break;
        case 0x9000:
            switch (instruction & 0x000F) {
                case 0x0000: SNE_Vx_Vy(instruction); break;
                default: break;
            }
            break;
        case 0xA000: LD_I_addr(instruction); break;
        case 0xB000: JP_V0_addr(instruction); break;
        case 0xC000: RND_Vx_byte(instruction); break;
        case 0xD000: DRW_Vx_Vy_nibble(instruction); break;
        case 0xE000:
            switch (instruction & 0xFF) {
                case 0x009E: SKP_Vx(instruction); break;
                case 0x00A1: SKNP_Vx(instruction); break;
                default: break;
            }
        case 0xF000:
            switch (instruction & 0x00FF) {
                case 0x0007: LD_Vx_DT(instruction); break;
                case 0x000A: LD_Vx_K(instruction); break;
                case 0x0015: LD_DT_Vx(instruction); break;
                case 0x0018: LD_ST_Vx(instruction); break;
                case 0x001E: ADD_I_Vx(instruction); break;
                case 0x0029: LD_F_Vx(instruction); break;
                case 0x0033: LD_B_Vx(instruction); break;
                case 0x0055: LD_I_Vx(instruction); break;
                case 0x0065: LD_Vx_I(instruction); break;
                default: break;
            }
        default: printf("Unimplemented opcode %08" PRIx16 "\n", instruction); break;
    }

    // update timers
    if (_delay_timer > 0) {
        // execute 60 opcodes in a second
        --_delay_timer;
    }

    if (_sound_timer > 0) {
        // execute 60 opcodes in a second
        if (_sound_timer == 1) {
            std::cout << "Sound timer triggered!\n";
        }
        --_sound_timer;
    }
}

void CHIP_8::set_key(uint8_t key) {
    _key[key] = 1;
}

void CHIP_8::unset_key(uint8_t key) {
    _key[key] = 0;
}

bool CHIP_8::get_draw_flag() {
    return _drawFlag;
}

void CHIP_8::set_draw_flag(bool draw) {
    _drawFlag = draw;
}

Graphics CHIP_8::get_graphics() {
    return _graphics;
}

MMU CHIP_8::get_mmu() {
    return _mmu;
}

void CHIP_8::stack_push() {
    _stack[_sp] = _pc;
    ++_sp;
    _pc += 2;
}

void CHIP_8::stack_pop() {
    --_sp;
    _pc = _stack[_sp];
    _pc += 2;
}

void CHIP_8::CHIP_8::SYS_addr(uint16_t instruction) {
    _pc += 2;
}

void CHIP_8::CLS() {
    _drawFlag = true;
    _pc += 2;
}


void CHIP_8::RET() {
    stack_pop();
    _pc += 2;
}

void CHIP_8::JP_addr(uint16_t instruction) {
    _pc = (instruction & 0xFFF);
}

void CHIP_8::CALL_addr(uint16_t instruction) {
    stack_push();
    _pc = (instruction & 0xFFF);
}

void CHIP_8::SE_Vx_byte(uint16_t instruction) {
    if (_v[(instruction & 0x0F00) >> 8] == (instruction & 0xFF))
        _pc += 4;
    else
        _pc += 2;
}

void CHIP_8::SNE_Vx_byte(uint16_t instruction) { 
    if (_v[(instruction & 0x0F00) >> 8] != (instruction & 0xFF))
        _pc += 4;
    else
        _pc += 2;
}

void CHIP_8::SE_Vx_Vy(uint16_t instruction) {
    if (_v[(instruction & 0x0F00) >> 8] == _v[(instruction & 0x00F0) >> 4])
        _pc += 4;
    else
        _pc += 2;
}

void CHIP_8::LD_Vx_byte(uint16_t instruction) {
    _v[(instruction & 0x0F00) >> 8] = _v[instruction & 0x00FF];
    _pc += 2;
    
}

void CHIP_8::ADD_Vx_byte(uint16_t instruction) {
    _v[(instruction & 0x0F00) >> 8] = (_v[(instruction & 0x0F00) >> 8] + _v[instruction & 0xFF]) & 0xFF;
    _pc += 2;
}

void CHIP_8::LD_Vx_Vy(uint16_t instruction) {
    _v[(instruction & 0x0F00) >> 8] = _v[(instruction & 0x0F00) >> 4];
    _pc += 2;
}

void CHIP_8::OR_Vx_Vy(uint16_t instruction) {
    _v[(instruction & 0x0F00) >> 8] |= _v[(instruction & 0x0F00) >> 4];
    _pc += 2;
}

void CHIP_8::AND_Vx_Vy(uint16_t instruction) { 
    _v[(instruction & 0x0F00) >> 8] &= _v[(instruction & 0x0F00) >> 4];
    _pc += 2;
}

void CHIP_8::XOR_Vx_Vy(uint16_t instruction) { 
    _v[(instruction & 0x0F00) >> 8] ^= _v[(instruction & 0x0F00) >> 4];
    _pc += 2;
}

void CHIP_8::ADD_Vx_Vy(uint16_t instruction) {
    auto val = _v[(instruction & 0x0F00) >> 8] + _v[(instruction & 0x00F0) >> 4];
    _v[0xF] = 1 ? val > 0xFF : 0;
    _v[(instruction & 0x0F00) >> 8] = val & 0xFF;
    _pc += 2;
}

void CHIP_8::SUB_Vx_Vy(uint16_t instruction) {
    _v[0xF] = 1 ? _v[(instruction & 0x0F00) >> 8] > _v[(instruction & 0x00F0) >> 4] : 0;
   _v[(instruction & 0x0F00) >> 8] -= _v[(instruction & 0x0F00) >> 4];
   _pc += 2;
}

void CHIP_8::SHR_Vx_Vy(uint16_t instruction) { 
    _v[0xF] = _v[(instruction & 0x0F00) >> 8] & 0x1;
    _v[(instruction & 0x0F00) >> 8] >>= 1;
    _pc += 2;
}

void CHIP_8::SUBN_Vx_Vy(uint16_t instruction) {
    _v[0xF] = 1 ? _v[(instruction & 0x00F0) >> 4] > _v[(instruction & 0x0F00) >> 8] : 0;
    _v[(instruction & 0x0F00) >> 8] = _v[(instruction & 0x00F0) >> 4] - _v[(instruction & 0x0F00) >> 8];
    _pc += 2;
}

void CHIP_8::SHL_Vx(uint16_t instruction) {
    _v[0xF] = _v[(instruction & 0x0F00) >> 8] & 0x1;
    _v[(instruction & 0x0F00) >> 8] <<= 1;
    _pc += 2;
}

void CHIP_8::SNE_Vx_Vy(uint16_t instruction) {
    if (_v[(instruction & 0x0F00) >> 8] != _v[(instruction & 0x00F0) >> 4])
        _pc += 4;
    else
        _pc += 2;
    
}

void CHIP_8::LD_I_addr(uint16_t instruction) {
    _index = instruction & 0xFFF;
    _pc += 2;
    
}

void CHIP_8::JP_V0_addr(uint16_t instruction) {
    _pc = (instruction & 0xFFF) + _v[0];
}

void CHIP_8::RND_Vx_byte(uint16_t instruction) {
    _v[(instruction & 0x0F00) >> 8] = (rand() % 256) & (instruction & 0xFF);
    _pc += 2;
}

void CHIP_8::DRW_Vx_Vy_nibble(uint16_t instruction) {
    auto vx = (instruction & 0x0F00) >> 8;
    auto vy = (instruction & 0x00F0) >> 4;
    auto nibble = (instruction & 0x000F);
    
    uint8_t pixel;

    for (auto idx = _index; idx < _index + nibble; ++idx) {
        pixel = _mmu.read_byte(idx);
        // display at Vx, Vy coordinate
        for (auto xline = 0; xline < 8; ++xline) {
            if ((pixel & (0x80 >> xline)) != 0) {
                if (_graphics.collision(vx + xline, (vy + idx) * 64)) {
                    _v[0xF] = 1;
                }
                _graphics.load_buffer(vx + xline, (vy + idx) * 64);
            }
        }
    }
    _drawFlag = true;
    _pc += 2;
}

void CHIP_8::SKP_Vx(uint16_t instruction) {
    if ((_key[(instruction & 0x0F00)] >> 8) != 0)
        _pc += 4;
    else
        _pc += 2;
}
void CHIP_8::SKNP_Vx(uint16_t instruction) {
    if ((_key[(instruction & 0x0F00)] >> 8) == 0)
        _pc += 4;
    else
        _pc += 2;
}

void CHIP_8::LD_Vx_DT(uint16_t instruction) {
    _v[(instruction & 0x0F00) >> 8] = _delay_timer;
    _pc += 2;
}

void CHIP_8::LD_Vx_K(uint16_t instruction) {
    while (true) {
        for (auto i = 0; i < 16; ++i) {
            if (_key[i] != 0) {
                _v[(instruction & 0x0F00) >> 8] = i;
                _pc += 2;
                return;
            }
        }
    }
}

void CHIP_8::LD_DT_Vx(uint16_t instruction) {
    _delay_timer = _v[(instruction & 0x0F00) >> 8];
    _pc += 2;
}

void CHIP_8::LD_ST_Vx(uint16_t instruction) {
    _sound_timer = _v[(instruction & 0x0F00) >> 8];
    _pc += 2;
}

void CHIP_8::ADD_I_Vx(uint16_t instruction) {
    _index = (_index + _v[(instruction & 0x0F00) >> 8]) & 0xFF;
    _pc += 2;
}

void CHIP_8::LD_F_Vx(uint16_t instruction) {
    _index = _v[(instruction & 0x0F00) >> 8] * 0x5;
    _pc += 2;
}

void CHIP_8::LD_B_Vx(uint16_t instruction) {
    auto reg = (instruction & 0x0F00) >> 8;
    _mmu.write_byte(_index, _v[reg] / 100);
    _mmu.write_byte(_index + 1, (_v[reg] / 10) % 10);
    _mmu.write_byte(_index + 2, _v[reg] % 10);
    _pc += 2;
}

void CHIP_8::LD_I_Vx(uint16_t instruction) {
    auto reg = (instruction & 0x0F00) >> 8;
    auto idx = _index;
    for (auto i = 0; i < reg; ++i) {
        _mmu.write_byte(idx, _v[i]);
        ++idx;
    }
    _pc += 2;
}

void CHIP_8::LD_Vx_I(uint16_t instruction) {
    auto reg = (instruction & 0x0F00) >> 8;
    auto idx = _index;
    for (auto i = 0; i < reg; ++i) {
        _v[reg] = _mmu.read_byte(idx);
        ++idx;
    }
    _pc += 2;
}
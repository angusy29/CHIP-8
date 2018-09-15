#include "chip_8.h"

CHIP_8::CHIP_8() {
    memset(_v, 0, sizeof(_v));
}

void CHIP_8::emulate_cycle() {
    // fetch
    instruction = _mmu[_pc] << 8 | _mmu[_pc + 1];

    // decode

    // execute
}

int CHIP_8::CHIP_8::SYS_addr() {
    return 0;
}

int CHIP_8::CLS() {
    return 0;
}

int CHIP_8::RET() {
    _pc = _sp;
    _sp -= 1;
}

int CHIP_8::JP_addr(uint16_t instruction) { 
    _pc = (instruction & 0xFFF);
}

int CHIP_8::CALL_addr() { return 0; }

int CHIP_8::SE_Vx_byte(uint16_t instruction) {
    if (_v[(instruction & 0x0F00) >> 8] == (instruction & 0xFF)) 
        _pc += 2;
}

int CHIP_8::SNE_Vx_byte(uint16_t instruction) { 
    if (_v[(instruction & 0x0F00) >> 8] != (instruction & 0xFF))
        _pc += 2;

}

int CHIP_8::SE_Vx_Vy(uint16_t instruction) {
    if (_v[(instruction & 0x0F00) >> 8] == _v[(instruction & 0x00F0) >> 4])
        _pc += 2;
}

int CHIP_8::LD_Vx_byte(uint16_t instruction) {
    _v[(instruction & 0x0F00) >> 8] = _v[instruction & 0x00FF];
}

int CHIP_8::ADD_Vx_byte(uint16_t instruction) {
    _v[(instruction & 0x0F00) >> 8] = (_v[(instruction & 0x0F00) >> 8] + _v[instruction & 0xFF]) & 0xFF;
}

int CHIP_8::LD_Vx_Vy(uint16_t instruction) {
    _v[(instruction & 0x0F00) >> 8] = _v[(instruction & 0x0F00) >> 4];
}

int CHIP_8::OR_Vx_Vy(uint16_t instruction) {
    _v[(instruction & 0x0F00) >> 8] |= _v[(instruction & 0x0F00) >> 4];
}

int CHIP_8::AND_Vx_Vy(uint16_t instruction) { 
    _v[(instruction & 0x0F00) >> 8] &= _v[(instruction & 0x0F00) >> 4];
}

int CHIP_8::XOR_Vx_Vy(uint16_t instruction) { 
    _v[(instruction & 0x0F00) >> 8] ^= _v[(instruction & 0x0F00) >> 4]; 
}

int CHIP_8::ADD_Vx_Vy(uint16_t instruction) {
    auto val = _v[(instruction & 0x0F00) >> 8] + _v[(instruction & 0x0F00) >> 4];
    _VF = 1 ? val > 0xFF : 0;
    _v[(instruction & 0x0F00) >> 8] = val & 0xFF;
}

int CHIP_8::SUB_Vx_Vy(uint16_t instruction) {
    _VF = 1 ? _v[(instruction & 0x0F00) >> 8] > _v[(instruction & 0x0F00) >> 4] : 0;
   _v[(instruction & 0x0F00) >> 8] -= _v[(instruction & 0x0F00) >> 4];
}

int CHIP_8::SHR_Vx(uint16_t instruction) { 
    _VF = _v[(instruction & 0x0F00) >> 8] & 0x1;
    _v[(instruction & 0x0F00) >> 8] >>= 1;
}

int CHIP_8::SUBN_Vx_Vy(uint16_t instruction) {
    _VF = 1 ? _v[(instruction & 0x0F00) >> 4] > _v[(instruction & 0x0F00) >> 8] : 0;
    _v[(instruction & 0x0F00) >> 8] = _v[(instruction & 0x0F00) >> 4] - _v[(instruction & 0x0F00) >> 8];
}

int CHIP_8::SHL_Vx(uint16_t instruction) {
    _VF = _v[(instruction & 0x0F00) >> 8] & 0x1;
    _v[(instruction & 0x0F00) >> 8] <<= 1;
}

int CHIP_8::SNE_Vx_Vy(uint16_t instruction) {
    if (_v[(instruction & 0x0F00) >> 8] != _v[(instruction & 0x0F00) >> 4]) _pc += 2;
}

int CHIP_8::LD_I_addr(uint16_t instruction) {
    _index = instruction & 0xFFF;
}

int CHIP_8::JP_V0_addr(uint16_t instruction) { 
    _pc = (instruction & 0xFFF) + _v[0];
}

int CHIP_8::RND_Vx_byte(uint16_t instruction) {
    _v[(instruction & 0x0F00) >> 8] = (rand() % 256) & (instruction & 0xFF);
}

int CHIP_8::DRW_Vx_Vy_nibble() { return 0; }
int CHIP_8::SKP_Vx() { return 0; }
int CHIP_8::SKNP_Vx() { return 0; }
int CHIP_8::LD_Vx_DT() { return 0; }
int CHIP_8::LD_Vx_K() { return 0; }
int CHIP_8::LD_Vx_K() { return 0; }
int CHIP_8::LD_DT_Vx() { return 0; }
int CHIP_8::LD_ST_Vx() { return 0; }
int CHIP_8::ADD_I_Vx(uint16_t instruction) {
    _index = (_index + v[(instruction & 0x0F00) >> 8]) & 0xFF)    
}

int CHIP_8::LD_F_Vx() { return 0; }
int CHIP_8::LD_B_Vx() { return 0; }
int CHIP_8::LD_I_Vx() { return 0; }
int CHIP_8::LD_Vx_I() { return 0; }
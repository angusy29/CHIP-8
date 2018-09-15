#include "chip_8.h"

uint16_t CHIP_8::read_two_bytes(const uint16_t addr) {

}

int CHIP_8::CHIP_8::SYS() {

}

int CHIP_8::CLS() {
    return 0;
}

int CHIP_8::RET() { return 0; }
int CHIP_8::JP() { return 0; }
int CHIP_8::CALL() { return 0; }
int CHIP_8::SE_Vx_byte() { return 0; }
int CHIP_8::SNE_Vx_byte() { return 0; }
int CHIP_8::SE_Vx_Vy() { return 0; }
int CHIP_8::LD_Vx_byte() { return 0; }
int CHIP_8::ADD_Vx_byte() { return 0; }
int CHIP_8::LD_Vx_Vy() { return 0; }
int CHIP_8::OR_Vx_Vy() { return 0; }

int CHIP_8::AND(uint8_t &vx, uint8_t &vy) { 
    vx &= vy;
}

int CHIP_8::XOR(uint8_t &vx, uint8_t &vy) { 
    vx ^= vy; 
}

int CHIP_8::ADD_Vx_Vy() { return 0; }
int CHIP_8::SUB_Vx_Vy() { return 0; }
int CHIP_8::SHR_Vx_Vy() { return 0; }
int CHIP_8::SUBN_Vx_Vy() { return 0; }
int CHIP_8::SHL_Vx_Vy() { return 0; }
int CHIP_8::SNE_Vx_Vy() { return 0; }
int CHIP_8::LD_I_addr() { return 0; }
int CHIP_8::JP_V0_addr() { return 0; }
int CHIP_8::RND_Vx_byte() { return 0; }
int CHIP_8::DRW_Vx_Vy_nibble() { return 0; }
int CHIP_8::SKP_Vx() { return 0; }
int CHIP_8::SKNP_Vx() { return 0; }
int CHIP_8::LD_Vx_DT() { return 0; }
int CHIP_8::LD_Vx_K() { return 0; }
int CHIP_8::LD_Vx_K() { return 0; }
int CHIP_8::LD_DT_Vx() { return 0; }
int CHIP_8::LD_ST_Vx() { return 0; }
int CHIP_8::ADD_I_Vx() { return 0; }
int CHIP_8::LD_F_Vx() { return 0; }
int CHIP_8::LD_B_Vx() { return 0; }
int CHIP_8::LD_I_Vx() { return 0; }
int CHIP_8::LD_Vx_I() { return 0; }
#ifndef _CHIP_8_H_
#define _CHIP_8_H_

#include <iostream>
#include <stdint.h>

class CHIP_8 {
    private:
        uint8_t _V0;
        uint8_t _V1;
        uint8_t _V2;
        uint8_t _V3;
        uint8_t _V4;
        uint8_t _V5;
        uint8_t _V6;
        uint8_t _V7;
        uint8_t _V8;
        uint8_t _V9;
        uint8_t _VA;
        uint8_t _VB;
        uint8_t _VC;
        uint8_t _VD;
        uint8_t _VE;
        uint8_t _VF;            // should not be used by programs, as used as flag in instructions

        uint16_t _index;        // stores memory addresses so only rightmost 12 bits are used 0xFFF
        uint16_t _pc;           // 16 bit, store currently executing address

        uint8_t _sp;            // 8 bit stack pointer to topmost level of stack
    public:
        uint16_t read_two_bytes(const uint16_t addr);

        /***********/
        /* Opcodes */
        /***********/

        int SYS();
        int CLS();
        int RET();
        int JP();
        int CALL();
        int SE_Vx_byte();
        int SNE_Vx_byte();
        int SE_Vx_Vy();
        int LD_Vx_byte();
        int ADD_Vx_byte();
        int LD_Vx_Vy();
        int OR_Vx_Vy();
        int AND(uint8_t &vx, uint8_t &vy);
        int XOR(uint8_t &vx, uint8_t &vy);
        int ADD_Vx_Vy();
        int SUB_Vx_Vy();
        int SHR_Vx_Vy();
        int SUBN_Vx_Vy();
        int SHL_Vx_Vy();
        int SNE_Vx_Vy();
        int LD_I_addr();
        int JP_V0_addr();
        int RND_Vx_byte();
        int DRW_Vx_Vy_nibble();
        int SKP_Vx();
        int SKNP_Vx();
        int LD_Vx_DT();
        int LD_Vx_K();
        int LD_Vx_K();
        int LD_DT_Vx();
        int LD_ST_Vx();
        int ADD_I_Vx();
        int LD_F_Vx();
        int LD_B_Vx();
        int LD_I_Vx();
        int LD_Vx_I();
};

#endif /* _CHIP_8_H_ */
#ifndef _CHIP_8_H_
#define _CHIP_8_H_

#include <iostream>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <random>
#include <string.h>
#include "mmu.h"

class CHIP_8 {
    private:
        uint8_t _v[16];         // 16 gp registers

        uint16_t _index;        // stores memory addresses so only rightmost 12 bits are used 0xFFF
        uint16_t _pc;           // 16 bit, store currently executing address

        uint8_t _sp;            // 8 bit stack pointer to topmost level of stack
        uint8_t _stack[16];     // 16 levels of stack

        // timer registers that count at 60Hz
        // when set above zero, they will count down to zero
        uint8_t _delay_timer;
        uint8_t _sound_timer;

        uint8_t _key[16];    // hex based keypad 0x0 -0xF

        MMU _mmu;
    public:
        CHIP_8(MMU &mmu);
        void emulate_cycle();

        /********************/
        /* Stack operations */
        /********************/
        
        void stack_push();
        void stack_pop();

        /***********/
        /* Opcodes */
        /***********/

        int SYS_addr(uint16_t instruction);
        int CLS();
        int RET();
        int JP_addr(uint16_t instruction);
        int CALL_addr(uint16_t instruction);
        int SE_Vx_byte(uint16_t instruction);
        int SNE_Vx_byte(uint16_t instruction);
        int SE_Vx_Vy(uint16_t instruction);
        int LD_Vx_byte(uint16_t instruction);
        int ADD_Vx_byte(uint16_t instruction);
        int LD_Vx_Vy(uint16_t instruction);
        int OR_Vx_Vy(uint16_t instruction);
        int AND_Vx_Vy(uint16_t instruction);
        int XOR_Vx_Vy(uint16_t instruction);
        int ADD_Vx_Vy(uint16_t instruction);
        int SUB_Vx_Vy(uint16_t instruction);
        int SHR_Vx_Vy(uint16_t instruction);
        int SUBN_Vx_Vy(uint16_t instruction);
        int SHL_Vx(uint16_t instruction);
        int SNE_Vx_Vy(uint16_t instruction);
        int LD_I_addr(uint16_t instruction);
        int JP_V0_addr(uint16_t instruction);
        int RND_Vx_byte(uint16_t instruction);
        int DRW_Vx_Vy_nibble();
        int SKP_Vx();
        int SKNP_Vx();
        int LD_Vx_DT();
        int LD_Vx_K();
        int LD_DT_Vx();
        int LD_ST_Vx();
        int ADD_I_Vx(uint16_t instruction);
        int LD_F_Vx();
        int LD_B_Vx(uint16_t instruction);
        int LD_I_Vx(uint16_t instruction);
        int LD_Vx_I(uint16_t instruction);
};

#endif /* _CHIP_8_H_ */
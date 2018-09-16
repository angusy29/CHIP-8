#ifndef _CHIP_8_H_
#define _CHIP_8_H_

#include <array>
#include <iostream>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <random>
#include <string.h>
#include "mmu.h"
#include "graphics.h"

class CHIP_8 {
    private:
        uint8_t _v[16];         // 16 gp registers

        uint16_t _index;        // stores memory addresses so only rightmost 12 bits are used 0xFFF
        uint16_t _pc;           // 16 bit, store currently executing address

        uint8_t _sp;            // 8 bit stack pointer to topmost level of stack
        uint16_t _stack[16];     // 16 levels of stack

        std::array<int, 80> _fontset;

        // timer registers that count at 60Hz
        // when set above zero, they will count down to zero
        uint8_t _delay_timer;
        uint8_t _sound_timer;

        uint8_t _key[16];    // hex based keypad 0x0 -0xF
        bool _drawFlag;

        MMU _mmu;
        Graphics _graphics;
    public:
        CHIP_8(MMU &mmu, Graphics &graphics);
        void emulate_cycle();
        void set_key(uint8_t key);
        void unset_key(uint8_t key);
        bool get_draw_flag();
        void set_draw_flag(bool draw);
        Graphics get_graphics();
        MMU get_mmu();

        /********************/
        /* Stack operations */
        /********************/
        
        void stack_push();
        void stack_pop();

        /***********/
        /* Opcodes */
        /***********/

        void SYS_addr(uint16_t instruction);
        void CLS();
        void RET();
        void JP_addr(uint16_t instruction);
        void CALL_addr(uint16_t instruction);
        void SE_Vx_byte(uint16_t instruction);
        void SNE_Vx_byte(uint16_t instruction);
        void SE_Vx_Vy(uint16_t instruction);
        void LD_Vx_byte(uint16_t instruction);
        void ADD_Vx_byte(uint16_t instruction);
        void LD_Vx_Vy(uint16_t instruction);
        void OR_Vx_Vy(uint16_t instruction);
        void AND_Vx_Vy(uint16_t instruction);
        void XOR_Vx_Vy(uint16_t instruction);
        void ADD_Vx_Vy(uint16_t instruction);
        void SUB_Vx_Vy(uint16_t instruction);
        void SHR_Vx_Vy(uint16_t instruction);
        void SUBN_Vx_Vy(uint16_t instruction);
        void SHL_Vx(uint16_t instruction);
        void SNE_Vx_Vy(uint16_t instruction);
        void LD_I_addr(uint16_t instruction);
        void JP_V0_addr(uint16_t instruction);
        void RND_Vx_byte(uint16_t instruction);
        void DRW_Vx_Vy_nibble(uint16_t instruction);
        void SKP_Vx(uint16_t instruction);
        void SKNP_Vx(uint16_t instruction);
        void LD_Vx_DT(uint16_t instruction);
        void LD_Vx_K(uint16_t instruction);
        void LD_DT_Vx(uint16_t instruction);
        void LD_ST_Vx(uint16_t instruction);
        void ADD_I_Vx(uint16_t instruction);
        void LD_F_Vx(uint16_t instruction);
        void LD_B_Vx(uint16_t instruction);
        void LD_I_Vx(uint16_t instruction);
        void LD_Vx_I(uint16_t instruction);
};

#endif /* _CHIP_8_H_ */
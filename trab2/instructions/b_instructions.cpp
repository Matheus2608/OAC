// Tipo B   - Funct3
// beq   - 000
// bne   - 001
// bge   - 101
// bgeu  - 111
// blt   - 100
// bltu  - 110

// Opcode = 1100011

#include "b_instructions.hpp"


void beq(int32_t reg1, int32_t reg2, int32_t imm) {
    if (reg1 == reg2) {
        pc += imm;
    }
}

void bne(int32_t reg1, int32_t reg2, int32_t imm) {
    if (reg1 != reg2) {
        pc += imm;
    }
}

void bge(int32_t reg1, int32_t reg2, int32_t imm) {
    if (reg1 >= reg2) {
        pc += imm;
    }
}

void bgeu(int32_t reg1, int32_t reg2, int32_t imm) {
    if ((uint32_t) reg1 >= (uint32_t) reg2) {
        pc += imm;
    }
}

void blt(int32_t reg1, int32_t reg2, int32_t imm) {
    if (reg1 < reg2) {
        pc += imm;
    }
}

void bltu(int32_t reg1, int32_t reg2, int32_t imm) {
    if ((uint32_t) reg1 < (uint32_t) reg2) {
        pc += imm;
    }
}

unordered_map<uint32_t, function<void(int32_t, int32_t, int32_t)>> initialize_b_instruction_map() {
    unordered_map<uint32_t, function<void(int32_t, int32_t, int32_t)>> b_instruction_map;

    b_instruction_map[0b000] = beq;
    b_instruction_map[0b001] = bne;
    b_instruction_map[0b101] = bge;
    b_instruction_map[0b111] = bgeu;
    b_instruction_map[0b100] = blt;
    b_instruction_map[0b110] = bltu;

    return b_instruction_map;
}

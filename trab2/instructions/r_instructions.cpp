#include "r_instructions.hpp"

int32_t add(int32_t reg1, int32_t reg2) {
    return reg1 + reg2;
}

int32_t sub(int32_t reg1, int32_t reg2) {
    return reg1 - reg2;
}

int32_t _and(int32_t reg1, int32_t reg2) {
    return reg1 & reg2;
}

int32_t _or(int32_t reg1, int32_t reg2) {
    return reg1 | reg2;
}

int32_t _xor(int32_t reg1, int32_t reg2) {
    return reg1 ^ reg2;
}

int32_t slt(int32_t reg1, int32_t reg2) {
    return reg1 < reg2;
}

int32_t sltu(int32_t reg1, int32_t reg2) {
    uint8_t idx = 31;
    while(idx-- != 0) {
        int32_t bit_reg_1 = reg1 & 1 << idx;
        int32_t bit_reg_2 = reg2 & 1 << idx;
        if(bit_reg_1 != bit_reg_2) {
            return bit_reg_1 == 1 ? 0 : 1;
        }
    }

    return -1;
}

unordered_map<uint32_t, function<int32_t(int32_t, int32_t)>> initialize_r_instruction_map() {
    unordered_map<uint32_t, function<int32_t(int32_t, int32_t)>> r_instruction_map;

    r_instruction_map[0b0] = add;
    r_instruction_map[0b0100000000] = sub;
    r_instruction_map[0b0000000111] = _and;
    r_instruction_map[0b0000000110] = _or;
    r_instruction_map[0b0000000100] = _xor;
    r_instruction_map[0b0000000010] = slt;
    r_instruction_map[0b0000000011] = sltu;

    return r_instruction_map;
}

// Tipo R   - Funct3   - Funct7
// add      - 000      - 0000000
// sub      - 000      - 0100000
// and      - 111      - 0000000
// or       - 110      - 0000000
// slt      - 010      - 0000000
// sltu     - 011      - 0000000
// xor      - 100      - 0000000


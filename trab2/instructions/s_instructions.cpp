// Tipo S   - Opcode    -Funct3
// sb       - 0100011   000
// sw       - 0100011   010

#include "s_instructions.hpp"

void sb(int32_t rs1, int32_t rs2, int32_t imm) {
    uint8_t byte = rs2 & 0xFF;
    Memory::getInstance().sb(rs1, imm, byte);
}

void sw(int32_t rs1, int32_t rs2, int32_t imm) {
    Memory::getInstance().sw(rs1, imm, rs2);
}

unordered_map<uint32_t, function<void(int32_t, int32_t, int32_t)>> initialize_s_instruction_map() {
    unordered_map<uint32_t, function<void(int32_t, int32_t, int32_t)>> s_instruction_map;

    s_instruction_map[0b0000100011] = sb;
    s_instruction_map[0b0100100011] = sw;

    return s_instruction_map;
}

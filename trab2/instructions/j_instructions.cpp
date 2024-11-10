// Tipo J   - Opcode     - Funct3
// jal      - 1101111
// jalr     - 1100111     000

#include "j_instructions.hpp"

using namespace std;

void jal(int32_t idx_rd, int32_t idx_rs1, int32_t imm) {
    regs[rd] = pc + 4;
    pc += imm;
}

void jalr(int32_t idx_rd, int32_t idx_rs1, int32_t imm) {
    regs[rd] = pc + 4;
    pc = regs[rs1] + imm;
}

unordered_map<uint32_t, function<void(int32_t, int32_t, int32_t)>> initialize_j_instruction_map() {
    unordered_map<uint32_t, function<void(int32_t, int32_t, int32_t)>> j_instruction_map;

    j_instruction_map[0b1101111] = jal;
    j_instruction_map[0b1100111] = jalr;

    return j_instruction_map;
}

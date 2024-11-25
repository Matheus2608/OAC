// Tipo U   - Opcode
// lui      - 0110111
// auipc    - 0010111

#include "u_instructions.hpp"

uint32_t lui(int32_t imm) {
    // cout << "lui with imm = "; memory.printHex(imm); cout << endl;

    return imm << 12;

}

uint32_t auipc(int32_t imm) {
    // cout << "auipc with imm = "; memory.printHex(imm); cout << endl;

    return pc - 4 + (imm << 12);
}

unordered_map<uint32_t, function<int32_t(int32_t)>> initialize_u_instruction_map() {
    unordered_map<uint32_t, function<int32_t(int32_t)>> u_instruction_map;

    u_instruction_map[0b0110111] = lui;
    u_instruction_map[0b0010111] = auipc;

    return u_instruction_map;
}

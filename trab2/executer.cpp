#include "executer.hpp"

unordered_map<uint32_t, function<void(int32_t, int32_t, int32_t)>> b_instruction_map;
unordered_map<uint32_t, function<int32_t(int32_t, int32_t)>> i_instruction_map;
unordered_map<uint32_t, function<void(int32_t, int32_t, int32_t)>> j_instruction_map;
unordered_map<uint32_t, function<int32_t(int32_t, int32_t)>> r_instruction_map;
unordered_map<uint32_t, function<void(int32_t, int32_t, int32_t)>> s_instruction_map;
unordered_map<uint32_t, function<int32_t(int32_t)>> u_instruction_map;

void initialize_instruction_maps() {
    b_instruction_map = initialize_b_instruction_map();
    i_instruction_map = initialize_i_instruction_map();
    j_instruction_map = initialize_j_instruction_map();
    r_instruction_map = initialize_r_instruction_map();
    s_instruction_map = initialize_s_instruction_map();
    u_instruction_map = initialize_u_instruction_map();
}

uint32_t generate_U_hash() {
    return opcode;
}

uint32_t generate_R_hash() {
    return funct3 | (funct7 << 3);
}

uint32_t generate_J_hash() {
    return opcode;
}

uint32_t generate_S_hash() {
    return opcode | (funct3 << 7);
}

uint32_t generate_B_hash() {
    return funct3;
}

uint32_t generate_I_hash() {
    uint32_t hash = 0;
    hash |= opcode;
    hash |= funct3 << 7;
    hash |= funct7 << 10;
    return hash;
}

uint32_t generate_hash(char instruction) {
    switch(instruction) {
        case 'B':
            return generate_B_hash();
        case 'I':
            return generate_I_hash();
        case 'R':
            return generate_R_hash();
        case 'S':
            return generate_S_hash();
        case 'U':
            return generate_U_hash();
        case 'J':
            return generate_J_hash();
        default:
            return 0;
    }
}

void execute_instruction(char instruction_format, uint32_t hash) {
    cout << "hash: ";
    memory.printBinaryWord(hash); cout << endl;

    switch (instruction_format) {
    case 'I':
        regs[rd] = i_instruction_map[hash](regs[rs1], imm);
        break;

    case 'B':
        b_instruction_map[hash](regs[rs1], regs[rs2], imm);
        break;

    case 'R':
        regs[rd] = r_instruction_map[hash](regs[rs1], regs[rs2]);
        break;

    case 'S':
        s_instruction_map[hash](regs[rs1], imm, regs[rs2]);
        break;

    case 'U':
        regs[rd] = u_instruction_map[hash](imm);
        break;

    case 'J':
        j_instruction_map[hash](rd, rs1, imm);
        break;

    default:
        break;
    }
}

void execute(char instruction_format) {
    uint32_t hash = generate_hash(instruction_format);

    cout << "instruction format: " << instruction_format << endl;

    execute_instruction(instruction_format, hash);
}

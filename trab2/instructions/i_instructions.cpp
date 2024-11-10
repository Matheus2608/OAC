// Tipo I - Funct3  - Opcode     - Funct7
// addi    - 000   - 0010011
// andi    - 111   - 0010011
// ori     - 110   - 0010011
// srai    - 101   - 0010011        0100000
// slli    - 001   - 0010011        0000000
// srli    - 101   - 0010011        0000000
// lb      - 000   - 0000011
// lbu     - 100   - 0000011
// lw      - 010   - 0000011
// ecall   - 000   - 1110011

#include "i_instructions.hpp"

int32_t addi(int32_t rs1, int32_t imm) {
    cout << "addi with rs1 = " << rs1 << " and imm = " << imm << endl;
    return rs1 + imm;
}


int32_t andi(int32_t rs1, int32_t imm) {
    cout << "andi with rs1 = " << rs1 << " and imm = " << imm << endl;
    return rs1 & imm;
}

int32_t ori(int32_t rs1, int32_t imm) {
    cout << "ori with rs1 = " << rs1 << " and imm = " << imm << endl;
    return rs1 | imm;
}

int32_t srai(int32_t rs1, int32_t imm) {
    cout << "srai with rs1 = " << rs1 << " and imm = " << imm << endl;

    return rs1 >> imm;
}

int32_t slli(int32_t rs1, int32_t imm) {
    cout << "slli with rs1 = " << rs1 << " and imm = " << imm << endl;
    return rs1 << imm;
}

int32_t srli(int32_t rs1, int32_t imm) {
    cout << "srli with rs1 = " << rs1 << " and imm = " << imm << endl;
    uint8_t signal_bit = rs1 >> 31;
    rs1 = rs1 >> imm;
    if (signal_bit) {
        uint32_t mask = ((1 << (imm + 1)) -1)  << (32 - imm);
        rs1 = rs1 | mask;
    }
    return rs1 >> imm;
}


int32_t lb(int32_t rs1, int32_t imm) {
    cout << "lb with rs1 = " << rs1 << " and imm = " << imm << endl;

    regs[rd] = Memory::getInstance().lb(regs[rs1], imm);

    return 0;
}

int32_t lbu(int32_t rs1, int32_t imm) {
    cout << "lbu with rs1 = " << rs1 << " and imm = " << imm << endl;

    regs[rd] = Memory::getInstance().lbu(regs[rs1], imm);

    return 0;
}

int32_t lw(int32_t rs1, int32_t imm) {
    cout << "lw with rs1 = " << rs1 << " and imm = " << imm << endl;

    regs[rd] = Memory::getInstance().lw(regs[rs1], imm);

    return 0;
}

void printInt(int32_t num) {
    cout << num << endl;
}

void printString(int32_t address) {
    string str = "";
    uint32_t idx = 0;
    char c = Memory::getInstance().lb(address, idx);
    idx++;
    while (c != '\0') {
        str += c;
        c = Memory::getInstance().lb(address, idx);
        idx++;
    }

    cout << str << endl;
}

void exitProgram(int32_t code) {
    cout << "Program exited with code " << code << endl;
    exit(code);
}

int32_t ecall(int32_t rs1, int32_t imm) {
    int32_t reg_a1 = regs[10];
    int32_t reg_a7 = regs[17];

    switch(reg_a7) {
        case 1:
            printInt(reg_a1);
            break;
        case 4:
            printString(reg_a1);
            break;
        case 10:
            exitProgram(reg_a1);
            break;
        default:
            cout << "Invalid ecall code" << endl;
            break;
    }

    cout << "ecall" << endl;
    return 0;
}


unordered_map<uint32_t, function<int32_t(int32_t, int32_t)>> initialize_i_instruction_map() {
    unordered_map<uint32_t, function<int32_t(int32_t, int32_t)>> i_instruction_map;

    i_instruction_map[0b0000010011] = addi;
    i_instruction_map[0b1110010011] = andi;
    i_instruction_map[0b1100010011] = ori;
    i_instruction_map[0b0000000011] = lb;
    i_instruction_map[0b1000000011] = lbu;
    i_instruction_map[0b0100000011] = lw;
    i_instruction_map[0b0001110011] = ecall;
    i_instruction_map[0b01000001010010011] = srai;
    i_instruction_map[0b00000000010010011] = slli;
    i_instruction_map[0b00000001010010011] = srli;

    return i_instruction_map;
}

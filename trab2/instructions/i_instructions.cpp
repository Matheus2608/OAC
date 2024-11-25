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

void common_print(int32_t rs1, int32_t imm) {
    // cout <<  " with rs1 = "; memory.printHex(rs1); // cout << "and imm = "; memory.printHex(imm); // cout << endl;
}

int32_t addi(int32_t rs1, int32_t imm) {
    // cout << "addi"; common_print(rs1, imm);
    return rs1 + imm;
}


int32_t andi(int32_t rs1, int32_t imm) {
    // cout << "andi"; common_print(rs1, imm);
    return rs1 & imm;
}

int32_t ori(int32_t rs1, int32_t imm) {
    // cout << "ori"; common_print(rs1, imm);
    return rs1 | imm;
}

int32_t srai(int32_t rs1, int32_t imm) {
    // cout << "srai"; common_print(rs1, imm);

    return rs1 >> imm;
}

int32_t slli(int32_t rs1, int32_t imm) {
    // cout << "slli"; common_print(rs1, imm);
    return rs1 << imm;
}

int32_t srli(int32_t rs1, int32_t imm) {
    // cout << "srli"; common_print(rs1, imm);
    uint8_t signal_bit = rs1 >> 31;
    rs1 = rs1 >> imm;
    if (signal_bit) {
        uint32_t mask = ((1 << (imm + 1)) -1)  << (32 - imm);
        rs1 = rs1 | mask;
    }
    return rs1 >> imm;
}


int32_t lb(int32_t rs1, int32_t imm) {
    // cout << "lb"; common_print(rs1, imm);

    return Memory::getInstance().lb(rs1, imm);
}

int32_t lbu(int32_t rs1, int32_t imm) {
    // cout << "lbu"; common_print(rs1, imm);

    return Memory::getInstance().lbu(rs1, imm);
}

int32_t lw(int32_t rs1, int32_t imm) {
    // cout << "lw"; common_print(rs1, imm);

    return Memory::getInstance().lw(rs1, imm);
}

void printInt(int32_t num) {
    cout << num;
}

void printString(int32_t address) {
    // cout << "address = "; memory.printHex(address); // cout << endl;
    string str = "";
    uint32_t idx = 0;

    char c = (char) Memory::getInstance().lb(address, idx);
    idx++;
    while (c != '\0') {
        str += c;
        c = (char) Memory::getInstance().lb(address, idx);;
        idx++;
    }

    cout << str;
}

void exitProgram(void) {
    cout << endl << "Program exited with code " << 0 << endl;
    exit(0);
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
            exitProgram();
            break;
        default:
            // cout << "Invalid ecall code" << endl;
            break;
    }

    // cout << "ecall with a7 = " << reg_a7 << endl << endl;
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

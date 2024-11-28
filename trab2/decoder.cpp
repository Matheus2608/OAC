#include "decoder.hpp"

using namespace std;


// Função genérica para extensão de sinal
int32_t signExtend(int32_t immediate, int bits) {
    int32_t mask = 1 << (bits - 1); // Bit de sinal na posição correta
    return (immediate ^ mask) - mask; // Estende o sinal
}

void decode_s_format(uint32_t instruction) {
    funct3 = parse_bits(12, 14, instruction);
    rs1 = parse_bits(15, 19, instruction);
    rs2 = parse_bits(20, 24, instruction);
    imm = parse_bits(7, 11, instruction);
    imm |= parse_bits(25, 31, instruction) << 5;
    imm = signExtend(imm, 12);
}

void decode_u_format(uint32_t instruction) {
    rd = parse_bits(7, 11, instruction);
    imm = parse_bits(12, 31, instruction);
}

void decode_jalr(uint32_t instruction) {
    rd = parse_bits(7, 11, instruction);
    rs1 = parse_bits(15, 19, instruction);
    imm = parse_bits(20, 31, instruction);
    imm = signExtend(imm, 12);
}

void decode_jal(uint32_t instruction) {
    rd = parse_bits(7, 11, instruction);

    imm = (parse_bits(31, 31, instruction) << 20);  // Bit 20 (sinal)
    imm |= (parse_bits(21, 30, instruction) << 1);  // Bits 10:1
    imm |= (parse_bits(20, 20, instruction) << 11); // Bit 11
    imm |= (parse_bits(12, 19, instruction) << 12); // Bits 19:12
    imm = signExtend(imm, 21);
}

void decode_B_format(uint32_t instruction) {
    funct3 = parse_bits(12, 14, instruction);
    rs1 = parse_bits(15, 19, instruction);
    rs2 = parse_bits(20, 24, instruction);

    imm = (parse_bits(31, 31, instruction) << 12); // Bit de sinal (12)
    imm |= (parse_bits(25, 30, instruction) << 5); // Bits 10:5
    imm |= (parse_bits(11, 11, instruction) << 4); // Bit 4
    imm |= (parse_bits(8, 10, instruction) << 1);  // Bits 3:1
    imm |= (parse_bits(7, 7, instruction) << 11);  // Bit 11
}

void decode_shift_I_format(uint32_t instruction) {
    cout << "entrei no shift porra";
    rd = parse_bits(7, 11, instruction);
    funct3 = parse_bits(12, 14, instruction);
    rs1 = parse_bits(15, 19, instruction);
    imm = parse_bits(20, 24, instruction);
    funct7 = parse_bits(25, 31, instruction);

    // cout << "rd = "; memory.printBinaryWord(rd); cout << endl;
    // cout << "funct3 = "; memory.printBinaryWord(funct3); cout << endl;
    // cout << "rs1 = "; memory.printBinaryWord(rs1); cout << endl;
    // cout << "shamt = "; memory.printBinaryWord(shamt); cout << endl;
    // cout << "funct7 = "; memory.printBinaryWord(funct7); cout << endl;
}

void decode_I_format(uint32_t instruction) {
    rd = parse_bits(7, 11, instruction);
    funct3 = parse_bits(12, 14, instruction);
    rs1 = parse_bits(15, 19, instruction);
    imm = parse_bits(20, 31, instruction);
    imm = signExtend(imm, 12);
    funct7 = 0;

    // cout << "rd = "; memory.printBinaryWord(rd); cout << endl;
    // cout << "funct3 = "; memory.printBinaryWord(funct3); cout << endl;
    // cout << "rs1 = "; memory.printBinaryWord(rs1); cout << endl;
    // cout << "imm = "; memory.printBinaryWord(imm); cout << endl;
}

void decode_R_format(uint32_t instruction) {
    rd = parse_bits(7, 11, instruction);
    funct3 = parse_bits(12, 14, instruction);
    rs1 = parse_bits(15, 19, instruction);
    rs2 = parse_bits(20, 24, instruction);
    funct7 = parse_bits(25, 31, instruction);

    // cout << "rd: 0x" << hex << (uint32_t) rd << endl;
    // cout << "funct3: 0x" << hex << (uint32_t) funct3 << endl;
    // cout << "rs1: 0x" << hex << (uint32_t) rs1 << endl;
    // cout << "rs2: 0x" << hex << (uint32_t) rs2 << endl;
    // cout << "funct7: 0x" << hex << (uint32_t) funct7 << endl;
}

char decode(uint32_t instruction) {
    opcode = parse_bits(0, 6, instruction);
    // cout << "opcode = ";
    // memory.printBinaryWord(opcode);
    // cout << endl;

    switch (opcode) {
        // R format
        case 0b0110011:
            decode_R_format(instruction);
            return 'R';
            break;
        // I format
        // 0b0000011
        // 0b1110011
        case 0b0010011:
            funct3 = parse_bits(12, 14, instruction);
            if (funct3 == 0b001 || funct3 == 0b101) {
                decode_shift_I_format(instruction);
            } else {
                decode_I_format(instruction);
            }

            return 'I';

        case 0b0000011:
        // case 0b1100111:
        case 0b0001111:
            decode_I_format(instruction);
            return 'I';
        case 0b1110011: // ecall
            // mais rapido setar para 0 do que fazer bitmask
            rd = 0;
            funct3 = 0;
            rs1 = 0;
            imm = 0;
            return 'I';
        case 0b1100011: // B format
            decode_B_format(instruction);
            return 'B';
        case 0b1101111: // J format
            decode_jal(instruction);
            return 'J';
        case 0b1100111: // J format
            decode_jalr(instruction);
            return 'J';
        case 0b0110111:
        case 0b0010111: // U format
            decode_u_format(instruction);
            return 'U';

        case 0b0100011: // S format
            decode_s_format(instruction);
            return 'S';
        default:
            cout << "nao existe formato para a instrucao" << endl;
            break;
    }

    return 0;
}

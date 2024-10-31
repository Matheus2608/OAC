#include "riscv_reader.hpp"
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

const string code_file_name = "code.bin";
const string data_file_name = "data.bin";

uint32_t pc = 0x00000000;
uint32_t ri = 0x00000000; // registrador de instrucao
uint32_t sp = 0x00003ffc; 
uint32_t gp = 0x00001800;

// nao precisa de um hashmap porque 
// as instrucoes nao vao vir com string e sim com o numero
// do registrador
int32_t regs[32];

vector<uint8_t> readInstructions(string filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Failed to open file: " << filename << endl;
        return vector<uint8_t>();
    }

    uint8_t byte;
    vector<uint8_t> instructions;
    while (file.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        instructions.push_back(byte);
    }

    file.close();

    return instructions;
}

void printInstructions(vector<uint8_t> instructions) {
    for (size_t i = 0; i < instructions.size(); ++i) {
        cout << "Byte " << i << ": " << hex << static_cast<int>(instructions[i]) << endl;
    }
}

int main() {

    vector<uint8_t> instructions = readInstructions(code_file_name);
    vector<uint8_t> data = readInstructions(data_file_name);
    // printInstructions(instructions);
    // cout << "Byte 4 = "  << hex << static_cast<int>(data[4]) << endl;
    //printInstructions(data);
    regs[1] = 20;
    cout << "regs[1] = " << regs[1] << endl;
    
    return 0;
}


void decode(uint32_t instruction) {
    uint8_t opcode = instruction & 0x7F;
    
    switch (opcode) {
        case 0b0110011: // R format
           decode_R_format(instruction);
           break;

        default:
            break;

    }

}

void decode_R_format(uint32_t instruction) {
    uint8_t rd = (instruction >> 7) & 0x1F;
    uint8_t funct3 = (instruction >> 12) & 0x03;
    uint8_t rs1 = (instruction >> 15) & 0x1F;
    uint8_t rs2 = (instruction >> 20) & 0x1F;
    uint8_t funct7 = (instruction >> 25) & 0x7F;
       
}



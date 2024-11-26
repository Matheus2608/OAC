#include "riscv_reader.hpp"
#include "executer.hpp"
#include "decoder.hpp"
#include "memory.hpp"
#include <iostream>
#include <unordered_map>

#define FOR(i, start, end) for (int i = (start); i < (end); ++i)

using namespace std;



// variaveis globais
Memory& memory = Memory::getInstance();

uint32_t pc = 0x00000000;
uint32_t ri = 0x00000000; // registrador de instrucao
uint32_t sp = 0x00003ffc;
uint32_t gp = 0x00001800;

uint8_t opcode = 0x00;
uint8_t rd = 0x00;
uint8_t rs1 = 0x00;
uint8_t rs2 = 0x00;
uint8_t funct3 = 0x00;
uint8_t funct7 = 0x00;
uint8_t shamt = 0x00;
uint32_t imm = 0x0000;

int32_t regs[32];


void printRegs(void) {
    for (int i = 0; i < 32; i++) {
        //cout << "reg " << dec << i << " = ";
        memory.printHex(regs[i]);
    }
    //cout << endl;
}

// funcao auxiliar para extrair bits de uma instrucao
// muito útil
uint32_t parse_bits(uint8_t start, uint8_t end, uint32_t instruction) {
    uint32_t mask = ((1 << (end -start + 1)) -1)  << start;
    //cout << "instruction = " ;
    //memory.printBinaryWord(instruction); cout << endl;
    //cout << "mask = ";
    //memory.printBinaryWord(mask); cout << endl;
    return (instruction & mask) >> start;
}

void fetch() {
    ri = memory.lw(pc, 0);
    //cout << "instruction = ";
    //memory.printBinaryWord(ri);

    //cout << "instruction = 0x" << setfill('0') << setw(8) << hex << ri << endl;
    pc += 4;
}

void clearRegister0(void) {
    regs[0] = 0;
}

void step() {
    fetch();
    char instruction_format = decode(ri);
    execute(instruction_format);
    clearRegister0();
    // printRegs();
}


int main(int argc, char const *argv[]) {

    const string code_file_name = argv[1];
    const string data_file_name = argv[2];

    memory.readInstructions(code_file_name, data_file_name);
    initialize_instruction_maps();
    // for (int i = 0; i <= 25; i++) {
    //     step();
    // }

    while (true) step();

    // cout << "finished" << endl;
    // cout << memory.lw(0, 0x2024) << endl;

    // return 0;
}

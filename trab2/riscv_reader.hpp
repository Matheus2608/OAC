#ifndef RISCV_READER_HPP
#define RISCV_READER_HPP

#include <iostream>
#include <unordered_map>
#include <functional>
#include <cstdint>
#include "memory.hpp"
#include "instructions/b_instructions.hpp"
#include "instructions/i_instructions.hpp"
#include "instructions/j_instructions.hpp"
#include "instructions/r_instructions.hpp"
#include "instructions/s_instructions.hpp"
#include "instructions/u_instructions.hpp"
#include "decoder.hpp"

// constantes globais
extern const std::string code_file_name;
extern const std::string data_file_name;

// variaveis globais
extern Memory& memory;

extern uint32_t pc;
extern uint32_t ri; // registrador de instrucao
extern uint32_t sp;
extern uint32_t gp;

extern uint8_t opcode;
extern uint8_t rd;
extern uint8_t rs1;
extern uint8_t rs2;
extern uint8_t funct3;
extern uint8_t funct7;
extern uint8_t shamt;
extern uint32_t imm;

extern int32_t regs[32];

// funcao auxiliar para extrair bits de uma instrucao
uint32_t parse_bits(uint8_t start, uint8_t end, uint32_t instruction);

#endif // RISCV_READER_HPP

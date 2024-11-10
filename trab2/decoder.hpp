#ifndef DECODER_HPP
#define DECODER_HPP

#include <cstdint>
#include <iostream>
#include "riscv_reader.hpp"
#include "memory.hpp"


// Declaração das variáveis globais
extern uint8_t opcode;
extern uint8_t rd;
extern uint8_t rs1;
extern uint8_t rs2;
extern uint8_t funct3;
extern uint8_t funct7;
extern uint8_t shamt;
extern uint32_t imm;

// Declaração das funções
char decode(uint32_t instruction);

#endif // DECODER_HPP

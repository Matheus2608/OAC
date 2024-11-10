#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip> // Para std::hex, std::setw, e std::setfill

using namespace std;

#define MEM_SIZE 16384

class Memory {
public:
    // Método estático para acessar a instância única
    static Memory& getInstance() {
        static Memory instance; // Instância única
        return instance;
    }

    void readInstructions(std::string code_filename, std::string data_filename);
    void printBytes(uint16_t start, uint16_t end);
    void printWord(uint32_t address);
    void printBinaryWord(uint32_t word);
    string returnBit(uint32_t byte, uint32_t position);
    void show_result_or_error(int32_t result);
    int32_t lb(uint8_t reg, int32_t kte);
    int32_t lbu(uint8_t reg, int32_t kte);
    int32_t lw(uint8_t reg, int32_t kte);
    void sb(uint8_t reg, int32_t kte, int8_t byte);
    void sw(uint8_t reg, int32_t kte, int32_t word);

private:
    Memory() = default; // Construtor privado
    Memory(const Memory&) = delete; // Evita cópia
    Memory& operator=(const Memory&) = delete; // Evita atribuição

    uint8_t mem[MEM_SIZE] = {0}; // Memória
};

#endif // MEMORY_HPP

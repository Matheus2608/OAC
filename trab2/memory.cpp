#include "memory.hpp"

Memory::Memory() : mem(MEM_SIZE) {}

int32_t Memory::lb(uint8_t reg, int32_t kte) {
    int8_t byte = mem[reg + kte];
    bool positive = (byte & (1 << 7)) == 0;

    if (positive)
        return 0x000000FF & byte;
    return 0xFFFFFF00 | byte;
}

int32_t Memory::lbu(uint8_t reg, int32_t kte) {
    int8_t byte = mem[reg + kte];
    return 0x000000FF & byte;
}

int32_t Memory::lw(uint8_t reg, int32_t kte) {
    uint32_t idx = reg + kte;
    int8_t byte1 = mem[idx];
    int8_t byte2 = mem[idx + 1];
    int8_t byte3 = mem[idx + 2];
    int8_t byte4 = mem[idx + 3];

    return ((uint8_t)byte4 << 24) | ((uint8_t)byte3 << 16) | ((uint8_t)byte2 << 8) | (uint8_t)byte1;
}

void Memory::sb(uint8_t reg, int32_t kte, int8_t byte) {
    mem[reg + kte] = byte;
}

void Memory::sw(uint8_t reg, int32_t kte, int32_t word) {
    uint32_t idx = reg + kte;
    int8_t byte1 = word & 0xFF;
    int8_t byte2 = (word >> 8) & 0xFF;
    int8_t byte3 = (word >> 16) & 0xFF;
    int8_t byte4 = (word >> 24) & 0xFF;

    mem[idx] = byte1;
    mem[idx + 1] = byte2;
    mem[idx + 2] = byte3;
    mem[idx + 3] = byte4;
}

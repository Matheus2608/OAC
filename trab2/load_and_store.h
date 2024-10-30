#ifndef LOAD_STORE_HEADER
#define LOAD_STORE_HEADER

#include <stdint.h>

#define MEM_SIZE 16384
extern int8_t mem[MEM_SIZE];

int32_t lb(uint8_t reg, int32_t kte);
int32_t lbu(uint8_t reg, int32_t kte);
int32_t lw(uint8_t reg, int32_t kte);
void sb(uint8_t reg, int32_t kte, int8_t byte);
void sw(uint8_t reg, int32_t kte, int32_t word);

#endif

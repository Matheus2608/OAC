#include "load_and_store.h"
#include <stdio.h>

#define MEM_SIZE 16384
int8_t mem[MEM_SIZE];

// lê um byte da memória e o converte para um inteiro de 32 bits estendendo o sinal do byte. 
// Retorna o inteiro de	32 bits.

int32_t lb(uint8_t reg, int32_t kte) {
	int8_t byte = mem[reg + kte];
	//printf("byte = %d\n", byte);
	
	int8_t positive = (byte & (1 << 8)) == 0;
	//printf("positive = %d\n", positive);

	if (positive) 
		return 0x000000FF & byte;  
	return 0xFFFFFF00 | byte;
}

// lê um byte da memória e o converte para um inteiro de 32 bits sem sinal (valor positivo).
// Retorna o inteiro de 32 bits.

int32_t lbu(uint8_t reg, int32_t kte) {
	int8_t byte = mem[reg + kte];
	return 0x000000FF & byte;
}

// lê uma palavra de 32 bits da memória e retorna o seu valor.

int32_t lw(uint8_t reg, int32_t kte) {
	uint32_t idx = reg + kte;
	int8_t byte1 = mem[idx];
	//printf("byte1 = 0x%x\n", (uint8_t)byte1);
	int8_t byte2 = mem[idx+1];
	//printf("byte2 = 0x%x\n", (uint8_t)byte2);
	int8_t byte3 = mem[idx+2];
	//printf("byte3 = 0x%x\n", (uint8_t)byte3);
	int8_t byte4 = mem[idx+3];
	//printf("byte4 = 0x%x\n", (uint8_t)byte4);

	return ((uint8_t)byte4 << 24) | ((uint8_t)byte3 << 16) | ((uint8_t)byte2 << 8) | (uint8_t)byte1;
}

// escreve o byte passado como parâmetro na memória.

void sb(uint8_t reg, int32_t kte, int8_t byte) {
	mem[reg + kte] = byte;
}

// escreve os 4	bytes de word na memória, colocando o menos significativo no endereço especificado 
// e os	outros nos endereços de	byte seguintes.

void sw(uint8_t reg, int32_t kte, int32_t word) {
	uint32_t idx = reg + kte;
	int8_t byte1 = word & 0xFF;
	//printf("byte1 = 0x%x\n", (uint8_t)byte1);
	int8_t byte2 = (word >> 8) & 0xFF;
	//printf("byte2 = 0x%x\n", (uint8_t)byte2);	
	int8_t byte3 = (word >>	16)	& 0xFF;
	//printf("byte3 = 0x%x\n", (uint8_t)byte3);
	int8_t byte4 = (word >>	24)	& 0xFF;
	//printf("byte4 = 0x%x\n", (uint8_t)byte4);

	mem[idx] = byte1;
	mem[idx+1] = byte2;
	mem[idx+2] = byte3;
	mem[idx+3] = byte4;
} 

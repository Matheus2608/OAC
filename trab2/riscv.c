#include <stdio.h>
#include <stdint.h>
#include <errno.h>

#define MEM_SIZE 16384
int8_t mem[MEM_SIZE];

// se nao houver erro, imprime o resultado
// caso contrario imprime a mensagem de erro

void show_result_or_error(int32_t result) {
	if (errno == EINVAL) {
        printf("Error: Invalid memory access\n");
    } else {
        printf("0x%x\n", result);
    }
	errno = 0; // Reset errno para que nao seja impresso erro na proxima chamada
}

// lê um byte da memória e o converte para um inteiro de 32 bits estendendo o sinal do byte.
// Retorna o inteiro de	32 bits.

int32_t lb(uint8_t reg, int32_t kte) {
	if (reg + kte >= MEM_SIZE) {
        errno = EINVAL; // Invalid argument
        return;
    }

	int8_t byte = mem[reg + kte];
	int8_t positive = (byte & (1 << 7)) == 0;

	if (positive)
		return 0x000000FF & byte;
	return 0xFFFFFF00 | byte;
}

// lê um byte da memória e o converte para um inteiro de 32 bits sem sinal (valor positivo).
// Retorna o inteiro de 32 bits.

int32_t lbu(uint8_t reg, int32_t kte) {
	if (reg + kte >= MEM_SIZE) {
        errno = EINVAL; // Invalid argument
        return;
    }

	int8_t byte = mem[reg + kte];
	return 0x000000FF & byte;
}

// lê uma palavra de 32 bits da memória e retorna o seu valor.

int32_t lw(uint8_t reg, int32_t kte) {
	if (reg + kte + 3 >= MEM_SIZE || (reg + kte) % 4 != 0) {
        errno = EINVAL; // Invalid argument
        return;
    }

	uint32_t idx = reg + kte;
	int8_t byte1 = mem[idx];
	int8_t byte2 = mem[idx+1];
	int8_t byte3 = mem[idx+2];
	int8_t byte4 = mem[idx+3];

	return ((uint8_t)byte4 << 24) | ((uint8_t)byte3 << 16) | ((uint8_t)byte2 << 8) | (uint8_t)byte1;
}

// escreve o byte passado como parâmetro na memória.

void sb(uint8_t reg, int32_t kte, int8_t byte) {
	if (reg + kte >= MEM_SIZE) {
        errno = EINVAL; // Invalid argument
        return;
    }

	mem[reg + kte] = byte;
}

// escreve os 4	bytes de word na memória, colocando o menos significativo no endereço especificado
// e os	outros nos endereços de	byte seguintes.

void sw(uint8_t reg, int32_t kte, int32_t word) {
	if (reg + kte + 3 >= MEM_SIZE || (reg + kte) % 4 != 0) {
        errno = EINVAL; // Invalid argument
        return;
    }

	uint32_t idx = reg + kte;
	int8_t byte1 = word & 0xFF;
	int8_t byte2 = (word >> 8) & 0xFF;
	int8_t byte3 = (word >>	16)	& 0xFF;
	int8_t byte4 = (word >>	24)	& 0xFF;

	mem[idx] = byte1;
	mem[idx+1] = byte2;
	mem[idx+2] = byte3;
	mem[idx+3] = byte4;
}

int main() {
    sw(0,0,0xABACADEF);
	sb(4,0,1);
	sb(4,1,2);
	sb(4,2,3);
	sb(4,3,4);

	show_result_or_error(lw(0,0));
	show_result_or_error(lb(0,0));
	show_result_or_error(lb(0,1));
	show_result_or_error(lb(0,2));
	show_result_or_error(lb(0,3));
	show_result_or_error(lbu(0,0));
	show_result_or_error(lbu(0,1));
	show_result_or_error(lbu(0,2));
	show_result_or_error(lbu(0,3));
}


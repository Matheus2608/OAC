#include "memory.hpp"

using namespace std;

void Memory::readInstructions(string code_filename, string data_filename) {
    ifstream code_file(code_filename, ios::binary | ios::ate);
    if (!code_file) {
        cerr << "Failed to open file: " << code_filename << endl;
        std::exit(EXIT_FAILURE);
    }

    ifstream data_file(data_filename, ios::binary | ios::ate);
    if (!data_file) {
        cerr << "Failed to open file: " << data_filename << endl;
        std::exit(EXIT_FAILURE);
    }

    streamsize code_size = code_file.tellg();
    streamsize data_size = data_file.tellg();

    //cout << "Code size: " << code_size << " bytes" << endl;
    //cout << "Data size: " << data_size << " bytes" << endl << endl;

    if (code_size > 0x2000 || data_size > (MEM_SIZE - 0x2000)) {
        cerr << "Error: Code or data size exceeds memory limits" << endl;
        std::exit(EXIT_FAILURE);
    }

    code_file.seekg(0, ios::beg);
    if (!code_file.read(reinterpret_cast<char*>(mem), code_size)) {
        cerr << "Error: Failed to read file: " << code_filename << endl;
        std::exit(EXIT_FAILURE);
    }

    data_file.seekg(0, ios::beg);
    if (!data_file.read(reinterpret_cast<char*>(mem + 0x2000), data_size)) {
        cerr << "Error: Failed to read file: " << data_filename << endl;
        std::exit(EXIT_FAILURE);
    }

    code_file.close();
    data_file.close();
}

void Memory::printBytes(uint16_t start, uint16_t end) {
    for (uint16_t idx = start; idx < end; idx++) {
        cout << "byte " << idx << " = 0x" << hex << setw(2) << setfill('0') << lbu(0, idx) << endl;
    }
}

void Memory::printWord(uint32_t byte) {
    cout << "0x" << hex << setw(2) << setfill('0') << byte << endl;
}

void Memory::printBinaryWord(uint32_t byte) {
    cout << "0b";

    for (int16_t idx = 31; idx >= 0; idx--) {
        cout << returnBit(byte, idx);
    }

    cout << endl;
}

string Memory::returnBit(uint32_t byte, uint32_t position) {
    uint32_t mask = 1 << position;
    uint32_t isSet = (byte & mask);

    return (isSet ? "1" : "0");
}

void Memory::show_result_or_error(int32_t result) {
    if (errno == EINVAL) {
        cerr << "Error: Invalid memory access" << endl;
    } else {
        cout << "0x" << hex << result << endl;
    }
    errno = 0; // Reset errno para que nao seja impresso erro na proxima chamada
}

int32_t Memory::lb(uint32_t reg, int32_t kte) {
    if (reg + kte >= MEM_SIZE) {
        errno = EINVAL; // Invalid argument
        return 0;
    }

    int8_t byte = mem[reg + kte];

    bool positive = (byte & (1 << 7)) == 0;
    // cout << "endereco = " ;printHex(reg + kte);
    if (positive)
        return 0x000000FF & byte;
    return 0xFFFFFF00 | byte;
}

int32_t Memory::lbu(uint32_t reg, int32_t kte) {
    if (reg + kte >= MEM_SIZE) {
        errno = EINVAL; // Invalid argument
        return 0;
    }

    int8_t byte = mem[reg + kte];
    return 0x000000FF & byte;
}

int32_t Memory::lw(uint32_t reg, int32_t kte) {
    if (reg + kte + 3 >= MEM_SIZE || (reg + kte) % 4 != 0) {
        errno = EINVAL; // Invalid argument
        return 0;
    }

    uint32_t idx = reg + kte;
    int8_t byte1 = mem[idx];
    //cout << "byte1 = 0x" << (uint32_t) byte1 << endl;
    int8_t byte2 = mem[idx + 1];
    //cout << "byte2 = 0x" << hex << (uint32_t) byte2 << endl;
    int8_t byte3 = mem[idx + 2];
    //cout << "byte3 = 0x" << hex << (uint32_t) byte3 << endl;
    int8_t byte4 = mem[idx + 3];
    //cout << "byte4 = 0x" << hex << (uint32_t) byte4 << endl;

    return ((uint8_t)byte4 << 24) | ((uint8_t)byte3 << 16) | ((uint8_t)byte2 << 8) | (uint8_t)byte1;
}

void Memory::sb(uint32_t reg, int32_t kte, int8_t byte) {
    if (reg + kte >= MEM_SIZE) {
        errno = EINVAL; // Invalid argument
        return;
    }

    mem[reg + kte] = byte;
}

void Memory::sw(uint32_t reg, int32_t kte, int32_t word) {
    if (reg + kte + 3 >= MEM_SIZE || (reg + kte) % 4 != 0) {
        errno = EINVAL; // Invalid argument
        return;
    }

    uint32_t idx = reg + kte;
    mem[idx] = word & 0xFF;
    mem[idx + 1] = (word >> 8) & 0xFF;
    mem[idx + 2] = (word >> 16) & 0xFF;
    mem[idx + 3] = (word >> 24) & 0xFF;
}

void Memory::printHex(int32_t num) {
    cout << "0x" << setfill('0') << setw(8) << hex << num << endl;
}
